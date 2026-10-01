import matplotlib.pyplot as plt

# Константы
k = 9e9  # Н·м²/Кл²
R = 0.15  # м, радиус сферы
q = 2e-9  # Кл, заряд сферы

# Создаем массивы данных
r_points = []
E_points = []

# Внутри сферы (r < R) - поле равно 0
for i in range(50):
    r = i * R / 50
    r_points.append(r)
    E_points.append(0)

# ПРАВИЛЬНОЕ поведение на поверхности:
# Добавляем точку слева от поверхности
r_points.append(R - 0.0001)
E_points.append(0)

# Добавляем точку на поверхности
r_points.append(R)
E_surface = k * abs(q) / (R ** 2)
E_points.append(E_surface)

# Добавляем точку справа от поверхности
r_points.append(R + 0.0001)
E_points.append(E_surface)

# Вне сферы (r > R) - поле убывает как 1/r²
for i in range(1, 100):
    r = R + i * 0.01  # шаг 1 см
    E = k * abs(q) / (r ** 2)
    r_points.append(r)
    E_points.append(E)

# Создаем график
plt.figure(figsize=(12, 6))

# Основной график
plt.subplot(1, 2, 1)
plt.plot(r_points, E_points, 'b-', linewidth=2)
plt.axvline(x=R, color='red', linestyle='--', alpha=0.7, label=f'R = {R} м')
plt.xlabel('Расстояние r (м)')
plt.ylabel('Напряженность E (В/м)')
plt.title('E(r) для заряженной металлической сферы')
plt.grid(True, alpha=0.3)
plt.legend()

# Увеличенный вид области вокруг поверхности
plt.subplot(1, 2, 2)
plt.plot(r_points, E_points, 'b-', linewidth=2)
plt.axvline(x=R, color='red', linestyle='--', alpha=0.7, label=f'R = {R} м')
plt.xlabel('Расстояние r (м)')
plt.ylabel('Напряженность E (В/м)')
plt.title('Область вокруг поверхности (увеличенно)')
plt.grid(True, alpha=0.3)
plt.legend()
plt.xlim(R - 0.02, R + 0.02)  # Увеличиваем область вокруг поверхности

plt.tight_layout()
plt.show()

# Вывод ключевых значений
print("ФИЗИЧЕСКИЕ ВЕЛИЧИНЫ:")
print(f"Радиус сферы: R = {R} м")
print(f"Заряд: q = {q} Кл = 2 нКл")
print(f"Напряженность на поверхности: E(R) = {E_surface:.1f} В/м")
print()
print("ОСОБЕННОСТИ ГРАФИКА:")
print("1. Внутри сферы (r < R): E = 0")
print("2. На поверхности (r = R): E = kq/R²")
print("3. Вне сферы (r > R): E = kq/r²")