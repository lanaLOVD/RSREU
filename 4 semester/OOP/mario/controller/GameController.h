#pragma once
#include <memory>
#include <functional>
#include <FL/Fl.H>
#include "../model/GameModel.h"
#include "../view/GameView.h"

class MenuController;

/**
 * @brief Контроллер игрового процесса.
 *
 * Создаёт GameModel и GameView, связывает их через callback-и.
 * Передаёт ввод пользователя из View в модель.
 * Взаимодействует с MenuController для возврата в меню.
 */
class GameController {
private:
    /// @brief Игровая модель
    std::unique_ptr<GameModel> m_model;

    /// @brief Игровое окно
    std::unique_ptr<GameView> m_view;

    /// @brief Указатель на контроллер меню (не владеет)
    MenuController* m_menuController;

    /// @brief Флаг активной игры
    bool m_isGameActive;

    /// @brief Состояние клавиши "влево"
    bool m_keyLeft;

    /// @brief Состояние клавиши "вправо"
    bool m_keyRight;

    /// @brief Состояние клавиши "пробел" (прыжок)
    bool m_keySpace;

    /**
     * @brief Статический таймер FLTK для игрового цикла.
     * @param data  Указатель на GameController
     */
    static void timerCallback(void* data);

    /**
     * @brief Передаёт текущее состояние клавиш в модель игрока.
     */
    void processInput();

    /**
     * @brief Останавливает таймер, скрывает окно, сбрасывает флаги.
     */
    void cleanUp();

public:
    /**
     * @brief Конструктор: создаёт модель и вид.
     * @param width   Ширина игрового окна
     * @param height  Высота игрового окна
     */
    GameController(int width, int height);

    /** @brief Деструктор: вызывает cleanUp() */
    ~GameController();

    /**
     * @brief Запускает новую игру: сбрасывает модель, показывает окно, запускает таймер.
     */
    void run();

    /**
     * @brief Скрывает игровое окно и передаёт управление в MenuController.
     */
    void returnToMenu();

    /**
     * @brief Устанавливает указатель на MenuController для возврата в меню.
     * @param menu  Указатель на MenuController
     */
    void setMenuController(MenuController* menu);

    /**
     * @brief Обрабатывает нажатие клавиши.
     * @param key  Код клавиши FLTK
     */
    void handleKeyDown(int key);

    /**
     * @brief Обрабатывает отпускание клавиши.
     * @param key  Код клавиши FLTK
     */
    void handleKeyUp(int key);
};
