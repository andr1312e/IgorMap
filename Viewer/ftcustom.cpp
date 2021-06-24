#include "ftcustom.h"
#include <QDebug>
//#include <ft2build.h>
//#include <freetype/freetype.h>
//#include <freetype2/include/ft2build.h>
//#include FT_FREETYPE_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <QOpenGLPixelTransferOptions>
#include <QVector3D>

ftCustom::ftCustom(QOpenGLFunctions_3_3_Core *func, QObject *parent) : QObject(parent),
    m_func(func)
{
    //genTexels();
}

ftCustom::~ftCustom()
{

}

QSizeF ftCustom::genRectForText(const QString &str, GLfloat scale)
{
    QSizeF totalSize(0,0);
    for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }

        const Character &ch = itemFounded.value();

        GLfloat xpos = ch.Bearing.x() * scale;
        //GLfloat origin = (ch.Size.height() - ch.Bearing.y()) * scale;
        //GLfloat ypos = ch.Bearing.y() * scale;

        GLfloat w = ch.Size.width() * scale;
        GLfloat h = ch.Size.height() * scale;

        totalSize.rwidth() += xpos + w;
        if (totalSize.height() < h) {
            totalSize.rheight() = h;
        }
    }
    return totalSize;
}

void ftCustom::genText(const QString &str, QPointF point, Qt::Alignment aligment, GLfloat scale, GLfloat *arrayVertices, GLfloat *arrayTexeles, quint32 &offset, GLfloat *arrayUBO)
{
    GLfloat x = point.x(), y = point.y();
    GLfloat xOffset = 0, yOffset = 0;
    QVector<const Character *> chars;

    for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }

        const Character &ch = itemFounded.value();
        chars.push_back(&itemFounded.value());

        if (aligment == Qt::AlignRight) {
            xOffset += ch.Size.width() * scale;
            yOffset = (ch.Size.height() / 2) * scale;
        }
        else if (aligment == Qt::AlignLeft) {
            //xOffset -= 5;
            yOffset = (ch.Size.height() / 2) * scale;
        }
        else if (aligment == Qt::AlignTop) {
            xOffset += ch.Size.width() / 2 * scale - 1;
            yOffset = (ch.Size.height()) * scale + 4;
        }
        else if (aligment == Qt::AlignBottom) {
            xOffset += ch.Size.width() / 2 * scale;
        }
        else if (aligment == Qt::AlignCenter) {
            xOffset += ch.Size.width() / 2 * scale;
        }

    }

    x -= xOffset + 1.5 * str.size();
    y -= yOffset - 2;

    for (quint16 pos = 0; pos != str.size(); pos++) {
        /*auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }*/
        const Character &ch = *chars.at(pos);//itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat ypos = y - (ch.Size.height() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.width() * scale;
        GLfloat h = ch.Size.height() * scale;

        GLfloat widthTexel = ch.Size.width() / static_cast<GLfloat>(fontPixelSize.height());
        GLfloat heightTexel = ch.Size.height() / static_cast<GLfloat>(fontPixelSize.height());

        //set texels
        quint32 tIndex = offset;
        const GLfloat tQuad[] = { 0.0f, 1.0f,
                                  1.0f, 1.0f,
                                  1.0f, 0.0f,
                                  0.0f, 1.0f,
                                  1.0f, 0.0f,
                                  0.0f, 0.0f };
        for (int f = 0; f < vertexOnFragment * nDimensional; ) {
            arrayTexeles[tIndex + f] = tQuad[f] * widthTexel;
            f++;
            arrayTexeles[tIndex + f] = tQuad[f] * heightTexel;
            f++;
        }

        //set vertex
        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos + h;

        x += (ch.Advance >> 6) * scale;

        arrayUBO[pos] = ch.layer;
    }
}

void ftCustom::genTextWithRect(const QString &str, const OpenGLRectF &rect, GLfloat scale, GLfloat *arrayVertices, GLfloat *arrayTexeles, quint32 &offset, GLfloat *arrayUBO)
{
    GLfloat x = rect.x(), y = rect.y();
    GLfloat xOffset = rect.width() / 2, yOffset = 2;
    QVector<const Character *> chars;

    for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }

        const Character &ch = itemFounded.value();
        chars.push_back(&itemFounded.value());

        xOffset -= (ch.Bearing.x() + ch.Size.width()) * scale / 2;
    }

    x += xOffset;
    y += yOffset;

    for (quint16 pos = 0; pos != str.size(); pos++) {
        /*auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }*/
        const Character &ch = *chars.at(pos);//itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat ypos = y - (ch.Size.height() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.width() * scale;
        GLfloat h = ch.Size.height() * scale;

        GLfloat widthTexel = ch.Size.width() / static_cast<GLfloat>(fontPixelSize.height());
        GLfloat heightTexel = ch.Size.height() / static_cast<GLfloat>(fontPixelSize.height());

        //set texels
        quint32 tIndex = offset;
        const GLfloat tQuad[] = { 0.0f, 1.0f,
                                  1.0f, 1.0f,
                                  1.0f, 0.0f,
                                  0.0f, 1.0f,
                                  1.0f, 0.0f,
                                  0.0f, 0.0f };
        for (int f = 0; f < vertexOnFragment * nDimensional; ) {
            arrayTexeles[tIndex + f] = tQuad[f] * widthTexel;
            f++;
            arrayTexeles[tIndex + f] = tQuad[f] * heightTexel;
            f++;
        }

        //set vertex
        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos + h;

        x += (ch.Advance >> 6) * scale;

        arrayUBO[pos] = ch.layer;
    }
}

