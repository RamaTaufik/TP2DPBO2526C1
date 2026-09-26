import java.util.ArrayList;
import java.util.Scanner;

public class Main {
  // Panjang maksimum dari setiap atribut milik semua objek. Secara default, maksimum nya di-set terlebih dahulu pada
  // panjang nama masing-masing atribut (SKU | Nama | Rasa | Harga | Kadaluarsa | Berat | Basah? | Butuh resep? | Khusus anak?)
  static int[] max_lens = {3, 4, 4, 5, 10, 5, 6, 12, 12};

  // Fungsi untuk menghitung jumlah digit suatu integer positif
  public static int intlen(int num) {
    if(num < 10) {
      return 1;
    }
    return intlen(num / 10) + 1;
  }

  // Fungsi untuk merubah string menjadi integer
  public static int cstrtoint(String str) {
    int num = 0;

    for(int i = 0; i < str.length(); i++) {
      if(str.charAt(i) < '0' || str.charAt(i) > '9') {
        // Karena semua atribut integer dipastikan hanya bilangan bulat positif, maka hanya digit berupa angka 0 sampai 9
        // yang akan diterima, sehingga fungsi ini juga sekaligus menjadi filter input
        return -1;
      } else {
        num = (num * 10) + (str.charAt(i) - '0');
      }
    }

    return num;
  }

  // Fungsi untuk mencari index dari item suatu vektor objek berdasarkan SKU (ID)
  public static int findBySKU(ArrayList<CatFood> src, String s) {
    int i = 0;

    while(i < src.size()) {
      if(src.get(i).getSKU().equals(s)) {
        return i;
      }

      i++;
    }

    return -1;
  }

  // Fungsi untuk mempersingkat penulisan tanggal
  public static String formatdate(CatFood src) {
    String formatted = src.getExpiryY() + "-";

    if(src.getExpiryM() < 10) {
      formatted += "0";
    }
    formatted += src.getExpiryM() + "-";

    if(src.getExpiryD() < 10) {
      formatted += "0";
    }
    formatted += src.getExpiryD();

    return formatted;
  }

  // Prosedur untuk meng-print karakter c sebanyak n
  public static void printchar(int n, char c) {
    for(int i = 0; i < n; i++) {
      System.out.print(c);
    }
  }

  // Prosedur untuk meng-print border pada tabel di CLI
  public static void printborder() {
    for(int i = 0; i < 9; i++) {
      System.out.print("+");
      printchar(max_lens[i] + 2, '-');
    }
    System.out.print("+\n");
  }

