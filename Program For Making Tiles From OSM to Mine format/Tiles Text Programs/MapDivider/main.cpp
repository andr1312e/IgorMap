#include <QDir>
#include <QDebug>
#include <QDomDocument>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug()<< "Программа разделения на текстовы и без текстовые тайлы";
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QString layer="10";
    qDebug()<<layer;
    QString sourseMap="E:\\Релиз\\ИСХОДНИКИ\\"+layer+"\\";
    qDebug()<< "Исходники: " << sourseMap;
    QString destination="E:\\MAP 2.0\\MapText\\Sources\\"+layer+"\\";
    qDebug()<< "Результат в папке : " << destination;
//    QString destinationNoAzm=destination+"\\noAzm\\";
//    QString destinationAzm=destination+"\\Azm\\";
//    if(!(QDir(destinationNoAzm).exists()))
//    {
//        QDir().mkdir(destinationNoAzm);
//    }
//    if (!(QDir(destinationAzm).exists()))
//    {
//        QDir().mkdir(destinationAzm);
//    }
    QDir sourseMapDirectory(sourseMap);
    QStringList tiles = sourseMapDirectory.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);
    for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
    {
        QString fullPath=sourseMap+*tile;
        QDomDocument svgDocument;
        QFile svgFile(fullPath);
        svgFile.open(QFile::ReadOnly | QFile::Text);
        qDebug()<< fullPath << "Размер " << svgFile.size();
        svgDocument.setContent(&svgFile);
        svgFile.close();
        QDomElement svg=svgDocument.firstChildElement();
        QDomNodeList useS=svgDocument.elementsByTagName("use");
        qDebug()<< QString::number(useS.count()) + " - Колличество элеметов <use>";
        bool hasText=false;
        for (int i=0; i<useS.count(); i++)
        {
            QDomElement use=useS.at(i).toElement();
            if(use.hasAttribute("x"))
            {
                hasText=true;
                break;
            }
        }
        if (hasText)
        {
            QFile::copy(fullPath, destination+*tile);
        }
//        else
//        {
//            QFile::copy(fullPath, destinationNoAzm+*tile);
//        }
    }
    qDebug()<< "Тайлы разделены на текстовы и без текстовые";
}
