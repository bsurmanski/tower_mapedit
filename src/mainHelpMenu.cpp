/**
 * mainHelpMenu.cpp
 * tower/mapedit
 * April 20, 2013
 * Brandon Surmanski
 */

#include <QMessageBox>
#include <QPixmap>

#include "mainHelpMenu.hpp"

MainHelpMenu::MainHelpMenu(QWidget *parent) : 
                            QMenu("Help", parent),
                            aboutAction("&About", this)
{
    connect(&aboutAction, SIGNAL(triggered()), this, SLOT(openAbout()));
    this->addAction(&aboutAction);
}

void MainHelpMenu::openAbout()
{
    QMessageBox about(this);
    //about.setIconPixmap(QPixmap("res/icons/emblem-web.png"));
    about.setText(
            "\
            <b>Tower - Map Editor</b><p/>\
            Copyright 2013 <p/>\
            Brandon Surmanski <p/>\
            <br/>\
            This program's source is availible online<p/>\
            under the MIT open source license, visit: <p/>\
            <a href=www.github.com/bsurmanski/tower_mapedit>\
            www.github.com/bsurmanski/tower_mapedit</a><p/>\
            <br/>\
            Icon set courtesy of the Oxygen Icon Theme.<p/>\
            Visit <a href=www.oxygen-icons.org>www.oxygen-icons.org</a>\
            "
            );
    about.exec();
}
