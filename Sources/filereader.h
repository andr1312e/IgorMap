#ifndef FILEREADER_H
#define FILEREADER_H
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>
class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QString &pathToSourceSvg);
    ~FileReader();
    QString m_tileName;
    QString m_layer;
    QString m_azm;
    void setParams(QString &tile, QString &azm, QString &layer);
private:
    int m_currentPositionInFile=0;
    QString m_pathToSourceSvg;
    char m_previousCharInArray=' ';
    QByteArray *m_array;
    QFile *m_file;
    QFile *m_fileCoords;
public slots:
    void doing();
signals:
    void finished();
};
#endif // FILEREADER_H
