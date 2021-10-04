#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void convertToPng()
{
    QFile file("command.txt");
    file.resize(0);
    QTextStream out(&file);
    QString layer="10";
    QString sourseMap="E:\\MAP 2.0\\MapNoText\\svg\\"+layer+"\\";
    QDir sourseMapDirectory(sourseMap);
    QStringList tiles = sourseMapDirectory.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);
    if(file.open(QIODevice::Append))
    {
        for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
        {
                QString name=*tile;
                name.remove(name.length()-4, 4);
                QString commandLine="file-open:"+ name+".svg; export-filename:"+ name+".png; export-width:497; export-do; file-close; quit-inkscape;\n";
                out<<commandLine;
        }
    }
    file.close();
}

void createConvertToInkscapeFile()
{
    QFile file("command.txt");
    file.resize(0);
    QTextStream out(&file);
    QString layer="10";
    QString sourseMap="E:\\MAP 2.0\\MapText\\TextOnly\\"+layer+"\\";
    QDir sourseMapDirectory(sourseMap);
    QStringList tiles = sourseMapDirectory.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);
    if(file.open(QIODevice::Append))
    {
        for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
        {
            QString commandLine="file-open:"+*tile+"; export-filename:.\\inkscape\\"+*tile+"; export-do; file-close; quit-inkscape;\n" ;
            out<<commandLine;
        }
    }
    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    createConvertToInkscapeFile();
    qDebug()<< "Готово";
    return 0;
}
