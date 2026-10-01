import turtle
# Настройка экрана
screen = turtle.Screen()
screen.bgcolor("white")
# Создание черепашки
t = turtle.Turtle()
t.speed(3)  # Устанавливаем скорость для наглядности
# Функция для рисования дома
def draw_house(x, y, body_color, roof_color):
    t.penup()
    t.goto(x, y)
    t.pendown()
    # Рисуем основу дома (прямоугольник)
    t.fillcolor(body_color)
    t.begin_fill()
    for _ in range(2):
        t.forward(80)  # Ширина дома
        t.left(90)
        t.forward(60)  # Высота дома
        t.left(90)
    t.end_fill()
    # Рисуем крышу (треугольник)
    t.fillcolor(roof_color)
    t.begin_fill()
    t.goto(x, y + 60)  # Переходим к верхней точке основы
    t.goto(x + 40, y + 100)  # Вершина крыши
    t.goto(x + 80, y + 60)  # Возвращаемся к правой точке основы
    t.goto(x, y + 60)  # Замыкаем треугольник
    t.end_fill()
    # Рисуем дымоход
    t.fillcolor("black")
    t.begin_fill()
    t.goto(x + 60, y + 70)  # Начало дымохода
    t.goto(x + 60, y + 90)
    t.goto(x + 70, y + 90)
    t.goto(x + 70, y + 70)
    t.goto(x + 60, y + 70)
    t.end_fill()
    # Рисуем окно
    t.penup()
    t.goto(x + 50, y + 30)
    t.pendown()
    t.fillcolor("white")
    t.begin_fill()
    for _ in range(4):
        t.forward(20)
        t.left(90)
    t.end_fill()
    # Рисуем дверь (для левого дома)
    if x == -100:  # Условие для левого дома
        t.penup()
        t.goto(x + 10, y)
        t.pendown()
        t.fillcolor("white")
        t.begin_fill()
        t.goto(x + 10, y + 30)
        t.goto(x + 30, y + 30)
        t.goto(x + 30, y)
        t.goto(x + 10, y)
        t.end_fill()
    else:  # Для правого дома рисуем второе окно
        t.penup()
        t.goto(x + 10, y + 30)
        t.pendown()
        t.fillcolor("white")
        t.begin_fill()
        for _ in range(4):
            t.forward(20)
            t.left(90)
        t.end_fill()
# Рисуем два дома с разными цветами
draw_house(-100, -50, "lightblue", "red")  # Левый дом
draw_house(0, -50, "lightgreen", "blue")  # Правый дом
# Скрываем черепашку
t.hideturtle()
# Оставляем окно открытым
screen.mainloop()
