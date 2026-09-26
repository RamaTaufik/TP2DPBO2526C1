<?php

require_once 'Food.php';

class PetFood extends Food {
  private string $sku = ""; // SKU (Stock Keeping Unit, ID)
  private DateTime $expiry; // Tanggal kadaluarsa
  private int $weight = 0; // Berat (dalam gram)

  public function __construct(string $s, string $n, string $f, int $p, string $i, string $e, int $w) {
    $this->setSKU($s);
    $this->setName($n);
    $this->setFlavor($f);
    $this->setPrice($p);
    $this->setImgUrl($i);
    $this->setExpiry($e);
    $this->setWeight($w);
  }

  public function setSKU(string $s) {
    if($s == "") {
      echo "SKU tidak bisa kosong!\n";
      return -1;
    }

    $this->sku = $s;
    return 0;
  }
  public function getSKU() {
    return $this->sku;
  }

  public function setExpiry(string $e) {
    $date = DateTime::createFromFormat("Y-m-d", $e);

    if($date && $date->format("Y-m-d") === $e) {
      $this->expiry = $date;
      return 0;
    }

    return -1;
  }
  public function getExpiry() {
    return $this->expiry;
  }

  public function setWeight(int $w) {
    if($w < 0) {
      return -1;
    }

    $this->weight = $w;
    return 0;
  }
  public function getWeight() {
    return $this->weight;
  }
}