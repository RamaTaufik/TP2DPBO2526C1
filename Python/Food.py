class Food:
  def __init__(self, n: str = "", f: str = "", p: int = -1):
    # Nama produk, Rasa, Harga
    self.__name = ""
    self.__flavor = ""
    self.__price = 0

    if n != "":
      self.set_name(n)
    if f != "":
      self.set_flavor(f)
    if p > 0:
      self.set_price(p)

  def set_name(self, n: str):
    if n == "":
      print("Nama tidak bisa kosong!")
      return -1

    self.__name = n
    return 0
  def get_name(self) -> str:
    return self.__name

  def set_flavor(self, f: str):
    if f == "":
      self.__flavor = "-"
    else:
      self.__flavor = f
  def get_flavor(self) -> str:
    return self.__flavor

  def set_price(self, p: int):
    if p < 0:
      print("Harga harus bilangan bulat positif!")
      return -1

    self.__price = p
    return 0
  def get_price(self):
    return self.__price