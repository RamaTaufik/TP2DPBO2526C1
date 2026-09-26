<?php
include "CatFood.php";

session_start();

// Serupa dengan kode di Delete.php, hanya saja disini proses berhenti pada penghapusan gambar, lalu langsung
// redirect kembali ke Main.php
if(isset($_SESSION["cat_foods"]) && isset($_POST["sku"])) {
  $sku = $_POST["sku"];
  $img = NULL;

  foreach($_SESSION["cat_foods"] as $idx => $cat_food) {
    if($cat_food->getSKU() === $sku) {
      $img = $cat_food->getImgUrl();
      $_SESSION["cat_foods"][$idx]->setImgUrl("-");
      break;
    }
  }

  if($img !== NULL && $img !== "-") {
    $file_path = __DIR__ . '/images/'.$img;

    if(file_exists($file_path)) {
      unlink($file_path);
    }
  }
}

header("Location: Main.php");
exit;