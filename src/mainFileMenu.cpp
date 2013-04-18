/**
 * mainFileMenu.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include <QApplication>

#include "newMapDialog.hpp"
#include "mainFileMenu.hpp"
#include "mainWindow.hpp"

MainFileMenu::MainFileMenu(QWidget *parent) : 
                QMenu(tr("File"), parent),
                newAction(tr("&New"), this), 
                quitAction(tr("&Quit"), this)
{
    connect(&newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(&quitAction, SIGNAL(triggered()), this, SLOT(quit()));
    this->addAction(&newAction);
    this->addAction(&quitAction);
}

MainFileMenu::~MainFileMenu()
{
}

void MainFileMenu::newFile()
{
    NewMapDialog dialog(this);
    dialog.exec();
    if(dialog.succeeded())
    {
        //create a new map 
        MainWindow::getInstance()->newMap(dialog.width(), dialog.height());
    }
}

void MainFileMenu::quit()
{
    qApp->quit();
}
