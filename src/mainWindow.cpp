/**
 * mainWindow.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include "mainWindow.hpp"

MainWindow *MainWindow::instance = NULL;

MainWindow::MainWindow(QWidget *parent) : 
                QMainWindow(parent),
                menuBar(this)
{
    instance = this;
    glWidget = new MainGLWidget(this);
    setCentralWidget(glWidget);
    setMenuBar(&menuBar);
    setGeometry(20, 40, 640, 480);
}

MainWindow::~MainWindow()
{
}

void MainWindow::newMap(int x, int y)
{
    if(glWidget)
    {
        glWidget->newMap(x, y);
    }
}

MainWindow *MainWindow::getInstance()
{
    return MainWindow::instance;
}
