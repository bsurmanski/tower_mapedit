/**
 * mainMenuBar.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include "mainMenuBar.hpp"

MainMenuBar::MainMenuBar(QWidget *parent) : 
                QMenuBar(parent),
                fileMenu(this)
{
    addMenu(&fileMenu);
}

MainMenuBar::~MainMenuBar()
{
}
