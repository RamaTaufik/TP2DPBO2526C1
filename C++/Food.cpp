#include <string>
#include <iostream>

class Food {
  private:
    std::string name, flavor; // Judul, Rasa
    int price; // Harga

  public:
    Food() {}

    Food(std::string n, std::string f, int p) {
      setName(n);
      setFlavor(f);
      setPrice(p);
    }

    int setName(std::string n) {
      if(n == "") {
        std::cout << "Nama tidak bisa kosong!\n";
        return -1;
      }

      name = n;
      return 0;
    }
    std::string getName() {
      return name;
    }

    void setFlavor(std::string f) {
      if(f == "") {
        flavor = "-";
      } else {
        flavor = f;
      }
    }
    std::string getFlavor() {
      return flavor;
    }

    int setPrice(int p) {
      if(p < 0) {
        std::cout << "Harga harus bilangan bulat positif!\n";
        return -1;
      }

      price = p;
      return 0;
    }
    int getPrice() {
      return price;
    }

    ~Food() {}
};