<?php
include "CatFood.php";

session_start();

// Kata kunci pencarian
$search = "";

// Kata kunci pencarian diterima lewat parameter metode GET
if(isset($_GET["search"])) $search = $_GET["search"];
if(!isset($_SESSION["cat_foods"])) {
  // Data dummy, sekaligus inisiasi session
  $_SESSION["cat_foods"] = [
    new CatFood("SKU001", "Whiskas Ocean Fish", "Tuna & Salmon", 45000, "pd_SKU001.avif", "2026-12-31", 400, "y", "n", "n"),
    new CatFood("SKU002", "Royal Canin Mother & Babycat", "Ayam", 120000, "pd_SKU002.webp", "2027-05-15", 1000, "n", "n", "y"),
    new CatFood("SKU003", "Hill's Prescription Diet i/d", "Ayam Turkey", 250000, "pd_SKU003.webp", "2026-09-20", 1500, "n", "y", "n"),
    new CatFood("SKU004", "Me-O Creamy Treat", "Salmon", 28000, "pd_SKU004.webp", "2025-11-10", 60, "y", "n", "n"),
    new CatFood("SKU005", "Pro Plan Adult Optirenal", "Ayam", 185000, "pd_SKU005.webp", "2027-02-28", 2500, "n", "n", "n")
  ];
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>FURRY FRIENDS DATA CENTER</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <img src="images/logo.png" alt="Logo" class="logo">
  <main>
    <div class="table-container">
      <div class="input-container">
        <form method="GET">
          <input type="text" name="search" placeholder="Cari SKU/nama produk..." value="<?= $search ?>">
          <button type="submit">🔎︎</button>
        </form>
        <a href="create.php">Tambah ＋</a>
      </div>
      <table>
        <thead>
          <tr>
            <th>SKU</th>
            <th>Nama Produk</th>
            <th>Rasa</th>
            <th>Harga</th>
            <th>Kadaluarsa</th>
            <th>Berat</th>
            <th>Basah?</th>
            <th>Butuh resep?</th>
            <th>Khusus anak?</th>
            <th>Gambar</th>
            <th>Aksi</th>
          </tr>
        </thead>
        <tbody>
          <?php
          if(isset($_SESSION["cat_foods"]) && count($_SESSION["cat_foods"]) > 0) {
            $cat_foods = array_filter($_SESSION["cat_foods"], fn($cat_food) => str_contains(strtolower($cat_food->getSKU()), strtolower($search)) || str_contains(strtolower($cat_food->getName()), strtolower($search)));

            // Tampilkan masing-masing data
            foreach($cat_foods as $cat_food) {
          ?>
            <tr>
              <td><?= $cat_food->getSKU() ?></td>
              <td><?= $cat_food->getName() ?></td>
              <td><?= $cat_food->getFlavor() ?></td>
              <td>Rp<?= $cat_food->getPrice() ?></td>
              <td><?= $cat_food->getExpiry()->format("Y-m-d") === "0001-01-01"? "-": $cat_food->getExpiry()->format("Y-m-d") ?></td>
              <td><?= $cat_food->getWeight() ?> gram</td>
              <td><?= $cat_food->getIsWet()? "Ya": "Tidak" ?></td>
              <td><?= $cat_food->getIsPrescriptionDiet()? "Ya": "Tidak" ?></td>
              <td><?= $cat_food->getIsForKitten()? "Ya": "Tidak" ?></td>
              <td>
                <?= $cat_food->getImgUrl() === "-"? "-": "<img src=\"images/".$cat_food->getImgUrl()."\">" ?>
              </td>
              <td>
                <form method="POST" action="delete.php">
                  <input type="hidden" name="sku" value="<?= $cat_food->getSKU() ?>">
                  <a href="update.php?sku=<?= $cat_food->getSKU() ?>" class="button button-warning">Edit</a>
                  <button type="submit" class="button button-danger" onclick="return confirm('Yakin hapus?')">Hapus</button>
                </form>
                <form method="POST" action="delete_img.php">
                  <input type="hidden" name="sku" value="<?= $cat_food->getSKU() ?>">
                  <button type="submit" class="button button-danger" onclick="return confirm('Yakin hapus gambar?')">Hapus Gambar</button>
                </form>
              </td>
            </tr>
          <?php } } else { ?>
          <tr>
            <td colspan="11" class="table-no-data">
              <h3>Tidak ada data produk</h3>
            </td>
          </tr>
          <?php } ?>
        </tbody>
      </table>
    </div>
  </main>
</body>
</html>