#include "CatFood.cpp"
#include <vector>
#include <cmath>

// Panjang maksimum dari setiap atribut milik semua objek. Secara default, maksimum nya di-set terlebih dahulu pada
// panjang nama masing-masing atribut (SKU | Nama | Rasa | Harga | Kadaluarsa | Berat | Basah? | Butuh resep? | Khusus anak?)
int max_lens[] = {3, 4, 4, 5, 10, 5, 6, 12, 12};

// Fungsi untuk menghitung jumlah digit suatu integer positif
int intlen(int num) {
  if(num < 10) {
    return 1;
  }
  return intlen(num / 10) + 1;
}

// Fungsi untuk merubah string menjadi integer
int cstrtoint(std::string str) {
  int num = 0;

  for(int i = 0; i < str.size(); i++) {
    if(str[i] < '0' || str[i] > '9') {
      // Karena semua atribut integer dipastikan hanya bilangan bulat positif, maka hanya digit berupa angka 0 sampai 9
      // yang akan diterima, sehingga fungsi ini juga sekaligus menjadi filter input
      return -1;
    } else {
      num = (num * 10) + (str[i] - '0');
    }
  }

  return num;
}

// Fungsi untuk mencari index dari item suatu vektor objek berdasarkan SKU (ID)
int findBySKU(std::vector<CatFood> src, std::string s) {
  int i = 0;

  while(i < src.size()) {
    if(src[i].getSKU() == s) {
      return i;
    }

    i++;
  }

  return -1;
}

// Fungsi untuk mempersingkat penulisan tanggal
std::string formatdate(CatFood src) {
  std::string formatted = std::to_string(src.getExpiryY()) + "-";

  if(src.getExpiryM() < 10) {
    formatted += "0";
  }
  formatted += std::to_string(src.getExpiryM()) + "-";
  
  if(src.getExpiryD() < 10) {
    formatted += "0";
  }
  formatted += std::to_string(src.getExpiryD());

  return formatted;
}

// Prosedur untuk meng-print karakter c sebanyak n
void printchar(int n, char c) {
  for(int i = 0; i < n; i++) {
    std::cout << c;
  }
}

// Prosedur untuk meng-print border pada tabel di CLI
void printborder() {
  for(int i = 0; i < 9; i++) {
    std::cout << "+";
    printchar(max_lens[i] + 2, '-');
  }
  std::cout << "+\n";
}

// Prosedur untuk meng-print data film ke bentuk tabel
void printCatFoods(std::vector<CatFood> ms) {
  // Print header tabel
  printborder();
  std::cout << "| SKU";
  printchar(max_lens[0] - 3, ' ');
  std::cout << " | Nama";
  printchar(max_lens[1] - 4, ' ');
  std::cout << " | Rasa";
  printchar(max_lens[2] - 4, ' ');
  std::cout << " | Harga";
  printchar(max_lens[3] - 5, ' ');
  std::cout << " | Kadaluarsa";
  printchar(max_lens[4] - 10, ' ');
  std::cout << " | Berat";
  printchar(max_lens[5] - 5, ' ');
  std::cout << " | Basah?";
  printchar(max_lens[6] - 6, ' ');
  std::cout << " | Butuh resep?";
  printchar(max_lens[7] - 12, ' ');
  std::cout << " | Khusus anak?";
  printchar(max_lens[8] - 12, ' ');
  std::cout << " |\n";
  printborder();

  for(int i = 0; i < ms.size(); i++) {
    // Print masing-masing data
    std::cout << "| " << ms[i].getSKU();
    printchar(max_lens[0] - ms[i].getSKU().size(), ' ');

    std::cout << " | " << ms[i].getName();
    printchar(max_lens[1] - ms[i].getName().size(), ' ');

    std::cout << " | " << ms[i].getFlavor();
    printchar(max_lens[2] - ms[i].getFlavor().size(), ' ');
    
    std::cout << " | Rp";
    printchar(max_lens[3] - 2 - intlen(ms[i].getPrice()), ' '); // Dikurangi dua karena ada penambahan 'Rp'
    std::string formatted = formatdate(ms[i]);
    std::cout << ms[i].getPrice() << " | " << formatted;
    printchar(max_lens[4] - formatted.size(), ' ');

    std::cout << " | ";
    printchar(max_lens[5] - 1 - intlen(ms[i].getWeight()), ' '); // Dikurangi dua karena ada penambahan 'Rp'
    std::cout << ms[i].getWeight() << "g | " << (ms[i].getIsWet()? "Ya": "Tidak");
    printchar(max_lens[6] - (ms[i].getIsWet()? 2: 5), ' ');

    std::cout << " | " << (ms[i].getIsPrescriptionDiet()? "Ya": "Tidak");
    printchar(max_lens[7] - (ms[i].getIsPrescriptionDiet()? 2: 5), ' ');

    std::cout << " | " << (ms[i].getIsForKitten()? "Ya": "Tidak");
    printchar(max_lens[8] - (ms[i].getIsForKitten()? 2: 5), ' ');
    std::cout << " |\n";

    printborder();
  }
}

