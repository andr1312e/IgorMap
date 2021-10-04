#include <QDir>
#include <QDomDocument>
//#include <QTextCodec>
#include <QDebug>


QStringList getSvgFileListInFolder(QString &sourseMap){
    QDir sourseMapDirectory(sourseMap);
    return sourseMapDirectory.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);
}

void readSvgDocumentFromFile(QDomDocument &document, QString &sourceFolder, QString &fileName)
{
    QString fullPath=sourceFolder+fileName;
    QFile svgFile(fullPath);
    svgFile.open(QFile::ReadOnly | QFile::Text);
    qDebug()<< fullPath << "Размер " << svgFile.size();
    document.setContent(&svgFile);
    svgFile.close();
}

int main(int argc, char *argv[])
{
    qDebug()<< "Программа отчистки слов в тайле";
    //    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QString layer="10";
    QString sourseMap="E:\\Релиз\\Исходники\\"+layer+"\\";
    qDebug()<< "Исходники: " << sourseMap;
    QString destination="E:\\MAP 2.0\\MapNoText\\svg\\"+layer+"\\";
    qDebug()<< "Результат в папке : " << destination;
    if(!(QDir(destination).exists()))
    {
        QDir().mkdir(destination);
    }
    QStringList tiles =getSvgFileListInFolder(sourseMap);
    for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
    {
        QDomDocument *svgDocument=new QDomDocument();
        readSvgDocumentFromFile(*svgDocument, sourseMap, *tile);

        QDomElement svg=svgDocument->firstChildElement();
        QDomElement g=svg.lastChildElement();
        qDebug()<< g.attribute("id");
        QDomNodeList childrensAtLastTag=g.childNodes();
        qDebug()<< QString::number(childrensAtLastTag.count()) + " - Колличество элеметов в теге последний";
        int startIndexOfCoords = 0;
        qDebug()<< "Находим начало слов, позицию в файле";
        for (int i=childrensAtLastTag.count()-1; i>=0; i--)
        {
//            qDebug()<< i;
            QDomElement currentElement=childrensAtLastTag.at(i).toElement();
//            qDebug()<< currentElement.tagName();
            if(currentElement.tagName()=="path")
            {
                if (currentElement.hasAttribute("style"))
                {
                    if (!(currentElement.attribute("style").contains("rgb(100%,100%,100%)")
                          ||currentElement.attribute("style").contains("stroke:none;fill-rule:nonzero;comp-op:darken;fill:rgb(34")
                          ||currentElement.attribute("style").contains("fill-rule:nonzero;comp-op:darken;fill:rgb")))
                    {
//                        qDebug()<< currentElement.attribute("style");
                        startIndexOfCoords=i;
                        break;
                    }
                }
            }
            else
            {
                //                qDebug()<< elem.tagName();
                if (currentElement.tagName()!="g")
                {
                    startIndexOfCoords=i;
                    break;
                }
            }
        }
        if (startIndexOfCoords!=0)
        {
            for (int i=childrensAtLastTag.count()-1; i>startIndexOfCoords; i--)
            {
                g.removeChild(childrensAtLastTag.at(i));
            }
        }
        qDebug()<< "Позицию в файле равна " << startIndexOfCoords;
        QString fullPath=destination+*tile;
        QFile file( fullPath );
        if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            qDebug( "Не могу открыть файл для записи." );
            return -1;
        }
        QTextStream stream( &file );
        stream << svgDocument->toString();
        file.close();
        delete svgDocument;
    }
    qDebug()<< "Слова в тайле отчищены. Результат в папке: " << destination;

    return 0;
}
