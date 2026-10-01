#include "Controller/MainMenuController.h"

int main()
{
    MainMenuController controller(
        MainMenuController::DEFAULT_WINDOW_WIDTH,
        MainMenuController::DEFAULT_WINDOW_HEIGHT,
        MainMenuController::DEFAULT_BUTTON_WIDTH,
        MainMenuController::DEFAULT_BUTTON_HEIGHT
    );

    controller.run();
    return 0;
}