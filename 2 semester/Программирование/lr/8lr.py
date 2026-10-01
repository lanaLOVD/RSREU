def create_square_dict(start, end):
    """Создаёт словарь, где ключи - числа от start до end, а значения - их квадраты."""
    square_dict = {}
    for num in range(start, end + 1):
        square_dict[num] = num ** 2
    return square_dict
square_dict = create_square_dict(5, 15)
print("Словарь квадратов чисел:", square_dict)
