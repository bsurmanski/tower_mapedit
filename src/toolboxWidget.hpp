/**
 * toolsWidget.hpp
 * tower/mapedit
 * April 18, 2013
 * Brandon Surmanski
 */

#ifndef _TOOLSWIDGET_HPP
#define _TOOLSWIDGET_HPP

#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QTabWidget>
#include <QPixmap>
#include <QLabel>
#include "FlowLayout.h"

class ToolboxWidget : public QWidget
{
    Q_OBJECT
    public:
        ToolboxWidget(QWidget *parent = 0);

    protected:

        /**
         * Tooltypes groupbox
         */
        class ToolTypeBox : public QGroupBox
        {
            public:
                ToolTypeBox(QWidget *parent = 0);
            protected:

            enum ButtonTypes
            {
                BUTTON_PENCIL = 0,
                BUTTON_RECT,
                BUTTON_LINE,
                BUTTON_FILL,
                BUTTON_LAST,
            };

            FlowLayout boxLayout;
            QButtonGroup toolButtonGroup;
            QPushButton *tooltypes[BUTTON_LAST];
        };

        /**
         * Tool tabwidget
         */
        class ToolTabWidget : public QTabWidget
        {
            public:
                ToolTabWidget(QWidget *parent = 0); 
            protected:

                class ToolTextureTab : public QWidget
                {
                    public:
                        ToolTextureTab(QWidget *parent = 0);
                    protected:
                        FlowLayout tabLayout;
                        QLabel currentTexture; 
                        QButtonGroup texButtonGroup;
                        QPushButton *texButtons[16];
                        QPixmap *textures[16];
                };

                class ToolHeightTab : public QWidget
                {
                    public: 
                        ToolHeightTab(QWidget *parent = 0); 
                };

                ToolTextureTab textureTab;
                ToolHeightTab heightTab;
                //TODO item and model tabs
        };


        QVBoxLayout layout; 
        ToolTypeBox toolTypeBox;
        ToolTabWidget toolTabWidget;
    
};

#endif
