// Helper method to convert a string to lowercase
class StringUtils {
  public static String strToLower(String str) {
    if(str == null) return "";
    return str.toLowerCase();
  }
}

public class CatFood extends PetFood {
  private boolean is_wet, is_prescription_diet, is_for_kitten; // Apakah makanan basah? Apakah perlu resep? Apakah untuk anak kucing?

  public CatFood() {}

  public CatFood(String s, String n, String f, int p, int y, int m, int d, int w, String iw, String ipd, String ifk) {
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

  public int setIsWet(String iw) {
    if(iw.toLowerCase().equals("y")) {
      is_wet = true;
      return 0;
    } else if(iw.toLowerCase().equals("n")) {
      is_wet = false;
      return 0;
    }

    System.out.println("Hanya bisa 'y' untuk ya atau 'n' untuk tidak!");
    return -1;
  }

  public boolean getIsWet() {
    return is_wet;
  }

  public int setIsPrescriptionDiet(String ipd) {
    if(ipd.toLowerCase().equals("y")) {
      is_prescription_diet = true;
      return 0;
    } else if(ipd.toLowerCase().equals("n")) {
      is_prescription_diet = false;
      return 0;
    }

    System.out.println("Hanya bisa 'y' untuk ya atau 'n' untuk tidak!");
    return -1;
  }

  public boolean getIsPrescriptionDiet() {
    return is_prescription_diet;
  }

  public int setIsForKitten(String ifk) {
    if(ifk.toLowerCase().equals("y")) {
      is_for_kitten = true;
      return 0;
    } else if(ifk.toLowerCase().equals("n")) {
      is_for_kitten = false;
      return 0;
    }

    System.out.println("Hanya bisa 'y' untuk ya atau 'n' untuk tidak!");
    return -1;
  }

  public boolean getIsForKitten() {
    return is_for_kitten;
  }
}