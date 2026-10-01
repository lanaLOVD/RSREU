import numpy as np
import tkinter as tk
from tkinter import ttk

def gauss_method(A, B):
    n = len(B)
    Ab = np.hstack((A.copy().astype(float), B.reshape(-1, 1).astype(float)))
    for i in range(n):
        # Частичный выбор главного элемента
        max_row = i
        for k in range(i + 1, n):
            if abs(Ab[k, i]) > abs(Ab[max_row, i]):
                max_row = k
        Ab[[i, max_row]] = Ab[[max_row, i]]
        for k in range(i + 1, n):
            if abs(Ab[i, i]) < 1e-12:
                return None
            c = -Ab[k, i] / Ab[i, i]
            for j in range(i, n + 1):
                if i == j:
                    Ab[k, j] = 0.0
                else:
                    Ab[k, j] += c * Ab[i, j]
    X = np.zeros(n)
    for i in range(n - 1, -1, -1):
        X[i] = Ab[i, n]
        for j in range(i + 1, n):
            X[i] -= Ab[i, j] * X[j]
        X[i] /= Ab[i, i]
    return X

def determinant(A):
    n = A.shape[0]
    Ab = A.copy().astype(float)
    det_val = 1.0
    sign = 1
    for i in range(n):
        max_row = i
        for k in range(i + 1, n):
            if abs(Ab[k, i]) > abs(Ab[max_row, i]):
                max_row = k
        if max_row != i:
            Ab[[i, max_row]] = Ab[[max_row, i]]
            sign = -sign
        if abs(Ab[i, i]) < 1e-12:
            return 0.0
        det_val *= Ab[i, i]
        for k in range(i + 1, n):
            c = Ab[k, i] / Ab[i, i]
            for j in range(i, n):
                Ab[k, j] -= c * Ab[i, j]
    return sign * det_val

def inf_norm(M):
    q = max(sum(abs(row)) for row in M)
    return q

def condition_number(A):
    g = inf_norm(A) * inf_norm(np.linalg.inv(A))
    return g

def simple_iteration_method(A, B, eps=0.001, max_iter=1000):
    n = len(B)
    C = np.zeros((n, n))
    F = np.zeros(n)

    for i in range(n):
        F[i] = B[i] / A[i, i]
        for j in range(n):
            if i != j:
                C[i, j] = -A[i, j] / A[i, i]

    X = np.zeros(n)
    steps = []  # список для хранения всех итераций

    for iter_count in range(max_iter):
        X_new = np.zeros(n)
        for i in range(n):
            s = sum(C[i, j] * X[j] for j in range(n))
            X_new[i] = s + F[i]

        delta_sum = sum(abs(X_new[k] - X[k]) for k in range(n))
        steps.append((iter_count, X_new.copy(), delta_sum))

        if delta_sum < eps:
            return X_new, iter_count + 1, steps
        X = X_new.copy()

    return X, max_iter, steps


# окно с итерациями
def show_iteration_steps(steps):
    step_window = tk.Toplevel()
    step_window.title("Шаги метода простых итераций")
    step_window.geometry("780x500")
    step_window.configure(bg="#2c3e50")

    tk.Label(step_window, text="Ход итерационного процесса",
             font=("Arial", 14, "bold"), fg="#ecf0f1", bg="#2c3e50").pack(pady=10)

    # Таблица
    columns = ("Итерация", "x1", "x2", "x3", "∑|Δx|")
    tree = ttk.Treeview(step_window, columns=columns, show="headings", height=18)

    tree.heading("Итерация", text="Итерация")
    tree.heading("x1", text="x₁")
    tree.heading("x2", text="x₂")
    tree.heading("x3", text="x₃")
    tree.heading("∑|Δx|", text="∑|Δx|")

    tree.column("Итерация", width=80, anchor="center")
    tree.column("x1", width=140, anchor="center")
    tree.column("x2", width=140, anchor="center")
    tree.column("x3", width=140, anchor="center")
    tree.column("∑|Δx|", width=120, anchor="center")

    for step in steps:
        iter_num, X, delta = step
        tree.insert("", "end", values=(iter_num, f"{X[0]:.8f}", f"{X[1]:.8f}", f"{X[2]:.8f}", f"{delta:.8f}"))

    tree.pack(padx=20, pady=10, fill="both", expand=True)

    tk.Button(step_window, text="Закрыть", font=("Arial", 10), bg="#e74c3c", fg="black",
              command=step_window.destroy).pack(pady=8)


# главное окно
def show_results():
    A = np.array([[3., 2., 1.], [1., 4., 1.], [2., 1., 5.]])
    B = np.array([10., 12., 13.])

    X_gauss = gauss_method(A, B)
    det_A = determinant(A)
    norm_A = inf_norm(A)
    cond_A = condition_number(A)

    X_iter, iterations, steps = simple_iteration_method(A, B)

    root = tk.Tk()
    root.title("Лабораторная работа №3 — Решение СЛАУ (Вариант 6)")
    root.geometry("740x580")
    root.resizable(False, False)
    root.configure(bg="#2c3e50")

    tk.Label(root, text="Решение системы линейных алгебраических уравнений",
             font=("Arial", 16, "bold"), fg="#ecf0f1", bg="#2c3e50").pack(pady=15)
    tk.Label(root, text="Вариант 6", font=("Arial", 12), fg="#bdc3c7", bg="#2c3e50").pack(pady=(0, 10))

    main_frame = tk.Frame(root, bg="#34495e", relief="groove", bd=3)
    main_frame.pack(padx=30, pady=10, fill="both", expand=True)

    result_text = f"""Метод Гаусса:
x₁ = {X_gauss[0]:.6f}
x₂ = {X_gauss[1]:.6f}
x₃ = {X_gauss[2]:.6f}

Характеристики матрицы:
det(A)              = {det_A:.2f}
||A||∞             ≈ {norm_A:.4f}
Число обусловленности cond(A) ≈ {cond_A:.4f}

Метод простых итераций:
x₁ = {X_iter[0]:.6f}
x₂ = {X_iter[1]:.6f}
x₃ = {X_iter[2]:.6f}

Количество итераций: {iterations} (при ε = 0.001)
"""

    text_box = tk.Text(main_frame, font=("Consolas", 11), bg="#ecf0f1", fg="#2c3e50",
                       width=78, height=16, padx=15, pady=15)
    text_box.pack(padx=20, pady=20)
    text_box.insert(tk.END, result_text)
    text_box.config(state="disabled")

    # Кнопки
    btn_frame = tk.Frame(root, bg="#2c3e50")
    btn_frame.pack(pady=15)

    tk.Button(btn_frame, text="Показать все шаги итераций", font=("Arial", 10, "bold"),
              bg="#3498db", fg="black", width=28, height=2,
              command=lambda: show_iteration_steps(steps)).pack(side="left", padx=15)

    tk.Button(btn_frame, text="Закрыть окно", font=("Arial", 10, "bold"),
              bg="#e74c3c", fg="black", width=20, height=2,
              command=root.destroy).pack(side="left", padx=15)

    root.mainloop()


show_results()