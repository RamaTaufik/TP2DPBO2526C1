public class PetFood extends Food {
  private String sku; // SKU (Stock Keeping Unit, ID)
  private int expiry_y, expiry_m, expiry_d, weight; // Tanggal kadaluarsa, Berat (dalam gram)

  public PetFood() {}

  public PetFood(String s, String n, String f, int p, int y, int m, int d, int w) {
    setSKU(s);
    setName(n);
    setFlavor(f);
    setPrice(p);
    setExpiryY(y);
    setExpiryM(m);
    setExpiryD(d);
    setWeight(w);
  }

  public int setSKU(String s) {
    if(s == null || s.isEmpty()) {
      System.out.println("SKU tidak bisa kosong!");
      return -1;
    }

    sku = s;
    return 0;
  }
  public String getSKU() {
    return sku;
  }

  public int setExpiryY(int y) {
    if(y < 0) {
      System.out.println("Tahun kadaluarsa harus bilangan bulat positif!");
      return -1;
    }

    expiry_y = y;
    return 0;
  }
  public int getExpiryY() {
    return expiry_y;
  }

  public int setExpiryM(int m) {
    if(m < 1 || m > 12) {
      System.out.println("Bulan kadaluarsa harus antara 1 dan 12!");
      return -1;
    }

    expiry_m = m;
    return 0;
  }
  public int getExpiryM() {
    return expiry_m;
  }

  public int setExpiryD(int d) {
    if(d < 1 || d > 31) {
      System.out.println("Hari kadaluarsa harus antara 1 dan 31!");
      return -1;
    }

    expiry_d = d;
    return 0;
  }
  public int getExpiryD() {
    return expiry_d;
  }

  public int setWeight(int w) {
    if(w < 0) {
      System.out.println("Berat harus bilangan bulat positif!");
      return -1;
    }

    weight = w;
    return 0;
  }
  public int getWeight() {
    return weight;
  }
}