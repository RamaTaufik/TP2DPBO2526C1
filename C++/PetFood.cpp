#include "Food.cpp"

class PetFood : public Food {
  private:
    std::string sku; // SKU (Stock Keeping Unit, ID)
    int expiry_y, expiry_m, expiry_d, weight; // Tanggal kadaluarsa, Berat (dalam gram)

  public:
    PetFood() {}

    PetFood(std::string s, std::string n, std::string f, int p, int y, int m, int d, int w) {
      setSKU(s);
      setName(n);
      setFlavor(f);
      setPrice(p);
      setExpiryY(y);
      setExpiryM(m);
      setExpiryD(d);
      setWeight(w);
    }
    
    int setSKU(std::string s) {
      if(s == "") {
        std::cout << "SKU tidak bisa kosong!\n";
        return -1;
      }

      sku = s;
      return 0;
    }
    std::string getSKU() {
      return sku;
    }

    int setExpiryY(int y) {
      if(y < 0) {
        std::cout << "Tahun kadaluarsa harus bilangan bulat positif!\n";
        return -1;
      }

      expiry_y = y;
      return 0;
    }
    int getExpiryY() {
      return expiry_y;
    }

    int setExpiryM(int m) {
      if(m < 1 || m > 12) {
        std::cout << "Bulan kadaluarsa harus antara 1 dan 12!\n";
        return -1;
      }

      expiry_m = m;
      return 0;
    }
    int getExpiryM() {
      return expiry_m;
    }

    int setExpiryD(int d) {
      if(d < 1 || d > 31) {
        std::cout << "Hari kadaluarsa harus antara 1 dan 31!\n";
        return -1;
      }

      expiry_d = d;
      return 0;
    }
    int getExpiryD() {
      return expiry_d;
    }

    int setWeight(int w) {
      if(w < 0) {
        std::cout << "Berat harus bilangan bulat positif!\n";
        return -1;
      }

      weight = w;
      return 0;
    }
    int getWeight() {
      return weight;
    }

    ~PetFood() {}
};