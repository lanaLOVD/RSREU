class Bakery:
    def __init__(self):
        self.products = []
    def add_product(self, product):
        self.products.append(product)
    def remove_product(self, product):
        self.products.remove(product)
    def display_products(self):
        for product in self.products:
            print(product.display())
class Product:
    def __init__(self, product_type, size, quantity, price):
        self.product_type = product_type
        self.size = size
        self.quantity = quantity
        self.price = price
    def display(self):
        return f"Тип: {self.product_type}, Размер: {self.size}, Количество: {self.quantity}, Цена: {self.price} рублей"
class Pastry(Product):
    def __init__(self, size, quantity, price, flavor):
        super().__init__("Кондитерское", size, quantity, price)
        self.flavor = flavor
    def display(self):
        return f"{super().display()}, Вкус: {self.flavor}"
class Bread(Product):
    def __init__(self, size, quantity, price, flour_type):
        super().__init__("Хлебопекарное", size, quantity, price)
        self.flour_type = flour_type
    def display(self):
        return f"{super().display()}, Тип муки: {self.flour_type}"
# Пример использования
if __name__ == "__main__":
    # Создаем пекарню
    bakery = Bakery()
    # Создаем несколько продуктов
    pastry1 = Pastry("Среднее", 6, 150, "Шоколадный")
    bread1 = Bread("Большое", 1, 100, "Пшеничная")
    # Добавляем продукты в пекарню
    bakery.add_product(pastry1)
    bakery.add_product(bread1)
    # Отображаем все продукты
    print("Продукты в пекарне:")
    bakery.display_products()
