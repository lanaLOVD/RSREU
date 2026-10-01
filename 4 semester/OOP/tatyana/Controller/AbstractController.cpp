#include "AbstractController.h"

// Дефолтный аргумент только в .h, здесь его не повторяем
AbstractController::AbstractController(AbstractController* p_parent) : m_p_parentController(p_parent)
{
}