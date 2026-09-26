from Food import Food

class PetFood(Food):
  def __init__(
    self,
    s: str = "",
    n: str = "",
    f: str = "",
    p: int = -1,
    y: int = -1,
    m: int = -1,
    d: int = -1,
    w: int = -1,
  ):
    super().__init__(n, f, p)

    self.__sku = ""
    self.__expiry_y = 0
    self.__expiry_m = 0
    self.__expiry_d = 0
    self.__weight = 0

    if s != "":
      self.set_sku(s)
    if y > 0:
      self.set_expiry_y(y)
    if m > 0:
      self.set_expiry_m(m)
    if d > 0:
      self.set_expiry_d(d)
    if w > 0:
      self.set_weight(w)

  def set_sku(self, s: str):
    if s == "":
      print("SKU tidak bisa kosong!")
      return -1

    self.__sku = s
    return 0
  def get_sku(self):
    return self.__sku

  def set_expiry_y(self, y: int):
    if y < 0:
      print("Tahun kadaluarsa harus bilangan bulat positif!")
      return -1

    self.__expiry_y = y
    return 0
  def get_expiry_y(self):
    return self.__expiry_y

  def set_expiry_m(self, m: int):
    if m < 1 or m > 12:
      print("Bulan kadaluarsa harus antara 1 dan 12!")
      return -1

    self.__expiry_m = m
    return 0
  def get_expiry_m(self):
    return self.__expiry_m

  def set_expiry_d(self, d: int):
    if d < 1 or d > 31:
      print("Hari kadaluarsa harus antara 1 dan 31!")
      return -1

    self.__expiry_d = d
    return 0
  def get_expiry_d(self):
    return self.__expiry_d

  def set_weight(self, w: int):
    if w < 0:
      print("Berat harus bilangan bulat positif!")
      return -1

    self.__weight = w
    return 0
  def get_weight(self):
    return self.__weight