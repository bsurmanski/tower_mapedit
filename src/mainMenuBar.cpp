/**
 * mainMenuBar.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include "mainMenuBar.hpp"

MainMenuBar::MainMenuBar(QWidget *parent) : 
                QMenuBar(parent),
                fileMenu(this),
                windowMenu(this),
                helpMenu(this)
{
    addMenu(&fileMenu);
    addMenu(&windowMenu);
    addMenu(&helpMenu);
}
