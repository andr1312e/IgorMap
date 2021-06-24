#ifndef FTCUSTOM_H
#define FTCUSTOM_H

#include <QObject>
//#include <GL/gl.h>
//#include <glm/glm.hpp>
#include <QMap>
#include <QOpenGLTexture>
#include <QSize>
#include <QVector2D>
#include <QOpenGLFunctions_3_3_Core>

#include "global.h"

struct Character {
    //GLuint     TextureID;  // ID handle of the glyph texture
    quint16 layer;
    QSize Size;       // Size of glyph
    QVector2D Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph    
};

using Characters = QMap<quint32, Character>;
using VectorCharacterId = QVector<quint16>;

class ftCustom : public QObject, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit ftCustom(QOpenGLFunctions_3_3_Core *func, QObject *parent = nullptr);
    ~ftCustom();
    QSizeF genRectForText(const QString &str, GLfloat scale);
    void genText(const QString &str, QPointF point, Qt::Alignment aligment, GLfloat scale, GLfloat *arrayVertices, GLfloat *arrayTexeles, quint32 &offset, GLfloat *arrayUBO);
    void genTextWithRect(const QString &str, const OpenGLRectF &rect, GLfloat scale, GLfloat *arrayVertices, GLfloat *arrayTexeles, quint32 &offset, GLfloat *arrayUBO);
    void genTextAtCurrentPosition(const QString &str, const QPointF &pos, GLfloat scale, GLfloat *arrayVertices, quint32 &offset, GLfloat *arrayTexels, quint32 &txOffset);
    void genTextAtCurrentVerticalPosition(const QString &str, const QVector3D &pos, GLfloat scale, GLfloat *arrayVertices, quint32 &offset, GLfloat *arrayTexels, quint32 &txOffset);
    void updateVertexArrayForTextAtCurrentPosition(const QString &str, const QPointF &pos, GLfloat scale, GLfloat *arrayVertices, quint32 &offset);
    void genTexels();    
    GLuint &getTextureArray() { return textureArray; };

private:

signals:

public slots:

private:
    QOpenGLFunctions_3_3_Core* m_func;

    Characters mapOfCharacters;
    GLuint idTexelVertex, idCoordsVertex;

    QSize fontPixelSize = QSize(0,128);

    GLuint textureArray, texelArray;
    const quint16 nDimensional = 2, vertexOnFragment = 6;

};

struct sCharacter {
    QOpenGLTexture *texture;  // ID handle of the glyph texture
    QVector2D Size;       // Size of glyph
    QVector2D Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

using sCharacters = QMap<quint32, sCharacter>;
using sVectorCharacterId = QVector< QOpenGLTexture * >;

class ftCustomSimple : public QObject
{
    Q_OBJECT
public:
    explicit ftCustomSimple(QObject *parent = nullptr);
    ~ftCustomSimple();
    sVectorCharacterId genText(QString str, GLfloat x, GLfloat y, GLfloat scale, GLfloat *arrayVertices);
    sVectorCharacterId genVerticalText(QString str, const QVector3D &position, GLfloat scale, GLfloat *arrayVertices);
    void genTexels();

private:

signals:

public slots:

private:

    sCharacters mapOfCharacters;
    GLuint idTexelVertex, idCoordsVertex;

    QSize fontPixelSize = QSize(0,128);

};


#endif // FTCUSTOM_H
