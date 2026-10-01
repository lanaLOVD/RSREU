#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <functional>
#include "../model/GameModel.h"

/**
 * @brief Окно игры — отрисовывает мир и передаёт события клавиатуры через callback-и.
 *
 * View не знает ничего о контроллере. Контроллер устанавливает обработчики
 * клавиш через setKeyDownCallback / setKeyUpCallback.
 */
class GameView : public Fl_Double_Window {
private:
    /// @brief Указатель на игровую модель (не владеет)
    GameModel* m_model;

    /// @brief Callback, вызываемый при нажатии клавиши (устанавливается контроллером)
    std::function<void(int)> m_keyDownCallback;

    /// @brief Callback, вызываемый при отпускании клавиши (устанавливается контроллером)
    std::function<void(int)> m_keyUpCallback;

    /**
     * @brief Статический таймер FLTK для перерисовки окна.
     * @param data  Указатель на экземпляр GameView
     */
    static void timerCallback(void* data);

    /**
     * @brief Обрабатывает события FLTK (клавиатура, фокус).
     * @param event  Код события FLTK
     * @return 1, если событие обработано; иначе результат базового класса
     */
    int handle(int event) override;

    /** @brief Отрисовывает все платформы */
    void drawPlatforms();

    /**
     * @brief Отрисовывает одну платформу.
     * @param x       Экранная координата X
     * @param y       Экранная координата Y
     * @param width   Ширина
     * @param height  Высота
     */
    void drawPlatform(double x, double y, double width, double height);

    /** @brief Отрисовывает градиентный фон */
    void drawBackground();

    /** @brief Отрисовывает декоративные облака */
    void drawClouds();

    /**
     * @brief Отрисовывает одно облако.
     * @param x     Центр X
     * @param y     Центр Y
     * @param size  Размер
     */
    void drawCloud(double x, double y, double size);

    /** @brief Отрисовывает всех активных врагов */
    void drawEnemies();

    /**
     * @brief Отрисовывает одного врага.
     * @param x       Экранная X
     * @param y       Экранная Y
     * @param width   Ширина
     * @param height  Высота
     */
    void drawEnemy(double x, double y, double width, double height);

    /** @brief Отрисовывает все активные монеты */
    void drawCoins();

    /**
     * @brief Отрисовывает одну монету.
     * @param x         Экранная X
     * @param y         Экранная Y
     * @param width     Ширина
     * @param height    Высота
     * @param rotation  Текущий угол вращения (для анимации)
     */
    void drawCoin(double x, double y, double width, double height, double rotation);

    /** @brief Отрисовывает игрока */
    void drawPlayer();

    /**
     * @brief Отрисовывает персонажа игрока.
     * @param x       Экранная X
     * @param y       Экранная Y
     * @param width   Ширина
     * @param height  Высота
     */
    void drawPlayerCharacter(double x, double y, double width, double height);

    /** @brief Отрисовывает HUD (монеты, жизни, сообщение о конце игры) */
    void drawUI();

public:
    /**
     * @brief Конструктор окна игры.
     * @param width   Ширина окна
     * @param height  Высота окна
     * @param title   Заголовок окна
     * @param model   Указатель на игровую модель
     */
    GameView(int width, int height, const char* title, GameModel* model)
        : Fl_Double_Window{ width, height, title }, m_model{ model } {
        Fl::add_timeout(1.0 / 60.0, timerCallback, this);
    }

    /**
     * @brief Устанавливает callback для нажатия клавиши.
     * @param cb  Функция, принимающая код клавиши FLTK
     */
    void setKeyDownCallback(std::function<void(int)> cb) {
        m_keyDownCallback = std::move(cb);
    }

    /**
     * @brief Устанавливает callback для отпускания клавиши.
     * @param cb  Функция, принимающая код клавиши FLTK
     */
    void setKeyUpCallback(std::function<void(int)> cb) {
        m_keyUpCallback = std::move(cb);
    }

    /** @brief Отрисовывает кадр игры */
    void draw() override;
};
