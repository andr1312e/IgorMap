#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QDir>
#include <QTextCodec>
#include <QDomDocument>
#include <QList>
#include <QPair>
#include <QRegExp>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtMath>
#include <QPointF>
#include <QSvgRenderer>
#include <QImage>
#include <QPainter>

//const int angle=340;
const double charecterHight=3.0;
const double doubleComparator=0.001;

struct FourPoints{
    qreal x;
    qreal y;
    qreal centerX;
    qreal centerY;

    FourPoints(){
        x=0.0;
        y=0.0;
        centerX=0.0;
        centerY=0.0;
    }
};

struct CirclePoint{
    qreal xCircle;
    qreal yCircle;
    qreal xUse;
    qreal yUse;

    CirclePoint(){
        xCircle=0.0;
        yCircle=0.0;
        xUse=0.0;
        yUse=0.0;
    }
};

struct Circle{
    qreal x;
    qreal y;
    qreal radius;

    Circle(){
        x=0.0;
        y=0.0;
        radius=0.0;
    }
};

void captureFirstTwoNumbersFromText(double &first, double &second, QString &text)
{
    QRegExp re(QString::fromLatin1("([+-]?\\d*\\.?\\d+)|(\\d+)"));
    QStringList capturedText;
    int pos = 0;
    int count=0;
    while (((pos = re.indexIn(text, pos)) != -1)&&(count<2)) {
        capturedText << re.cap(1);
        pos += re.matchedLength();
        count++;
    }
    if (capturedText.count()==2)
    {
        first=capturedText.at(0).toDouble();
        second=capturedText.at(1).toDouble();
    }
    else
    {
        if (capturedText.count()==1)
        {
            first=capturedText.at(0).toDouble();
            second=0.0;
            qDebug()<< text;
        }
        else
        {
            qFatal("cant capture 2 points check file");
        }
    }
}

void captureLastTwoNumbersFromText(double &first, double &second, QString &text)
{
    const int countNum=6;
    QRegExp re("([+-]?\\d*\\.?\\d+)|(\\d+)");
    QStringList capturedText;
    int pos = 0;
    int count=0;
    while (((pos = re.indexIn(text, pos)) != -1)&&(count<countNum)) {
        capturedText << re.cap(1);
        pos += re.matchedLength();
        count++;
    }
    if (capturedText.count()==countNum)
    {
        first=capturedText.at(countNum-2).toDouble();
        second=capturedText.at(countNum-1).toDouble();
    }
    else
    {
        qFatal("cant capture transform matrix in circle check file");
    }
}

bool compareDoubles(double value1, double value2)
{
    return std::abs(value1 - value2) < doubleComparator;
}

bool chirclesHasUnion(Circle &first, Circle &second)
{
    double temp;
    temp=sqrt(pow((first.x-second.x), 2.) + pow((first.y-second.y), 2.));
    if(temp>(first.radius+second.radius) || temp+first.radius<second.radius || temp+second.radius<first.radius)
        return false;
    else
        return true;
}

QList<QList<QPointF>> PointIntoOneLine(QList<QPointF> &Points)
{
    QList<QList<QPointF>> listOfLineWords;
    int currentWord = 0;
    QPointF previousPoint = Points.at(0);
    listOfLineWords.append(QList<QPointF>());
    listOfLineWords[currentWord].append(Points.at(0));
    for (int i = 1; i < Points.count(); i++)
    {
        double distanceX = std::fabs(previousPoint.x() - Points[i].x());
        double distanceY = std::fabs(previousPoint.y() - Points[i].y());
        if (distanceX > 15.3 || distanceY > 0.8)
        {
            listOfLineWords.append(QList<QPointF>());
            currentWord++;
        }
        listOfLineWords[currentWord].append(Points[i]);
        previousPoint = Points[i];
    }
    return listOfLineWords;
}