void ftCustom::genTextAtCurrentPosition(const QString &str, const QPointF &pos, GLfloat scale,
                                        GLfloat *arrayVertices, quint32 &offset,
                                        GLfloat *arrayTexels, quint32 &txOffset)
{
    const GLfloat tQuad[] = { 0.0f, 1.0f,
                              1.0f, 1.0f,
                              1.0f, 0.0f,
                              0.0f, 1.0f,
                              1.0f, 0.0f,
                              0.0f, 0.0f };

    QSizeF sizeOfRect = genRectForText(str, scale);
    OpenGLRectF rect(pos.x() - sizeOfRect.width() / 2,
                     pos.y() - sizeOfRect.height() / 2,
                     sizeOfRect.width(), sizeOfRect.height());

    GLfloat x = rect.x(), y = rect.y();
    GLfloat xOffset = rect.width() / 2, yOffset = 2;
    QVector<const Character *> chars;

    /*for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }

        const Character &ch = itemFounded.value();
        chars.push_back(&itemFounded.value());

        xOffset -= (ch.Bearing.x() + ch.Size.width()) * scale / 2;
    }

    x += xOffset;
    y += yOffset;*/

    for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }
        const Character &ch = itemFounded.value();//*chars.at(pos);//itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat ypos = y - (ch.Size.height() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.width() * scale;
        GLfloat h = ch.Size.height() * scale;

        GLfloat widthTexel = ch.Size.width() / static_cast<GLfloat>(fontPixelSize.height());
        GLfloat heightTexel = ch.Size.height() / static_cast<GLfloat>(fontPixelSize.height());

        int f = 0;
        //set vertex
        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos + h;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        x += (ch.Advance >> 6) * scale;
    }
}

void ftCustom::genTextAtCurrentVerticalPosition(const QString &str, const QVector3D &position, GLfloat scale, GLfloat *arrayVertices, quint32 &offset, GLfloat *arrayTexels, quint32 &txOffset)
{
    const GLfloat tQuad[] = { 0.0f, 1.0f,
                              1.0f, 1.0f,
                              1.0f, 0.0f,
                              0.0f, 1.0f,
                              1.0f, 0.0f,
                              0.0f, 0.0f };

    QSizeF sizeOfRect = genRectForText(str, scale);
    OpenGLRectF rect(position.x() - sizeOfRect.width() / 2,
                     position.z() - sizeOfRect.height() / 2,
                     sizeOfRect.width(), sizeOfRect.height());

    GLfloat x = rect.x(), z = rect.y();
    QVector<const Character *> chars;

    for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }
        const Character &ch = itemFounded.value();//*chars.at(pos);//itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat zpos = z - (ch.Size.height() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.width() * scale;
        GLfloat h = ch.Size.height() * scale;

        GLfloat widthTexel = ch.Size.width() / static_cast<GLfloat>(fontPixelSize.height());
        GLfloat heightTexel = ch.Size.height() / static_cast<GLfloat>(fontPixelSize.height());

        int f = 0;
        //set vertex
        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = position.y();
        arrayVertices[offset++] = zpos;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = position.y();
        arrayVertices[offset++] = zpos;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = position.y();
        arrayVertices[offset++] = zpos + h;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = position.y();
        arrayVertices[offset++] = zpos;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = position.y();
        arrayVertices[offset++] = zpos + h;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = position.y();
        arrayVertices[offset++] = zpos + h;
        arrayTexels[txOffset++] = tQuad[f++] * widthTexel;
        arrayTexels[txOffset++] = tQuad[f++] * heightTexel;
        arrayTexels[txOffset++] = ch.layer;

        x += (ch.Advance >> 6) * scale;
    }
}

