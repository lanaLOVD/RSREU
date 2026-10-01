#ifndef ABOUT_CONTROLLER_H
#define ABOUT_CONTROLLER_H

#include <memory>
#include <iostream>

#include "AbstractController.h"
#include "../View/AboutView.h"

class AboutController : public AbstractController
{
public:
    AboutController(int x, int y, int width, int height, int buttonWidth, int buttonHeight, AbstractController* parent);

    AboutController(const AboutController&) = delete;

    void takeControl() override;
    void releaseControl() override;

private:
    AboutView m_aboutView;
};

#endif