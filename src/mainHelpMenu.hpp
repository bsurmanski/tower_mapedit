/**
 * mainHelpMenu.hpp
 * tower/mapedit
 * April 20, 2013
 * Brandon Surmanski
 */

#ifndef _MAINHELPMENU_HPP
#define _MAINHELPMENU_HPP

#include <QMenuBar>

class MainHelpMenu : public QMenu
{
    Q_OBJECT
    public:
        MainHelpMenu(QWidget *parent = 0);

    protected slots:
        void openAbout();

    private:
        QAction aboutAction;
};

#endif
