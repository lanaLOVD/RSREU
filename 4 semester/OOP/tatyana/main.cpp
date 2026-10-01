#include "Controller/MainMenuController.h"

int main()
{
    MainMenuController controller(
        MainMenuController::DEFAULT_WINDOW_LEFT,
        MainMenuController::DEFAULT_WINDOW_TOP,
        MainMenuController::DEFAULT_WINDOW_WIDTH,
        MainMenuController::DEFAULT_WINDOW_HEIGHT,
        MainMenuController::DEFAULT_BUTTON_WIDTH,
        MainMenuController::DEFAULT_BUTTON_HEIGHT
    );

    std::cout << "Starting Main Menu...\n";
    controller.run();

    std::cout << "Program finished.\n";
    return 0;
}