QVector<QPointF> findCentersOfPoint(QList<QList<QPointF>> &listOfLineWords){
    QVector<QPointF> centersOfWords(listOfLineWords.count());
    for (int i = 0; i < listOfLineWords.count(); i++)
    {
        if (listOfLineWords[i].count() > 1)
        {
            qreal centerX = listOfLineWords[i][0].x() + (listOfLineWords[i][listOfLineWords[i].count()- 1].x() - listOfLineWords[i][0].x()) / 2.0 + ((listOfLineWords[i][1].x()-listOfLineWords[i][0].x())/2.0);
            qreal centerY = listOfLineWords[i][0].y() + (listOfLineWords[i][listOfLineWords[i].count()- 1].y() - listOfLineWords[i][0].y()) / 2.0 - charecterHight;
            centersOfWords[i]=QPointF(centerX, centerY);
        }
        else
        {
            centersOfWords[i]=QPointF(listOfLineWords[i][0].x(), listOfLineWords[i][0].y());
        }
    }
    return centersOfWords;
}

void findCenterOfWordsInMultipleRows(QVector<QPointF> &centersOfWords){
    int firstCenterIndex = -1;
    for (int i = 1; i < centersOfWords.count(); i++)
    {
        double distCentX = std::fabs(centersOfWords[i - 1].x() - centersOfWords[i].x());
        double distCentY = std::fabs(centersOfWords[i - 1].y() - centersOfWords[i].y());
        if (distCentX > 18 || distCentY > 25)
        {
            if (firstCenterIndex == -1)
            {
                continue;
            }
            else
            {
                double centX = centersOfWords[firstCenterIndex].x() + (centersOfWords[i - 1].x() - centersOfWords[firstCenterIndex].x()) / 2.0;
                double centY = centersOfWords[firstCenterIndex].y() + (centersOfWords[i - 1].y() - centersOfWords[firstCenterIndex].y()) / 2.0;
                for (int j = firstCenterIndex; j < i; j++)
                {
                    centersOfWords[j].setX(centX);
                    centersOfWords[j].setY(centY);
                }
                firstCenterIndex = -1;
            }
        }
        else
        {
            if (firstCenterIndex == -1)
            {
                firstCenterIndex = i - 1;
                if (i == centersOfWords.count() - 1)
                {
                    double centX = centersOfWords[firstCenterIndex].x() + (centersOfWords[i].x() - centersOfWords[firstCenterIndex].x()) / 2.0;
                    double centY = centersOfWords[firstCenterIndex].y() + (centersOfWords[i].y() - centersOfWords[firstCenterIndex].y()) / 2.0;
                    for (int j = firstCenterIndex; j <= i; j++)
                    {
                        centersOfWords[j].setX(centX);
                        centersOfWords[j].setY(centY);
                    }
                }
            }
        }
        if (i == centersOfWords.count() - 1)
        {
            if (firstCenterIndex != -1)
            {
                double centX = centersOfWords[firstCenterIndex].x() + (centersOfWords[i].x() - centersOfWords[firstCenterIndex].x()) / 2.0;
                double centY = centersOfWords[firstCenterIndex].y() + (centersOfWords[i].y() - centersOfWords[firstCenterIndex].y()) / 2.0;
                for (int j = firstCenterIndex; j <= (i); j++)
                {
                    centersOfWords[j].setX(centX);
                    centersOfWords[j].setY(centY);
                }
            }
        }
    }
}

void findNearLocatedPointsAndCircles(QVector<QVector<FourPoints>> &CoordAndCenters, QList<CirclePoint> &circles)
{
    for (int cirle = 0; cirle < circles.count(); cirle++)
    {
        for (int i = 0; i < CoordAndCenters.count(); i++)
        {
            double nearCicleX=circles.at(cirle).xUse;
            double nearCicleY=circles.at(cirle).yUse;
            double firstUseX=CoordAndCenters.at(i).at(0).x;
            double firstUseY=CoordAndCenters.at(i).at(0).y;
            if (compareDoubles(nearCicleX, firstUseX) && compareDoubles(nearCicleY, firstUseY))
            {
                for (int useIndex=0; useIndex<CoordAndCenters.at(i).count(); useIndex++)
                {
                    CoordAndCenters[i][useIndex].centerX=circles.at(cirle).xCircle;
                    CoordAndCenters[i][useIndex].centerY=circles.at(cirle).yCircle;
                }
            }

        }
    }
}