int main() {
  std::vector<CatFood> cat_foods; // Vector data film
  std::string choice = "0"; // Variabel untuk input opsi

  // Data dummy
  cat_foods.push_back(CatFood("SKU001", "Whiskas Ocean Fish", "Tuna & Salmon", 45000, 2026, 12, 31, 400, "y", "n", "n"));
  cat_foods.push_back(CatFood("SKU002", "Royal Canin Mother & Babycat", "Chicken", 120000, 2027, 5, 15, 1000, "n", "n", "y"));
  cat_foods.push_back(CatFood("SKU003", "Hill's Prescription Diet i/d", "Turkey", 250000, 2026, 9, 20, 1500, "n", "y", "n"));
  cat_foods.push_back(CatFood("SKU004", "Me-O Creamy Treat", "Salmon", 28000, 2025, 11, 10, 60, "y", "n", "n"));
  cat_foods.push_back(CatFood("SKU005", "Pro Plan Adult Optirenal", "Salmon & Rice", 185000, 2027, 2, 28, 2500, "n", "n", "n"));

  // Perubahan panjang maksimum setiap atribut setelah penambahan data dummy
  max_lens[0] = 6;
  max_lens[1] = 28;
  max_lens[2] = 13;
  max_lens[3] = 8;

  std::cout << "   ____  __ __  _____  _____  _  __    ____  _____  __  ____  __   __  ____    _____\n";
  std::cout << "  / __/ / // / / // / / // / | |/ /   / __/ / // / / / / __/ /  | / / / /| |  /  __/\n";
  std::cout << " / __/ / // / / //_/ / //_/  |   /   / __/ / //_/ / / / __/ / /||/ / / /_/ / /__  /\n";
  std::cout << "/_/   /____/ /_/|_| /_/|_|   /__/   /_/   /_/|_| /_/ /___/ /_/ |__/ /_____/ /____/\n";
  std::cout << "\n> FURRY FRIENDS DATA CENTER <";
  
  // Loop utama
  do{
    // Jika terjadi kesalahan dalam input opsi, tidak perlu print ulang pilihan opsi agar tidak memenuhi layar
    if(cstrtoint(choice) >= 0 && cstrtoint(choice) <= 5) {
      std::cout << "\n1. Lihat data produk\n";
      std::cout << "2. Tambah data produk baru\n";
      std::cout << "3. Ubah data produk\n";
      std::cout << "4. Hapus data produk\n";
      std::cout << "5. Cari produk berdasarkan SKU / nama produk\n";
      std::cout << "0. Keluar\n";
    }
    std::cout << "\nPilih opsi: ";

    std::cin >> choice;

    if(choice == "1") {
      // Lihat semua data
      printCatFoods(cat_foods);
    } else if(choice == "2") {
      // Tambah data
      int temp_int, res = 0;
      std::string temp_str;
      CatFood temp_c_food;

      do{
        std::cout << "Masukkan SKU produk             : ";
        // Ketika melakukan std::cin sebelumnya, ada sisa '\n' yang tidak terbawa ketika pengguna menekan Enter.
        // Kode di bawah 'melahap' '\n' sisaan tersebut agar input tidak seolah-olah ter-'skip'. Validasi res == 0
        // memastikan kode dibawah hanya dijalankan sekali karena jika berulang-ulang, juga akan seolah-olah ter-'skip'
        if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, temp_str);

        // Pastikan SKU unik dan tidak duplikat
        if(findBySKU(cat_foods, temp_str) >= 0) {
          std::cout << "SKU sudah ada!\n";
        } else {
          res = temp_c_food.setSKU(temp_str);
          // Cek panjang maksimum atribut 'SKU'
          if(res == 0 && max_lens[0] < temp_c_food.getSKU().size()) max_lens[0] = temp_c_food.getSKU().size();
        }
      } while(res != 0);
      
      do{
        std::cout << "Masukkan nama/merk produk       : ";
        // Pemakaian std::getline konsekutif tidak perlu 'melahap' '\n' lagi
        std::getline(std::cin, temp_str);
        res = temp_c_food.setName(temp_str);
        // Cek panjang maksimum atribut 'Nama'
        if(res == 0 && max_lens[1] < temp_c_food.getName().size()) max_lens[1] = temp_c_food.getName().size();
      } while(res != 0);

      std::cout << "Masukkan rasa produk            : ";
      std::getline(std::cin, temp_str);
      temp_c_food.setFlavor(temp_str);
      // Cek panjang maksimum atribut 'Rasa produk'
      if(max_lens[2] < temp_c_food.getFlavor().size()) max_lens[2] = temp_c_food.getFlavor().size();

      do{
        std::cout << "Masukkan harga                  : Rp";
        // Input untuk atribut integer tetap menggunakan input string, dikarenakan ketika pengguna memasukkan string
        // saat input integer, C++ akan mengeluarkan error yang tidak bisa ditangkap dengan try-catch
        std::getline(std::cin, temp_str);
        // Daripada membuat fungsi baru sehingga dapat 'menangkap' error ketika memasukkan string pada input integer,
        // lebih simpel menerima input dalam string lalu di validasi manual
        temp_int = cstrtoint(temp_str);
        res = temp_c_food.setPrice(temp_int);
        // Cek panjang maksimum atribut 'Harga'. +2 karena ada 'Rp'
        if(res == 0 && max_lens[3] < intlen(temp_c_food.getPrice()) + 2) max_lens[3] = intlen(temp_c_food.getPrice()) + 2;
      } while(res != 0);

      do{
        std::cout << "Masukkan tahun kadaluarsa       : ";
        std::getline(std::cin, temp_str);
        temp_int = cstrtoint(temp_str);
        res = temp_c_food.setExpiryY(temp_int);
        // Cek panjang maksimum atribut 'Tahun kadaluarsa'. +6 karena panjang nilai bulan dan tanggal tetap 2 digit
        // masing-masing (-mm-dd)
        if(res == 0 && max_lens[4] < intlen(temp_c_food.getExpiryY()) + 6) max_lens[4] = intlen(temp_c_food.getExpiryY()) + 6;
      } while(res != 0);
      
      do{
        std::cout << "Masukkan bulan kadaluarsa       : ";
        std::getline(std::cin, temp_str);
        temp_int = cstrtoint(temp_str);
        res = temp_c_food.setExpiryM(temp_int);
        // Tidak seperti tahun, nilai bulan dibatasi hanya 1-12 sehingga tidak perlu cek panjang digit
      } while(res != 0);
      
      do{
        std::cout << "Masukkan tanggal kadaluarsa : ";
        std::getline(std::cin, temp_str);
        temp_int = cstrtoint(temp_str);
        res = temp_c_food.setExpiryD(temp_int);
        // Sama seperti bulan, nilai tanggal dibatasi hanya 1-31 sehingga tidak perlu cek panjang digit
      } while(res != 0);

      do{
        std::cout << "Masukkan berat (gram)           : ";
        std::getline(std::cin, temp_str);
        temp_int = cstrtoint(temp_str);
        res = temp_c_food.setWeight(temp_int);
        // Cek panjang maksimum atribut 'Berat'. +1 karena ada 'g'
        if(res == 0 && max_lens[5] < intlen(temp_c_food.getWeight()) + 1) max_lens[5] = intlen(temp_c_food.getWeight()) + 1;
      } while(res != 0);

      do{
        std::cout << "Apakah makanan basah (y/n)      ? ";
        std::getline(std::cin, temp_str);
        res = temp_c_food.setIsWet(temp_str);
        // Karena atribut bool hanya memiliki dua nilai, panjang atribut tidak akan berubah banyak
      } while(res != 0);

      do{
        std::cout << "Apakah perlu resep (y/n)        ? ";
        std::getline(std::cin, temp_str);
        res = temp_c_food.setIsPrescriptionDiet(temp_str);
      } while(res != 0);

      do{
        std::cout << "Apakah khusus anak kucing (y/n) ? ";
        std::getline(std::cin, temp_str);
        res = temp_c_food.setIsForKitten(temp_str);
      } while(res != 0);

      cat_foods.push_back(temp_c_food);
    } else if(choice == "3") {
      // Ubah data
      if(cat_foods.size() <= 0) {
        std::cout << "Tidak ada data produk untuk diubah!";
        choice = "-1";
      } else {
        std::string temp_str = "";
        int temp_id = -2;

        // Blok kode do-while() disini memastikan SKU yang dimasukkan benar-benar ada
        do{
          std::cout << "Masukkan SKU : ";
          if(temp_id == -2) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::getline(std::cin, temp_str);
          temp_id = findBySKU(cat_foods, temp_str);
          
          if(temp_id < 0 && temp_str != "00") {
            std::cout << "SKU tidak ditemukan! (masukkan 00 untuk membatalkan)\n";
          }
        } while(temp_id < 0 && temp_str != "00");

        if(temp_id >= 0) {
          std::string temp_choice = "0";

          do{
            int res = 0, temp_int;
            std::string temp_str;

            if(cstrtoint(temp_choice) >= 0 && cstrtoint(temp_choice) <= 9) {
              std::cout << "\n1. SKU                : " << cat_foods[temp_id].getSKU();
              std::cout << "\n2. Nama               : " << cat_foods[temp_id].getName();
              std::cout << "\n3. Rasa               : " << cat_foods[temp_id].getFlavor();
              std::cout << "\n4. Harga              : Rp" << cat_foods[temp_id].getPrice();
              std::cout << "\n5. Tanggal Kadaluarsa : " << formatdate(cat_foods[temp_id]);
              std::cout << "\n6. Berat              : " << cat_foods[temp_id].getWeight() << "g";
              std::cout << "\n7. Makanan basah      ? " << (cat_foods[temp_id].getIsWet()? "Ya": "Tidak");
              std::cout << "\n8. Butuh Resep        ? " << (cat_foods[temp_id].getIsPrescriptionDiet()? "Ya": "Tidak");
              std::cout << "\n9. Khusus anak kucing ? " << (cat_foods[temp_id].getIsForKitten()? "Ya": "Tidak");
              std::cout << "\n0. Kembali" << "\n";
            }

            std::cout << "\nMasukkan nomor atribut untuk diubah : ";
            std::cin >> temp_choice;

            // Input untuk merubah data kurang lebih sama dengan menambah data baru
            if(temp_choice == "1") {
              do{
                std::cout << "Masukkan SKU baru : ";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);

                if(findBySKU(cat_foods, temp_str) >= 0 && findBySKU(cat_foods, temp_str) == temp_id) {
                  std::cout << "SKU sudah ada!\n";
                  res = -1;
                } else {
                  res = cat_foods[temp_id].setSKU(temp_str);
                  if(res == 0 && max_lens[0] < cat_foods[temp_id].getSKU().size()) max_lens[0] = cat_foods[temp_id].getSKU().size();
                }
              } while(res != 0);
            } else if(temp_choice == "2") {
              do{
                std::cout << "Masukkan nama/merk produk : ";
                // Karena input perubahan setiap atribut terpisah, dan diantara input atribut terdapat input untuk opsi, 
                // maka '\n' dari input opsi harus dilahap pada tiap input perubahan atribut
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                res = cat_foods[temp_id].setName(temp_str);
                if(res == 0 && max_lens[1] < cat_foods[temp_id].getName().size()) max_lens[1] = cat_foods[temp_id].getName().size();
              } while(res != 0);
            } else if(temp_choice == "3") {
              std::cout << "Masukkan rasa produk : ";
              if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              std::getline(std::cin, temp_str);
              cat_foods[temp_id].setFlavor(temp_str);
              if(max_lens[2] < cat_foods[temp_id].getFlavor().size()) max_lens[2] = cat_foods[temp_id].getFlavor().size();
            } else if(temp_choice == "4") {
              do{
                std::cout << "Masukkan harga : Rp";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                temp_int = cstrtoint(temp_str);
                res = cat_foods[temp_id].setPrice(temp_int);
                if(res == 0 && max_lens[3] < intlen(cat_foods[temp_id].getPrice()) + 2) max_lens[3] = intlen(cat_foods[temp_id].getPrice()) + 2;
              } while(res != 0);
            } else if(temp_choice == "5") {
              do{
                std::cout << "Masukkan tahun kadaluarsa baru : ";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                temp_int = cstrtoint(temp_str);
                res = cat_foods[temp_id].setExpiryY(temp_int);
                if(res == 0 && max_lens[4] < intlen(cat_foods[temp_id].getExpiryY()) + 6) max_lens[4] = intlen(cat_foods[temp_id].getExpiryY()) + 6;
              } while(res != 0);
              
              do{
                std::cout << "Masukkan bulan kadaluarsa baru : ";
                std::getline(std::cin, temp_str);
                temp_int = cstrtoint(temp_str);
                res = cat_foods[temp_id].setExpiryM(temp_int);
              } while(res != 0);
              
              do{
                std::cout << "Masukkan tanggal kadaluarsa baru : ";
                std::getline(std::cin, temp_str);
                temp_int = cstrtoint(temp_str);
                res = cat_foods[temp_id].setExpiryD(temp_int);
              } while(res != 0);
            } else if(temp_choice == "6") {
              do{
                std::cout << "Masukkan berat baru : ";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                temp_int = cstrtoint(temp_str);
                res = cat_foods[temp_id].setWeight(temp_int);
                if(res == 0 && max_lens[5] < intlen(cat_foods[temp_id].getWeight()) + 1) max_lens[5] = intlen(cat_foods[temp_id].getWeight()) + 1;
              } while(res != 0);
            } else if(temp_choice == "7") {
              do{
                std::cout << "Apakah makanan basah (y/n) ? ";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                res = cat_foods[temp_id].setIsWet(temp_str);
              } while(res != 0);
            } else if(temp_choice == "8") {
              do{
                std::cout << "Apakah perlu resep (y/n) ? ";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                res = cat_foods[temp_id].setIsPrescriptionDiet(temp_str);
              } while(res != 0);
            } else if(temp_choice == "9") {
              do{
                std::cout << "Apakah khusus anak kucing (y/n) ? ";
                if(res == 0) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, temp_str);
                res = cat_foods[temp_id].setIsForKitten(temp_str);
              } while(res != 0);
            } else if(temp_choice != "0") {
              std::cout << "Tidak ada opsi atribut '" << temp_choice << "'!";
            }
          } while(temp_choice != "0");
        }
      }
    } else if(choice == "4") {
      // Hapus data produk
      if(cat_foods.size() <= 0) {
        std::cout << "Tidak ada data produk untuk dihapus!";
        choice = "-1";
      } else {
        std::string temp_str = "";
        int temp_id = -2;

        // Sama seperti di blok kode perubahan data, ada blok kode do-while() di awal untuk memastikan ID yang
        // dimasukkan benar-benar ada
        do{
          std::cout << "Masukkan SKU : ";
          if(temp_id == -2) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::getline(std::cin, temp_str);
          temp_id = findBySKU(cat_foods, temp_str);
          
          if(temp_id < 0 && temp_str != "00") {
            std::cout << "SKU tidak ditemukan! (masukkan 00 untuk membatalkan)\n";
          }
        } while(temp_id < 0 && temp_str != "00");

        if(temp_id >= 0) {
          std::cout << "Berhasil menghapus produk \"" << cat_foods[temp_id].getName() << "\"!\n";
          cat_foods.erase(cat_foods.begin() + (temp_id));
        }
      }
    } else if(choice == "5") {
      // Cari data spesifik. Pencarian dibuat berdasarkan atribut sku atau nama produk
      std::vector<CatFood> temp_cat_foods;
      std::string temp_str = "";
      
      std::cout << "Masukkan kata kunci pencarian : ";
      // Seperti biasa, lahap dulu '\n' dari input opsi sebelumnya
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, temp_str);
      temp_str = strToLower(temp_str);

      // Filter vektor, pastikan hanya produk yang mengandung kata kunci pada SKU atau nama produknya yang 
      // ditampilkan. SKU serta nama produk dan kata kunci diubah ke lowercase sehingga pencarian menjadi
      // case-insensitive
      for(int i = 0; i < cat_foods.size(); i++) {
        if(
          strToLower(cat_foods[i].getSKU()).find(temp_str) != std::string::npos || 
          strToLower(cat_foods[i].getName()).find(temp_str) != std::string::npos
        ) {
          temp_cat_foods.push_back(cat_foods[i]);
        }
      }

      printCatFoods(temp_cat_foods);
    } else if(choice != "0") {
      std::cout << "Tidak ada opsi '" << choice << "'!";
    }
  } while(choice != "0");

  return 0;
}