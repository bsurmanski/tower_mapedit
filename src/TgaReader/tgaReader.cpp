/**
 * tgaReader.cpp
 * tower/mapedit
 * April 19, 2013
 * Brandon Surmanski
 */

#include <stdint.h>
#include <cstdio>

#include "tgaReader.hpp"

/*{{{ TgaPlugin*/
TgaPlugin::TgaPlugin()
{
    printf("plugin created!\n");
}

QStringList TgaPlugin::keys() const
{
    return QStringList() << "tga";
}

QImageIOPlugin::Capabilities TgaPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
    if(format ==  "tga")
    {
        return Capabilities(CanRead);
    }

    return 0;
}

QImageIOHandler *TgaPlugin::create(QIODevice *device, const QByteArray &format) const
{
    printf("Iohandler created!\n");
    TgaHandler *handler = new TgaHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

/*}}}*/

/*{{{ TgaHandler*/

class TgaHeader {
    uint8_t id_len;
    uint8_t cmap_type;
    uint8_t img_type;

    //Colormap Specification
    class TgaHeaderCmap {
        uint16_t offset;
        uint16_t len;
        uint8_t entry_sz;
    } cmap;

    //Image specification
    class TgaHeaderImg {
        uint16_t xorg;
        uint16_t yorg;
        uint16_t w;
        uint16_t h;
        uint8_t depth;
        uint8_t discriptor;
    } img;
};

TgaHandler::TgaHandler()
{

}

bool TgaHandler::canRead() const
{
    return true;
}

bool TgaHandler::read(QImage *image)
{
    QIODevice *dev = device();
    TgaHeader header;
    dev->read((char*) &header, sizeof(TgaHeader));
    printf("Read TGA header\n");
    return true;
}

bool TgaHandler::write(const QImage &image)
{
    return false;
}


QByteArray TgaHandler::name() const
{
    return "tga";
}


bool TgaHandler::canRead(QIODevice *device)
{
    return true;
}


QVariant TgaHandler::option(ImageOption option) const
{
    return QVariant();
}

void TgaHandler::setOption(ImageOption option, const QVariant &value)
{

}

bool TgaHandler::supportsOption(ImageOption option)
{
    return true;
}

/*}}}*/
