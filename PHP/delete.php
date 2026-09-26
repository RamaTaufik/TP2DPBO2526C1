<?php
include "CatFood.php";

session_start();

// Pastikan data session ada dan SKU dikirim lewat metode POST
if(isset($_SESSION["cat_foods"]) && isset($_POST["sku"])) {
  $sku = $_POST["sku"]; // Secara default data selalu dikirim dalam bentuk string, sehingga ubah lagi ke integer
  $img = NULL;

  // Cari record yang ingin dihapus berdasarkan SKU-nya
  foreach($_SESSION["cat_foods"] as $cat_food) {
    if($cat_food->getSKU() === $sku) {
      $img = $cat_food->getImgUrl();
      break;
    }
  }

  // Hapus terlebih dahulu gambar record tersebut di direktori lokal jika ada
  if($img !== NULL && $img !== "-") {
    $file_path = __DIR__ . '/images/'.$img;

    if(file_exists($file_path)) {
      unlink($file_path);
    }
  }

  // Baru hilangkan record
  $_SESSION["cat_foods"] = array_filter($_SESSION["cat_foods"], fn($cat_food) => $cat_food->getSKU() !== $sku);
}

// Redirect kembali ke Main.php
header("Location: Main.php");
exit;