QVector<QVector<FourPoints>> makeReturnedStructWithCoordsAndCenters(QList<QList<QPointF>> &listOfLineWords,  QVector<QPointF> &centersOfWords)
{
    QVector<QVector<FourPoints>> result;
    result.resize(listOfLineWords.count());
    for (int i = 0; i < listOfLineWords.count(); i++)
    {
        result[i].resize(listOfLineWords[i].count());
        for (int j = 0; j < listOfLineWords[i].count(); j++)
        {
            FourPoints point;
            point.x=listOfLineWords[i][j].x();
            point.y=listOfLineWords[i][j].y();
            point.centerX = centersOfWords[i].x();
            point.centerY = centersOfWords[i].y();
            result[i][j]=point;
        }
    }
    return result;
}

static QVector<QVector<FourPoints>> TransformAllSymbols(QList<QPointF> &Points, QList<CirclePoint> &circles)
{
    //группируем точки которые в одну линию
    QList<QList<QPointF>> listOfLineWords;
    listOfLineWords=PointIntoOneLine(Points);
    //ищем центры отсортированных групп
    QVector<QPointF> centersOfWords=findCentersOfPoint(listOfLineWords);
    //слова в 2-3-4 ряда общий центр
    findCenterOfWordsInMultipleRows(centersOfWords);
    //обьеденяем полученные результаты
    QVector<QVector<FourPoints>> CoordAndCenters=makeReturnedStructWithCoordsAndCenters(listOfLineWords, centersOfWords);
    //точка и центр круга, смотрим если близко делаем круг центом, так как это названия городов и они должны вращаться вокруг точки
    findNearLocatedPointsAndCircles(CoordAndCenters, circles);
    return CoordAndCenters;
}

void applyTranslateToUse(QDomElement &use, double deltaX, double deltaY)
{
    if(use.tagName()=="use")
    {
        double x=use.attribute("x", 0).toDouble();
        double y=use.attribute("y", 0).toDouble();
        if (x!=0 && y!=0)
        {
            if(deltaX!=0 || deltaY!=0)
            {
                x=x+deltaX;
                y=y+deltaY;
                use.setAttribute("x", QString::number(x, 'g'));
                use.setAttribute("y", QString::number(y, 'g'));
            }
        }
        else
        {
            qFatal("не могу захватить переменые у use");
        }
    }
    else
    {
        qFatal("неизвесное имя тэга у точки");
    }
}

void getGElemTranform(QDomElement &gElem, double &gXTransform, double &gYTransform)
{
    if (gElem.tagName()==QLatin1String("g"))
    {
        if(gElem.hasAttribute("transform"))
        {
            QString tranform=gElem.attribute("transform");
            if(tranform.contains("translate"))
            {
                captureFirstTwoNumbersFromText(gXTransform, gYTransform, tranform);
                gElem.removeAttribute("transform");
            }
            else
            {
                qFatal("неизвесный параметр");
            }
        }
    }
    else
    {
        qFatal("неизвесное имя тэга у группы точек");
    }
}

void checkPointTranformAttributeAndApplyGlobalTransform(QDomElement &use, double xTranform,double yTranform)
{
    if (use.tagName()=="use")
    {
        double useXTransform=0.0, useYTransform=0.0;
        if (use.hasAttribute("transform"))
        {
            QString tranform=use.attribute("transform");
            if(tranform.contains("translate"))
            {
                captureFirstTwoNumbersFromText(useXTransform, useYTransform, tranform);
                use.removeAttribute("transform");
            }
            else
            {
                qFatal("неизвесный параметр");
            }
        }
        useXTransform=useXTransform+xTranform;
        useYTransform=useYTransform+yTranform;
        applyTranslateToUse(use, useXTransform, useYTransform);
    }
    else
    {
        qFatal("неизвесное имя тэга у точки в трансофрме");
    }
}

void checkGroupTranformAttribute(QDomElement &gElem)
{
    if (gElem.tagName()=="g")
    {
        double gTranformX=0.0, gTranformY=0.0;
        getGElemTranform(gElem, gTranformX, gTranformY);
        QDomNodeList uses=gElem.childNodes();
        for (int i=0; i<uses.count(); i++)
        {
            QDomElement use=uses.at(i).toElement();
            checkPointTranformAttributeAndApplyGlobalTransform(use, gTranformX, gTranformY);
        }
    }
    else
    {
        qFatal("неизвесное имя тэга у группы точек в трансофрме");
    }

}

