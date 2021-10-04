#include <QCoreApplication>
#include <QDir>
#include <QDomDocument>
#include <QDebug>

void checkFolderAndCreateInNotExists(QString &path)
{
    if(!(QDir(path).exists()))
    {
        QDir().mkdir(path);
    }
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

void writeSvgDocumentToFile(QDomDocument &document, QString &sourceFolder, QString &fileName)
{
    QString fullPath=sourceFolder+fileName;
    QFile file( fullPath );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qFatal( "Failed to open file for writing." );
    }
    QTextStream stream( &file );
    stream << document.toString();
    file.close();
}

void insertImage(QDomDocument &document, QString fileName)
{
    QDomElement svg=document.firstChildElement();
    QDomElement defs=svg.childNodes().at(1).toElement();
    defs.setAttribute("overflow", "visible");
    defs.setAttribute("style", "stroke:none;");
    QDomNodeList firstElemChildrens=defs.firstChildElement().childNodes();
    for (int i=0; i<firstElemChildrens.count(); i++)
    {
        QDomElement symbol=firstElemChildrens.at(i).toElement();
        symbol.removeAttribute("overflow");
        if (!symbol.hasAttribute("id"))
        {
            qFatal("Нет аттрибута");
        }
        else
        {
            QString symbolId=symbol.attribute("id");
            symbol.removeAttribute("id");
            QDomElement path=symbol.firstChildElement();
            path.removeAttribute("style");
            path.setAttribute("id", symbolId);
        }
    }
    QDomElement imageElement=document.createElement("image");
    fileName.remove("svg").append("jpg");
    imageElement.setAttribute("xlink:href", fileName);
    imageElement.setAttribute("height", "279");
    imageElement.setAttribute("width", "497");
    svg.insertBefore(imageElement, svg.lastChildElement());
}

int main(int argc, char *argv[])
{
    QString layer="8";
    QString folderRead="E:\\MAP 2.0\\MapText\\Inkscaped\\"+layer+"\\";
    QString folderWrite="E:\\MAP 2.0\\MapText\\WithImage\\"+layer+"\\";
    QDir sourseMapDirectory(folderRead);
    checkFolderAndCreateInNotExists(folderWrite);
    QStringList tiles = sourseMapDirectory.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);
    for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
    {
        QDomDocument *doc= new QDomDocument();
        readSvgDocumentFromFile(*doc, folderRead, *tile);
        insertImage(*doc, *tile);
        writeSvgDocumentToFile(*doc, folderWrite, *tile);
        delete doc;
    }
    return 0;
}
