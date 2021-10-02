#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QSvgRenderer>

class ImageRotator : public QObject
{
    Q_OBJECT
public:
    explicit ImageRotator(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType, const QString *slash, const QString *svgType, QObject *parent);
    ~ImageRotator();
    void setParams(QString &tile, QString &azm, QString &layer, char &firstNum, char &secondNum, char &thirdNum);
private:
    QFile *m_file;
    const QString *m_pathToSourceSvg;
    const QString *m_pathToRendedImage;
    const QString *m_fileType;
    const QString *m_slash;
    const QString *m_svgType;

    QImage *m_image;
    QSvgRenderer *m_renderer;
    QPainter *m_painter;
    int index;
    char m_previousCharInArray;


    char m_firstNum;
    char m_secondNum;
    char m_thirdNum;
    QString m_tileName;
    QString m_layer;
    QString m_azm;

    QByteArray m_array;

public Q_SLOTS:
    void doing();
Q_SIGNALS:
    void finished();
};
#endif // FILEREADER_H