void ftCustom::updateVertexArrayForTextAtCurrentPosition(const QString &str, const QPointF &pos, GLfloat scale,
                                                         GLfloat *arrayVertices, quint32 &offset)
{
    QSizeF sizeOfRect = genRectForText(str, scale);
    OpenGLRectF rect(pos.x() - sizeOfRect.width() / 2,
                     pos.y() - sizeOfRect.height() / 2,
                     sizeOfRect.width(), sizeOfRect.height());

    GLfloat x = rect.x(), y = rect.y();
    GLfloat xOffset = rect.width() / 2, yOffset = 2;
    QVector<const Character *> chars;

    /*for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }

        const Character &ch = itemFounded.value();
        chars.push_back(&itemFounded.value());

        xOffset -= (ch.Bearing.x() + ch.Size.width()) * scale / 2;
    }

    x += xOffset;
    y += yOffset;*/

    for (quint16 pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }
        const Character &ch = itemFounded.value();//*chars.at(pos);//itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat ypos = y - (ch.Size.height() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.width() * scale;
        GLfloat h = ch.Size.height() * scale;

        //set vertex
        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos;

        arrayVertices[offset++] = xpos + w;
        arrayVertices[offset++] = ypos + h;

        arrayVertices[offset++] = xpos;
        arrayVertices[offset++] = ypos + h;

        x += (ch.Advance >> 6) * scale;
    }
}

