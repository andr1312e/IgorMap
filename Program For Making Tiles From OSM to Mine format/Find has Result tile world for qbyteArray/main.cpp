#include <QByteArray>
#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QString folder=QString::fromLatin1("E:\\Map\\8\\");
//    QString zero=QString::fromLatin1("\\x00");
//    QString one=QString::fromLatin1("\\x01");
    QString zero=QString::fromLatin1("x00");
    QString one=QString::fromLatin1("x01");
    QString arr="";
    for (int i=0; i<=55; i++)
    {
        for (int j=0; j<=39; j++)
        {
            QString tileName=QString::number(i)+"_"+QString::number(j)+".svg";
            QString resPath=folder+tileName;
            if (QFile::exists(resPath))
            {
                arr.append(one);
            }
            else
            {
                arr.append(zero);
            }
        }
    }
    qDebug()<< arr;
    return 0;
}
