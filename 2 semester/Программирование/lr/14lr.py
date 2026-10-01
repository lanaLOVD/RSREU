import tkinter as tk
from tkinter import messagebox
def order():
    quantity = 0
    for flag in all_flags:
        if flag.get():
            quantity += 1
    if quantity <= 1:
        messagebox.showinfo("Ошибка", "Выберете игрушки!")
    else:
        total = quantity * 2500
        address = address_field.get()
        if not address.strip():
            messagebox.showinfo("Ошибка", "Пожалуйста, введите адресс доставки!")
        else:
            messagebox.showinfo("Заказ подтвержден", f"Сумма: {total} rub.\nАдрес доставки: {address}")
window = tk.Tk()
window.title("Toy Store")
all_flags = []
def add_group(group_name, toy_list):
    frame = tk.LabelFrame(window, text=group_name, font=('Arial', 12, 'bold'), padx=10, pady=10)
    frame.pack(padx=10, pady=5, fill="both")
    for toy in toy_list:
        var = tk.BooleanVar()
        checkbox = tk.Checkbutton(frame, text=toy, variable=var, font=('Arial', 10))
        checkbox.pack(anchor='w')
        all_flags.append(var)
add_group("Машины", ["Машина 1", "Машина 2", "Машина 3"])
add_group("Куклы", ["Кукла 1", "Кукла 2", "Кукла 3", "Кукла 4", "Кукла 5"])
add_group("Роботы", ["Робот 1", "Робот 2"])
add_group("Другое", ["Леденец"])
address_frame = tk.LabelFrame(window, text="Адрес доставки", font=('Arial', 12, 'bold'), padx=10, pady=10)
address_frame.pack(padx=10, pady=10, fill="both")
address_field = tk.Entry(address_frame, width=50, font=('Arial', 10))
address_field.pack()
order_button = tk.Button(window, text="Заказать", command=order, font=('Arial', 12, 'bold'), bg='lightgreen')
order_button.pack(pady=20)
window.mainloop()
