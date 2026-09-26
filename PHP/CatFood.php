<?php

require_once 'PetFood.php';

class CatFood extends PetFood {
  private bool $is_wet = false, $is_prescription_diet = false, $is_for_kitten = false; // Apakah makanan basah? Apakah perlu resep? Apakah untuk anak kucing?

  public function __construct(string $s, string $n, string $f, int $p, string $i, string $e, int $w, bool $iw, bool $ipd, bool $ifk) {
    $this->setSKU($s);
    $this->setName($n);
    $this->setFlavor($f);
    $this->setPrice($p);
    $this->setImgUrl($i);
    $this->setExpiry($e);
    $this->setWeight($w);
    $this->setIsWet($iw);
    $this->setIsPrescriptionDiet($ipd);
    $this->setIsForKitten($ifk);
  }

  public function setIsWet(bool $iw) {
    $this->is_wet = $iw;
  }
  public function getIsWet() {
    return $this->is_wet;
  }

  public function setIsPrescriptionDiet(bool $ipd) {
    $this->is_prescription_diet = $ipd;
  }
  public function getIsPrescriptionDiet() {
    return $this->is_prescription_diet;
  }

  public function setIsForKitten(bool $ifk) {
    $this->is_for_kitten = $ifk;
  }
  public function getIsForKitten() {
    return $this->is_for_kitten;
  }
}