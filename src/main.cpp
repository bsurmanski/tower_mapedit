/**
 * main.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include "mainWindow.hpp"
#include "toolboxWidget.hpp"

#include "TgaReader/tgaReader.hpp"

#include <QApplication>
#include <QCoreApplication>
#include <QPluginLoader>

//Q_IMPORT_PLUGIN(TgaPlugin);

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    return app.exec();
}
