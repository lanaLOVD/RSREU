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
 * Взаимодействует с MenuController через std::weak_ptr.
 *
 * Не содержит игровой логики — только маршрутизацию действий пользователя.
 */
class GameController {
private:
    /// @brief Игровая модель (владеет)
    std::unique_ptr<GameModel> m_model;

    /// @brief Игровое окно (владеет)
    std::unique_ptr<GameView> m_view;

    /// @brief Слабая ссылка на контроллер меню (не владеет)
    std::weak_ptr<MenuController> m_menuController;

    /// @brief Флаг: игровой сеанс в данный момент активен
    bool m_isGameActive;

    /// @brief Флаг нажатия клавиши движения влево
    bool m_keyLeft;

    /// @brief Флаг нажатия клавиши движения вправо
    bool m_keyRight;

    /// @brief Флаг нажатия клавиши прыжка (пробел)
    bool m_keySpace;

    /**
     * @brief Статический таймер FLTK для игрового цикла контроллера.
     * @param data  Указатель на экземпляр GameController
     */
    static void timerCallback(void* data);

    /**
     * @brief Передаёт текущее состояние клавиш в модель.
     */
    void processInput();

    /**
     * @brief Останавливает таймер, скрывает окно, сбрасывает флаги.
     */
    void cleanUp();

public:
    /**
     * @brief Конструктор: создаёт модель и вид, устанавливает callback-и клавиш.
     * @param width   Ширина игрового окна в пикселях
     * @param height  Высота игрового окна в пикселях
     */
    GameController(int width, int height);

    /**
     * @brief Деструктор: вызывает cleanUp() для освобождения ресурсов.
     */
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
     * @brief Устанавливает слабую ссылку на MenuController.
     * @param menu  shared_ptr на MenuController
     */
    void setMenuController(std::shared_ptr<MenuController> menu);

    /**
     * @brief Обрабатывает нажатие клавиши — обновляет соответствующий флаг.
     * @param key  Код клавиши FLTK
     */
    void handleKeyDown(int key);

    /**
     * @brief Обрабатывает отпускание клавиши — сбрасывает соответствующий флаг.
     * @param key  Код клавиши FLTK
     */
    void handleKeyUp(int key);
};