void appendPointToList(QList<QPointF> &Points, QDomElement g)
{
    QDomNodeList uses=g.childNodes();
    qDebug()<< g.tagName();
    for (int i=0; i<uses.count(); i++)
    {
        QDomElement use=uses.at(i).toElement();
        const double x=use.attribute("x", 0).toDouble();
        const double y=use.attribute("y", 0).toDouble();
        if (x!=0 && y!=0)
        {
            Points.append(QPointF(x, y));
        }
        else
        {
            qFatal("не могу захватить X и Y у use");
        }
    }

}

void getCirlceRealLocation(QDomElement &circle, double &x, double &y){
    double transformX=0.0, transformY=0.0;
    QString transform=circle.attribute("transform");
    captureFirstTwoNumbersFromText(transformX, transformY, transform);
    QString str=circle.attribute("d");
    captureFirstTwoNumbersFromText(x, y, str);
    x=x+transformX;
    y=y+transformY;
}

void appendCircleToList(QList<CirclePoint> &Points, QDomElement &circle, QDomElement &use)
{
    double x, y;
    getCirlceRealLocation(circle, x, y);

    CirclePoint point;
    point.xCircle=x;
    point.yCircle=y;

    double xUse=use.attribute("x").toDouble();
    double yUse=use.attribute("y").toDouble();

    point.xUse=xUse;
    point.yUse=yUse;

    Points.append(point);
}



QStringList getSvgFileListInFolder(QString &sourseMap){
    QDir sourseMapDirectory(sourseMap);
    return sourseMapDirectory.entryList(QStringList() << "*.svg" << "*.SVG",QDir::Files);
}

QStringList getJpegFileListInFolder(QString &sourseMap){
    QDir sourseMapDirectory(sourseMap);
    return sourseMapDirectory.entryList(QStringList() << "*.jpeg" << "*.JPEG",QDir::Files);
}

void getSvgDocument(QDomDocument &document, QString &sourceFolder, QString &fileName)
{
    QString fullPath=sourceFolder+fileName;
    QFile svgFile(fullPath);
    svgFile.open(QFile::ReadOnly | QFile::Text);
    qDebug()<< fullPath << "Размер " << svgFile.size();
    document.setContent(&svgFile);
    svgFile.close();
}

void deleteSvgInskcapeAttributesAndFirstChild(QDomElement &svg)
{
    if (svg.tagName()=="svg")
    {
        svg.removeAttribute("sodipodi:docname");
        svg.removeAttribute("inkscape:version");
        svg.removeAttribute("xmlns:inkscape");
        svg.removeAttribute("xmlns:sodipodi");
        svg.removeAttribute("xmlns:svg");
        svg.removeAttribute("id");
        svg.removeAttribute("version");
        svg.removeChild(svg.childNodes().at(0));
    }
    else
    {
        qFatal("Неверный тэг svg");
    }
}

void removeIdAttribute(QDomElement &elem)
{
    elem.removeAttribute("id");
}

void clearDefsPaqrt(QDomElement &defs)
{
    if (defs.tagName()=="defs")
    {
        removeIdAttribute(defs);
        if (defs.childNodes().count()!=1)
        {
            qFatal("Проверь svg колличество потомков должно быть равным единице");
        }
        else
        {
            QDomElement g=defs.firstChildElement();
            removeIdAttribute(g);
            QDomNodeList symbols=g.childNodes();
            for (int i=symbols.count()-1; i>=0; i--)
            {
                defs.appendChild(symbols.at(i).firstChild());
                g.removeChild(symbols.at(i));
            }
            defs.removeChild(defs.firstChild());
        }
    }
    else
    {
        qFatal("Неверный тэг defs");
    }
}

