#include "AbstractController.h"

/**
* Реализация конструктора
* AbstractController *p_parent - сырой указатель на контроллер, являющийся главным для этого контроллера
*/
AbstractController::AbstractController(AbstractController* p_parent) : m_pParentController(p_parent)
{
}