/**
 * mainMenuBar.hpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#ifndef _MAINMENUBAR_HPP
#define _MAINMENUBAR_HPP

#include <QMenuBar>

#include "mainFileMenu.hpp"
#include "mainWindowMenu.hpp"
#include "mainHelpMenu.hpp"

class MainMenuBar : public QMenuBar
{
    Q_OBJECT
    public:
        MainMenuBar(QWidget *parent = 0);

    private:
        MainFileMenu fileMenu;
        MainWindowMenu windowMenu;
        MainHelpMenu helpMenu;
};

#endif
