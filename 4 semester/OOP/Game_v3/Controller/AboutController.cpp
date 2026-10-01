#include "AboutController.h"

/**
* Реализация конструктора
* int width - ширина окна
* int height - высота окна
* int buttonWidth - ширина кнопок
* int buttonHeight - высота кнопок
* AbstractController* parent - сырой указатель на главный контроллер
*/
AboutController::AboutController(int width, int height, int buttonWidth, int buttonHeight, AbstractController* parent) :
	AbstractController(parent), m_aboutView(width, height, buttonWidth, buttonHeight)
{
	m_aboutView.setButtonBackCallback([this]()
		{
			this->releaseControl();
			this->getParent()->takeControl();
		});

}

/**
* Получение управления
*/
void AboutController::takeControl()
{
	m_aboutView.show();
}

/**
* Завершение управления
*/
void AboutController::releaseControl()
{
	m_aboutView.hide();
}