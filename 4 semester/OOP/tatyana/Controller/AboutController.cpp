#include "AboutController.h"

AboutController::AboutController(int x, int y, int width, int height, int buttonWidth, int buttonHeight, AbstractController* parent) :
	AbstractController(parent), m_aboutView(x, y, width, height, buttonWidth, buttonHeight)
{
	m_aboutView.setButtonBackCallback([this]()
		{
			//std::cout << "About back callback\n";

			this->releaseControl();
			this->getParent()->takeControl();
		});

}

void AboutController::takeControl()
{
	m_aboutView.show();
	//m_aboutView.redraw();
}

void AboutController::releaseControl()
{
	m_aboutView.hide();
}