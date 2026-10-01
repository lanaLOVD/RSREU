#ifndef ABSTRACT_CONTROLLER_H
#define ABSTRACT_CONTROLLER_H

class AbstractController
{
public:
	virtual void takeControl() = 0;

	virtual void releaseControl() = 0;

	virtual ~AbstractController()
	{
	}

protected:
	AbstractController(AbstractController *p_parent);

	void setParent(AbstractController *p_parent)
	{
		m_p_parentController = p_parent;
	}

	AbstractController* getParent()
	{
		return this->m_p_parentController;
	}

private:
	AbstractController *m_p_parentController;

};

#endif