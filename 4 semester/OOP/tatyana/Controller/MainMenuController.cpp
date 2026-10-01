#include "MainMenuController.h"
#include "GameController.h"
#include "AboutController.h"

void MainMenuController::run()
{
	std::cout << "MainMenuController::run() started\n";
	m_menuView->show();
	std::cout << "MainMenuController::run() finished\n";  // Это не должно быстро появляться
}

MainMenuController::MainMenuController(int windowLeft, int windowTop,
	int windowWidth, int windowHeight,
	int buttonWidth, int buttonHeight)
	: AbstractController(nullptr)
	, m_menuView(std::make_unique<MainMenuView>(0, 0, windowWidth, windowHeight, buttonWidth, buttonHeight))
	, m_aboutController(windowLeft, windowTop, windowWidth, windowHeight, buttonWidth, buttonHeight, this)
	, m_gameController(windowLeft, windowTop, windowWidth, windowHeight, this)
{
	m_menuView->setButtonStartGameCallback([this]()
	{
		std::cout << "Button play callback\n";
		releaseControl();
		m_gameController.takeControl();
	});

	m_menuView->setButtonAboutCallback([this]()
	{
		std::cout << "Button about callback\n";
		releaseControl();
		m_aboutController.takeControl();
	});

	m_menuView->setButtonExitCallback([]()
	{
		std::cout << "Button exit callback\n";
		exit(0);
	});
}

void MainMenuController::takeControl()
{
	m_menuView->showMenu();
}

void MainMenuController::releaseControl()
{
	m_menuView->hideMenu();
}