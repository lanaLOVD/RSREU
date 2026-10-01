#include "MainMenuController.h"
#include "GameController.h"
#include "AboutController.h"

/**
* Запуск приложения
*/
void MainMenuController::run()
{
	m_menuView->display();
}

/**
* Реализация конструктора
* int windowWidth - ширина окна
* int windowHeight
* int buttonWidth
* int buttonHeight
*/
MainMenuController::MainMenuController(
	int windowWidth, int windowHeight,
	int buttonWidth, int buttonHeight)
	: AbstractController(nullptr)
	, m_menuView(std::make_unique<MainMenuView>(windowWidth, windowHeight, buttonWidth, buttonHeight))
	, m_aboutController(windowWidth, windowHeight, buttonWidth, buttonHeight, this)
	, m_gameController(windowWidth, windowHeight, this)
{
	m_menuView->setButtonStartGameCallback([this]()
	{
		releaseControl();
		m_gameController.takeControl();
	});

	m_menuView->setButtonAboutCallback([this]()
	{
		this->releaseControl();
		this->m_aboutController.takeControl();
	});

	m_menuView->setButtonExitCallback([]()
	{
		exit(0);
	});
}

/**
* Получение управления
*/
void MainMenuController::takeControl()
{
	m_menuView->show();
}

/**
* Прекращение управления
*/
void MainMenuController::releaseControl()
{
	m_menuView->hide();
}