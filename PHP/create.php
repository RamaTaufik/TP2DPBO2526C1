<?php
include "CatFood.php";

session_start();

$e_msg = ""; // Pesan error yang tampil jika ada error
$e_idx = -1;  // Indeks input ke-berapa yang mengalami error

// Form penambahan data sekaligus kode menambahkan data ke session dibuat dalam satu file yang sama disini. Untuk
// membedakan proses penambahan data dan menambahkan data ke session, proses menambahkan data ke session menggunakan
// metode POST
if($_SERVER['REQUEST_METHOD'] === 'POST') {
  if(!isset($_SESSION["cat_foods"])) {
    // Inisiasi session
    $_SESSION["cat_foods"] = [];
  }

  // Validasi input 'SKU'
  $sku = $_POST["sku"];
  if($sku === "") {
    $e_msg = "SKU tidak boleh kosong!";
    $e_idx = 0;
  } else if(!empty(array_filter($_SESSION["cat_foods"], fn($cat_food) => $cat_food->getSKU() === $sku))) {
    $e_msg = "SKU '".$sku."' sudah ada!";
    $e_idx = 0;
  }

  // Validasi input 'Nama produk'
  $name = $_POST["name"];
  if($e_idx === -1 && $name === "") {
    $e_msg = "Nama tidak boleh kosong!";
    $e_idx = 1;
  }

  // Input 'Rasa' dan 'Tanggal kadaluarsa' memerlukan minim validasi
  $flavor = $_POST["flavor"];
  $expiry = $_POST["expiry"] === ""? "0001-01-01": $_POST["expiry"];
  // Validasi input 'Makanan basah', 'Makanan obat', dan 'Makanan khusus anak kucing'
  $is_wet = isset($_POST["is_wet"])? true: false;
  $is_prescription_diet = isset($_POST["is_prescription_diet"])? true: false;
  $is_for_kitten = isset($_POST["is_for_kitten"])? true: false;

  // Validasi input 'Harga'
  $price = $_POST["price"];
  if($e_idx === -1) {
    if($price !== "" && !ctype_digit($price)) {
      $e_msg = "Harga produk harus berupa bilangan bulat positif!";
      $e_idx = 4;
    } else if($price === "") {
      $price = 0;
    } else {
      $price = (int)$price;
    }
  }
  
  // Validasi input 'Berat'
  $weight = $_POST["weight"];
  if($e_idx === -1) {
    if($weight !== "" && !ctype_digit($weight)) {
      $e_msg = "Berat produk harus berupa bilangan bulat positif!";
      $e_idx = 5;
    } else if($weight === "") {
      $weight = 0;
    } else {
      $weight = (int)$weight;
    }
  }

  if($e_idx === -1) {
    $img_url = "-";

    // Proses memasukkan file ke direktori lokal /images
    if(isset($_FILES['img']) && $_FILES['img']['error'] === UPLOAD_ERR_OK) {
      $img = $_FILES['img'];
      // Nama gambar di-format sebagai pd_[sku].[extensi file]
      $file_name = 'pd_'.$sku.'.'.strtolower(pathinfo($img['name'], PATHINFO_EXTENSION));
      $target_dir = __DIR__.'/images/';

      // Memastikan direktori /images benar-benar ada, dan jika tidak, buat dulu
      if(!is_dir($target_dir)) {
        mkdir($target_dir, 0755, true);
      }

      $target_path = $target_dir.$file_name;

      if(move_uploaded_file($img['tmp_name'], $target_path)) {
        $img_url = $file_name;
      }
    }
    
    // Masukkan data baru ke session
    $_SESSION["cat_foods"][] = new CatFood($sku, $name, $flavor, $price, $img_url, $expiry, $weight, $is_wet, $is_prescription_diet, $is_for_kitten);

    // Redirect ke Main.php
    header("Location: Main.php");
    exit;
  }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>FURRY FRIENDS DATA CENTER - Tambah data</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <main>
    <div class="form-container">
      <img src="images/logo-create.png" alt="Tambah Data Baru" class="logo">
      <form method="POST" enctype="multipart/form-data">
        <a href="Main.php" class="button-back">&larr; Kembali</a>
        <div class="input-group">
          <label for="sku">SKU<span class="text-danger">*</span></label>
          <input type="text" name="sku" id="sku" class="<?= $e_idx == 0? "error": "" ?>" value="<?= isset($sku)? $sku :"" ?>" required>
        </div>
        <div class="input-group">
          <label for="name">Nama/Merk Produk<span class="text-danger">*</span></label>
          <input type="text" name="name" id="name" class="<?= $e_idx == 1? "error": "" ?>" value="<?= isset($name)? $name :"" ?>" required>
        </div>
        <div class="input-group">
          <label for="flavor">Rasa</label>
          <input type="text" name="flavor" id="flavor" class="<?= $e_idx == 2? "error": "" ?>" value="<?= isset($flavor)? $flavor :"" ?>">
        </div>
        <div class="input-group">
          <label for="price">Harga</label>
          <input type="number" name="price" id="price" class="<?= $e_idx == 3? "error": "" ?>" min="0" value="<?= isset($price)? $price :"" ?>">
        </div>
        <div class="input-group">
          <label for="expiry">Tanggal Kadaluarsa</label>
          <input type="date" name="expiry" id="expiry" class="<?= $e_idx == 4? "error": "" ?>" value="<?= isset($expiry) && $expiry !== "0001-01-01"? $expiry :"" ?>">
        </div>
        <div class="input-group">
          <label for="weight">Berat (gram)</label>
          <input type="number" name="weight" id="weight" class="<?= $e_idx == 5? "error": "" ?>" min="0" value="<?= isset($weight)? $weight :"" ?>">
        </div>
        <div class="checkbox-group">
          <div class="input-group">
            <input type="checkbox" name="is_wet" id="is_wet" class="<?= $e_idx == 6? "error": "" ?>" <?= isset($is_wet) && $is_wet? "checked" :"" ?>>
            <label for="is_wet" class="checkbox-label">Makanan basah</label>
          </div>
          <div class="input-group">
            <input type="checkbox" name="is_prescription_diet" id="is_prescription_diet" class="<?= $e_idx == 7? "error": "" ?>" <?= isset($is_prescription_diet) && $is_prescription_diet? "checked" :"" ?>>
            <label for="is_prescription_diet" class="checkbox-label">Butuh resep</label>
          </div>
          <div class="input-group">
            <input type="checkbox" name="is_for_kitten" id="is_for_kitten" class="<?= $e_idx == 8? "error": "" ?>" <?= isset($is_for_kitten) && $is_for_kitten? "checked" :"" ?>>
            <label for="is_for_kitten" class="checkbox-label">Khusus anak kucing</label>
          </div>
        </div>
        <div class="input-group">
          <label for="img">Gambar Produk</label>
          <input type="file" name="img" id="img" accept="image/*" class="<?= $e_idx == 9? "error": "" ?>">
        </div>
        <?= $e_msg != ""? "<p class=\"text-danger text-end\">".$e_msg."</p>": "" ?>
        <button type="submit" class="button button-submit">TAMBAH</button>
      </form>
    </div>
  </main>
</body>
</html>