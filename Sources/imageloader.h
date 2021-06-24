#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QImage>
#include <QSvgRenderer>
#include <QPainter>
class ImageLoader : public QObject
{
    Q_OBJECT
public:
    ImageLoader(QString &pathToSourceSvg, QString &pathToRendedImage, QString &fileType, int width, int height);
    ~ImageLoader();
    void setParams(QString &tile, QString &layer, bool hasAzm, QString &azm);
    QString il_tilename;
    QString il_layer;
    QString il_azm;
    bool il_hasAzm;
public slots:
    void doing();
signals:
    void finished();
private:
    QImage *m_image;
    QSvgRenderer *m_renderer;
    QPainter *m_painter;
    QString *m_pathToRendedImage;
    QString *m_pathToSourceSvg;
    QString *m_fileType;
};

#endif // IMAGELOADER_H