void ftCustom::genTexels()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        qDebug() << "ERROR::FREETYPE: Could not init FreeType Library";
    }

    FT_Face face;
    if (FT_New_Face(ft, "8277.ttf", 0, &face)) {
        qDebug() << "ERROR::FREETYPE: Failed to load font";
    }

    FT_Set_Pixel_Sizes(face, fontPixelSize.width(), fontPixelSize.height());

    const quint16 first = 2, second = 2;
    FT_ULong charRanges[first][second] = {
        { 32, 126 },
        /*{ 160, 191 },*/
        { 1040, 1103}
    };
    quint16 charArraySize = 0;
    for (quint16 i = 0; i < first; i++) {
        charArraySize += charRanges[i][1] - charRanges[i][0] + 1;
    }

    const quint16 vertexOnTriangles = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 oneBuffSize = vertexOnTriangles * nDimensionalFont;    

    //Generate an array texture
    m_func->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    m_func->glGenTextures( 1, &textureArray );
    m_func->glActiveTexture(GL_TEXTURE0);
    m_func->glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

    //Create storage for the texture. (100 layers of 1x1 texels)
    /*m_func->glTexStorage3D(
                GL_TEXTURE_2D_ARRAY,
                1,                    //No mipmaps as textures are 1x1
                GL_R8,              //Internal format
                fontPixelSize.height(), fontPixelSize.height(),   //width,height
                charArraySize                //Number of layers
                );*/

    m_func->glTexImage3D(GL_TEXTURE_2D_ARRAY,
                         0,
                         GL_R8,
                         fontPixelSize.height(),
                         fontPixelSize.height(),
                         charArraySize,
                         0,
                         GL_RED,
                         GL_UNSIGNED_BYTE,
                         0);


    for (quint16 i = 0, textIndex = 0; i < first; i++) {
        quint16 charCountInRow = charRanges[i][1] - charRanges[i][0] + 1;
        for (quint16 j = 0; j != charCountInRow; j++) {

            if (FT_Load_Char(face, charRanges[i][0] + j, FT_LOAD_RENDER))
                qDebug() << "ERROR::FREETYPE: Failed to load Glyph";            

            m_func->glTexSubImage3D( GL_TEXTURE_2D_ARRAY,
                             0,                     //Mipmap number
                             0,0,textIndex,       //xoffset, yoffset, zoffset
                             face->glyph->bitmap.width,
                             face->glyph->bitmap.rows,1,//width, height, depth
                             GL_RED,                //format
                             GL_UNSIGNED_BYTE,      //type
                             face->glyph->bitmap.buffer);                //pointer to data



            // Now store character for later use
            Character character = {
                textIndex++,
                QSize(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                QVector2D(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            };
            mapOfCharacters.insert(charRanges[i][0] + j, character);
        }
    }

    m_func->glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    m_func->glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    m_func->glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    m_func->glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    m_func->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_func->glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

ftCustomSimple::ftCustomSimple(QObject *parent) : QObject(parent)

{

}

ftCustomSimple::~ftCustomSimple()
{

}

sVectorCharacterId ftCustomSimple::genText(QString str, GLfloat x, GLfloat y, GLfloat scale, GLfloat *arrayVertices)
{
    sVectorCharacterId strParameter;
    quint32 indexArray = 0;
    for (int pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }
        sCharacter ch = itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat ypos = y - (ch.Size.y() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.x() * scale;
        GLfloat h = ch.Size.y() * scale;
        // Update VBO for each character
        arrayVertices[indexArray++] = xpos;
        arrayVertices[indexArray++] = ypos;

        arrayVertices[indexArray++] = xpos + w;
        arrayVertices[indexArray++] = ypos;

        arrayVertices[indexArray++] = xpos + w;
        arrayVertices[indexArray++] = ypos + h;

        arrayVertices[indexArray++] = xpos;
        arrayVertices[indexArray++] = ypos;

        arrayVertices[indexArray++] = xpos + w;
        arrayVertices[indexArray++] = ypos + h;

        arrayVertices[indexArray++] = xpos;
        arrayVertices[indexArray++] = ypos + h;

        x += (ch.Advance >> 6) * scale;

        strParameter.push_back(itemFounded.value().texture);
    }

    return strParameter;
}

sVectorCharacterId ftCustomSimple::genVerticalText(QString str,const QVector3D &position, GLfloat scale, GLfloat *arrayVertices)
{
    sVectorCharacterId strParameter;
    quint32 indexArray = 0;
    float x = position.x();
    for (int pos = 0; pos != str.size(); pos++) {
        auto itemFounded = mapOfCharacters.find(str.at(pos).unicode());
        if (itemFounded == mapOfCharacters.end()) {
            qDebug() << QString("ERROR::FREETYPE: Could not find necessary character %1").arg(str.at(pos));
            continue;
        }
        sCharacter ch = itemFounded.value();

        GLfloat xpos = x + ch.Bearing.x() * scale;
        GLfloat zpos = position.z() - (ch.Size.y() - ch.Bearing.y()) * scale;

        GLfloat w = ch.Size.x() * scale;
        GLfloat h = ch.Size.y() * scale;
        // Update VBO for each character
        arrayVertices[indexArray++] = xpos;
        arrayVertices[indexArray++] = position.y();
        arrayVertices[indexArray++] = zpos;

        arrayVertices[indexArray++] = xpos + w;
        arrayVertices[indexArray++] = position.y();
        arrayVertices[indexArray++] = zpos;

        arrayVertices[indexArray++] = xpos + w;
        arrayVertices[indexArray++] = position.y();
        arrayVertices[indexArray++] = zpos + h;

        arrayVertices[indexArray++] = xpos;
        arrayVertices[indexArray++] = position.y();
        arrayVertices[indexArray++] = zpos;

        arrayVertices[indexArray++] = xpos + w;
        arrayVertices[indexArray++] = position.y();
        arrayVertices[indexArray++] = zpos + h;

        arrayVertices[indexArray++] = xpos;
        arrayVertices[indexArray++] = position.y();
        arrayVertices[indexArray++] = zpos + h;

        x += (ch.Advance >> 6) * scale;

        strParameter.push_back(itemFounded.value().texture);
    }

    return strParameter;
}

void ftCustomSimple::genTexels()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        qDebug() << "ERROR::FREETYPE: Could not init FreeType Library";
    }

    FT_Face face;
    if (FT_New_Face(ft, "8277.ttf", 0, &face)) {
        qDebug() << "ERROR::FREETYPE: Failed to load font";
    }

    FT_Set_Pixel_Sizes(face, fontPixelSize.width(), fontPixelSize.height());

    const quint16 first = 3, second = 2;
    FT_ULong charRanges[first][second] = {
        { 32, 126 },
        { 160, 191 },
        { 1040, 1103}
    };
    quint16 charArraySize = 0;
    for (quint16 i = 0; i < first; i++) {
        charArraySize += charRanges[i][1] - charRanges[i][0] + 1;
    }

    const quint16 vertexOnTriangles = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 oneBuffSize = vertexOnTriangles * nDimensionalFont;

    for (quint16 i = 0; i < first; i++) {
        for (FT_ULong j = charRanges[i][0]; j != charRanges[i][1] + 1; j++) {

            if (FT_Load_Char(face, j, FT_LOAD_RENDER))
                qDebug() << "ERROR::FREETYPE: Failed to load Glyph";

            QOpenGLPixelTransferOptions option;
            option.setAlignment(1);
            QOpenGLTexture *glTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);
            glTexture->setFormat(QOpenGLTexture::R8_UNorm);
            glTexture->setSize(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            glTexture->allocateStorage();
            glTexture->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, face->glyph->bitmap.buffer, &option);
            glTexture->setMinificationFilter(QOpenGLTexture::Linear);
            glTexture->setMagnificationFilter(QOpenGLTexture::Linear);
            glTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
            glTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);


            if (!glTexture->isCreated()) {
                qDebug() << "Texture was not created";
            }

            // Now store character for later use
            sCharacter character = {
                glTexture,
                QVector2D(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                QVector2D(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            };
            mapOfCharacters.insert(j, character);
        }
    }

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
