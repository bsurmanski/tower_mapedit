/**
 * mainWindowMenu.hpp
 * tower/mapedit
 * April 18, 2013
 * Brandon Surmanski
 */

#ifndef _MAINWINDOWMENU_HPP
#define _MAINWINDOWMENU_HPP

#include <QMenu>
#include <QObject>
#include <QWidget>

class MainWindowMenu : public QMenu
{
    Q_OBJECT

    public:
        MainWindowMenu(QWidget *parent = 0);

    protected slots:
        void openToolbox();

    private:
        QAction toolboxAction;
};

#endif
