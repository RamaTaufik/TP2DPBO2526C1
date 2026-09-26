from PetFood import PetFood

class CatFood(PetFood):
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
    iw: str = "",
    ipd: str = "",
    ifk: str = "",
  ):
    super().__init__(s, n, f, p, y, m, d, w)

    self.__is_wet = False
    self.__is_prescription_diet = False
    self.__is_for_kitten = False

    if iw != "":
      self.set_is_wet(iw)
    if ipd != "":
      self.set_is_prescription_diet(ipd)
    if ifk != "":
      self.set_is_for_kitten(ifk)

  def set_is_wet(self, iw: str):
    if iw.lower() == "y":
      self.__is_wet = True
      return 0
    elif iw.lower() == "n":
      self.__is_wet = False
      return 0

    print("Hanya bisa 'y' untuk ya atau 'n' untuk tidak!")
    return -1
  def get_is_wet(self):
    return self.__is_wet

  def set_is_prescription_diet(self, ipd: str):
    if ipd.lower() == "y":
      self.__is_prescription_diet = True
      return 0
    elif ipd.lower() == "n":
      self.__is_prescription_diet = False
      return 0

    print("Hanya bisa 'y' untuk ya atau 'n' untuk tidak!")
    return -1
  def get_is_prescription_diet(self):
    return self.__is_prescription_diet

  def set_is_for_kitten(self, ifk: str):
    if ifk.lower() == "y":
      self.__is_for_kitten = True
      return 0
    elif ifk.lower() == "n":
      self.__is_for_kitten = False
      return 0

    print("Hanya bisa 'y' untuk ya atau 'n' untuk tidak!")
    return -1
  def get_is_for_kitten(self):
    return self.__is_for_kitten