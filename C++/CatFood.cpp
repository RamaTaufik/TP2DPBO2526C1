#include "PetFood.cpp"

// Fungsi yang merubah keseluruhan string menjadi lowercase
std::string strToLower(std::string str) {
  int i = 0;
  std::string new_str = str;

  while(i < str.size()) {
    // Memastikan bahwa hanya karakter abjad romawi saja yang diubah ke lowercase
    if(new_str[i] >= 'A' && new_str[i] <= 'Z') new_str[i] += 32;

    i++;
  }

  return new_str;
}

class CatFood : public PetFood {
  private:
    bool is_wet, is_prescription_diet, is_for_kitten; // Apakah makanan basah? Apakah perlu resep? Apakah untuk anak kucing?

  public:
    CatFood() {
      is_wet = false;
      is_prescription_diet = false;
      is_for_kitten = false;
    }

    CatFood(std::string s, std::string n, std::string f, int p, int y, int m, int d, int w, std::string iw, std::string ipd, std::string ifk) {
      setSKU(s);
      setName(n);
      setFlavor(f);
      setPrice(p);
      setExpiryY(y);
      setExpiryM(m);
      setExpiryD(d);
      setWeight(w);
      setIsWet(iw);
      setIsPrescriptionDiet(ipd);
      setIsForKitten(ifk);
    }

    int setIsWet(std::string iw) {
      if(strToLower(iw) == "y") {
        is_wet = true;
        return 0;
      } else if(strToLower(iw) == "n") {
        is_wet = false;
        return 0;
      }

      std::cout << "Hanya bisa 'y' untuk ya atau 'n' untuk tidak!\n";
      return -1;
    }
    bool getIsWet() const {
      return is_wet;
    }

    int setIsPrescriptionDiet(std::string ipd) {
      if(strToLower(ipd) == "y") {
        is_prescription_diet = true;
        return 0;
      } else if(strToLower(ipd) == "n") {
        is_prescription_diet = false;
        return 0;
      }

      std::cout << "Hanya bisa 'y' untuk ya atau 'n' untuk tidak!\n";
      return -1;
    }
    bool getIsPrescriptionDiet() const {
      return is_prescription_diet;
    }

    int setIsForKitten(std::string ifk) {
      if(strToLower(ifk) == "y") {
        is_for_kitten = true;
        return 0;
      } else if(strToLower(ifk) == "n") {
        is_for_kitten = false;
        return 0;
      }

      std::cout << "Hanya bisa 'y' untuk ya atau 'n' untuk tidak!\n";
      return -1;
    }
    bool getIsForKitten() const {
      return is_for_kitten;
    }

    ~CatFood() {}
};