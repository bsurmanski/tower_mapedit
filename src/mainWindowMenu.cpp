/**
 * mainWindowMenu.cpp
 * tower/mapedit
 * April 18, 2013
 * Brandon Surmanski
 */

#include "mainWindowMenu.hpp"
#include "toolboxWidget.hpp"

MainWindowMenu::MainWindowMenu(QWidget *parent) :
                QMenu(tr("Windows"), parent),
                toolboxAction(tr("Open Toolbox"), this)
{
    connect(&toolboxAction, SIGNAL(triggered()), this, SLOT(openToolbox()));
    this->addAction(&toolboxAction);
}

void MainWindowMenu::openToolbox()
{
    ToolboxWidget *toolbox = new ToolboxWidget();
    toolbox->show(); //TODO: memory leak on toolbox
}