void clearLastLinks(QDomElement &g)
{
    if (g.tagName()=="g")
    {
        removeIdAttribute(g);
        QDomNodeList gChildrens=g.childNodes();
        //        qDebug()<< "Последний символ " << g.tagName() << " колличество потомков" << gChildrens.count();
        for (int i=gChildrens.count()-1; i>=0; i--)
        {
            QDomElement elem=gChildrens.at(i).toElement();
            QString elemTagName=elem.tagName();
            //            qDebug()<< elemTagName;
            //            qDebug()<< "id " <<  elem.attribute("id");
            removeIdAttribute(elem);
            //            qDebug()<< elem.tagName();
            if (elemTagName=="g")
            {
                if (elem.hasAttribute("inkscape:groupmode"))
                {
                    elem.removeAttribute("inkscape:groupmode");
                }
                QDomNodeList uses=elem.childNodes();
                if (uses.count()==0)
                {
                    g.removeChild(elem);
                }
                else
                {
                    //                    qDebug()<<uses.count();
                    for (int j=0; j<uses.count(); j++)
                    {
                        QDomElement use=uses.at(j).toElement();
                        //                        qDebug() << use.tagName();
                        use.removeAttribute("id");
                        use.removeAttribute("width");
                        use.removeAttribute("height");
                    }
                }
            }
            else
            {
                if (elemTagName!="path")
                {
                    g.removeChild(elem);
                }

            }
        }
        int lastIndex=gChildrens.count()-1;
        while(lastIndex>0)
        {
            if(gChildrens.at(lastIndex).toElement().tagName()=="path")
            {
                g.removeChild(gChildrens.at(lastIndex));
                lastIndex--;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        qFatal("Неверный тэг g");
    }

}

void clearUnusedAttributesSVG(QDomElement &svg, QString &layer)
{
    deleteSvgInskcapeAttributesAndFirstChild(svg);
    QDomElement defs=svg.childNodes().at(0).toElement();
    clearDefsPaqrt(defs);
    QDomElement image=svg.childNodes().at(1).toElement();
    QString path=image.attribute("xlink:href");
    path="svg/"+layer+"/"+path;
    image.setAttribute("xlink:href", path);
    QDomElement g=svg.lastChildElement();
    //    qDebug()<< g.attribute("id");
    clearLastLinks(g);
}

bool elementIsAPoint(QDomElement &elem)
{
    if (elem.tagName()=="path")
    {
        if (elem.hasAttribute("style"))
        {
            if (elem.attribute("style").contains("fill-rule:nonzero"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void setTransformToElem(double x, double y, QDomElement &elem, const int angle)
{
    QString previousTransform=elem.attribute("transform", "");
    if (previousTransform=="")
    {
        elem.setAttribute("transform",  " rotate(  "+QString::number(angle)+ " "+ QString::number(x, 'g') + " " +  QString::number(y, 'g') + ") " +previousTransform);
    }
    else
    {
        elem.setAttribute("transform",  "rotate(  "+QString::number(angle)+ " "+ QString::number(x, 'g') + " " +  QString::number(y, 'g') + ") " +previousTransform);
    }
}

void renderToJpg(QString &fullPath, QString &tile, const int angle)
{
    QSvgRenderer renderer;
    renderer.load(fullPath);
    QImage image(497, 279, QImage::Format_ARGB32);
    image.fill(0xaaA08080);
    QPainter painter(&image);
    renderer.render(&painter);
    image.save("E:\\MAP 2.0\\MapText\\img\\"+tile+ "_" + QString::number(angle)+"_.jpg");
}

int main(int argc, char *argv[])
{
//        const QVector<int> angles={0, 1, 30, 40, 50, 60, 70, 80, 90, 100, 110, 130, 150, 170, 180, 210, 224, 241, 260, 280, 290, 300, 310, 330};
    const QVector<int> angles{340};
    for (QVector<int>::ConstIterator angle=angles.cbegin(); angle!=angles.cend(); ++angle)
    {
        qDebug()<< "Программа поворота слов в тайле";
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        QString layer=QStringLiteral("8");
        QString sourseMap="E:\\MAP 2.0\\MapText\\WithImage\\"+layer+"\\";
        qDebug()<< "Исходники: " << sourseMap;
        QString destination="E:\\MAP 2.0\\MapText\\Rotated\\"+layer+"\\";
        qDebug()<< "Результат в папке : " << destination;
        if(!(QDir(destination).exists()))
        {
            QDir().mkdir(destination);
        }
        QStringList tiles =getSvgFileListInFolder(sourseMap);
        for (QStringList::iterator tile=tiles.begin(); tile!=tiles.end(); ++tile)
        {
            //        QString sourceName=*tile+"_0";
            //        renderToJpg(sourseMap, sourceName);
            QDomDocument svgDocument;
            getSvgDocument(svgDocument, sourseMap, *tile);

            QDomElement svgElement=svgDocument.firstChildElement();
            clearUnusedAttributesSVG(svgElement, layer);


            QDomNodeList childrensAtLastTag=svgElement.lastChildElement().childNodes();
            QList<QPointF> listOfPoints;
            QList<CirclePoint> listOfCirclesAndFirstUses;//if 5-6-7 layer

            for (int i=0; i<childrensAtLastTag.count(); i++)
            {
                QDomElement charecterPath=childrensAtLastTag.at(i).toElement();
                QString tagName=charecterPath.tagName();
                if (tagName=="g")
                {
                    checkGroupTranformAttribute(charecterPath);
                    appendPointToList(listOfPoints, charecterPath);
                }
                else
                {
                    if (tagName=="path")
                    {
                        if (charecterPath.attribute("style").contains("fill-opacity:1;fill-rule:nonzero") && charecterPath.hasAttribute("transform"))
                        {
                            int nextTagIndex=i+1;
                            QDomElement nextTag=childrensAtLastTag.at(nextTagIndex).toElement();
                            while (nextTag.tagName()!="g")
                            {
                                if (nextTagIndex==childrensAtLastTag.count())
                                {
                                    qFatal("вышли за пределы svg");
                                }
                                nextTagIndex++;
                                nextTag=childrensAtLastTag.at(nextTagIndex).toElement();
                            }
                            checkGroupTranformAttribute(nextTag);
                            QDomElement gFirstPoint=nextTag.childNodes().at(0).toElement();
                            appendCircleToList(listOfCirclesAndFirstUses, charecterPath, gFirstPoint);
                        }
                    }
                    else
                    {
                        qFatal("Незнакомое имя тега");
                    }
                }

            }
            qDebug()<< "Символы получены";
            if (listOfPoints.count()==0)
            {
                qFatal("точек нет проверь алгоритм");
            }

            QVector<QVector<FourPoints>> resultTranform=TransformAllSymbols(listOfPoints, listOfCirclesAndFirstUses);
            FourPoints currentUseXYAndCenterPoint;
            qDebug()<< "Символы трансформированы";

            for (int i=0; i<childrensAtLastTag.count(); i++)
            {
                QDomElement elem=childrensAtLastTag.at(i).toElement();
                QString elementTagName=elem.tagName();
                if (elementTagName=="path" && !elem.attribute("style").contains("fill-rule:nonzero"))
                {
                    //по 1 точке ищем подходящий центр
                    int findUseIndex=1;
                    QDomElement elemG=childrensAtLastTag.at(i+findUseIndex).toElement();
                    while (elemG.tagName()!="g")
                    {
                        findUseIndex++;
                        elemG=childrensAtLastTag.at(i+findUseIndex).toElement();
                    }
                    double x=elemG.firstChildElement().attribute("x").toDouble();
                    double y=elemG.firstChildElement().attribute("y").toDouble();
                    for(int i=0; i<resultTranform.count(); i++)
                    {
                        if(compareDoubles(resultTranform[i][0].x,x) && compareDoubles(resultTranform[i][0].y,y))
                        {
                            currentUseXYAndCenterPoint=resultTranform[i][0];
                            break;
                        }
                    }

                }
                if (!elementIsAPoint(elem))
                {
                    setTransformToElem(currentUseXYAndCenterPoint.centerX, currentUseXYAndCenterPoint.centerY, elem, *angle);
                }
            }
            QString fullPath=destination+*tile;
            QFile file( fullPath );
            if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
            {
                qDebug( "Failed to open file for writing." );
                return -1;
            }
            QTextStream stream( &file );
            stream << svgDocument.toString();
            stream.flush();
            file.close();


//                        renderToJpg(fullPath, *tile, *angle);
        }
        qDebug()<< "Слова в тайле повернуты. Результат в папке: " << destination;
    }
    return 0;
}
