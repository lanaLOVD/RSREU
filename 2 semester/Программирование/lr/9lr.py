def menu():
    print()
    print('  МЕНЮ:  '.center(50, "*"))
    print('1. Просмотр всех записей в базе данных')
    print('2. Добавление  N  записей')
    print('3. Удаление записи по ФИО')
    print('4. Поиск необходимой информации')
    print('5. Определение победителей')
    print('6. Завершение работы с базой данных\n')
    num = int(input('Выберите пункт меню для продолжения: '))
    return num
# ФИО: [100м, 1км, длина, высота]
data = {
    "Шарапов Василий Генадьевич": [11.2, 165.3, 6.5, 1.8],
    "Кузьмин Иннокентий Васильевич": [10.9, 160.1, 6.9, 1.7],
    "Добрынин Фёдор Юрьевич": [11.0, 158.2, 6.2, 1.85],
    "Козлова Марина Ивановна": [11.3, 170.0, 6.8, 1.9]
}
def show_all():
    print("\n|{:<30}|{:^12}|{:^12}|{:^14}|{:^14}|".format("ФИО", "100м", "1км", "длина", "высота"))
    print("-" * 84)
    for name, results in data.items():
        print("|{:<30}|{:^12}|{:^12}|{:^14}|{:^14}|".format(name, *results))

def add_records():
    n = int(input("Сколько новых записей добавить? "))
    for _ in range(n):
        fio = input("Введите ФИО спортсмена: ")
        r100 = float(input("Результат на 100м: "))
        r1km = float(input("Результат на 1км: "))
        long_jump = float(input("Прыжок в длину: "))
        high_jump = float(input("Прыжок в высоту: "))
        data[fio] = [r100, r1km, long_jump, high_jump]
def delete_record():
    fio = input("Введите ФИО для удаления: ")
    if fio in data:
        del data[fio]
        print("Запись удалена.")
    else:
        print("Нет записи с таким ФИО.")
def search_info():
    query = input("Введите фамилию для поиска: ").lower()
    found = False
    for name in data:
        if query in name.lower():
            print(f"{name} — {data[name]}")
            found = True
    if not found:
        print("Записей не найдено.")
def show_winners():
    if not data:
        print("База данных пуста.")
        return
    print("\nПобедители по каждому виду:")
    best_100m = min(data, key=lambda x: data[x][0])
    best_1km = min(data, key=lambda x: data[x][1])
    best_long = max(data, key=lambda x: data[x][2])
    best_high = max(data, key=lambda x: data[x][3])
    print(f"100 м: {best_100m}")
    print(f"1 км: {best_1km}")
    print(f"Прыжок в длину: {best_long}")
    print(f"Прыжок в высоту: {best_high}")
    print("\nОбщий список победителей:")
    for name in set([best_100m, best_1km, best_long, best_high]):
        print("-", name)
# Основная программа
num = 0
while num != 6:
    num = menu()
    while num not in range(1, 7):
        num = int(input('Повторите выбор пункта меню: '))
    if num == 1:
        show_all()
    elif num == 2:
        add_records()
    elif num == 3:
        delete_record()
    elif num == 4:
        search_info()
    elif num == 5:
        show_winners()
    elif num == 6:
        print("Работа с программой завершена.")
