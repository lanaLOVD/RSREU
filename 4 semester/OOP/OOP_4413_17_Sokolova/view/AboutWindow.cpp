#include "AboutWindow.h"

AboutWindow::AboutWindow(int width, int height, const char* title)
    : Fl_Double_Window(width, height, title) {

    color(FL_DARK3);
    begin();

    m_controlLines = {
        "Управление:",
        "",
        "← → — Двигаться влево/вправо",
        "ПРОБЕЛ — Прыгать",
        "SHIFT — Бежать",
        "",
        "Цель:",
        "Собирай монеты, прыгай на врагов",
        "Не падай вниз и не умирай!"
    };

    m_okButton = new Fl_Button(width / 2 - 60, height - 60, 120, 40, "OK");
    m_okButton->callback(onOkButtonClicked, this);
    m_okButton->color(FL_WHITE);
    m_okButton->labelcolor(FL_DARK_BLUE);
    m_okButton->labelsize(18);

    end();
    position((Fl::w() - width) / 2, (Fl::h() - height) / 2);
}

AboutWindow::~AboutWindow() {}

void AboutWindow::draw() {
    Fl_Double_Window::draw();

    // Заголовок
    fl_color(FL_YELLOW);
    fl_font(FL_HELVETICA_BOLD, 28);
    fl_draw("SUPER MARIO", 40, 50);

    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 18);
    fl_draw("Как играть", 40, 85);

    // Разделитель
    fl_color(FL_YELLOW);
    fl_line_style(FL_SOLID, 3);
    fl_line(40, 95, w() - 40, 95);
    fl_line_style(0);

    // Текст
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA, 16);

    int y = 120;
    for (const auto& line : m_controlLines) {
        fl_draw(line.c_str(), 50, y);
        y += 26;
    }

    // Рамка
    fl_color(FL_YELLOW);
    fl_rect(20, 20, w() - 40, h() - 40);
}

void AboutWindow::onOkButtonClicked(Fl_Widget*, void* data) {
    AboutWindow* window = static_cast<AboutWindow*>(data);
    if (window && window->m_closeCallback) {
        window->m_closeCallback();
    }
    if (window) window->hide();
}

void AboutWindow::setCloseCallback(std::function<void()> callback) {
    m_closeCallback = std::move(callback);
}