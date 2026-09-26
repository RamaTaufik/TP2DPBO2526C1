public class Food {
  private String name, flavor; // Nama produk, Rasa
  private int price; // Harga

  public Food() {}

  public Food(String n, String f, int p) {
    setName(n);
    setFlavor(f);
    setPrice(p);
  }

  public int setName(String n) {
    if(n == null || n.isEmpty()) {
      System.out.println("Nama tidak bisa kosong!");
      return -1;
    }

    name = n;
    return 0;
  }
  public String getName() {
    return name;
  }

  public void setFlavor(String f) {
    if(f == null || f.isEmpty()) {
      flavor = "-";
    } else {
      flavor = f;
    }
  }
  public String getFlavor() {
    return flavor;
  }

  public int setPrice(int p) {
    if(p < 0) {
      System.out.println("Harga harus bilangan bulat positif!");
      return -1;
    }

    price = p;
    return 0;
  }
  public int getPrice() {
    return price;
  }
}