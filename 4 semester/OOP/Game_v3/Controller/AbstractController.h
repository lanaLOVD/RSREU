#ifndef ABSTRACT_CONTROLLER_H
#define ABSTRACT_CONTROLLER_H

#include <memory>

/**
 * Базовый абстрактный класс для всех контроллеров
 */
class AbstractController
{
public:
	/**
	 * Получение управления
	 */
	virtual void takeControl() = 0;

	/**
	 * Завершение управления
	 */
	virtual void releaseControl() = 0;

	/**
	 * Виртуальный деструктор
	 */
	virtual ~AbstractController()
	{
	}

protected:
	/**
	 * Конструктор
	 * AbstractController *p_parent - сырой указатель на контроллер, являющийся главным для этого контроллера
	 */
	AbstractController(AbstractController *p_parent);

	/**
	 * Геттер для m_pParentController
	 */
	AbstractController* getParent()
	{
		return this->m_pParentController;
	}

private:
	/**
	 * Контроллер, являющийся главным для этого контроллера
	 */
	AbstractController *m_pParentController;

};

#endif