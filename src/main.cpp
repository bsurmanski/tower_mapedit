/**
 * main.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include "mainWindow.hpp"

#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->setWindowTitle("Tower Mapedit");
    mainWindow->show();
    return app.exec();
}
