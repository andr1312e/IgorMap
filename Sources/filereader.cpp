#include "filereader.h"

FileReader::FileReader(QString &pathToSourceSvg)
    :m_array(new QByteArray)
    ,m_file(new QFile())
    ,m_fileCoords(new QFile())
    ,m_pathToSourceSvg(pathToSourceSvg)
{
}

FileReader::~FileReader()
{
    delete m_file;
    delete m_fileCoords;
    delete m_array;
}
void FileReader::setParams(QString &tile,  QString &azm, QString &layer)
{
    m_tileName=tile;
    m_azm=azm;
    m_layer=layer;
}
void FileReader::doing(){
    m_fileCoords->setFileName(m_pathToSourceSvg+m_layer+"/"+m_tileName+"_.svg");
    m_fileCoords->open(QIODevice::ReadOnly);
    *m_array=m_fileCoords->readAll();
    m_fileCoords->close();
    int startIndex=0;
    for (startIndex; startIndex<m_array->length(); startIndex++)
    {
        if (m_array->operator [](startIndex)=='@')
            break;
    }
    m_currentPositionInFile=m_array->left(startIndex).toInt();
    for (int i=0; i<=startIndex; i++)
    {
        m_array->operator [](i)=' ';
    }
    m_previousCharInArray=' ';
    for (int i=startIndex+4; i<m_array->length()-20; i++)
    {
        if(m_previousCharInArray=='e'&&m_array->operator[](i)=='(' && m_array->operator[](i+4)==',')
        {
            m_array->operator[](i+1)=m_azm.at(0).toLatin1();
            m_array->operator[](i+2)=m_azm.at(1).toLatin1();
            m_array->operator[](i+3)=m_azm.at(2).toLatin1();
            i=i+60;
        }
        m_previousCharInArray=m_array->operator [](i);
    }
    m_file->setFileName(m_pathToSourceSvg+m_layer+"/"+m_tileName+".svg");
    m_file->open(QIODevice::ReadWrite);
    m_file->resize(m_currentPositionInFile);
    m_file->seek(m_currentPositionInFile-1);
    m_file->write(*m_array);
    m_file->close();
    m_array->clear();
    emit finished();
}
