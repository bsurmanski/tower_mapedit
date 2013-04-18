/**
 * mainFileMenu.hpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#ifndef _MAINFILEMENU_HPP
#define _MAINFILEMENU_HPP

#include <QMenuBar>

class MainFileMenu : public QMenu
{
    Q_OBJECT

    public:
        MainFileMenu(QWidget *parent = 0);
        ~MainFileMenu();

    private slots:
        void newFile();
        void quit();
    private:
        QAction newAction;
        QAction quitAction;
};

#endif
