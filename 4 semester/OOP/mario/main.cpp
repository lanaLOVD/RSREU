#include "controller/MenuController.h"

/**
 * @brief Точка входа в приложение.
 *
 * Создаёт MenuController, открывает главное меню и передаёт управление
 * в цикл событий FLTK.
 *
 * @return Код завершения приложения
 */
int main() {
    MenuController menuController;
    menuController.run();
    return Fl::run();
}
