<?php

if($_SERVER["REQUEST_METHOD"] == "POST"){
    $uploadDir = "uploads/";
    $uploadFile = $uploadDir . basename($_FILES["archiveWWW"]["name"]);

    if(move_uploaded_file($_FILES["archiveWWW"]["tmp_name"], $uploadFile)){
        echo "Envoi réussi";
    }
}

?>