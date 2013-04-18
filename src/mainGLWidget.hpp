/**
 * mainGLWidget.hpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#ifndef _MAINGLWIDGET_HPP
#define _MAINGLWIDGET_HPP

#include <QGLWidget>
#include <QKeyEvent>
#include <QEvent>
#include <QTimer>
#include <GL/gl.h>
#include <GL/glext.h>

extern "C" {
    #include <glb/glb.h>
    #include "map.h"
}

class MainGLWidget : public QGLWidget
{
    Q_OBJECT
    public:
        MainGLWidget(QWidget *parent = 0);
        ~MainGLWidget();
        void newMap(int w, int h);

    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        bool event(QEvent *event);

    protected slots:
        void timeout();

    private:
        enum Controls
        {
            KEY_UP = 0,
            KEY_DOWN,
            KEY_LEFT,
            KEY_RIGHT,
            KEY_ZOOMIN,
            KEY_ZOOMOUT,

            KEY_LAST,

            MOUSE_LEFT = KEY_LAST,
            MOUSE_RIGHT,
            MOUSE_LAST,

            CONTROLS_LAST = MOUSE_LAST,
        };

        static int keyMap[CONTROLS_LAST];

        int mousePos[2];
        uint8_t keys[CONTROLS_LAST];

        GLuint primQuery;
        QTimer timer;
        GLBProgram *drawProgram;
        GLBProgram *pickProgram;
        GLBTexture *pickTexture;
        GLBFramebuffer *pickBuffer;
        Map *map;
};

#endif
