<?php
include "CatFood.php";

session_start();

// Jika laman ini dicoba untuk diakses tanpa mengirim parameter SKU lewat metode GET, langsung 'lempar' balik ke laman
// Main.php
if(!isset($_GET["sku"])) {
  header("Location: Main.php");
  exit;
}

$old_sku = $_GET["sku"];
$cat_food = NULL;
$e_msg = "";
$e_idx = -1;

// Pastikan session sudah ada, dan jika sudah ada, maka cari data dari record dengan SKU yang dikirim
if(!isset($_SESSION["cat_foods"])) {
  $_SESSION["cat_foods"] = [];
} else {
  foreach($_SESSION["cat_foods"] as $c) {
    if($c->getSKU() === $old_sku) {
      $cat_food = $c;
      break;
    }
  }
}

// Sama seperti laman Create.php, proses pengubahan data dan merubah data di session dilakukan dalam laman yang sama,
// dibedakan dengan metode. Validasi pun kurang lebih serupa dengan yang ada di laman Create.php
if($_SERVER['REQUEST_METHOD'] === 'POST') {
  $sku = $_POST["sku"];
  if($sku === "") {
    $e_msg = "SKU tidak boleh kosong!";
    $e_idx = 0;
  } else if(!empty(array_filter($_SESSION["cat_foods"], fn($cat_food) => $cat_food->getSKU() === $sku)) && $sku !== $old_sku) {
    $e_msg = "SKU '".$sku."' sudah ada!";
    $e_idx = 0;
  }

  $name = $_POST["name"];
  if($e_idx === -1 && $name === "") {
    $e_msg = "Nama tidak boleh kosong!";
    $e_idx = 1;
  }

  $flavor = $_POST["flavor"];
  $expiry = $_POST["expiry"] === ""? "0001-01-01": $_POST["expiry"];
  $is_wet = isset($_POST["is_wet"])? true: false;
  $is_prescription_diet = isset($_POST["is_prescription_diet"])? true: false;
  $is_for_kitten = isset($_POST["is_for_kitten"])? true: false;

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
    $img_url = $cat_food->getImgUrl();

    // Berbeda dengan Create.php, disini ada sedikit proses tambahan pada penambahan gambar, yaitu memastikan
    // gambar sebelumnya dihapus dulu, baru menambahkan gambar yang baru. Tentu, gambar lama hanya akan dihapus
    // jika ada input gambar baru
    if(isset($_FILES['img']) && $_FILES['img']['error'] === UPLOAD_ERR_OK) {
      $img = $_FILES['img'];
      $file_name = 'pd_'.$sku.'.'.strtolower(pathinfo($img['name'], PATHINFO_EXTENSION));
      $target_dir = __DIR__.'/images/';

      if(!is_dir($target_dir)) {
        mkdir($target_dir, 0755, true);
      }
      
      if($img_url !== "-") {
        $old_file_path = $target_dir.$img_url;
        if(file_exists($old_file_path)) {
          unlink($old_file_path);
        }
      }

      $target_path = $target_dir.$file_name;

      if(move_uploaded_file($img['tmp_name'], $target_path)) {
        $img_url = $file_name;
      }
    } else if($img_url !== "-" && $sku !== $old_sku) {
      // Selain itu, karena SKU mungkin berubah, maka nama gambar juga ikut dirubah agar tetap unik
      $file_name = 'pd_'.$sku.'.'.strtolower(pathinfo($img_url, PATHINFO_EXTENSION));
      rename("images/".$img_url, "images/".$file_name);
      $img_url = $file_name;
    }
    
    foreach($_SESSION["cat_foods"] as $idx => $c) {
      if($c->getSKU() === $old_sku) {
        $_SESSION["cat_foods"][$idx] = new CatFood($sku, $name, $flavor, $price, $img_url, $expiry, $weight, $is_wet, $is_prescription_diet, $is_for_kitten);
        break;
      }
    }

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
  <title>FURRY FRIENDS DATA CENTER - Ubah data</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <main>
    <div class="form-container">
      <img src="images/logo-update.png" alt="Ubah Data" class="logo">
      <form method="POST" enctype="multipart/form-data">
        <a href="Main.php" class="button-back">&larr; Kembali</a>
        <div class="input-group">
          <label for="sku">SKU<span class="text-danger">*</span></label>
          <input type="text" name="sku" id="sku" class="<?= $e_idx == 0? "error": "" ?>" value="<?= isset($sku)? $sku: $cat_food->getSKU() ?>" required>
        </div>
        <div class="input-group">
          <label for="name">Nama/Merk Produk<span class="text-danger">*</span></label>
          <input type="text" name="name" id="name" class="<?= $e_idx == 1? "error": "" ?>" value="<?= isset($name)? $name: $cat_food->getName() ?>" required>
        </div>
        <div class="input-group">
          <label for="flavor">Rasa</label>
          <input type="text" name="flavor" id="flavor" class="<?= $e_idx == 2? "error": "" ?>" value="<?= isset($flavor)? $flavor: $cat_food->getFlavor() ?>">
        </div>
        <div class="input-group">
          <label for="price">Harga</label>
          <input type="number" name="price" id="price" class="<?= $e_idx == 3? "error": "" ?>" min="0" value="<?= isset($price)? $price: $cat_food->getPrice() ?>">
        </div>
        <div class="input-group">
          <label for="expiry">Tanggal Kadaluarsa</label>
          <input type="date" name="expiry" id="expiry" class="<?= $e_idx == 4? "error": "" ?>" value="<?= isset($expiry) && $expiry !== "0001-01-01"? $expiry: ($cat_food->getExpiry()->format("Y-m-d") !== "0001-01-01"? $cat_food->getExpiry()->format("Y-m-d"): "") ?>">
        </div>
        <div class="input-group">
          <label for="weight">Berat (gram)</label>
          <input type="number" name="weight" id="weight" class="<?= $e_idx == 5? "error": "" ?>" value="<?= isset($weight)? $weight: $cat_food->getWeight() ?>">
        </div>
        <div class="checkbox-group">
          <div class="input-group">
            <input type="checkbox" name="is_wet" id="is_wet" class="<?= $e_idx == 6? "error": "" ?>" <?= (!isset($is_wet) && $cat_food->getIsWet()) || (isset($is_wet) && $is_wet)? "checked": "" ?>>
            <label for="is_wet" class="checkbox-label">Makanan basah</label>
          </div>
          <div class="input-group">
            <input type="checkbox" name="is_prescription_diet" id="is_prescription_diet" class="<?= $e_idx == 7? "error": "" ?>" <?= (!isset($is_prescription_diet) && $cat_food->getIsPrescriptionDiet()) || (isset($is_prescription_diet) && $is_prescription_diet)? "checked": "" ?>>
            <label for="is_prescription_diet" class="checkbox-label">Butuh resep</label>
          </div>
          <div class="input-group">
            <input type="checkbox" name="is_for_kitten" id="is_for_kitten" class="<?= $e_idx == 8? "error": "" ?>" <?= (!isset($is_for_kitten) && $cat_food->getIsForKitten()) || (isset($is_for_kitten) && $is_for_kitten)? "checked": "" ?>>
            <label for="is_for_kitten" class="checkbox-label">Khusus anak kucing</label>
          </div>
        </div>
        <div class="input-group">
          <label for="img">Gambar Produk</label>
          <input type="file" name="img" id="img" accept="image/*" class="<?= $e_idx == 9? "error": "" ?>">
        </div>
        <?= $e_msg != ""? "<p class=\"text-danger text-end\">".$e_msg."</p>": "" ?>
        <button type="submit" class="button button-warning">UBAH</button>
      </form>
    </div>
  </main>
</body>
</html>