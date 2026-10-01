#include "MenuView.h"
#include <FL/fl_draw.H>

MenuView::MenuView(int w, int h, const char* title)
    : Fl_Window{ w, h, title } {

    begin();
    color(0xE6F0FA);   // Светлый фон

    // === ИЗМЕНЕНИЕ: делаем окно больше ===
    int btnWidth = 280;
    int btnHeight = 55;
    int spacing = 25;

    // Новые размеры окна
    int newWidth = 500;
    int newHeight = 420;

    // Центрируем кнопки
    m_newGameBtn = new Fl_Button(newWidth/2 - btnWidth/2, 140, btnWidth, btnHeight, "ИГРАТЬ");
    m_aboutBtn   = new Fl_Button(newWidth/2 - btnWidth/2, 140 + btnHeight + spacing, btnWidth, btnHeight, "КАК ИГРАТЬ");
    m_exitBtn    = new Fl_Button(newWidth/2 - btnWidth/2, 140 + 2*(btnHeight + spacing), btnWidth, btnHeight, "ВЫХОД");

    // Стиль кнопок
    for (auto* btn : {m_newGameBtn, m_aboutBtn, m_exitBtn}) {
        btn->color(0xA8DADC);
        btn->labelcolor(FL_DARK_BLUE);
        btn->labelsize(20);
        btn->box(FL_ROUND_UP_BOX);
    }

    // Callback'и
    m_newGameBtn->callback([](Fl_Widget*, void* data) {
        static_cast<MenuView*>(data)->m_startGameCallback();
    }, this);

    m_aboutBtn->callback([](Fl_Widget*, void* data) {
        static_cast<MenuView*>(data)->m_aboutCallback();
    }, this);

    m_exitBtn->callback([](Fl_Widget*, void* data) {
        static_cast<MenuView*>(data)->m_exitCallback();
    }, this);

    end();

    // Устанавливаем новый размер окна
    size(newWidth, newHeight);
}

void MenuView::draw() {
    Fl_Window::draw();

    // Красная надпись MARIO
    fl_color(FL_RED);
    fl_font(FL_HELVETICA_BOLD, 42);
    fl_draw("MARIO", w()/2 - 78, 80);
}

void MenuView::setCallBackNewGame(std::function<void()> callback) {
    m_startGameCallback = std::move(callback);
}

void MenuView::setCallBackAbout(std::function<void()> callback) {
    m_aboutCallback = std::move(callback);
}

void MenuView::setCallBackExit(std::function<void()> callback) {
    m_exitCallback = std::move(callback);
}