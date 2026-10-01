#include "controller/MenuController.h"
#include <FL/Fl.H>

/**
 * @brief Точка входа в приложение.
 *
 * Создаёт MenuController через shared_ptr, инициализирует связи
 * между контроллерами и передаёт управление в цикл событий FLTK.
 *
 * @return Код завершения приложения
 */
int main() {
    std::shared_ptr<MenuController> menuController {std::make_shared<MenuController>()};
    menuController->init();
    menuController->run();
    return Fl::run();
}