  // Prosedur untuk meng-print data film ke bentuk tabel
  public static void printCatFoods(ArrayList<CatFood> ms) {
    // Print header tabel
    printborder();
    System.out.print("| SKU");
    printchar(max_lens[0] - 3, ' ');
    System.out.print(" | Nama");
    printchar(max_lens[1] - 4, ' ');
    System.out.print(" | Rasa");
    printchar(max_lens[2] - 4, ' ');
    System.out.print(" | Harga");
    printchar(max_lens[3] - 5, ' ');
    System.out.print(" | Kadaluarsa");
    printchar(max_lens[4] - 10, ' ');
    System.out.print(" | Berat");
    printchar(max_lens[5] - 5, ' ');
    System.out.print(" | Basah?");
    printchar(max_lens[6] - 6, ' ');
    System.out.print(" | Butuh resep?");
    printchar(max_lens[7] - 12, ' ');
    System.out.print(" | Khusus anak?");
    printchar(max_lens[8] - 12, ' ');
    System.out.print(" |\n");
    printborder();

    for(int i = 0; i < ms.size(); i++) {
      // Print masing-masing data
      System.out.print("| " + ms.get(i).getSKU());
      printchar(max_lens[0] - ms.get(i).getSKU().length(), ' ');

      System.out.print(" | " + ms.get(i).getName());
      printchar(max_lens[1] - ms.get(i).getName().length(), ' ');

      System.out.print(" | " + ms.get(i).getFlavor());
      printchar(max_lens[2] - ms.get(i).getFlavor().length(), ' ');

      System.out.print(" | Rp");
      printchar(max_lens[3] - 2 - intlen(ms.get(i).getPrice()), ' '); // Dikurangi dua karena ada penambahan 'Rp'
      String formatted = formatdate(ms.get(i));
      System.out.print(ms.get(i).getPrice() + " | " + formatted);
      printchar(max_lens[4] - formatted.length(), ' ');

      System.out.print(" | ");
      printchar(max_lens[5] - 1 - intlen(ms.get(i).getWeight()), ' '); // Dikurangi dua karena ada penambahan 'Rp'
      System.out.print(ms.get(i).getWeight() + "g | " + (ms.get(i).getIsWet() ? "Ya" : "Tidak"));
      printchar(max_lens[6] - (ms.get(i).getIsWet() ? 2 : 5), ' ');

      System.out.print(" | " + (ms.get(i).getIsPrescriptionDiet() ? "Ya" : "Tidak"));
      printchar(max_lens[7] - (ms.get(i).getIsPrescriptionDiet() ? 2 : 5), ' ');

      System.out.print(" | " + (ms.get(i).getIsForKitten() ? "Ya" : "Tidak"));
      printchar(max_lens[8] - (ms.get(i).getIsForKitten() ? 2 : 5), ' ');
      System.out.print(" |\n");

      printborder();
    }
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    ArrayList<CatFood> cat_foods = new ArrayList<>(); // Vector data film
    String choice = "0"; // Variabel untuk input opsi

    // Data dummy
    cat_foods.add(new CatFood("SKU001", "Whiskas Ocean Fish", "Tuna & Salmon", 45000, 2026, 12, 31, 400, "y", "n", "n"));
    cat_foods.add(new CatFood("SKU002", "Royal Canin Mother & Babycat", "Chicken", 120000, 2027, 5, 15, 1000, "n", "n", "y"));
    cat_foods.add(new CatFood("SKU003", "Hill's Prescription Diet i/d", "Turkey", 250000, 2026, 9, 20, 1500, "n", "y", "n"));
    cat_foods.add(new CatFood("SKU004", "Me-O Creamy Treat", "Salmon", 28000, 2025, 11, 10, 60, "y", "n", "n"));
    cat_foods.add(new CatFood("SKU005", "Pro Plan Adult Optirenal", "Salmon & Rice", 185000, 2027, 2, 28, 2500, "n", "n", "n"));

    // Perubahan panjang maksimum setiap atribut setelah penambahan data dummy
    max_lens[0] = 6;
    max_lens[1] = 28;
    max_lens[2] = 13;
    max_lens[3] = 8;

    System.out.print("   ____  __ __  _____  _____  _  __    ____  _____  __  ____  __   __  ____    _____\n");
    System.out.print("  / __/ / // / / // / / // / | |/ /   / __/ / // / / / / __/ /  | / / / /| |  /  __/\n");
    System.out.print(" / __/ / // / / //_/ / //_/  |   /   / __/ / //_/ / / / __/ / /||/ / / /_/ / /__  /\n");
    System.out.print("/_/   /____/ /_/|_| /_/|_|   /__/   /_/   /_/|_| /_/ /___/ /_/ |__/ /_____/ /____/\n");
    System.out.print("\n> FURRY FRIENDS DATA CENTER <");

    // Loop utama
    do {
      // Jika terjadi kesalahan dalam input opsi, tidak perlu print ulang pilihan opsi agar tidak memenuhi layar
      if(cstrtoint(choice) >= 0 && cstrtoint(choice) <= 5) {
        System.out.print("\n1. Lihat data produk\n");
        System.out.print("2. Tambah data produk baru\n");
        System.out.print("3. Ubah data produk\n");
        System.out.print("4. Hapus data produk\n");
        System.out.print("5. Cari produk berdasarkan SKU / nama produk\n");
        System.out.print("0. Keluar\n");
      }
      System.out.print("\nPilih opsi: ");

      choice = scanner.nextLine().trim();

      if(choice.equals("1")) {
        // Lihat semua data
        printCatFoods(cat_foods);
      } else if(choice.equals("2")) {
        // Tambah data
        int temp_int, res = 0;
        String temp_str;
        CatFood temp_c_food = new CatFood();

        do {
          System.out.print("Masukkan SKU produk             : ");
          temp_str = scanner.nextLine();

          // Pastikan SKU unik dan tidak duplikat
          if(findBySKU(cat_foods, temp_str) >= 0) {
            System.out.print("SKU sudah ada!\n");
            res = -1;
          } else {
            res = temp_c_food.setSKU(temp_str);
            // Cek panjang maksimum atribut 'SKU'
            if(res == 0 && max_lens[0] < temp_c_food.getSKU().length()) {
              max_lens[0] = temp_c_food.getSKU().length();
            }
          }
        } while(res != 0);

        do {
          System.out.print("Masukkan nama/merk produk       : ");
          temp_str = scanner.nextLine();
          res = temp_c_food.setName(temp_str);
          // Cek panjang maksimum atribut 'Nama'
          if(res == 0 && max_lens[1] < temp_c_food.getName().length()) {
            max_lens[1] = temp_c_food.getName().length();
          }
        } while(res != 0);

        System.out.print("Masukkan rasa produk            : ");
        temp_str = scanner.nextLine();
        temp_c_food.setFlavor(temp_str);
        // Cek panjang maksimum atribut 'Rasa produk'
        if(max_lens[2] < temp_c_food.getFlavor().length()) {
          max_lens[2] = temp_c_food.getFlavor().length();
        }

        do {
          System.out.print("Masukkan harga                  : Rp");
          // Input untuk atribut integer tetap menggunakan input string, dikarenakan ketika pengguna memasukkan string
          // saat input integer, C++ akan mengeluarkan error yang tidak bisa ditangkap dengan try-catch
          temp_str = scanner.nextLine();
          // Daripada membuat fungsi baru sehingga dapat 'menangkap' error ketika memasukkan string pada input integer,
          // lebih simpel menerima input dalam string lalu di validasi manual
          temp_int = cstrtoint(temp_str);
          res = temp_c_food.setPrice(temp_int);
          // Cek panjang maksimum atribut 'Harga'. +2 karena ada 'Rp'
          if(res == 0 && max_lens[3] < intlen(temp_c_food.getPrice()) + 2) {
            max_lens[3] = intlen(temp_c_food.getPrice()) + 2;
          }
        } while(res != 0);

        do {
          System.out.print("Masukkan tahun kadaluarsa       : ");
          temp_str = scanner.nextLine();
          temp_int = cstrtoint(temp_str);
          res = temp_c_food.setExpiryY(temp_int);
          // Cek panjang maksimum atribut 'Tahun kadaluarsa'. +6 karena panjang nilai bulan dan tanggal tetap 2 digit
          // masing-masing (-mm-dd)
          if(res == 0 && max_lens[4] < intlen(temp_c_food.getExpiryY()) + 6) {
            max_lens[4] = intlen(temp_c_food.getExpiryY()) + 6;
          }
        } while(res != 0);

        do {
          System.out.print("Masukkan bulan kadaluarsa       : ");
          temp_str = scanner.nextLine();
          temp_int = cstrtoint(temp_str);
          res = temp_c_food.setExpiryM(temp_int);
          // Tidak seperti tahun, nilai bulan dibatasi hanya 1-12 sehingga tidak perlu cek panjang digit
        } while(res != 0);

        do {
          System.out.print("Masukkan tanggal kadaluarsa : ");
          temp_str = scanner.nextLine();
          temp_int = cstrtoint(temp_str);
          res = temp_c_food.setExpiryD(temp_int);
          // Sama seperti bulan, nilai tanggal dibatasi hanya 1-31 sehingga tidak perlu cek panjang digit
        } while(res != 0);

        do {
          System.out.print("Masukkan berat (gram)           : ");
          temp_str = scanner.nextLine();
          temp_int = cstrtoint(temp_str);
          res = temp_c_food.setWeight(temp_int);
          // Cek panjang maksimum atribut 'Berat'. +1 karena ada 'g'
          if(res == 0 && max_lens[5] < intlen(temp_c_food.getWeight()) + 1) {
            max_lens[5] = intlen(temp_c_food.getWeight()) + 1;
          }
        } while(res != 0);

        do {
          System.out.print("Apakah makanan basah (y/n)      ? ");
          temp_str = scanner.nextLine();
          res = temp_c_food.setIsWet(temp_str);
          // Karena atribut bool hanya memiliki dua nilai, panjang atribut tidak akan berubah banyak
        } while(res != 0);

        do {
          System.out.print("Apakah perlu resep (y/n)        ? ");
          temp_str = scanner.nextLine();
          res = temp_c_food.setIsPrescriptionDiet(temp_str);
        } while(res != 0);

        do {
          System.out.print("Apakah khusus anak kucing (y/n) ? ");
          temp_str = scanner.nextLine();
          res = temp_c_food.setIsForKitten(temp_str);
        } while(res != 0);

        cat_foods.add(temp_c_food);
      } else if(choice.equals("3")) {
        // Ubah data
        if(cat_foods.size() <= 0) {
          System.out.print("Tidak ada data produk untuk diubah!");
          choice = "-1";
        } else {
          String temp_str = "";
          int temp_id = -2;

          // Blok kode do-while() disini memastikan SKU yang dimasukkan benar-benar ada
          do {
            System.out.print("Masukkan SKU : ");
            temp_str = scanner.nextLine();
            temp_id = findBySKU(cat_foods, temp_str);

            if(temp_id < 0 && !temp_str.equals("00")) {
              System.out.print("SKU tidak ditemukan! (masukkan 00 untuk membatalkan)\n");
            }
          } while(temp_id < 0 && !temp_str.equals("00"));

          if(temp_id >= 0) {
            String temp_choice = "0";

            do {
              int res = 0, temp_int;

              if(cstrtoint(temp_choice) >= 0 && cstrtoint(temp_choice) <= 9) {
                System.out.print("\n1. SKU                : " + cat_foods.get(temp_id).getSKU());
                System.out.print("\n2. Nama               : " + cat_foods.get(temp_id).getName());
                System.out.print("\n3. Rasa               : " + cat_foods.get(temp_id).getFlavor());
                System.out.print("\n4. Harga              : Rp" + cat_foods.get(temp_id).getPrice());
                System.out.print("\n5. Tanggal Kadaluarsa : " + formatdate(cat_foods.get(temp_id)));
                System.out.print("\n6. Berat              : " + cat_foods.get(temp_id).getWeight() + "g");
                System.out.print("\n7. Makanan basah      ? " + (cat_foods.get(temp_id).getIsWet() ? "Ya" : "Tidak"));
                System.out.print("\n8. Butuh Resep        ? " + (cat_foods.get(temp_id).getIsPrescriptionDiet() ? "Ya" : "Tidak"));
                System.out.print("\n9. Khusus anak kucing ? " + (cat_foods.get(temp_id).getIsForKitten() ? "Ya" : "Tidak"));
                System.out.print("\n0. Kembali\n");
              }

              System.out.print("\nMasukkan nomor atribut untuk diubah : ");
              temp_choice = scanner.nextLine().trim();

              // Input untuk merubah data kurang lebih sama dengan menambah data baru
              if(temp_choice.equals("1")) {
                do {
                  System.out.print("Masukkan SKU baru : ");
                  temp_str = scanner.nextLine();

                  if(findBySKU(cat_foods, temp_str) >= 0 && findBySKU(cat_foods, temp_str) == temp_id) {
                    System.out.print("SKU sudah ada!\n");
                    res = -1;
                  } else {
                    res = cat_foods.get(temp_id).setSKU(temp_str);
                    if(res == 0 && max_lens[0] < cat_foods.get(temp_id).getSKU().length()) {
                      max_lens[0] = cat_foods.get(temp_id).getSKU().length();
                    }
                  }
                } while(res != 0);
              } else if(temp_choice.equals("2")) {
                do {
                  System.out.print("Masukkan nama/merk produk : ");
                  temp_str = scanner.nextLine();
                  res = cat_foods.get(temp_id).setName(temp_str);
                  if(res == 0 && max_lens[1] < cat_foods.get(temp_id).getName().length()) {
                    max_lens[1] = cat_foods.get(temp_id).getName().length();
                  }
                } while(res != 0);
              } else if(temp_choice.equals("3")) {
                System.out.print("Masukkan rasa produk : ");
                temp_str = scanner.nextLine();
                cat_foods.get(temp_id).setFlavor(temp_str);
                if(max_lens[2] < cat_foods.get(temp_id).getFlavor().length()) {
                  max_lens[2] = cat_foods.get(temp_id).getFlavor().length();
                }
              } else if(temp_choice.equals("4")) {
                do {
                  System.out.print("Masukkan harga : Rp");
                  temp_str = scanner.nextLine();
                  temp_int = cstrtoint(temp_str);
                  res = cat_foods.get(temp_id).setPrice(temp_int);
                  if(res == 0 && max_lens[3] < intlen(cat_foods.get(temp_id).getPrice()) + 2) {
                    max_lens[3] = intlen(cat_foods.get(temp_id).getPrice()) + 2;
                  }
                } while(res != 0);
              } else if(temp_choice.equals("5")) {
                do {
                  System.out.print("Masukkan tahun kadaluarsa baru : ");
                  temp_str = scanner.nextLine();
                  temp_int = cstrtoint(temp_str);
                  res = cat_foods.get(temp_id).setExpiryY(temp_int);
                  if(res == 0 && max_lens[4] < intlen(cat_foods.get(temp_id).getExpiryY()) + 6) {
                    max_lens[4] = intlen(cat_foods.get(temp_id).getExpiryY()) + 6;
                  }
                } while(res != 0);

                do {
                  System.out.print("Masukkan bulan kadaluarsa baru : ");
                  temp_str = scanner.nextLine();
                  temp_int = cstrtoint(temp_str);
                  res = cat_foods.get(temp_id).setExpiryM(temp_int);
                } while(res != 0);

                do {
                  System.out.print("Masukkan tanggal kadaluarsa baru : ");
                  temp_str = scanner.nextLine();
                  temp_int = cstrtoint(temp_str);
                  res = cat_foods.get(temp_id).setExpiryD(temp_int);
                } while(res != 0);
              } else if(temp_choice.equals("6")) {
                do {
                  System.out.print("Masukkan berat baru : ");
                  temp_str = scanner.nextLine();
                  temp_int = cstrtoint(temp_str);
                  res = cat_foods.get(temp_id).setWeight(temp_int);
                  if(res == 0 && max_lens[5] < intlen(cat_foods.get(temp_id).getWeight()) + 1) {
                    max_lens[5] = intlen(cat_foods.get(temp_id).getWeight()) + 1;
                  }
                } while(res != 0);
              } else if(temp_choice.equals("7")) {
                do {
                  System.out.print("Apakah makanan basah (y/n) ? ");
                  temp_str = scanner.nextLine();
                  res = cat_foods.get(temp_id).setIsWet(temp_str);
                } while(res != 0);
              } else if(temp_choice.equals("8")) {
                do {
                  System.out.print("Apakah perlu resep (y/n) ? ");
                  temp_str = scanner.nextLine();
                  res = cat_foods.get(temp_id).setIsPrescriptionDiet(temp_str);
                } while(res != 0);
              } else if(temp_choice.equals("9")) {
                do {
                  System.out.print("Apakah khusus anak kucing (y/n) ? ");
                  temp_str = scanner.nextLine();
                  res = cat_foods.get(temp_id).setIsForKitten(temp_str);
                } while(res != 0);
              } else if(!temp_choice.equals("0")) {
                System.out.print("Tidak ada opsi atribut '" + temp_choice + "'!");
              }
            } while(!temp_choice.equals("0"));
          }
        }
      } else if(choice.equals("4")) {
        // Hapus data produk
        if(cat_foods.size() <= 0) {
          System.out.print("Tidak ada data produk untuk dihapus!");
          choice = "-1";
        } else {
          String temp_str = "";
          int temp_id = -2;

          // Sama seperti di blok kode perubahan data, ada blok kode do-while() di awal untuk memastikan ID yang
          // dimasukkan benar-benar ada
          do {
            System.out.print("Masukkan SKU : ");
            temp_str = scanner.nextLine();
            temp_id = findBySKU(cat_foods, temp_str);

            if(temp_id < 0 && !temp_str.equals("00")) {
              System.out.print("SKU tidak ditemukan! (masukkan 00 untuk membatalkan)\n");
            }
          } while(temp_id < 0 && !temp_str.equals("00"));

          if(temp_id >= 0) {
            System.out.print("Berhasil menghapus produk \"" + cat_foods.get(temp_id).getName() + "\"!\n");
            cat_foods.remove(temp_id);
          }
        }
      } else if(choice.equals("5")) {
        // Cari data spesifik. Pencarian dibuat berdasarkan atribut sku atau nama produk
        ArrayList<CatFood> temp_cat_foods = new ArrayList<>();
        String temp_str = "";

        System.out.print("Masukkan kata kunci pencarian : ");
        temp_str = scanner.nextLine().toLowerCase();

        // Filter vektor, pastikan hanya produk yang mengandung kata kunci pada SKU atau nama produknya yang 
        // ditampilkan. SKU serta nama produk dan kata kunci diubah ke lowercase sehingga pencarian menjadi
        // case-insensitive
        for(int i = 0; i < cat_foods.size(); i++) {
          if(cat_foods.get(i).getSKU().toLowerCase().contains(temp_str) ||
              cat_foods.get(i).getName().toLowerCase().contains(temp_str)) {
            temp_cat_foods.add(cat_foods.get(i));
          }
        }

        printCatFoods(temp_cat_foods);
      } else if(!choice.equals("0")) {
        System.out.print("Tidak ada opsi '" + choice + "'!");
      }
    } while(!choice.equals("0"));

    scanner.close();
  }
}