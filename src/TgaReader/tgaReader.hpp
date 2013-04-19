/**
 * tgaReader.hpp
 * tower/mapedit
 * April 18, 2013
 * Brandon Surmanski
 */

#ifndef _TGAREADER_HPP
#define _TGAREADER_HPP

#include <QImageIOPlugin>
#include <QImageIOHandler>
#include <QStringList>
#include <QVariant>
#include <QIODevice>
#include <QDataStream>

class TgaPlugin : public QImageIOPlugin
{
    Q_OBJECT
    public:
        TgaPlugin();
        QStringList keys() const;
        Capabilities capabilities(QIODevice *device, 
                                  const QByteArray &format) const;
        QImageIOHandler *create(QIODevice *device, 
                                const QByteArray &format = QByteArray()) const;
};

class TgaHandler : public QObject, public QImageIOHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.tga" FILE "tga.json")
    public:
        TgaHandler();
        bool canRead() const;
        bool read(QImage *image);
        bool write(const QImage &image);

        QByteArray name() const;

        static bool canRead(QIODevice *device);

        QVariant option(ImageOption option) const;
        void setOption(ImageOption option, const QVariant &value);
        bool supportsOption(ImageOption option);
};

#endif


