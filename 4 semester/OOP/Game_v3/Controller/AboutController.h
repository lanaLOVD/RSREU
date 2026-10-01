#ifndef ABOUT_CONTROLLER_H
#define ABOUT_CONTROLLER_H

#include <memory>

#include "AbstractController.h"
#include "../View/AboutView.h"

/**
 * Контроллер для окна справки
 */
class AboutController : public AbstractController
{
public:
    /**
     * Конструктор
     * int width - ширина окна
     * int height - высота окна
     * int buttonWidth - ширина кнопок
     * int buttonHeight - высота кнопок
     * AbstractController* parent - сырой указатель на главный контроллер
     */
    AboutController(int width, int height, int buttonWidth, int buttonHeight, AbstractController* pParent);

    /**
     * Конструктор копирования удален
     */
    AboutController(const AboutController&) = delete;

    /**
     * Получение управления
     */
    void takeControl() override;

    /**
     * Завершение управления
     */
    void releaseControl() override;

private:
    /**
     * Отображение окна справки
     */
    AboutView m_aboutView;
};

#endif