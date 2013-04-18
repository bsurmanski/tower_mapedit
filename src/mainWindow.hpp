/**
 * mainWindow.hpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#ifndef _MAINWINDOW_HPP
#define _MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QMenuBar>

#include "mainMenuBar.hpp"
#include "mainFileMenu.hpp"
#include "mainGLWidget.hpp"

class MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        static MainWindow *getInstance();

    public slots: 
        void newMap(int x, int y);

    private:
        MainMenuBar menuBar;
        MainGLWidget *glWidget;
        static MainWindow *instance;
};

#endif
