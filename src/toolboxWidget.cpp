/**
 * toolsWidget.cpp
 * tower/mapedit
 * April 18, 2013
 * Brandon Surmanski
 */

#include "toolboxWidget.hpp"

extern "C"
{
    #include <glb/glb.h> //TGA loading
}

/*{{{ ToolboxWidget*/
ToolboxWidget::ToolTypeBox::ToolTypeBox(QWidget *parent) : 
                    QGroupBox("Tools", parent),
                    boxLayout(this),
                    toolButtonGroup(this)
{
    const char *const icons[] = 
    {
        "res/icons/draw-brush.png",
        "res/icons/fill-color.png",
        "res/icons/select-rectangular.png",
        "res/icons/draw-path.png"
    };

    for(int i = 0; i < BUTTON_LAST; i++)
    {
        tooltypes[i] = new QPushButton(this); 
        tooltypes[i]->setIcon(QIcon(QPixmap(icons[i])));
        tooltypes[i]->setCheckable(true);
        boxLayout.addWidget(tooltypes[i]);
        toolButtonGroup.addButton(tooltypes[i]);
    }

    tooltypes[0]->setChecked(true);
    toolButtonGroup.setExclusive(true);
}/*}}}*/

/*{{{ ToolTabWidget*/

/*{{{ ToolTextureTab*/

/**
 * i attempted to create a plugin for Qt, but that seemed imcomprehensible.
 * Good nuf!
 */
static QPixmap tgaToQPixmap(const char *filenm)
{
        GLBTexture *texture = glbCreateTextureWithTGA(GLB_READ_WRITE, filenm, NULL);
        const int *const texSize = glbTextureSize(texture);
        QImage image = QImage(texSize[0], texSize[1], QImage::Format_ARGB32);
        int origin[2] = {0, 0};
        glbReadTexture(texture, 0, origin, texSize, GLB_RGBA, 0, image.bits());
        glbDeleteTexture(texture);
        return QPixmap::fromImage(image);
}

ToolboxWidget::ToolTabWidget::ToolTextureTab::ToolTextureTab(QWidget *parent) :
                    QWidget(parent),
                    tabLayout(this),
                    currentTexture(this),
                    texButtonGroup(this)
{
    for(int i = 0; i < 16; i++)
    {
        texButtons[i] = new QPushButton(this);
        texButtons[i]->setIcon(QIcon(tgaToQPixmap("res/tex/grass.tga")));
        texButtons[i]->setCheckable(true);
        tabLayout.addWidget(texButtons[i]);
        texButtonGroup.addButton(texButtons[i]);
    }
    texButtons[0]->setChecked(true);
    texButtonGroup.setExclusive(true);
    setLayout(&tabLayout);
}/*}}}*/

/*{{{ ToolHeightTab*/
ToolboxWidget::ToolTabWidget::ToolHeightTab::ToolHeightTab(QWidget *parent) :
                    QWidget(parent)
{

}
/*}}}*/

ToolboxWidget::ToolTabWidget::ToolTabWidget(QWidget *parent) :
                    QTabWidget(parent),
                    textureTab(this),
                    heightTab(this)
{
    addTab(&textureTab, "Texture");
    addTab(&heightTab, "Heightmap");
}/*}}}*/

ToolboxWidget::ToolboxWidget(QWidget *parent) : 
                    QWidget(parent),
                    layout(this),
                    toolTypeBox(this),
                    toolTabWidget(this)
{
    layout.addWidget(&toolTypeBox); 
    layout.addWidget(&toolTabWidget);
}
