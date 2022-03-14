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
    explicit ImageRotator(const QString &pathToSourceSvg, const QString &pathToRendedImage, const QString &fileType, const char slash, const QString &svgType, QObject *parent);
    ~ImageRotator();
    void SetParams(const QString &tile, QString &azm, QString &layer, char firstNum, char secondNum, char thirdNum);
private:
    QFile * const m_file;
    const QString m_pathToSourceSvgFolder;
    const QString m_pathToRendedImageFolder;
    const QString m_fileType;
    const char m_slash;
    const QString m_svgType;

    QImage *const m_image;
    QSvgRenderer * const m_renderer;
    QPainter *const m_painter;
    QString m_pathToSource;
    QString m_pathToRender;
    int index;
    char m_previousCharInArray;


    char m_firstNum;
    char m_secondNum;
    char m_thirdNum;

    const char m_openBracket;
    const char m_whiteSpace;

    QByteArray m_array;

public Q_SLOTS:
    void OnMakingImage();
Q_SIGNALS:
    void ToFinished();
};
#endif // FILEREADER_H
