# Первая программа: без регулярных выражений
def remove_single_letter_words_no_regex(input_text):
    words = input_text.split()
    result = " ".join(word for word in words if len(word) > 1)
    return result
# Вторая программа: с использованием регулярных выражений
import re
def remove_single_letter_words_with_regex(input_text):
    # Регулярное выражение для поиска однобуквенных слов
    result = re.sub(r'\b\w\b', '', input_text)
    # Убираем лишние пробелы после удаления
    result = re.sub(r'\s{2,}', ' ', result).strip()
    return result
# Основная программа
if __name__ == "__main__":
    print("Введите текст (минимум две строки, завершите ввод пустой строкой):")
    input_lines = []
    while True:
        line = input()
        if line == "":
            break
        input_lines.append(line)
    input_text = "\n".join(input_lines)
    print("\nВведённый текст:")
    print(input_text)
    # Результаты обработки
    result_no_regex = remove_single_letter_words_no_regex(input_text)
    result_with_regex = remove_single_letter_words_with_regex(input_text)
    # Вывод результатов
    print("\nРезультат (без регулярных выражений):")
    print(result_no_regex)
    print("\nРезультат (с использованием регулярных выражений):")
    print(result_with_regex)
    # Сравнение результатов
    comparison = "совпадают" if result_no_regex == result_with_regex else "различаются"
    print(f"\nРезультаты {comparison}.")

