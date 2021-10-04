#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QList>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtMath>
#include <QPointF>

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

void checkFolderAndCreateInNotExists(QString &path)
{
    if(!(QDir(path).exists()))
    {
        QDir().mkdir(path);
    }
}

void RemoveImageFromSvgDocumentTextOnly(QDomDocument &svgDocumentTextOnly,QString &destinationNoAzm, QString &tile)
{
    QDomElement svg=svgDocumentTextOnly.firstChildElement();
    qDebug()<< "svg.tagName() " << svg.tagName();
    QDomNodeList defsChildrens=svg.firstChildElement().childNodes();
    for (int i=defsChildrens.count(); i>0; i--)
    {
        svg.firstChildElement().removeChild(defsChildrens.at(i));
    }
    QDomNodeList svgsChildres= svg.lastChildElement().childNodes();
    qDebug()<< "Находим начало слов, позицию в файле";
    //    qDebug()<< svgsChildres.count();
    int startIndexOfCoords=0;
    for (int i=svgsChildres.count()-1; i>=0; i--)
    {
        QDomElement elem=svgsChildres.at(i).toElement();
        if(elem.tagName()=="use")
        {
            startIndexOfCoords=i+1;
            break;
        }
        if(elem.tagName()=="path")
        {
            if (elem.hasAttribute("style"))
            {
                if (!(elem.attribute("style").contains("rgb(100%,100%,100%)")||elem.attribute("style").contains("fill-rule:nonzero;comp-op:darken")))
                {
                    startIndexOfCoords=i+1;
                    break;
                }
            }
            else
            {
                if (elem.tagName()!="g")
                {
                    startIndexOfCoords=i+1;
                    break;
                }
            }
        }
    }
    if (startIndexOfCoords==0)
    {
        qFatal(" не найдена стартовая точка у тайла" );
    }
    qDebug()<< "Позицию в файле равна " << startIndexOfCoords << " всего элементов " << svgsChildres.count();
    startIndexOfCoords--;
    for (int i=startIndexOfCoords; i>=0; i--)
    {
        svg.lastChildElement().removeChild(svgsChildres.at(i));
    }



    int gFirst=0;
    for (int i=0; i<svgsChildres.count(); i++)
    {
        QDomElement gElem=svgsChildres.at(i).toElement();
        if (gElem.tagName()=="g")
        {
            if (gFirst==0)
            {
                gFirst=i;
            }
            else
            {
                if (!gElem.hasAttribute("d"))
                {
                    QDomElement useElem=gElem.firstChildElement();
                    svgsChildres.at(gFirst).appendChild(useElem);
                    gElem.removeChild(useElem);
                }
            }

        }
        else
        {
            gFirst=0;
        }
    }

    for (int i=svgsChildres.count()-1; i>0; i--)
    {
        QDomElement gElem=svgsChildres.at(i).toElement();
        if (gElem.tagName()=="g")
        {
            if (gElem.childNodes().count()==0)
            {
                svg.lastChildElement().removeChild(gElem);
            }
        }
    }


    QString fullPath=destinationNoAzm+tile;
    QFile file( fullPath );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qFatal( "Failed to open file for writing." );
    }
    QTextStream stream( &file );
    stream << svgDocumentTextOnly.toString();
    file.close();
}

int main(int argc, char *argv[])
{
    qDebug()<< "Программа раделеления тайлов с текcтом";
    qDebug()<< "вырезается слой катринки";
    QString layer="10";
    QString sourseMap="E:\\MAP 2.0\\MapText\\Sources\\"+layer+"\\";
    qDebug()<< "Исходники: " << sourseMap;
    QString destinationText="E:\\MAP 2.0\\MapText\\TextOnly\\"+layer+"\\";
    qDebug()<< "Результат в папке : " << destinationText;
    checkFolderAndCreateInNotExists(destinationText);

    QStringList tiles =getSvgFileListInFolder(sourseMap);
    for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
    {
        QDomDocument svgDocumentTextOnly;
        readSvgDocumentFromFile(svgDocumentTextOnly, sourseMap, *tile);
        qDebug()<< *tile;
        RemoveImageFromSvgDocumentTextOnly(svgDocumentTextOnly, destinationText, *tile);
        int fdfsd=4;
    }
    qDebug()<< "Слова в тайле разделены. Результат в папке: " << destinationText;

    return 0;
}
