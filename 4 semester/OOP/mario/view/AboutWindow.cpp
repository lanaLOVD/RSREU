#include "AboutWindow.h"

/**
 * @brief Конструктор: создаёт окно, заполняет текст управления, добавляет кнопку OK.
 * @param width   Ширина окна
 * @param height  Высота окна
 * @param title   Заголовок окна
 */
AboutWindow::AboutWindow(int width, int height, const char* title)
    : Fl_Double_Window(width, height, title) {
    color(FL_GRAY);
    begin();

    m_controlLines = {
        "Game Controls:",
        "",
        "Left Arrow - Move Left",
        "Right Arrow - Move Right",
        "Space - Jump",
        ""
    };

    m_okButton = new Fl_Button(width / 2 - 50, height - 50, 100, 30, "OK");
    m_okButton->callback(onOkButtonClicked, this);
    m_okButton->color(FL_LIGHT2);

    end();

    position((Fl::w() - width) / 2, (Fl::h() - height) / 2);
}

/**
 * @brief Деструктор.
 */
AboutWindow::~AboutWindow() {
}

/**
 * @brief Отрисовывает содержимое окна: заголовок, разделитель, строки управления.
 */
void AboutWindow::draw() {
    Fl_Double_Window::draw();

    // Заголовок
    fl_color(FL_BLUE);
    fl_font(FL_HELVETICA_BOLD, 24);
    fl_draw("About Mario Game", 20, 40);

    // Разделитель
    fl_line_style(FL_SOLID, 2);
    fl_line(20, 50, w() - 20, 50);
    fl_line_style(0);

    // Строки описания
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, 16);

    int y = 80;
    for (const auto& line : m_controlLines) {
        fl_draw(line.c_str(), 30, y);
        y += 20;
    }

    // Рамка окна
    fl_color(FL_GRAY);
    fl_rect(0, 0, w(), h());
}

/**
 * @brief Обработчик нажатия кнопки OK: вызывает m_closeCallback и скрывает окно.
 * @param widget  Виджет-источник события (не используется)
 * @param data    Указатель на AboutWindow
 */
void AboutWindow::onOkButtonClicked(Fl_Widget* widget, void* data) {
    AboutWindow* window = static_cast<AboutWindow*>(data);
    if (window) {
        if (window->m_closeCallback) {
            window->m_closeCallback();
        }
        window->hide();
    }
}

/**
 * @brief Устанавливает callback для закрытия окна.
 * @param callback  Функция без аргументов, вызываемая при нажатии OK
 */
void AboutWindow::setCloseCallback(std::function<void()> callback) {
    m_closeCallback = callback;
}
