import tkinter as tk
from tkinter import ttk, messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np


# ===================== ФУНКЦИИ УРАВНЕНИЯ =====================
def f(x):
    """Исходная функция: x^4 - x^2 + 5x - 10"""
    return x ** 4 - x ** 2 + 5 * x - 10


def df(x):
    """Производная: 4x^3 - 2x + 5"""
    return 4 * x ** 3 - 2 * x + 5


# ===================== МЕТОДЫ РЕШЕНИЯ =====================
def dihotomy(a, b, eps):
    """Метод дихотомии (половинного деления)"""
    steps = []
    iter_count = 1
    while (b - a) / 2 > eps:
        c = (a + b) / 2
        steps.append((iter_count, a, b, c, f(c)))
        if f(c) == 0:
            return c, steps
        elif f(a) * f(c) < 0:
            b = c
        else:
            a = c
        iter_count += 1
    return (a + b) / 2, steps


def chord(a, b, eps):
    """Метод хорд (пропорциональных частей)"""
    steps = []
    iter_count = 1
    x0, x1 = a, b
    while abs(x1 - x0) > eps:
        if f(x1) - f(x0) == 0:
            break
        x_new = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0))
        steps.append((iter_count, x0, x1, x_new, f(x_new)))
        x0, x1 = x1, x_new
        iter_count += 1
    return x1, steps


def newton(x0, eps):
    """Метод Ньютона (касательных)"""
    steps = []
    iter_count = 1
    while True:
        x_new = x0 - f(x0) / df(x0)
        steps.append((iter_count, x0, x_new, f(x_new)))
        if abs(x_new - x0) < eps:
            break
        x0 = x_new
        iter_count += 1
    return x_new, steps


def modified_newton(x0, eps):
    """Модифицированный метод Ньютона (с фиксированной производной)"""
    df0 = df(x0)
    steps = []
    iter_count = 1
    while True:
        x_new = x0 - f(x0) / df0
        steps.append((iter_count, x0, x_new, f(x_new)))
        if abs(x_new - x0) < eps:
            break
        x0 = x_new
        iter_count += 1
    return x_new, steps


def combined(a, b, eps):
    """Комбинированный метод: сначала метод хорд, потом метод Ньютона"""
    x_chord, steps_chord = chord(a, b, eps * 10)
    x_newton, steps_newton = newton(x_chord, eps)
    all_steps = steps_chord + steps_newton
    return x_newton, all_steps


def simple_iteration(x0, eps, lam=0.01):
    """Метод простых итераций"""
    steps = []
    iter_count = 1
    while True:
        x_new = x0 - lam * f(x0)
        steps.append((iter_count, x0, x_new, f(x_new)))
        if abs(x_new - x0) < eps:
            break
        x0 = x_new
        iter_count += 1
    return x_new, steps


