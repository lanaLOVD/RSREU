class Photos:
    """Класс, представляющий фотографию"""

    def __init__(self, chromaticity="цветная", size="1920x1080", photo_type="JPEG"):
        """
        Конструктор класса Photos
        :param chromaticity: цветность (цветная, черно-белая, сепия и т.д.)
        :param size: разрешение в формате "ширинаxвысота"
        :param photo_type: тип файла (JPEG, PNG, TIFF и т.д.)
        """
        self.__chromaticity = chromaticity
        self.__size = size
        self.__type = photo_type

    # Геттеры (получение значений)
    def get_chromaticity(self):
        """Возвращает цветность фотографии"""
        return self.__chromaticity

    def get_size(self):
        """Возвращает размер фотографии"""
        return self.__size

    def get_type(self):
        """Возвращает тип файла фотографии"""
        return self.__type

    # Сеттеры (установка значений с проверкой)
    def set_chromaticity(self, chromaticity):
        """
        Устанавливает цветность фотографии
        :param chromaticity: цветность (строка)
        """
        if isinstance(chromaticity, str) and chromaticity.strip():
            self.__chromaticity = chromaticity.strip()
        else:
            raise ValueError("Цветность должна быть непустой строкой")

    def set_size(self, size):
        """
        Устанавливает размер фотографии
        :param size: размер в формате "ширинаxвысота" (например, 1920x1080)
        """
        if isinstance(size, str) and "x" in size and len(size.split("x")) == 2:
            try:
                w, h = size.split("x")
                int(w)
                int(h)
                self.__size = size
            except ValueError:
                raise ValueError("Размер должен содержать числа, например: 1920x1080")
        else:
            raise ValueError("Размер должен быть в формате 'ширинаxвысота', например: 1920x1080")

    def set_type(self, photo_type):
        """
        Устанавливает тип файла фотографии
        :param photo_type: тип файла (JPEG, PNG, GIF и т.д.)
        """
        valid_types = ["JPEG", "PNG", "GIF", "TIFF", "BMP", "WEBP"]
        if photo_type.upper() in valid_types:
            self.__type = photo_type.upper()
        else:
            raise ValueError(f"Недопустимый тип файла. Допустимые: {valid_types}")

    def display_info(self):
        """Выводит информацию о фотографии (для удобного просмотра)"""
        print(f"Фотография: цветность={self.__chromaticity}, размер={self.__size}, тип={self.__type}")


# Демонстрация работы класса
if __name__ == "__main__":
    # Создаем пять экземпляров класса Photos с разными значениями
    photo1 = Photos()
    photo2 = Photos("черно-белая", "1024x768", "PNG")
    photo3 = Photos("сепия", "2048x1536", "JPEG")
    photo4 = Photos("цветная", "3840x2160", "TIFF")
    photo5 = Photos("монохромная", "800x600", "GIF")

    # Изменяем значения через сеттеры для демонстрации
    photo1.set_chromaticity("цветная")
    photo1.set_size("1280x720")
    photo1.set_type("WEBP")

    photo2.set_chromaticity("сепия")

    # Выводим информацию о каждом экземпляре
    print("=== Информация о фотографиях ===")
    photo1.display_info()
    photo2.display_info()
    photo3.display_info()
    photo4.display_info()
    photo5.display_info()

    print("\n=== Проверка работы геттеров ===")
    print(f"photo1: цветность = {photo1.get_chromaticity()}, размер = {photo1.get_size()}, тип = {photo1.get_type()}")
    print(f"photo3: цветность = {photo3.get_chromaticity()}, размер = {photo3.get_size()}, тип = {photo3.get_type()}")

    # Попытка установить некорректное значение (будет выброшено исключение)
    print("\n=== Проверка защиты атрибутов ===")
    try:
        photo3.set_size("abc")
    except ValueError as e:
        print(f"Ошибка при установке размера: {e}")

    try:
        photo4.set_type("RAW")
    except ValueError as e:
        print(f"Ошибка при установке типа: {e}")