#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <memory>

#include "../View/MainMenuView.h"

#include "GameController.h"
#include "AboutController.h"
#include "AbstractController.h"

/**
 * Контроллер для главного меню
 */
class MainMenuController : public AbstractController
{
public:
    /**
     * Конструктор
     * int windowWidth - ширина окна
     * int windowHeight
     * int buttonWidth
     * int buttonHeight
     */
    MainMenuController(int windowWidth, int windowHeight,
                       int buttonWidth, int buttonHeight);

    /**
     * Конструктор копирования удалён
     */
    MainMenuController(const MainMenuController&) = delete;

    /**
     * Запуск приложения
     */
    void run();

    /**
     * Страндартная ширина окна
     */
    static const int DEFAULT_WINDOW_WIDTH  { 768 };

    /**
     * Стандартная высота окна
     */
    static const int DEFAULT_WINDOW_HEIGHT {  768 };

    /**
     * Стандартная ширина кнопок
     */
    static const int DEFAULT_BUTTON_WIDTH  {  300 };

    /**
     * Стандартная высота кнопок
     */
    static const int DEFAULT_BUTTON_HEIGHT {   80 };

    /**
     * Получение управления
     */
    void takeControl() override;

    /**
     * Прекращение управления
     */
    void releaseControl() override;

private:
    /**
     * Контроллер окна справки
     */
    AboutController m_aboutController;

    /**
     * Контроллер окна игры
     */
    GameController m_gameController;

    /**
     * Указатель на отображение окна главного меню
     */
    std::unique_ptr<MainMenuView> m_menuView;
};

#endif