<?php

class Food {
  private string $name = "", $flavor = "", $img_url = ""; // Nama, Rasa, Direktori gambar
  private int $price = -1;     // Harga

  public function __construct(string $n, string $f, int $p, string $i) {
    $this->setName($n);
    $this->setFlavor($f);
    $this->setPrice($p);
    $this->setImgUrl($i);
  }

  public function setName(string $n) {
    if($n === "") {
      return -1;
    }

    $this->name = $n;
    return 0;
  }
  public function getName() {
    return $this->name;
  }

  public function setFlavor(string $f) {
    if($f === "") {
      $this->flavor = "-";
    } else {
      $this->flavor = $f;
    }
  }
  public function getFlavor() {
    return $this->flavor;
  }

  public function setPrice(int $p) {
    if($p < 0) {
      return -1;
    }

    $this->price = $p;
    return 0;
  }
  public function getPrice() {
    return $this->price;
  }

  public function setImgUrl(string $i): void {
    if($i === "") {
      $this->img_url = "-";
    } else {
      $this->img_url = $i;
    }
  }
  public function getImgUrl() {
    return $this->img_url;
  }
}