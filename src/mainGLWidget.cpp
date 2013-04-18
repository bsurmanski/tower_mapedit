/**
 * mainGLWidget.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */


#include "mainGLWidget.hpp"

int MainGLWidget::keyMap[CONTROLS_LAST] = 
{
    Qt::Key_Up,
    Qt::Key_Down,
    Qt::Key_Left,
    Qt::Key_Right,
    Qt::Key_Plus,
    Qt::Key_Minus,

    //Mouse
    Qt::LeftButton,
    Qt::RightButton,
};

MainGLWidget::MainGLWidget(QWidget *parent) : QGLWidget(parent), timer(this)
{
    map = NULL;
    memset(keys, 0, sizeof(uint8_t[KEY_LAST]));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer.start(16);
    setFocus();
    setMouseTracking(true);
}

MainGLWidget::~MainGLWidget()
{
    glbDeleteProgram(drawProgram);
}

void MainGLWidget::initializeGL()
{
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    //glEnable(GL_SCISSOR_TEST);
   // glEnable(GL_DEBUG_OUTPUT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glGenQueries(1, &primQuery);

    drawProgram = glbCreateProgram(NULL);
    glbProgramAttachNewShaderSourceFile(drawProgram, "glsl/drawmap.vs", GLB_VERTEX_SHADER);
    glbProgramAttachNewShaderSourceFile(drawProgram, "glsl/drawmap.fs", GLB_FRAGMENT_SHADER);
    pickProgram = glbCreateProgram(NULL);
    glbProgramAttachNewShaderSourceFile(pickProgram, "glsl/pickmap.vs", GLB_VERTEX_SHADER);
    glbProgramAttachNewShaderSourceFile(pickProgram, "glsl/pickmap.fs", GLB_FRAGMENT_SHADER);
    pickTexture = glbCreateTexture(0, GLB_2INT16, 640, 480, 1, NULL, NULL);
    pickBuffer = glbCreateFramebuffer(NULL); 
    glbFramebufferColor(pickBuffer, 0, pickTexture);
    glbProgramOutput(pickProgram, pickBuffer);
}

void MainGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MainGLWidget::paintGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glbFramebufferClear(pickBuffer);
    glBeginQuery(GL_PRIMITIVES_GENERATED, primQuery);

    if(map)
    {
        map_draw(map, drawProgram);
        map_draw(map, pickProgram);
    }

    glEndQuery(GL_PRIMITIVES_GENERATED);
}

void MainGLWidget::newMap(int w, int h)
{
    if(map) map_delete(map);
    map = map_new(w, h, (Tile*) calloc(w * h, sizeof(Tile)));
}

bool MainGLWidget::event(QEvent *event)
{
    //set appropriate 'keys' value to 1 on keydown, 0 on release
    if(event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        int i;
        for(i = 0; i < KEY_LAST; i++)
        {
            if(keyMap[i] == ke->key())
            {
                keys[i] = event->type() == QEvent::KeyPress;
            }
        }
    } else if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        mousePos[0] = me->x();
        mousePos[1] = 480 - me->y() - 26;
    } else if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);

        int i;

        for(i = KEY_LAST; i < MOUSE_LAST; i++)
        {
            if((unsigned) keyMap[i] == me->button())
            {
                keys[i] = event->type() == QEvent::MouseButtonPress;
            }
        }
    }


    else if (event->type() == QEvent::Enter)
    {
        setFocus();
    }

    return QGLWidget::event(event);
}

void MainGLWidget::timeout()
{
    if(keys[KEY_UP])
    {
        map_move(map, 0, 0, 0.5f);
    } 
    
    if(keys[KEY_DOWN])
    {
        map_move(map, 0, 0, -0.5f);
    }

    if(keys[KEY_LEFT])
    {
        map_move(map, 0.5f, 0, 0);
    }

    if(keys[KEY_RIGHT])
    {
        map_move(map, -0.5f, 0, 0);
    }

    if(keys[KEY_ZOOMIN])
    {
        map_zoom(map, 0.1f);
    }

    if(keys[KEY_ZOOMOUT])
    {
        map_zoom(map, -0.1f);
    }

    if(keys[MOUSE_LEFT])
    {
        uint16_t coord[2]; 
        int region[2] = {1,1};
        glbFramebufferReadColor(pickBuffer, 0, mousePos, region, coord);
        printf("MOUSE: %d, %d\n", mousePos[0], mousePos[1]);
        printf("COORD: %d, %d\n", coord[0], coord[1]);
        if(coord[0] != 0xffff && coord[1] != 0xffff)
        {
            map_setTexture(map, coord[0], coord[1], 1);
        }
    }

    updateGL();
}
