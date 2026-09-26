from CatFood import CatFood

# Panjang maksimum dari setiap atribut milik semua objek. Secara default, maksimum nya di-set terlebih dahulu pada
# panjang nama masing-masing atribut (SKU | Nama | Rasa | Harga | Kadaluarsa | Berat | Basah? | Butuh resep? | Khusus anak?)
max_lens = [3, 4, 4, 5, 10, 5, 6, 12, 12]

# Fungsi untuk menghitung jumlah digit suatu integer positif
def intlen(num: int) -> int:
  if num < 10:
    return 1
  return intlen(num // 10) + 1

# Fungsi untuk merubah string menjadi integer
def cstrtoint(string: str) -> int:
  num = 0

  for char in string:
    if char < '0' or char > '9':
      # Karena semua atribut integer dipastikan hanya bilangan bulat positif, maka hanya digit berupa angka 0 sampai 9
      # yang akan diterima, sehingga fungsi ini juga sekaligus menjadi filter input
      return -1
    else:
      num = (num * 10) + (ord(char) - ord('0'))

  return num

# Fungsi untuk mencari index dari item suatu array objek berdasarkan SKU (ID)
def findBySKU(src: list[CatFood], s: str) -> int:
  i = 0

  while i < len(src):
    if src[i].get_sku() == s:
      return i
    i += 1

  return -1

# Fungsi untuk mempersingkat penulisan tanggal
def formatdate(src: CatFood) -> str:
  formatted = str(src.get_expiry_y()) + '-'

  if src.get_expiry_m() < 10:
    formatted += '0'
  formatted += str(src.get_expiry_m()) + '-'

  if src.get_expiry_d() < 10:
    formatted += '0'
  formatted += str(src.get_expiry_d())

  return formatted

# Prosedur untuk meng-print karakter c sebanyak n
def printchar(n: int, c: str) -> None:
  print(c * n, end='')

# Prosedur untuk meng-print border pada tabel di CLI
def printborder() -> None:
  for i in range(9):
    print('+', end='')
    printchar(max_lens[i] + 2, '-')
  print('+')

# Prosedur untuk meng-print data film ke bentuk tabel
def printCatFoods(ms: list[CatFood]) -> None:
  # Print header tabel
  printborder()
  print('| SKU', end='')
  printchar(max_lens[0] - 3, ' ')
  print(' | Nama', end='')
  printchar(max_lens[1] - 4, ' ')
  print(' | Rasa', end='')
  printchar(max_lens[2] - 4, ' ')
  print(' | Harga', end='')
  printchar(max_lens[3] - 5, ' ')
  print(' | Kadaluarsa', end='')
  printchar(max_lens[4] - 10, ' ')
  print(' | Berat', end='')
  printchar(max_lens[5] - 5, ' ')
  print(' | Basah?', end='')
  printchar(max_lens[6] - 6, ' ')
  print(' | Butuh resep?', end='')
  printchar(max_lens[7] - 12, ' ')
  print(' | Khusus anak?', end='')
  printchar(max_lens[8] - 12, ' ')
  print(' |')
  printborder()

  for i in range(len(ms)):
    # Print masing-masing data
    print('| ' + ms[i].get_sku(), end='')
    printchar(max_lens[0] - len(ms[i].get_sku()), ' ')

    print(' | ' + ms[i].get_name(), end='')
    printchar(max_lens[1] - len(ms[i].get_name()), ' ')

    print(' | ' + ms[i].get_flavor(), end='')
    printchar(max_lens[2] - len(ms[i].get_flavor()), ' ')

    print(' | Rp', end='')
    printchar(max_lens[3] - 2 - intlen(ms[i].get_price()), ' ') # Dikurangi dua karena ada penambahan 'Rp'
    formatted = formatdate(ms[i])
    print(f'{ms[i].get_price()} | {formatted}', end='')
    printchar(max_lens[4] - len(formatted), ' ')

    print(' | ', end='')
    printchar(max_lens[5] - 1 - intlen(ms[i].get_weight()), ' ') # Dikurangi dua karena ada penambahan 'Rp'
    print(f'{ms[i].get_weight()}g | ' + ('Ya' if ms[i].get_is_wet() else 'Tidak'), end='',)
    printchar(max_lens[6] - (2 if ms[i].get_is_wet() else 5), ' ')

    print(' | ' + ('Ya' if ms[i].get_is_prescription_diet() else 'Tidak'), end='')
    printchar(max_lens[7] - (2 if ms[i].get_is_prescription_diet() else 5), ' ')

    print(' | ' + ('Ya' if ms[i].get_is_for_kitten() else 'Tidak'), end='')
    printchar(max_lens[8] - (2 if ms[i].get_is_for_kitten() else 5), ' ')
    print(' |')

    printborder()

def main():
  cat_foods: list[CatFood] = []  # Vector data film
  choice = '0'  # Variabel untuk input opsi

  # Data dummy
  cat_foods.append(
    CatFood(
      'SKU001',
      'Whiskas Ocean Fish',
      'Tuna & Salmon',
      45000,
      2026,
      12,
      31,
      400,
      'y',
      'n',
      'n',
    )
  )
  cat_foods.append(
    CatFood(
      'SKU002',
      'Royal Canin Mother & Babycat',
      'Chicken',
      120000,
      2027,
      5,
      15,
      1000,
      'n',
      'n',
      'y',
    )
  )
  cat_foods.append(
    CatFood(
      'SKU003',
      "Hill's Prescription Diet i/d",
      'Turkey',
      250000,
      2026,
      9,
      20,
      1500,
      'n',
      'y',
      'n',
    )
  )
  cat_foods.append(
    CatFood(
      'SKU004',
      'Me-O Creamy Treat',
      'Salmon',
      28000,
      2025,
      11,
      10,
      60,
      'y',
      'n',
      'n',
    )
  )
  cat_foods.append(
    CatFood(
      'SKU005',
      'Pro Plan Adult Optirenal',
      'Salmon & Rice',
      185000,
      2027,
      2,
      28,
      2500,
      'n',
      'n',
      'n',
    )
  )

  # Perubahan panjang maksimum setiap atribut setelah penambahan data dummy
  max_lens[0] = 6
  max_lens[1] = 28
  max_lens[2] = 13
  max_lens[3] = 8

  print('   ____  __ __  _____  _____  _  __    ____  _____  __  ____  __   __  ____    _____')
  print('  / __/ / // / / // / / // / | |/ /   / __/ / // / / / / __/ /  | / / / /| |  /  __/')
  print(' / __/ / // / / //_/ / //_/  |   /   / __/ / //_/ / / / __/ / /||/ / / /_/ / /__  /')
  print('/_/   /____/ /_/|_| /_/|_|   /__/   /_/   /_/|_| /_/ /___/ /_/ |__/ /_____/ /____/')
  print('\n> FURRY FRIENDS DATA CENTER <')

  # Karena pada Python tidak ada do-while(), Maka digunakan kombinasi while() dan break
  while True:
    # Jika terjadi kesalahan dalam input opsi, tidak perlu print ulang pilihan opsi agar tidak memenuhi layar
    if 0 <= cstrtoint(choice) <= 5:
      print('\n1. Lihat data produk')
      print('2. Tambah data produk baru')
      print('3. Ubah data produk')
      print('4. Hapus data produk')
      print('5. Cari produk berdasarkan SKU / nama produk')
      print('0. Keluar')

    choice = input('\nPilih opsi: ').strip()

    if choice == '1':
      # Lihat semua data
      printCatFoods(cat_foods)
    elif choice == '2':
      # Tambah data
      res = 0
      temp_c_food = CatFood()

      while True:
        temp_str = input('Masukkan SKU produk             : ')

        # Pastikan SKU unik dan tidak duplikat
        if findBySKU(cat_foods, temp_str) >= 0:
          print('SKU sudah ada!')
          res = -1
        else:
          res = temp_c_food.set_sku(temp_str)
          # Cek panjang maksimum atribut 'SKU'
          if res == 0 and max_lens[0] < len(temp_c_food.get_sku()):
            max_lens[0] = len(temp_c_food.get_sku())

        if res == 0:
          break

      while True:
        temp_str = input('Masukkan nama/merk produk       : ')
        res = temp_c_food.set_name(temp_str)
        # Cek panjang maksimum atribut 'Nama'
        if res == 0 and max_lens[1] < len(temp_c_food.get_name()):
          max_lens[1] = len(temp_c_food.get_name())

        if res == 0:
          break

      temp_str = input('Masukkan rasa produk            : ')
      temp_c_food.set_flavor(temp_str)
      # Cek panjang maksimum atribut 'Rasa produk'
      if max_lens[2] < len(temp_c_food.get_flavor()):
        max_lens[2] = len(temp_c_food.get_flavor())

      while True:
        temp_str = input('Masukkan harga                  : Rp')
        temp_int = cstrtoint(temp_str)
        res = temp_c_food.set_price(temp_int)
        # Cek panjang maksimum atribut 'Harga'. +2 karena ada 'Rp'
        if res == 0 and max_lens[3] < intlen(temp_c_food.get_price()) + 2:
          max_lens[3] = intlen(temp_c_food.get_price()) + 2

        if res == 0:
          break

      while True:
        temp_str = input('Masukkan tahun kadaluarsa       : ')
        temp_int = cstrtoint(temp_str)
        res = temp_c_food.set_expiry_y(temp_int)
        # Cek panjang maksimum atribut 'Tahun kadaluarsa'. +6 karena panjang nilai bulan dan tanggal tetap 2 digit
        # masing-masing (-mm-dd)
        if res == 0 and max_lens[4] < intlen(temp_c_food.get_expiry_y()) + 6:
          max_lens[4] = intlen(temp_c_food.get_expiry_y()) + 6

        if res == 0:
          break

      while True:
        temp_str = input('Masukkan bulan kadaluarsa       : ')
        temp_int = cstrtoint(temp_str)
        res = temp_c_food.set_expiry_m(temp_int)
        # Tidak seperti tahun, nilai bulan dibatasi hanya 1-12 sehingga tidak perlu cek panjang digit
        if res == 0:
          break

      while True:
        temp_str = input('Masukkan tanggal kadaluarsa : ')
        temp_int = cstrtoint(temp_str)
        res = temp_c_food.set_expiry_d(temp_int)
        # Sama seperti bulan, nilai tanggal dibatasi hanya 1-31 sehingga tidak perlu cek panjang digit
        if res == 0:
          break

      while True:
        temp_str = input('Masukkan berat (gram)           : ')
        temp_int = cstrtoint(temp_str)
        res = temp_c_food.set_weight(temp_int)
        # Cek panjang maksimum atribut 'Berat'. +1 karena ada 'g'
        if res == 0 and max_lens[5] < intlen(temp_c_food.get_weight()) + 1:
          max_lens[5] = intlen(temp_c_food.get_weight()) + 1

        if res == 0:
          break

      while True:
        temp_str = input('Apakah makanan basah (y/n)      ? ')
        res = temp_c_food.set_is_wet(temp_str)
        # Karena atribut bool hanya memiliki dua nilai, panjang atribut tidak akan berubah banyak
        if res == 0:
          break

      while True:
        temp_str = input('Apakah perlu resep (y/n)        ? ')
        res = temp_c_food.set_is_prescription_diet(temp_str)
        if res == 0:
          break

      while True:
        temp_str = input('Apakah khusus anak kucing (y/n) ? ')
        res = temp_c_food.set_is_for_kitten(temp_str)
        if res == 0:
          break

      cat_foods.append(temp_c_food)

    elif choice == '3':
      # Ubah data
      if len(cat_foods) <= 0:
        print('Tidak ada data produk untuk diubah!', end='')
        choice = '-1'
      else:
        temp_str = ''
        temp_id = -2

        # Blok kode do-while() disini memastikan SKU yang dimasukkan benar-benar ada
        while True:
          temp_str = input('Masukkan SKU : ')
          temp_id = findBySKU(cat_foods, temp_str)

          if temp_id < 0 and temp_str != '00':
            print('SKU tidak ditemukan! (masukkan 00 untuk membatalkan)')

          if temp_id >= 0 or temp_str == '00':
            break

        if temp_id >= 0:
          temp_choice = '0'

          while True:
            if 0 <= cstrtoint(temp_choice) <= 9:
              print(f'\n1. SKU                : {cat_foods[temp_id].get_sku()}')
              print(f'2. Nama               : {cat_foods[temp_id].get_name()}')
              print(f'3. Rasa               : {cat_foods[temp_id].get_flavor()}')
              print(f'4. Harga              : Rp{cat_foods[temp_id].get_price()}')
              print('5. Tanggal Kadaluarsa :' f' {formatdate(cat_foods[temp_id])}')
              print(f'6. Berat              : {cat_foods[temp_id].get_weight()}g')
              print('7. Makanan basah      ? ' + ('Ya' if cat_foods[temp_id].get_is_wet() else 'Tidak'))
              print('8. Butuh Resep        ? ' + ('Ya' if cat_foods[temp_id].get_is_prescription_diet() else 'Tidak'))
              print('9. Khusus anak kucing ? ' + ('Ya' if cat_foods[temp_id].get_is_for_kitten() else 'Tidak'))
              print('0. Kembali')

            temp_choice = input('\nMasukkan nomor atribut untuk diubah : ').strip()

            # Input untuk merubah data kurang lebih sama dengan menambah data baru
            if temp_choice == '1':
              while True:
                temp_str = input('Masukkan SKU baru : ')

                if(findBySKU(cat_foods, temp_str) >= 0 and findBySKU(cat_foods, temp_str) == temp_id):
                  print('SKU sudah ada!')
                  res = -1
                else:
                  res = cat_foods[temp_id].set_sku(temp_str)
                  if res == 0 and max_lens[0] < len(cat_foods[temp_id].get_sku()):
                    max_lens[0] = len(cat_foods[temp_id].get_sku())

                if res == 0:
                  break
            elif temp_choice == '2':
              while True:
                temp_str = input('Masukkan nama/merk produk : ')
                res = cat_foods[temp_id].set_name(temp_str)
                if res == 0 and max_lens[1] < len(cat_foods[temp_id].get_name()):
                  max_lens[1] = len(cat_foods[temp_id].get_name())

                if res == 0:
                  break
            elif temp_choice == '3':
              temp_str = input('Masukkan rasa produk : ')
              cat_foods[temp_id].set_flavor(temp_str)
              if max_lens[2] < len(cat_foods[temp_id].get_flavor()):
                max_lens[2] = len(cat_foods[temp_id].get_flavor())
            elif temp_choice == '4':
              while True:
                temp_str = input('Masukkan harga : Rp')
                temp_int = cstrtoint(temp_str)
                res = cat_foods[temp_id].set_price(temp_int)
                if(res == 0 and max_lens[3] < intlen(cat_foods[temp_id].get_price()) + 2):
                  max_lens[3] = intlen(cat_foods[temp_id].get_price()) + 2

                if res == 0:
                  break
            elif temp_choice == '5':
              while True:
                temp_str = input('Masukkan tahun kadaluarsa baru : ')
                temp_int = cstrtoint(temp_str)
                res = cat_foods[temp_id].set_expiry_y(temp_int)
                if(res == 0 and max_lens[4] < intlen(cat_foods[temp_id].get_expiry_y()) + 6):
                  max_lens[4] = intlen(cat_foods[temp_id].get_expiry_y()) + 6

                if res == 0:
                  break

              while True:
                temp_str = input('Masukkan bulan kadaluarsa baru : ')
                temp_int = cstrtoint(temp_str)
                res = cat_foods[temp_id].set_expiry_m(temp_int)
                if res == 0:
                  break

              while True:
                temp_str = input('Masukkan tanggal kadaluarsa baru : ')
                temp_int = cstrtoint(temp_str)
                res = cat_foods[temp_id].set_expiry_d(temp_int)
                if res == 0:
                  break
            elif temp_choice == '6':
              while True:
                temp_str = input('Masukkan berat baru : ')
                temp_int = cstrtoint(temp_str)
                res = cat_foods[temp_id].set_weight(temp_int)
                if(res == 0 and max_lens[5] < intlen(cat_foods[temp_id].get_weight()) + 1):
                  max_lens[5] = intlen(cat_foods[temp_id].get_weight()) + 1

                if res == 0:
                  break
            elif temp_choice == '7':
              while True:
                temp_str = input('Apakah makanan basah (y/n) ? ')
                res = cat_foods[temp_id].set_is_wet(temp_str)
                if res == 0:
                  break
            elif temp_choice == '8':
              while True:
                temp_str = input('Apakah perlu resep (y/n) ? ')
                res = cat_foods[temp_id].set_is_prescription_diet(temp_str)
                if res == 0:
                  break
            elif temp_choice == '9':
              while True:
                temp_str = input('Apakah khusus anak kucing (y/n) ? ')
                res = cat_foods[temp_id].set_is_for_kitten(temp_str)
                if res == 0:
                  break
            elif temp_choice != '0':
              print(f"Tidak ada opsi atribut '{temp_choice}'!", end='')

            if temp_choice == '0':
              break

    elif choice == '4':
      # Hapus data produk
      if len(cat_foods) <= 0:
        print('Tidak ada data produk untuk dihapus!', end='')
        choice = '-1'
      else:
        temp_str = ''
        temp_id = -2

        # Sama seperti di blok kode perubahan data, ada blok kode do-while() di awal untuk memastikan ID yang
        # dimasukkan benar-benar ada
        while True:
          temp_str = input('Masukkan SKU : ')
          temp_id = findBySKU(cat_foods, temp_str)

          if temp_id < 0 and temp_str != '00':
            print('SKU tidak ditemukan! (masukkan 00 untuk membatalkan)')

          if temp_id >= 0 or temp_str == '00':
            break

        if temp_id >= 0:
          print(f'Berhasil menghapus produk "{cat_foods[temp_id].get_name()}"!')
          cat_foods.pop(temp_id)

    elif choice == '5':
      # Cari data spesifik. Pencarian dibuat berdasarkan atribut sku atau nama produk
      temp_cat_foods: list[CatFood] = []

      temp_str = input('Masukkan kata kunci pencarian : ').lower()

      # Filter array, pastikan hanya produk yang mengandung kata kunci pada SKU atau nama produknya yang
      # ditampilkan. SKU serta nama produk dan kata kunci diubah ke lowercase sehingga pencarian menjadi
      # case-insensitive
      for item in cat_foods:
        if(temp_str in item.get_sku().lower() or temp_str in item.get_name().lower()):
          temp_cat_foods.append(item)

      printCatFoods(temp_cat_foods)

    elif choice != '0':
      print(f"Tidak ada opsi '{choice}'!", end='')

    if choice == '0':
      break


if __name__ == '__main__':
  main()