# ===================== ОСНОВНОЕ ОКНО =====================
class RootFinderApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Решение уравнений с одной переменной - Вариант 6")
        self.root.geometry("1200x750")
        self.root.resizable(False, False)  # Запрещаем изменение размера окна

        # Переменные
        self.method_var = tk.StringVar(value="chord")
        self.eps_var = tk.StringVar(value="0.0001")
        self.a_var = tk.StringVar(value="1.0")
        self.b_var = tk.StringVar(value="2.0")
        self.x0_var = tk.StringVar(value="1.5")
        self.lam_var = tk.StringVar(value="0.01")

        self.create_widgets()
        self.plot_function()

    def create_widgets(self):
        # Верхняя панель с уравнением
        top_frame = ttk.Frame(self.root)
        top_frame.pack(fill=tk.X, padx=10, pady=5)

        ttk.Label(top_frame, text="Уравнение: x⁴ - x² + 5x - 10 = 0",
                  font=("Arial", 14, "bold")).pack()
        ttk.Label(top_frame, text="Найти положительный корень с точностью 0.0001",
                  font=("Arial", 11)).pack()

        # Основная горизонтальная панель
        main_panel = ttk.Frame(self.root)
        main_panel.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

        # Левая панель - график (фиксированный размер)
        left_frame = ttk.LabelFrame(main_panel, text="График функции", padding=5)
        left_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=False)
        left_frame.config(width=600, height=500)
        left_frame.pack_propagate(False)

        # График фиксированного размера
        self.fig, self.ax = plt.subplots(figsize=(6, 5), dpi=100)
        self.canvas = FigureCanvasTkAgg(self.fig, master=left_frame)
        self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

        # Правая панель - параметры и результаты
        right_frame = ttk.Frame(main_panel, width=500)
        right_frame.pack(side=tk.RIGHT, fill=tk.BOTH, padx=(10, 0), expand=True)
        right_frame.pack_propagate(False)

        # === Параметры решения ===
        params_frame = ttk.LabelFrame(right_frame, text="Параметры решения", padding=10)
        params_frame.pack(fill=tk.X, pady=(0, 10))

        # Выбор метода
        ttk.Label(params_frame, text="Выберите метод:", font=("Arial", 10)).pack(anchor=tk.W)

        methods = [
            ("Дихотомии", "dihotomy"),
            ("Хорд", "chord"),
            ("Ньютона", "newton"),
            ("Модифицированный Ньютона", "modified_newton"),
            ("Комбинированный", "combined"),
            ("Итерационный", "simple_iteration")
        ]

        for text, value in methods:
            ttk.Radiobutton(params_frame, text=text, variable=self.method_var,
                            value=value, command=self.update_input_fields).pack(anchor=tk.W, pady=2)

        ttk.Separator(params_frame).pack(fill=tk.X, pady=10)

        # Точность
        ttk.Label(params_frame, text="Точность (eps):", font=("Arial", 10)).pack(anchor=tk.W)
        ttk.Entry(params_frame, textvariable=self.eps_var, font=("Arial", 10)).pack(fill=tk.X, pady=(0, 10))

        # Динамические поля ввода
        self.input_frame = ttk.Frame(params_frame)
        self.input_frame.pack(fill=tk.X, pady=5)

        # Инициализация полей ввода
        self.update_input_fields()

        # === Результат ===
        result_frame = ttk.LabelFrame(right_frame, text="Результат", padding=10)
        result_frame.pack(fill=tk.X, pady=(0, 10))

        self.root_label = ttk.Label(result_frame, text="Корень: не найден",
                                    font=("Arial", 12, "bold"))
        self.root_label.pack(anchor=tk.W)

        self.iter_label = ttk.Label(result_frame, text="Итераций: 0", font=("Arial", 11))
        self.iter_label.pack(anchor=tk.W)

        # === Текстовое поле для этапов вычисления (БОЛЬШОЕ) ===
        steps_frame = ttk.LabelFrame(right_frame, text="Этапы вычисления", padding=10)
        steps_frame.pack(fill=tk.BOTH, expand=True)

        # Текстовое поле с прокруткой (КРУПНЫЙ ТЕКСТ)
        text_frame = ttk.Frame(steps_frame)
        text_frame.pack(fill=tk.BOTH, expand=True)

        scrollbar = ttk.Scrollbar(text_frame)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        self.steps_text = tk.Text(text_frame, wrap=tk.WORD,
                                  font=("Courier", 11),  # Крупный текст
                                  yscrollcommand=scrollbar.set,
                                  height=20,  # Больше строк
                                  width=50)  # Больше символов в строке
        scrollbar.config(command=self.steps_text.yview)
        self.steps_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.steps_text.insert(tk.END, "Нажмите 'Найти корень' для начала вычислений\n")

    def update_input_fields(self):
        """Обновляет поля ввода в зависимости от выбранного метода"""
        # Очищаем фрейм ввода
        for widget in self.input_frame.winfo_children():
            widget.destroy()

        method = self.method_var.get()

        # Для всех методов показываем интервал
        ttk.Label(self.input_frame, text="Начало интервала a:", font=("Arial", 10)).pack(anchor=tk.W)
        ttk.Entry(self.input_frame, textvariable=self.a_var, font=("Arial", 10)).pack(fill=tk.X, pady=(0, 5))

        ttk.Label(self.input_frame, text="Конец интервала b:", font=("Arial", 10)).pack(anchor=tk.W)
        ttk.Entry(self.input_frame, textvariable=self.b_var, font=("Arial", 10)).pack(fill=tk.X, pady=(0, 10))

        # Для методов Ньютона показываем начальное приближение
        if method in ["newton", "modified_newton", "simple_iteration"]:
            ttk.Label(self.input_frame, text="Начальное приближение x0:", font=("Arial", 10)).pack(anchor=tk.W)
            ttk.Entry(self.input_frame, textvariable=self.x0_var, font=("Arial", 10)).pack(fill=tk.X, pady=(0, 5))

        # Для итерационного метода показываем параметр lambda
        if method == "simple_iteration":
            ttk.Label(self.input_frame, text="Параметр lambda:", font=("Arial", 10)).pack(anchor=tk.W)
            ttk.Entry(self.input_frame, textvariable=self.lam_var, font=("Arial", 10)).pack(fill=tk.X, pady=(0, 5))

        # Кнопки (ВСЕ ТРИ)
        button_frame = ttk.Frame(self.input_frame)
        button_frame.pack(fill=tk.X, pady=10)

        ttk.Button(button_frame, text="Найти интервал",
                   command=self.find_interval, width=15).pack(side=tk.LEFT, padx=2)
        ttk.Button(button_frame, text="Найти корень",
                   command=self.solve, width=15).pack(side=tk.LEFT, padx=2)
        ttk.Button(button_frame, text="Очистить",
                   command=self.clear, width=15).pack(side=tk.LEFT, padx=2)

    def find_interval(self):
        """Автоматически находит интервал"""
        step = 0.5
        x = 0
        for i in range(100):
            if f(x) * f(x + step) < 0:
                self.a_var.set(f"{x:.2f}")
                self.b_var.set(f"{x + step:.2f}")
                messagebox.showinfo("Интервал найден", f"Корень находится на интервале [{x:.2f}, {x + step:.2f}]")
                return
        messagebox.showwarning("Не найдено", "Интервал не найден")

    def plot_function(self):
        """Строит график"""
        self.ax.clear()

        x = np.linspace(-3, 3, 400)
        y = f(x)

        self.ax.plot(x, y, 'b-', linewidth=2)
        self.ax.axhline(y=0, color='k', linewidth=0.5)
        self.ax.axvline(x=0, color='k', linewidth=0.5)
        self.ax.grid(True, alpha=0.3)

        # Настройка осей
        self.ax.set_xticks([-3, -2, -1, 0, 1, 2, 3])
        self.ax.set_yticks([-15, -10, -5, 0, 5, 10, 15])
        self.ax.set_xlim(-3, 3)
        self.ax.set_ylim(-15, 15)
        self.ax.set_xlabel('x', fontsize=10)
        self.ax.set_ylabel('f(x)', fontsize=10)

        # Выделяем корень если есть
        if hasattr(self, 'current_root'):
            self.ax.plot(self.current_root, f(self.current_root), 'ro', markersize=8,
                         label=f'Корень: x={self.current_root:.6f}')
            self.ax.legend()

        self.canvas.draw()

    def solve(self):
        """Находит корень"""
        try:
            eps = float(self.eps_var.get())
            method = self.method_var.get()
            a = float(self.a_var.get())
            b = float(self.b_var.get())

            self.steps_text.delete(1.0, tk.END)

            # Выбираем метод
            if method == "dihotomy":
                root, steps = dihotomy(a, b, eps)
                method_name = "Дихотомии"
                format_func = lambda s: f"Шаг {s[0]}: a={s[1]:.6f}, b={s[2]:.6f}, c={s[3]:.6f}, f(c)={s[4]:.6f}"
            elif method == "chord":
                root, steps = chord(a, b, eps)
                method_name = "Хорд"
                format_func = lambda s: f"Шаг {s[0]}: ({s[1]:.6f}, {s[2]:.6f}, {s[3]:.6f}, {s[4]:.6f})"
            elif method == "newton":
                x0 = float(self.x0_var.get())
                root, steps = newton(x0, eps)
                method_name = "Ньютона"
                format_func = lambda s: f"Шаг {s[0]}: x_old={s[1]:.6f}, x_new={s[2]:.6f}, f(x_new)={s[3]:.6f}"
            elif method == "modified_newton":
                x0 = float(self.x0_var.get())
                root, steps = modified_newton(x0, eps)
                method_name = "Модифицированный Ньютона"
                format_func = lambda s: f"Шаг {s[0]}: x_old={s[1]:.6f}, x_new={s[2]:.6f}, f(x_new)={s[3]:.6f}"
            elif method == "combined":
                root, steps = combined(a, b, eps)
                method_name = "Комбинированный"
                format_func = lambda s: f"Шаг {s[0]}: ({s[1]:.6f}, {s[2]:.6f}, {s[3]:.6f}, {s[4]:.6f})" if len(
                    s) == 5 else f"Шаг {s[0]}: x_old={s[1]:.6f}, x_new={s[2]:.6f}, f(x_new)={s[3]:.6f}"
            else:  # simple_iteration
                x0 = float(self.x0_var.get())
                lam = float(self.lam_var.get())
                root, steps = simple_iteration(x0, eps, lam)
                method_name = "Простых итераций"
                format_func = lambda s: f"Шаг {s[0]}: x_old={s[1]:.6f}, x_new={s[2]:.6f}, f(x_new)={s[3]:.6f}"

            # Выводим шаги
            self.steps_text.insert(tk.END, f"МЕТОД {method_name}\n", "header")
            self.steps_text.insert(tk.END, "=" * 60 + "\n\n")

            for step in steps:
                self.steps_text.insert(tk.END, format_func(step) + "\n")

            self.steps_text.insert(tk.END, f"\n{'=' * 60}\n")
            self.steps_text.insert(tk.END, f"НАЙДЕННЫЙ КОРЕНЬ: x = {root:.10f}\n")
            self.steps_text.insert(tk.END, f"ЗНАЧЕНИЕ ФУНКЦИИ: f(x) = {f(root):.2e}\n")
            self.steps_text.insert(tk.END, f"КОЛИЧЕСТВО ИТЕРАЦИЙ: {len(steps)}")

            # Обновляем результат
            self.root_label.config(text=f"Корень: x = {root:.10f}")
            self.iter_label.config(text=f"Итераций: {len(steps)}")

            self.current_root = root
            self.plot_function()

            # Прокручиваем в начало
            self.steps_text.see(1.0)

        except Exception as e:
            messagebox.showerror("Ошибка", str(e))

    def clear(self):
        """Очищает всё"""
        self.steps_text.delete(1.0, tk.END)
        self.steps_text.insert(tk.END, "Нажмите 'Найти корень' для начала вычислений\n")
        self.root_label.config(text="Корень: не найден")
        self.iter_label.config(text="Итераций: 0")

        if hasattr(self, 'current_root'):
            delattr(self, 'current_root')
        self.plot_function()


# ===================== ЗАПУСК =====================
if __name__ == "__main__":
    root = tk.Tk()
    app = RootFinderApp(root)
    root.mainloop()