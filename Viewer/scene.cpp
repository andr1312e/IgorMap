#include "scene.h"
#include "camera.h"
#include "bMath.h"

#include <QImage>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QElapsedTimer>
#include <QOpenGLPixelTransferOptions>
#include <ft2build.h>
#include FT_FREETYPE_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <QTimer>
#include <QTime>
#include <QSet>
#include <QRandomGenerator>

const float degToRad = float( M_PI / 180.0 );

Scene::Scene(QObject *parent) : QObject(parent),
    m_programGrid(nullptr),
    m_camera(new Camera(this)),
    m_extraCamera(new Camera(this)),
    m_v(),
    m_viewCenterFixed(false),
    m_pitchAngle(0.0f),
    m_yawAngle(0.0f),
    m_patchBuffer(QOpenGLBuffer::VertexBuffer),
    m_screenSpaceError(12.0f),
    m_modelMatrix(),
    m_horizontalScale(1.0f),
    m_verticalScale(20.0f),
    m_time(0.0f),
    m_funcs(nullptr),
    extraWindow(365,215),
    m_cameraExtraWindow(new Camera(this)),
    backgroundColor(QColor::fromRgbF(.0f, .0f, .0f, 1))
{
    resetCamera();
    resetExtraCamera();
}


void Scene::initialize()
{
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_3_Core>();
    if ( !m_funcs )
    {
        qFatal("Requires OpenGL >= 3.3");
        exit( 1 );
    }
    initializeOpenGLFunctions();

    // Initialize resources
    //prepareShaders();
    //prepareTextures();
    //prepareVertexBuffers( m_heightMapSize );
    //prepareVertexArrayObject();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //m_funcs->glCullFace(GL_BACK);
    //m_funcs->glFrontFace(GL_CW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    //glClearColor(.0f, .0f, .0f, 1);
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), backgroundColor.alphaF());

    /*const quint8 windowsCount = 2;
    widthPort = height() / windowsCount,
                  heightPort = height() / windowsCount;

    sceneOptions.setScreenRect(width() - widthPort, height());

    camParam2.camPos = QVector3D(75.f, 150.0f, -100.0f);
    camParam2.camLookAt = QVector3D(0.f, 0.0f, -1.0f);

    sceneOptions2.setInitialSizeNormal();
    sceneOptions2.setScreenRect(widthPort, heightPort);*/

    /*m_programFont = new QOpenGLShaderProgram(this);

    QFile file(":/source/ftVertexShader.vert");
    if (!file.exists()) {
        qDebug() << "Fuck up";
    }

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/ftVertexShader.vert")) {
        qDebug() << m_programFont->log();
        return;
    }

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/ftFragmentShader.frag")) {
        qDebug() << m_programFont->log();
        return;
    }
    if (!m_programFont->link()) {
        qDebug() << m_programFont->log();
        return;
    }

    m_vaoFont = new QOpenGLVertexArrayObject();
    m_vaoFont->create();
    m_vaoFont->bind();
    if (!m_vaoFont->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    //customFontDriver = new ftCustom(this);
    //customFontDriver->genTexels();

    const quint16 sizeFontPoint = 4;
    const quint16 nDimensionalFont = 2;
    const quint16 buffSizeInByte = sizeFontPoint * nDimensionalFont * sizeof(GLfloat);
    GLfloat fontVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0
    };
    GLfloat texelVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0
    };

    vboFont = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboFont->create();
    vboFont->bind();
    vboFont->allocate(fontVertex, 2 * buffSizeInByte);
    vboFont->write(buffSizeInByte, texelVertex,buffSizeInByte);
    vboFont->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    m_programFont->enableAttributeArray("vertex");
    m_programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalFont, 0);
    m_programFont->enableAttributeArray("texels");
    m_programFont->setAttributeBuffer("texels", GL_FLOAT, buffSizeInByte, nDimensionalFont, 0);

    vboFont->release();
    m_vaoFont->release();*/

    m_programGrid = new QOpenGLShaderProgram(this);

    if (!m_programGrid->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/vertShGrid.vert")) {
        qDebug() << m_programGrid->log();
        return;
    }

    if (!m_programGrid->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/fragShGrid.frag")) {
        qDebug() << m_programGrid->log();
        return;
    }
    if (!m_programGrid->link()) {
        qDebug() << m_programGrid->log();
        return;
    }

    m_programButton = new QOpenGLShaderProgram(this);

    if (!m_programButton->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/buttonVert.vert")) {
        qDebug() << m_programButton->log();
        return;
    }

    if (!m_programButton->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/buttonFrag.frag")) {
        qDebug() << m_programButton->log();
        return;
    }
    if (!m_programButton->link()) {
        qDebug() << m_programButton->log();
        return;
    }

    /*m_vao = new QOpenGLVertexArrayObject(this);
    m_vao->create();
    m_vao->bind();
    if (!m_vao->isCreated()){
        qDebug() << "Can't use VAO";
        return;
    }
    //prepareGrid();
    //prepareDSP();
    m_vao->release();*/
    //prepareSectors();

    float sectorDepth = 2;
    m_sectorsGLData = new SectorsGLData(m_funcs, m_camera, &sceneOptions, m_programGrid, sectorDepth);

    float dspDepth = 8;
    dspData = new DSPGLData(m_funcs, m_camera, &sceneOptions, dspDepth);
    dspData->preapre();
    //m_sectorsGLData->bindVAO();
    //m_programGrid->enableAttributeArray("posAttr");
    //m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 0);
    //m_sectorsGLData->releaseVAO();
    //connect(m_sectorsGLData, &SectorsGLData::addSectorViewer, this, &Scene::addExtraWindow);

    //prepareFont();
    prepareFontArray();

    int maxVUB, maxGUB, maxFUB, maxUBS, UBoffset, sampleBuffer, samples;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVUB);
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &maxGUB);
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &maxFUB);
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUBS);
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UBoffset);
    glGetIntegerv(GL_SAMPLE_BUFFERS, &sampleBuffer);
    glGetIntegerv(GL_SAMPLES, &samples);

    glGenBuffers(1, &uboIndex);
    glBindBuffer(GL_UNIFORM_BUFFER, uboIndex);
    glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(GLfloat) * 500, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    uniformBlockIndex = glGetUniformBlockIndex(m_programFont->programId(), "myblock");
    glUniformBlockBinding(m_programFont->programId(), uniformBlockIndex, 0);

    float grideDepth = 0.1;
    grideGL = new GrideGL(m_funcs, m_camera, m_extraCamera, &sceneOptions, m_programGrid, customFontDriver, grideDepth);
    grideGL->prepare();    

    ngrideGL = new NewGrideGL(m_funcs, m_camera, &sceneOptions, grideDepth);
    ngrideGL->prepare();

    //test3D = new Test3D(m_funcs, m_programGrid, customFontDriver);
    //test3D->prepare();

    float ktaDepth = 6.;
    ktaData = new KTAGLData(m_funcs, m_camera, ktaDepth);
    ktaData->setSceneOptions(&sceneOptions);
    ktaData->prepare();

    float traceDepth = 12.;
    traceData = new TraceGLData(m_funcs, m_camera, m_extraCamera, traceDepth);
    traceData->setSceneOptions(&sceneOptions);
    traceData->prepareGrideForTrace();
    //traceData->prepare();

    float rayDepth = 3.5;
    rayData = new RayGLData(m_funcs, m_camera, rayDepth);
    //rayData->prepare();
    rayData->prepareFlatRay();

    float mapDepth = 0.;
    mapGL = new MapGL(m_funcs, m_camera, &sceneOptions, mapDepth);
    mapGL->prepare();

    initRect();

    connect(traceData, &TraceGLData::addExtraWindowSignal,
            this, &Scene::addExtraWindow);
    connect(traceData, &TraceGLData::traceInfoToExtraWindow,
            this, &Scene::updateInfoInExtraWindow);

    connect(m_camera, &Camera::resetCamera,
            grideGL, &GrideGL::resetCameraSlot);

    /*m_programKTA = new QOpenGLShaderProgram(this);

    if (!m_programKTA->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/KTAVertexSh.vert")) {
        qDebug() << m_programKTA->log();
        return;
    }

    if (!m_programKTA->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/KTAFragmentSh.frag")) {
        qDebug() << m_programKTA->log();
        return;
    }
    if (!m_programKTA->link()) {
        qDebug() << m_programKTA->log();
        return;
    }

    const quint8 nDimensional = 3;
    const quint16 ktaCountMax = 10000;

    quint16 indexKTA = 0;
    GLfloat *currentPoint = new GLfloat[4 * nDimensional];
    currentPoint[indexKTA++] = 10.;
    currentPoint[indexKTA++] = 20.;
    currentPoint[indexKTA++] = 2.;

    currentPoint[indexKTA++] = 20;
    currentPoint[indexKTA++] = 20;
    currentPoint[indexKTA++] = 2.;

    currentPoint[indexKTA++] = 30;
    currentPoint[indexKTA++] = 20;
    currentPoint[indexKTA++] = 2.;

    currentPoint[indexKTA++] = 40;
    currentPoint[indexKTA++] = 20;
    currentPoint[indexKTA++] = 2.;

    qVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    qVBO->create();
    qVBO->bind();
    qVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    qVBO->allocate(currentPoint, 4 * nDimensional * sizeof(GLfloat));

    qVAO = new QOpenGLVertexArrayObject();
    qVAO->create();
    qVAO->bind();
    if (!qVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programKTA->enableAttributeArray("posAttr");
    m_programKTA->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    qVBO->release();
    qVAO->release();

    delete [] currentPoint;*/


    //prepareExtraWindow();

    //prepareSectors();

    /*const quint32 freqCircleInKm = 5;
    //const quint32 numCircle = maxDist / freqCircleInKm;
    const quint32 nDimensional = 3;

    quint32 coordsNumber = 0;
    for (quint32 k = freqCircleInKm; k <= sceneOptions.maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        coordsNumber += l * 10;
    }
    const quint32 sizeVertBuf = coordsNumber * nDimensional + 2 * 4 * nDimensional;
    GLfloat *vertBuf = new GLfloat[sizeVertBuf];

    quint32 posArr = 0;
    QVector<QPointF> vect;
    for (quint32 k = freqCircleInKm; k <= sceneOptions.maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        quint32 segmentation = l * 10;
        double deltaAlpha = 2. * M_PI / static_cast<double>(segmentation);
        //quint32 counter = 0;
        double alpha = 0;
        QVector<QPointF> tvector;
        for (quint32 counter = 0; counter != segmentation; counter++) {
            vertBuf[posArr++] = k * cos(alpha);
            vertBuf[posArr++] = k * sin(alpha);
            vertBuf[posArr++] = 0.;
            tvector << QPointF(vertBuf[posArr - 2], vertBuf[posArr - 1]);
            alpha += deltaAlpha;
//            counter++;
//            if (segmentation < counter) {
//                qDebug() << "Overflow №1";
//            }
        }
        vect << tvector;
        if (k > 110) {
            int ie = 5;
            ie++;
        }
        if (posArr > sizeVertBuf) {
            qDebug() << "Overflow №2";
        }
    }
    for (quint32 i = 0; i < 4; i++) {
        vertBuf[posArr++] = sceneOptions.maxDist * cos(i * M_PI_2);
        vertBuf[posArr++] = sceneOptions.maxDist * sin(i * M_PI_2);
        vertBuf[posArr++] = 0.;

        vertBuf[posArr++] = sceneOptions.maxDist * cos(i * M_PI_2);
        vertBuf[posArr++] = sceneOptions.maxDist * sin(i * M_PI_2);
        vertBuf[posArr++] = sceneOptions.maxDist;
    }


    const quint16 fullTurn = 360, deltaAz = 45;
    const quint16 azCount = fullTurn / deltaAz;
    const qreal coeffDeg2Rad = M_PI / 180.;
    const qreal fullTurnReal = fullTurn * coeffDeg2Rad, deltaAzReal = deltaAz * coeffDeg2Rad;

    const quint32 sizeVertBuf2 = 2 * azCount * nDimensional;
    GLfloat *vertBuf2 = new GLfloat[sizeVertBuf2];

    posArr = 0;
    for (quint16 i = 0; i < azCount; i++) {
        vertBuf2[posArr++] = sceneOptions.maxDist * cos(i * deltaAzReal);
        vertBuf2[posArr++] = sceneOptions.maxDist * sin(i * deltaAzReal);
        vertBuf2[posArr++] = 0.;

        vertBuf2[posArr++] = sceneOptions.maxDist * cos(i * deltaAzReal + M_PI);
        vertBuf2[posArr++] = sceneOptions.maxDist * sin(i * deltaAzReal + M_PI);
        vertBuf2[posArr++] = 0.;
    }

    const quint32 sizeVertBuf3 = 8 * nDimensional;
    GLfloat *vertBuf3 = new GLfloat[sizeVertBuf3];

    posArr = 0;
    for (quint16 i = 0; i < 4; i++) {
        vertBuf3[posArr++] = 20 * sin(i * M_PI_2 + deltaAzReal);
        vertBuf3[posArr++] = 20 * cos(i * M_PI_2 + deltaAzReal);
        vertBuf3[posArr++] = 0.;
    }

    vertBuf3[posArr++] = 20 * sin(deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(2 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(2 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(3 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(3 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;*/

    /*const quint8 sideCount = 3,
                 //squareCount = 1,
                 squarePointNumber = 4;
    const quint32 sizeVertBuf5 = 8 * nDimensional;//nDimensional * sideCount * squareCount * squarePointNumber;
    const int side = 200;
    GLfloat vertBuf5[sizeVertBuf5] = {
        0, 0, 0,
        side, 0, 0,
        side, side, 0,
        0, side, 0,
        0, side, -side,
        0, 0, side,
        side, 0, -side,
        side, 0, 0,
    };

    const quint16 distBound = 300,
                  speedBound = 150,
                  ampBound = 200;

    const quint16 sideOfPrimitive = 25;
    const quint16 distFragment = distBound / sideOfPrimitive + 1,
                  speedFragment = speedBound / sideOfPrimitive + 1,
                  ampFragment = ampBound / sideOfPrimitive + 1;
    const quint16 offsetOnAxis1 = 5.f;
    //const quint32 sizeVertBuf6 = nDimensional * 4 * (distFragment + speedFragment + ampFragment);
    const quint32 sizeVertBuf6 = nDimensional * 2 * (distFragment + speedFragment);
    GLfloat vertBuf6[sizeVertBuf6];
    quint16 buf6Pos = 0;

    //along y-axis
    for (int i = 0; i < speedFragment; ++i) { // on YX-planes
        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = -offsetOnAxis1;//0
        vertBuf6[buf6Pos++] = 0;

        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = distBound;
        vertBuf6[buf6Pos++] = 0;
    }

    //along x-axis
    for (int i = 0; i < distFragment; ++i) { // on XY-planes
        vertBuf6[buf6Pos++] = -offsetOnAxis1;//0
        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = 0;

        vertBuf6[buf6Pos++] = speedBound;
        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = 0;
    }

    //along z-axis
    //for (int i = 0; i < speedFragment; ++i) { // on ZX-planes
//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = 0;

//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = -distBound;
//    }
//    for (int i = 0; i < ampFragment; ++i) { // on ZY-planes
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = 0;

//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = -distBound;
//    }

//    //along y-axis
//    for (int i = 0; i < speedFragment; ++i) { // on YX-planes
//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = -distBound;

//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = ampBound;
//        vertBuf6[buf6Pos++] = -distBound;
//    }
//    for (int i = 0; i < distFragment; ++i) { // on YZ-planes
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;

//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = ampBound;
//        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;
//    }
//    //along x-axis
//    for (int i = 0; i < ampFragment; ++i) { // on XY-planes
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = -distBound;

//        vertBuf6[buf6Pos++] = speedBound;
//        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
//        vertBuf6[buf6Pos++] = -distBound;
//    }
//    for (int i = 0; i < distFragment; ++i) { // on XZ-planes
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;

//        vertBuf6[buf6Pos++] = speedBound;
//        vertBuf6[buf6Pos++] = 0;
//        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;
//    }

    const quint32 sizeVertBuf7 = nDimensional * distBound * speedBound;
    GLfloat vertBuf7[sizeVertBuf7];
    quint32 vbuf7Pos = 0;
    for (quint16 i = 0; i < distBound; i++) {
        for (quint16 j = 0; j < speedBound; j++) {
            const quint16 a = 30, b = 80; //[a,b]
            vertBuf7[vbuf7Pos++] = j;
            vertBuf7[vbuf7Pos++] = i;
            vertBuf7[vbuf7Pos++] = static_cast<double>(qrand()) * (b-a) / RAND_MAX + a;
        }
    }
    if (sizeVertBuf7 != vbuf7Pos) {
        qDebug() << "Have same problm with vertBuf7";
    }

    const quint16 primitivesPerSquare = 8,
                  pointPerPrimitive = 3;
    sizeIndexBuf1 = primitivesPerSquare * pointPerPrimitive * (speedBound / 2 - 1) * (distBound / 2 - 1);
    GLuint *indexBuf1 = new GLuint[sizeIndexBuf1];
    quint32 ibuf1Pos = 0;
    for (quint16 i = 2; i < distBound; i+=2) {
        for (quint16 j = 2; j < speedBound; j+=2) {
            quint16 tj = j, ti = i;
            for (quint16 k = 0; k < primitivesPerSquare; k++) {
                int pos = (i - 1) * speedBound + (j - 1);
                indexBuf1[ibuf1Pos++] = pos;
                if (k == 0 || k == 1) { //x--
                    pos = ti * speedBound + tj--;
                }
                else if (k == 2 || k == 3) { //y--
                    pos = ti-- * speedBound + tj;
                }
                else if (k == 4 || k == 5) { //x++
                    pos = ti * speedBound + tj++;
                }
                else if (k == 6 || k == 7) { //y++
                    pos = ti++ * speedBound + tj;
                }
                indexBuf1[ibuf1Pos++] = pos;
                pos = ti * speedBound + tj;
                indexBuf1[ibuf1Pos++] = pos;
            }
        }
    }
    if (sizeIndexBuf1 != ibuf1Pos) {
        qDebug() << "Have same problm with indexBuf1";
    }

    const quint8 fanNumber = 4;
    const quint16 objectNumber = distFragment + speedFragment;
    const quint32 sizeVertBuf8 = nDimensional * objectNumber * (fanNumber + 1);
    GLfloat vertBuf8[sizeVertBuf8];
    quint32 vbuf8Pos = 0;
    const quint16 offsetOnAxis = offsetOnAxis1 + 2,
                  aObject = 10,
                  bObject = 5;
    for(quint16 i = 0; i < distFragment; i++) {
        for (quint16 j = 0; j < fanNumber + 1; j++) {
            if (j == 0) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - aObject;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive;
            }
            else if (j == 1) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + bObject;
            }
            else if (j == 2) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * aObject;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + bObject;
            }
            else if (j == 3) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * aObject;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - bObject;
            }
            else if (j == 4) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - bObject;
            }
            vertBuf8[vbuf8Pos++] = 0;
        }
    }
    for(quint16 i = 0; i < speedFragment; i++) {
        for (quint16 j = 0; j < fanNumber + 1; j++) {
            if (j == 0) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - bObject;
            }
            else if (j == 1) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
            }
            else if (j == 2) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
            }
            else if (j == 3) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * bObject;
            }
            else if (j == 4) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * bObject;
            }
            vertBuf8[vbuf8Pos++] = 0;
        }
    }

    const quint8 trianglePoint = 3;
    sizeIndexBuf2 = objectNumber * fanNumber * trianglePoint;
    GLuint indexBuf2[sizeIndexBuf2];
    quint32 ibuf2Pos = 0;
    for (quint16 i = 0; i < objectNumber; i++) {
        quint32 pos = i * (fanNumber + 1);
        for (quint16 j = 0; j < fanNumber; j++) {
            indexBuf2[ibuf2Pos++] = pos;
            indexBuf2[ibuf2Pos++] = pos + j + 1;
            indexBuf2[ibuf2Pos++] = (j == 3) ? pos + 1 : pos + j + 2;
        }
    }
    if (sizeIndexBuf2 != ibuf2Pos) {
        qDebug() << "Have same problm with indexBuf2";
    }


    //QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo->allocate(vertBuf, (sizeVertBuf + sizeVertBuf2 + sizeVertBuf3 + sizeVertBuf5 + sizeVertBuf6) * sizeof(GLfloat));
    m_vbo->write(sizeVertBuf * sizeof(GLfloat), vertBuf2, sizeVertBuf2 * sizeof(GLfloat));
    m_vbo->write((sizeVertBuf + sizeVertBuf2) * sizeof(GLfloat), vertBuf3, sizeVertBuf3 * sizeof(GLfloat));
    m_vbo->write((sizeVertBuf + sizeVertBuf2 + sizeVertBuf3) * sizeof(GLfloat), &vertBuf5, sizeVertBuf5 * sizeof(GLfloat));
    m_vbo->write((sizeVertBuf + sizeVertBuf2 + sizeVertBuf3 + sizeVertBuf5) * sizeof(GLfloat), &vertBuf6, sizeVertBuf6 * sizeof(GLfloat));


    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    m_vbo->release();
    m_vao->release();*/

    /*m_vao2 = new QOpenGLVertexArrayObject();
    m_vao2->create();
    m_vao2->bind();
    if (!m_vao2->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    QOpenGLBuffer vbo2(QOpenGLBuffer::VertexBuffer);
    vbo2.create();
    vbo2.bind();
    vbo2.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo2.allocate(vertBuf7, sizeVertBuf7 * sizeof(GLfloat));

    QOpenGLBuffer ibo1(QOpenGLBuffer::IndexBuffer);
    ibo1.create();
    ibo1.bind();
    ibo1.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo1.allocate(indexBuf1, sizeIndexBuf1 * sizeof(GLuint));

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    vbo2.release();

    m_vao2->release();

    m_vao3 = new QOpenGLVertexArrayObject();
    m_vao3->create();
    m_vao3->bind();
    if (!m_vao3->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    QOpenGLBuffer vbo3(QOpenGLBuffer::VertexBuffer);
    vbo3.create();
    vbo3.bind();
    vbo3.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo3.allocate(vertBuf8, sizeVertBuf8 * sizeof(GLfloat));

    QOpenGLBuffer ibo3(QOpenGLBuffer::IndexBuffer);
    ibo3.create();
    ibo3.bind();
    ibo3.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo3.allocate(indexBuf2, sizeIndexBuf2 * sizeof(GLuint));

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    vbo3.release();

    m_vao3->release();

    m_programKTA = new QOpenGLShaderProgram(this);
    if (!m_programKTA->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/KTAVertexSh.vert")) {
        qDebug() << m_programKTA->log();
        return;
    }

    if (!m_programKTA->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/KTAFragmentSh.frag")) {
        qDebug() << m_programKTA->log();
        return;
    }
    if (!m_programKTA->link()) {
        qDebug() << m_programKTA->log();
        return;
    }

    const quint8 ktaDimensional = 3;
    const quint32 sizeVertBuf4 = ktaDimensional * KTAcount;
    vertBuf4 = new GLfloat[sizeVertBuf4];

    int counterKta = 0;
    qreal ktaPos = 5;
    for (int i = 0; i < KTAcount; i++) {
        vertBuf4[counterKta++] = ktaPos;
        vertBuf4[counterKta++] = ktaPos;
        vertBuf4[counterKta++] = -sqrt(ktaPos) * 10;
        ktaPos += 0.01;
    }

    m_vaoKTA = new QOpenGLVertexArrayObject();
    m_vaoKTA->create();
    m_vaoKTA->bind();
    if (!m_vaoKTA->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    vboKTA = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboKTA->create();
    vboKTA->bind();
    vboKTA->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboKTA->allocate(vertBuf4, sizeVertBuf4 * sizeof(GLfloat));

    m_programKTA->enableAttributeArray("posAttr");
    m_programKTA->setAttributeBuffer("posAttr", GL_FLOAT, 0, ktaDimensional, 0);

    vboKTA->release();
    m_vaoKTA->release();*/

    /*struct structSector {
        double r, R;
        double az1, az2;
        double ug1, ug2;
    };
    QVector<structSector> SectorsVector = { {25,75, 270,330, 10,45}
                                            };

    QVector<QVector3D> triangleVector, verticesUg;
    QVector<quint32> iboSectors;
    for (auto item : SectorsVector) {
        QVector<QVector3D> verticesUg1, verticesUg2;

        double R = item.R, r = item.r,
                az1 = item.az1 * M_PI / 180.0, az2 = item.az2 * M_PI / 180.0,
                ug1 = (90 - item.ug1) * M_PI / 180.0, ug2 = (90 - item.ug2) * M_PI / 180.0,
                seg = 60;
        double dAz = (az2 - az1) / seg;
        for (int i = 0; i < seg + 1; i++) {
            verticesUg1 << QVector3D(r * cos(az1 + i * dAz) * sin(ug1), r * sin(az1 + i * dAz) * sin(ug1), r * cos(ug1))
                        << QVector3D(R * cos(az1 + i * dAz) * sin(ug1), R * sin(az1 + i * dAz) * sin(ug1), R * cos(ug1));
            verticesUg2 << QVector3D(r * cos(az1 + i * dAz) * sin(ug2), r * sin(az1 + i * dAz) * sin(ug2), r * cos(ug2))
                        << QVector3D(R * cos(az1 + i * dAz) * sin(ug2), R * sin(az1 + i * dAz) * sin(ug2), R * cos(ug2));
        }
        verticesUg << verticesUg1 << verticesUg2;

        const quint32   begin = verticesUg.size() - verticesUg1.size() - verticesUg2.size(),
                        end = verticesUg.size() - 1;
        const quint32   beginUg1Array = begin,
                        endUg1Array = ((end + 1) - begin) / 2 - 1;
        const quint32   beginUg2Array = endUg1Array + 1,
                        endUg2Array = end;
        const quint32   verticesNumber = verticesUg1.size() - 1;


        enum Direction {
            CW,
            CCW
        };
        Direction direction = CCW;
        quint16 p1 = 0, p2 = 0, p3 = 0;
        quint32 firstNumber;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CW;
                firstNumber = beginUg1Array;
            }
            else {
                direction = Direction::CCW;
                firstNumber = beginUg2Array;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = 0; index < verticesNumber - 2; index += 2) {
                p1 = firstNumber + index;
                quint16 &refP2 = direction == Direction::CCW ? p2 : p3,
                        &refP3 = direction == Direction::CCW ? p3 : p2;

                refP2 = firstNumber + index + 2;
                refP3 = firstNumber + index + 1;
                iboSectors << p1 << p2 << p3;
                p1++, refP3 += 2;
                iboSectors << p1 << p2 << p3;
            }
        }*/
    /*QVector<quint32> tiboSectors;
        for (quint16 index = 0; index < verticesUg.size() / 2 - 2; index +=2 ) { //CW
            tiboSectors << index << index + 1 << index + 2
                       << index + 1 << index + 3 << index + 2;
        }
        for (quint16 index = verticesUg.size() / 2; index < verticesUg.size() - 2; index += 2) { //CCW
            tiboSectors << index << index + 2 << index + 1
                       << index + 1 << index + 2 << index + 3;
        }*/

    // Правая грань, Левая грань
    /*iboSectors << beginUg1Array + 1 << beginUg2Array << beginUg2Array + 1
                   << beginUg1Array + 1 << beginUg1Array << beginUg2Array;
        iboSectors << endUg1Array - 1 << endUg2Array << endUg2Array - 1
                   << endUg1Array - 1 << endUg1Array << endUg2Array;*/

    /*tiboSectors << 1 << verticesUg.size() / 4 << verticesUg.size() / 4 + 1
                    << 1 << 0 << verticesUg.size() / 4;
        tiboSectors << verticesUg.size() / 4 - 2 << verticesUg.size() / 2 - 1 << verticesUg.size() / 2 - 2
                    << verticesUg.size() / 4 - 2 << verticesUg.size() / 4 - 1 << verticesUg.size() / 2 - 1;*/

    // Лицевая грань, Задняя грань
    /*p1 = 0, p2 = 0, p3 = 0;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CCW;
                firstNumber = beginUg1Array;
            }
            else {
                direction = Direction::CW;
                firstNumber = beginUg1Array;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = i; index < verticesNumber + i - 2; index += 2) {
                p1 = firstNumber + index;
                quint16 &refP2 = direction == Direction::CCW ? p2 : p3,
                        &refP3 = direction == Direction::CCW ? p3 : p2;

                refP2 = firstNumber + index + 2;
                refP3 = beginUg2Array + index;
                iboSectors << p1 << p2 << p3;
                p1 += 2, refP2 = beginUg2Array + index + 2;
                iboSectors << p1 << p2 << p3;
            }
        }*/


    //Верхняя грань
    //quint16 p1 = 0, p2 = 0, p3 = 0;
    /*for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = halfVerticesUg + 2 * index;
            p2 = halfVerticesUg + 2 * index + 2;
            p3 = halfVerticesUg + 2 * index + 1;
            iboSectors << p1 << p2 << p3;
            p1 += 2, p2++;
            iboSectors << p1 << p2 << p3;
        }*/
    /*for (quint16 index = halfVerticesUg - 1; index != 1; index--) {
            iboSectors << index << index - 1 << index - 2;
        }*/
    /*for (quint16 index = halfVerticesUg; index != verticesUg1.size() - 2; index++) {
            iboSectors << index << index + 1 << index + 2;
        }*/

    /*for (quint16 index = verticesUg.size() / 4; index < verticesUg.size() / 2 - 2; index += 2) {
            iboSectors << index << index + 2 << index + 1 << index + 1 << index + 2 << index + 3;
        }
        for (quint16 index = 0; index < verticesUg.size() / 4 - 2; index +=2 ) {
            iboSectors << index << index + 1 << index + 2 << index + 1 << index + 3 << index + 2;
        }*/

    /*iboSectors << 1 << verticesUg.size() / 4 << verticesUg.size() / 4 + 1
                   << 1 << 0 << verticesUg.size() / 4;
        iboSectors << verticesUg.size() / 4 - 2 << verticesUg.size() / 2 - 1 << verticesUg.size() / 2 - 2
                   << verticesUg.size() / 4 - 2 << verticesUg.size() / 4 - 1 << verticesUg.size() / 2 - 1;*/

    /*for (quint16 index = 0; index < 120; index +=2 ) {
            iboSectors << index << index + 2 << verticesUg.size() / 4 + index
                       << index + 2 << verticesUg.size() / 4 + 2 + index << verticesUg.size() / 4 + index;
        }
        for (quint16 index = 1; index < 121; index +=2 ) {
            iboSectors << index << verticesUg.size() / 4 + index << index + 2
                       << index + 2 << verticesUg.size() / 4 + index << verticesUg.size() / 4 + 2 + index;
        }*/
    /*for (quint16 index = 3 * verticesUg.size() / 4; index < verticesUg.size() - 2; index += 2) {
            iboSectors << index << index + 2 << index + 1 << index + 1 << index + 2 << index + 3;
        }*/

    /*enum Direction {
            CW,
            CCW
        };
        Direction direction;
        quint32 firstNumber;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CCW;
                firstNumber = 0;
            }
            else {
                direction = Direction::CW;
                firstNumber = halfVerticesUg;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = 0; index != iterationLimit; index++) {
                p1 = firstNumber + 2 * (index + 1);
                quint16 &refP2 = direction == Direction::CW ? p2 : p3,
                        &refP3 = direction == Direction::CW ? p3 : p2;

                refP2 = firstNumber + 2 * index;
                refP3 = firstNumber + 2 * index + 1;
                iboSectors << p1 << refP2 << refP3;
                refP2++, refP3 += 2;
                iboSectors << p1 << refP2 << refP3;

            }
        }*/

    //Левая грань
    /*p1 = 1, p2 = 0, p3 = halfVerticesUg + 1;
        iboSectors << p1 << p2 << p3;
        p1 = 0, p2 = halfVerticesUg, p3 = halfVerticesUg + 1;
        iboSectors << p1 << p2 << p3;
        //Лицевая грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = 2 * index;
            p2 = 2 * index;
            p3 = halfVerticesUg + 2 * index;
            iboSectors << p1 << p2 << p3;
            p1 += 2;
            p2 = p3 + 2;
            iboSectors << p1 << p2 << p3;
        }
        //Правая грань
        p1 = 0, p2 = 1, p3 = halfVerticesUg;
        iboSectors << p1 << p2 << p3;
        p1 = 1, p2 = halfVerticesUg + 1, p3 = halfVerticesUg;
        iboSectors << p1 << p2 << p3;
        //Задняя грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = 2 * index;
            p2 = 2 * index;
            p3 = halfVerticesUg + 2 * index;
            iboSectors << p1 << p2 << p3;
            p1 += 2;
            p2 = p3 + 2;
            iboSectors << p1 << p2 << p3;
        }
        //Нижняя грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = 2 * index + 1;
            p2 = 2 * index + 3;
            p3 = 2 * index;
            iboSectors << p1 << p2 << p3;
            p1 += 2, p2--;
            iboSectors << p1 << p2 << p3;
        }*/


    /*auto iterUg1 = verticesUg1.end() - 2,
                iterUg2 = verticesUg2.end() - 2;
        for (; iterUg1 != verticesUg1.begin() - 2; iterUg1 -= 2, iterUg2 -= 2) {
            triangleVector << *iterUg2;
            triangleVector << *iterUg1;
        }
        iterUg1 = verticesUg1.begin();
        iterUg2 = verticesUg2.begin();
        triangleVector << *iterUg2;
        triangleVector << *iterUg1;
        for (; iterUg1 != verticesUg1.end(); iterUg1++) {
            triangleVector << *iterUg1;
        }
        iterUg2 = verticesUg2.end() - 2;
        for (; iterUg2 != verticesUg2.begin(); iterUg2 -= 2) {
            triangleVector << *iterUg2;
            iterUg2++;
            triangleVector << *iterUg2;
        }
        triangleVector << *iterUg2;
        iterUg2++;
        triangleVector << *iterUg2;
        iterUg1 = verticesUg1.begin();
        triangleVector << *iterUg1;
        iterUg1++;
        triangleVector << *iterUg1;
        for (; iterUg1 != verticesUg1.end() + 1; iterUg1 += 2, iterUg2 += 2) {
            triangleVector << *iterUg1;
            triangleVector << *iterUg2;
        }*/
    /*}
    sizeVertBuf11 = nDimensional * verticesUg.size();
    GLfloat *vertBuf11 = new GLfloat[sizeVertBuf11];
    quint32 indexBuf11 = 0;
    for (auto i = 0; i != verticesUg.size(); i++) {
        vertBuf11[indexBuf11++] = verticesUg.at(i).x();
        vertBuf11[indexBuf11++] = verticesUg.at(i).y();
        vertBuf11[indexBuf11++] = verticesUg.at(i).z();
    }
    if (indexBuf11 != sizeVertBuf11) {
        qDebug() << "Sectors massiv vertex is invalid";
    }

    sizeIBO12 = iboSectors.size();
    GLuint *iboBuf11 = new GLuint[sizeIBO12];
    quint32 indexIBO11 = 0;
    for (auto i = 0; i != iboSectors.size(); i++) {
        iboBuf11[indexIBO11++] = iboSectors.at(i);
    }
    if (indexIBO11 != sizeIBO12) {
        qDebug() << "Sectors massiv index is invalid";
    }

    m_vaoSector = new QOpenGLVertexArrayObject(this);
    m_vaoSector->create();
    m_vaoSector->bind();
    if (!m_vaoSector->isCreated()){
        qDebug() << "Can't use VAO";
        return;
    }

    m_vboSectors = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboSectors->create();
    m_vboSectors->bind();
    m_vboSectors->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vboSectors->allocate(vertBuf11, sizeVertBuf11 * sizeof(GLfloat));

    QOpenGLBuffer ibo3(QOpenGLBuffer::IndexBuffer);
    ibo3.create();
    ibo3.bind();
    ibo3.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    ibo3.allocate(iboBuf11, sizeIBO12 * sizeof(GLuint));

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    m_vboSectors->release();
    m_vaoSector->release();*/


    //delete [] vertBuf;
    //delete [] vertBuf2;
    //delete [] vertBuf3;
    //delete [] indexBuf1;
}

void Scene::render()
{
    QElapsedTimer frame;
    frame.start();    

    //if (!m_v.isNull()) {
    updateCamera(); //TODO: вынести по сигналу
    //}

    /*QVector2D tVecKM(sceneOptions.sceneRect.width() / m_camera->viewMatrixScale().x(),
                     sceneOptions.sceneRect.height() / m_camera->viewMatrixScale().y());
    QVector2D tVecPix(sceneOptions.screenRect.width() / tVecKM.x(),
                      sceneOptions.screenRect.height() / tVecKM.y());
    qDebug() << tVecKM << tVecPix;*/

    static float m_angle = 0;
    static GLfloat deltaTime = 0;
    static qint64 lastTime = 0;
    static quint64 currentTime = 0;
    static quint64 frameFull = 0;
    static bool firstEntery = true;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(mainViewPort.x(), mainViewPort.y(), mainViewPort.width(), mainViewPort.height());

    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix();

    /*m_programGrid->bind();

    bool isColorDependenceOnY = false;

    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix() * m_modelMatrix;
    m_programGrid->setUniformValue("mvp", mvp);*/

    //    matrixView.scale(camParam.camScale);
    //    matrixView.lookAt(camParam.camPos,
    //                      camParam.camPos + camParam.camLookAt,
    //                      camParam.up);
    //    matrixModel.translate(0, 0, 0);

    //    m_programGrid->setUniformValue("proj", matrixProj);
    //    m_programGrid->setUniformValue("view", matrixView);
    //    m_programGrid->setUniformValue("model", matrixModel);
    /*m_programGrid->setUniformValue("objectColor", QVector4D(0.4f, 0.4f, 0.4f, 0.6f));
    m_programGrid->setUniformValue("isColorDependenceOnY", isColorDependenceOnY);

    m_vao->bind();
    //m_vbo->bind();
    m_vboGrid->bind();
    GLsizei counter = 0;
    for (quint32 k = 5; k <= sceneOptions.maxDist; k+=5) {
        quint32 l = k * 2 * M_PI;
        GLsizei segmentation = l * 10;

        glDrawArrays(GL_LINE_LOOP, counter, segmentation);
        counter += segmentation;
    }

    glDrawArrays(GL_LINES, counter, 4 * 2 + 12 * 2);
    counter += 24 * 3;
    m_vboGrid->release();
    m_vao->release();*/
    //m_vbo->release();

    /*m_sectorsGLData->bindVAO();
    m_programGrid->setUniformValue("objectColor", QVector4D(0.28f, 0.77f, 0.15f, 0.15f));

    QVector<QPair<GLushort, GLushort> > vector;
    m_sectorsGLData->calcDrawVector(vector);
    for (auto &item : vector)
        glDrawElements(GL_TRIANGLES, item.first, GL_UNSIGNED_SHORT, (void *)item.second);

    m_sectorsGLData->releaseVAO();*/

    /*m_programGrid->setUniformValue("objectColor", QVector4D(0.2f, 0.2f, 0.2f, 0.5f));

    const quint16 fullTurn = 360, deltaAz = 45;
    const quint16 azCount = fullTurn / deltaAz;
    for (quint16 i = 0; i < azCount; i++) {
        GLsizei segmentation = 2;

        glDrawArrays(GL_LINES, counter, segmentation);
        counter += segmentation;
    }*/

    /*QMatrix4x4 tempMatrix(matrixModel);
    QQuaternion tempQuater = QQuaternion::fromEulerAngles(-eulerAngles.pitch * 180 / M_PI, -(eulerAngles.yaw + M_PI_2) * 180 / M_PI, -eulerAngles.roll * 180 / M_PI);
    tempMatrix.rotate(tempQuater);
    tempMatrix.translate(camParam.camPos);
    m_programGrid->setUniformValue("model", tempMatrix);
    m_programGrid->setUniformValue("objectColor", QVector4D(0.05f, 0.5f, 0.05f, 1.f));
    glDrawArrays(GL_LINE_LOOP, counter, 4);
    counter += 4;
    glDrawArrays(GL_LINES, counter, 2);
    counter += 2;
    glDrawArrays(GL_LINES, counter, 2);
    counter += 2;*/

    //m_vao->release();

    //m_programGrid->release();


    grideGL->render();
    //ngrideGL->render();

    m_sectorsGLData->render();



//    m_programKTA->bind();
//    GLfloat pointSize = 10;
//    m_programKTA->setUniformValue("mvp", mvp);
//    m_programKTA->setUniformValue("objectColor", QVector4D(0.15f, 0.56f, 0.15f, 1.f));
//    m_programKTA->setUniformValue("pointSize", pointSize);

//    //glFunc->glBindVertexArray(vao);
//    qVAO->bind();

//    glDrawArrays(GL_POINTS, 0, 4);

//    qVAO->release();

//    //glFunc->glBindVertexArray(0);
//    m_programKTA->release();

    rayData->render();

    ktaData->render();

    dspData->render();

    traceData->render();

    mapGL->render();


    //traceData->renderHAz();


    m_programGrid->bind();
    m_programGrid->setUniformValue("mvp", mvp);
    m_programGrid->setUniformValue("objectColor", QVector4D(0.0f, 0.1f, 0.45f, 0.8f));

    vaoRect->bind();
    m_funcs->glDrawArrays(GL_TRIANGLES, 0, sizeRectForSampling / 3);
    vaoRect->release();

    m_programGrid->release();

    //glViewport(extraViewPort.x(), extraViewPort.y(), extraViewPort.width(), extraViewPort.height());

//    grideGL->renderAzH();

  //  traceData->renderHAz();


    /*for (auto &item : vectorExtraWindows) {
        item->preRender();
        //item->renderDSP();
        //item->renderExtraWindow();
        //item->simpleRender();
    }*/

    //test3D->render();
    /*for (int index = 0; index != vectorExtraWindows.size(); index++) {
        vectorExtraWindows.at(index)->simpleRender();
    }*/
    //if (isExtraWindowAdd)
    //    simpleRender();

    /*glViewport(m_viewportSize.width(),
               m_viewportSize.height() - extraWindow.height(),
               extraWindow.width(),
               extraWindow.height());*/


    //renderExtraWindow();

    /*static quint64 counter2 = 0;

    m_programGrid->release();

    const qreal cameraSpeed2 = 0.01;
    static qreal alpha = 0, betta = 0;
    if (keyPressed.key_8){
        alpha += cameraSpeed2;
    }
    if (keyPressed.key_5){
        alpha -= cameraSpeed2;
    }
    if (keyPressed.key_4){
        betta += cameraSpeed2;
    }
    if (keyPressed.key_6){
        betta -= cameraSpeed2;
    }

    if (alpha > M_PI_2) {
        alpha = M_PI_2;
    }
    else if (alpha < -M_PI_2) {
        alpha = -M_PI_2;
    }
    if (betta > M_PI) {
        betta = M_PI;
    }
    else if (betta < -M_PI) {
        betta = -M_PI;
    }*/

    /*GLfloat pointSize = 5;
    m_programKTA->bind();
    m_programKTA->setUniformValue("proj", matrixProj);
    m_programKTA->setUniformValue("view", matrixView);
    m_programKTA->setUniformValue("model", matrixModel);
    m_programKTA->setUniformValue("pointSize", pointSize);
    m_programKTA->setUniformValue("objectColor", QVector4D(0.15f, 0.56f, 0.15f, 0.7f));

    m_vaoKTA->bind();

    static quint16 pointNumber = 0;
    const quint16 pointDraw = 1;

    if (pointNumber > pointDraw)
        glDrawArrays(GL_POINTS, pointNumber - pointDraw, pointDraw);
    else
        glDrawArrays(GL_POINTS, pointNumber, 1);

    m_vaoKTA->release();

    m_programKTA->release();*/

    /*GLint deltaYPort = height(),
          deltaXPort = width() - widthPort;

    QMatrix4x4 matrixProj2;
    if (!sceneOptions2.setOrtho(matrixProj2)) {
        qDebug() << "Ortho projection not set";
    }


    for (quint8 i = 1; i < 2; i++) { //windowsCount
        QMatrix4x4 matrixView2, matrixModel2;

        glViewport(deltaXPort, deltaYPort - i * heightPort, widthPort, heightPort);

        GLfloat *data = vertBuf4 + 0 * 3;  //pointNumber

        matrixView2.scale(camParam2.camScale);
        matrixView2.lookAt(camParam2.camPos,
                          camParam2.camPos + camParam2.camLookAt,
                          camParam2.up);
        //matrixModel2.translate(0, 0, 0);
        //matrixModel2.scale(camParam2.camScale);
        matrixModel2.translate(camParam2.camLookAt);
        QQuaternion tempQuater2 = QQuaternion::fromEulerAngles(-eulerAnglesForPort.pitch * 180 / M_PI, -(eulerAnglesForPort.yaw + M_PI_2) * 180 / M_PI, -eulerAnglesForPort.roll * 180 / M_PI);
        matrixModel2.rotate(tempQuater2);
        matrixModel2.translate(-camParam2.camLookAt);

        m_programGrid->bind();

        m_programGrid->setUniformValue("proj", matrixProj2);
        m_programGrid->setUniformValue("view", matrixView2);
        m_programGrid->setUniformValue("model", matrixModel2);
        m_programGrid->setUniformValue("objectColor", QVector4D(0.30f, 0.30f, 0.30f, 1.0f));

        m_vao->bind();

        //glDrawArrays(GL_TRIANGLE_FAN, counter, 3*6);
        counter += 8;

        //m_programGrid->setUniformValue("objectColor", QVector4D(1.0f, 1.0f, 1.0f, 0.8f));
        glDrawArrays(GL_LINES, counter, 40); //116
        counter += 40;
        //m_programGrid->setUniformValue("objectColor", QVector4D(0.07f, 0.68f, 0.0f, 0.8f));
        //counter += 48;
        //glDrawArrays(GL_LINES, counter, 6);
        m_vao->release();

        m_vao2->bind();

        isColorDependenceOnY = true;
        m_programGrid->setUniformValue("objectColor", QVector4D(0.51f, 0.30f, 0.30f, 1.0f));
        m_programGrid->setUniformValue("isColorDependenceOnY", isColorDependenceOnY);
        glDrawElements(GL_TRIANGLES, sizeIndexBuf1, GL_UNSIGNED_INT, 0);
        isColorDependenceOnY = false;

        m_vao2->release();

        m_vao3->bind();

        m_programGrid->setUniformValue("objectColor", QVector4D(0.30f, 0.30f, 0.30f, 0.5f));
        m_programGrid->setUniformValue("isColorDependenceOnY", isColorDependenceOnY);
        glDrawElements(GL_TRIANGLES, sizeIndexBuf2, GL_UNSIGNED_INT, 0);

        m_vao3->release();


        m_programGrid->release();
    }*/

    /*if (++pointNumber > KTAcount)
        pointNumber = 0;*/

    currentTime = frame.nsecsElapsed() / 1000;
    //deltaTime = currentTime / 1000;
    //qDebug() << currentTime << " мкс";
    //counter2++;

    frameFull += currentTime;
}

void Scene::resize(int w, int h, int x, int y)
{
    // Make sure the viewport covers the entire window
    //glViewport(0, 0, w, h);

    //h *= 0.66; //for Test3D
    //y = h * 0.35;
    float mainOccupiedSpace = 1.;//0.65;
    float hMain = h * mainOccupiedSpace,
          hExtra = h * (1 - mainOccupiedSpace);
    screenSize = QSize(w, h);
    //mainViewPort = OpenGLRectF(x, y, w, h);
    //sceneOptions.setScreenRect(qreal(w), qreal(h), x, y);
    mainViewPort = OpenGLRectF(x, y, w, hMain);
    extraViewPort = OpenGLRectF(x, hMain, w, hExtra);
    sceneOptions.setScreenRect(qreal(w), hMain, x, y);

    extraSceneOptions.maxDist = 180;
    extraSceneOptions.initialRect = OpenGLRectF(-extraSceneOptions.maxDist, -10,
                                                extraSceneOptions.maxDist * 2, sceneOptions.maxDist + 10);
    extraSceneOptions.setScreenRect(w, hExtra, x, hMain);
    //extraSceneOptions.aspectRatio = (float)w / hExtra;
    //extraSceneOptions.screenRect = QRectF(x, hMain, w, hExtra);
    //extraSceneOptions.sceneRect = OpenGLRectF(-extraSceneOptions.maxDist, -10,
    //                                          extraSceneOptions.maxDist * 2, sceneOptions.maxDist + 10);


    //if (orthoProjection) {
        m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
                                            sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
                                            sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());
        m_extraCamera->setOrthographicProjection(extraSceneOptions.sceneRect.left(), extraSceneOptions.sceneRect.right(),
                                                 extraSceneOptions.sceneRect.bottom(), extraSceneOptions.sceneRect.top(),
                                                 extraSceneOptions.farNearPlane.x(), extraSceneOptions.farNearPlane.y());
    /*}
    else {
        m_camera->setPerspectiveProjection(40.f,
                                           sceneOptions.aspectRatio,
                                           0.1, 1000);
    }*/
    // Update the orthographic matrix
    /*m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
                                        sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
                                        sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());*/

    // Update the projection matrix
    //float aspect = static_cast<float>( w ) / static_cast<float>( h );
    //m_camera->setPerspectiveProjection( 25.0f, aspect, 0.1f, 128.0f );

//    OpenGLRectF tempSize(mainViewPort.x(), mainViewPort.y(),
//                         mainViewPort.width() - extraWindow.width(), mainViewPort.height());
//    //glViewport(0, 0, tempSize.width(), tempSize.height());
//    mainViewPort = OpenGLRectF(tempSize);
//    sceneOptions.setScreenRect(tempSize.width(), tempSize.height());

//    // Update the orthographic matrix
//    m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
//                                        sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
//                                        sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());

    /*m_cameraExtraWindow->setPosition( QVector3D( 0.0f, 0.0f, 10.0f ) );
    m_cameraExtraWindow->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
    m_cameraExtraWindow->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );
    m_cameraExtraWindow->setOrthographicProjection(0, extraWindow.width(),
                                                   0, extraWindow.height(),
                                                   -100,100);*/
}

void Scene::resizeViewPort(int w, int h) {
    mainViewPort = OpenGLRectF(0, 0, w, h);
    sceneOptions.setScreenRect(qreal(w), qreal(h));

    //if (orthoProjection) {
        m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
                                            sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
                                            sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());
    //}
    /*else {
        m_camera->setPerspectiveProjection(40.f,
                                           sceneOptions.aspectRatio,
                                           0.1, 1000);
    }*/
}

void Scene::setTerrainHorizontalScale(const float &horizontalScale)
{
    /*if ((m_camera->viewMatrixScale().x() < 0.5 && horizontalScale < 1) ||
            (m_camera->viewMatrixScale().x() > 150 && horizontalScale > 1))
        return;

    QVector3D preScale(m_camera->viewMatrixScale());
    preScale *= horizontalScale;

    if (preScale.x() > 150.) {
        float maxScale = 150. / m_camera->viewMatrixScale().x();
        m_camera->updateScaleOfViewMatrix(maxScale);
        grideGL->updateText(maxScale);
    }
    else if (preScale.x() < 0.5) {
        float minScale = 0.5 / m_camera->viewMatrixScale().x();
        m_camera->updateScaleOfViewMatrix(minScale);
        grideGL->updateText(minScale);
    }
    else {
        m_camera->updateScaleOfViewMatrix(horizontalScale);
        grideGL->updateText(horizontalScale);
    }*/
    //test3D->updateScaleOfView(horizontalScale);
    m_extraCamera->updateScaleOfViewMatrix(horizontalScale);
}

void Scene::userScaling(const float &horizontalScale, bool centerOnMouseCursor, QPointF mouseCursor)
{
    if ((m_camera->viewMatrixScale().x() < 0.5 && horizontalScale < 1) ||
            (m_camera->viewMatrixScale().x() > 150 && horizontalScale > 1))
        return;

    if (centerOnMouseCursor) {
        QVector3D scenePoint(screenToSceneDxDy(mouseCursor));
        scenePoint.setZ(0.0);
        Camera::CameraTranslationOption option = m_viewCenterFixed
                ? Camera::DontTranslateViewCenter
                : Camera::TranslateViewCenter;
        QVector3D dCenterPoint(scenePoint - m_camera->viewCenter());
        dCenterPoint.setY(-dCenterPoint.y());

        m_camera->translate( dCenterPoint, option );
        //qDebug() << m_camera->viewCenter();
    }    

    QVector3D preScale(m_camera->viewMatrixScale());
    preScale *= horizontalScale;

    //qDebug() << "preScale " << preScale;

    if (preScale.x() > 150.) {
        float maxScale = 150. / m_camera->viewMatrixScale().x();
        m_camera->updateScaleOfViewMatrix(maxScale);
        grideGL->updateText(maxScale);
    }
    else if (preScale.x() < 0.5) {
        float minScale = 0.5 / m_camera->viewMatrixScale().x();
        m_camera->updateScaleOfViewMatrix(minScale);
        grideGL->updateText(minScale);
    }
    else {
        m_camera->updateScaleOfViewMatrix(horizontalScale);
        grideGL->updateText(horizontalScale);
    }

    traceData->reCalcAllTrace();
}

void Scene::updateCamera()
{
    m_modelMatrix.setToIdentity();

    // Update the camera position and orientation
    Camera::CameraTranslationOption option = m_viewCenterFixed
            ? Camera::DontTranslateViewCenter
            : Camera::TranslateViewCenter;

    /*if (!m_v.isNull()){
        qDebug() << "is no null";
    }*/

    if (!m_v.isNull()) {
        //m_v.setX(m_v.x() * sceneOptions.aspectRatioScreenWithScene.x() / m_camera->viewMatrixScale().x());
        //m_v.setY(m_v.y() * sceneOptions.aspectRatioScreenWithScene.y() / m_camera->viewMatrixScale().y());
        m_camera->translate( m_v, option );
        m_v = QVector3D();

        //emit cameraIsUpdate(m_camera->viewCenter());
    }


    /*if ( !qFuzzyIsNull( m_yawAngle ) )
    {
        //m_camera->yaw( m_yawAngle, QVector3D( 0.0f, 1.0f, 0.0f ) );
        m_camera->yawAboutViewCenter(m_yawAngle);
        m_yawAngle = 0.0f;
    }

    if ( !qFuzzyIsNull( m_pitchAngle ) )
    {
        //m_camera->pitch( m_pitchAngle );
        m_camera->pitchAboutViewCenter(m_pitchAngle);
        m_pitchAngle = 0.0f;
    }

    if ( !qFuzzyIsNull( m_rollAngle ) )
    {
        //m_camera->roll( m_rollAngle );
        m_camera->rollAboutViewCenter(m_rollAngle);
        m_rollAngle = 0.0f;
    }*/
}

void Scene::resetCamera()
{
    m_modelMatrix.setToIdentity();

    // Initialize the camera position and orientation
    m_camera->setPosition( QVector3D( 0.0f, 0.0f, 100.0f ) );
    m_camera->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
    m_camera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );

    m_camera->resetScaleOfViewMatrix();
}

void Scene::resetScaling()
{
    resetCamera();
    traceData->reCalcAllTrace();
}

void Scene::resetExtraCamera()
{
    m_extraCamera->setPosition( QVector3D( 0.0f, 0.0f, 10.0f ) );
    m_extraCamera->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
    m_extraCamera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );

    m_extraCamera->resetScaleOfViewMatrix();
}

void Scene::mouseTracking(const QPointF &point)
{
    QPoint _point(point.toPoint());
    for ( auto &item : vectorExtraWindows) {
        if (item->getQRect().contains(_point)) {
            item->searchHoveredSelectedItem(_point, true);
        }
    }
    /*QPoint _point(point.toPoint());
    if (buttonAltitudeQRect.contains(_point)) {
        hoveredItem = 0;
    }
    else if (buttonDSPQRect.contains(_point)) {
        hoveredItem = 1;
    }
    else if (buttonNTQRect.contains(_point)) {
        hoveredItem = 2;
    }
    else {
        hoveredItem = -1;
    }*/
}

void Scene::mouseRelease(const QPointF &point)
{
    QPoint _point(point.toPoint());
    for ( auto &item : vectorExtraWindows) {
        if (item->getQRect().contains(_point)) {
            item->searchHoveredSelectedItem(_point, false);
        }
    }
    /*QPoint _point(point.toPoint());
    if (buttonAltitudeQRect.contains(_point)) {
        selectedItem = 0;
    }
    else if (buttonDSPQRect.contains(_point)) {
        selectedItem = 1;
    }
    else if (buttonNTQRect.contains(_point)) {
        selectedItem = 2;
    }*/
}

QVector3D Scene::screenToScene(const QPointF &point)
{
    QPointF tempPoint(point.x() + mainViewPort.x(),
                      point.y() + mainViewPort.y() / 2);


    QVector3D vector(QVector3D(point.x() + mainViewPort.x(), point.y() + mainViewPort.y() / 2, 0.0)
                     .unproject(m_camera->viewMatrix(),
                                m_camera->projectionMatrix(),
                                QRect(mainViewPort.x(), mainViewPort.y(), mainViewPort.width(), mainViewPort.height())));
    vector.setY(-vector.y());
    QVector3D pos(m_camera->position());
    vector.setY(vector.y() + 2 * pos.y());


    return vector;
}

QVector3D Scene::screenToSceneDxDy(const QPointF &point)
{
    return QVector3D(point.x() + mainViewPort.x(), point.y() + mainViewPort.y() / 2, 0.0)
            .unproject(m_camera->viewMatrix(),
                       m_camera->projectionMatrix(),
                       QRect(mainViewPort.x(), mainViewPort.y(), mainViewPort.width(), mainViewPort.height()));
}

void Scene::mouseMoveGride()
{
    grideGL->updateMoveText();
}

void Scene::KTASampling(const QPointF &point1, const QPointF &point2)
{
    QVector3D vector1(screenToScene(point1)),
              vector2(screenToScene(point2));

    QPointF leftBottom, rightTop;
    if (vector1.x() < vector2.x()) {
        leftBottom.rx() = vector1.x();
        rightTop.rx() = vector2.x();
    }
    else {
        leftBottom.rx() = vector2.x();
        rightTop.rx() = vector1.x();
    }
    if (vector1.y() < vector2.y()) {
        leftBottom.ry() = vector1.y();
        rightTop.ry() = vector2.y();
    }
    else {
        leftBottom.ry() = vector2.y();
        rightTop.ry() = vector1.y();
    }
    qDebug() << leftBottom;

    emit KTASamplingRequest(leftBottom, rightTop);

    sizeRectForSampling = 0;
}

void Scene::updateRect(const QPointF &point1, const QPointF &point2)
{
    QVector3D vector1(screenToScene(point1)),
              vector2(screenToScene(point2));

    QPointF leftBottom, rightTop;
    if (vector1.x() < vector2.x()) {
        leftBottom.rx() = vector1.x();
        rightTop.rx() = vector2.x();
    }
    else {
        leftBottom.rx() = vector2.x();
        rightTop.rx() = vector1.x();
    }
    if (vector1.y() < vector2.y()) {
        leftBottom.ry() = vector1.y();
        rightTop.ry() = vector2.y();
    }
    else {
        leftBottom.ry() = vector2.y();
        rightTop.ry() = vector1.y();
    }

    float rectWidth = abs(rightTop.x() - leftBottom.x()),
            rectHeight = abs(rightTop.y() - leftBottom.y());

    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;

    //background of window
    sizeRectForSampling = pointPerRect;
    GLfloat *rectForSamplingBuf = new GLfloat[sizeRectForSampling];

    float zcoord = 10;
    calcRect(OpenGLRectF(leftBottom.x(), leftBottom.y(),
                         rectWidth, rectHeight), rectForSamplingBuf, 0, zcoord);

    m_funcs->glBindBuffer(GL_ARRAY_BUFFER, vboRect->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)m_funcs->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      sizeRectForSampling * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, rectForSamplingBuf, sizeRectForSampling * sizeof(GLfloat));
    m_funcs->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    delete [] rectForSamplingBuf;
}

void Scene::targetingAdd(const QPointF &point)
{
    QVector3D vector(screenToScene(point));

    emit targetingAddRequest(QPointF(vector.x(), vector.y()), false);
}

void Scene::targetingAddQuick(const QPointF &point)
{
    QVector3D vector(screenToScene(point));

    emit targetingAddRequest(QPointF(vector.x(), vector.y()), true);
}

void Scene::targetingExclude(const QPointF &point)
{
    QVector3D vector(screenToScene(point));

    emit targetingExcludeRequest(QPointF(vector.x(), vector.y()));
}

void Scene::test3DCamera(float yaw, float pitch, float roll)
{
    //test3D->updateEulerAngels(yaw, pitch, roll);
}

void Scene::addExtraWindow(const quint8 size)
{
    /*static int currentWindows = 0;
    if (currentWindows >= 0 && currentWindows < 5) {
        if (currentWindows == 0) {
            emit resizeRequest(QSize(m_viewportSize.width() - extraWindow.width(), m_viewportSize.height()));
        }
    }
    else if (currentWindows >= 5 && currentWindows <= 9) {
        if (currentWindows == 5) {
            emit resizeRequest(QSize(m_viewportSize.width() - extraWindow.width(), m_viewportSize.height()));
        }
    }
    else if (currentWindows > 9)
        return;

    currentWindows++;*/
    if (vectorExtraWindows.size() == 10) {
        qDebug() << "No space for extra window";
        return;
    }

    /*if (size <= vectorExtraWindows.size()) {
        return;
    }*/

    ExtraWindow *ptr_extraWindow = new ExtraWindow(m_funcs, m_programFont, m_programButton, customFontDriver);
    OpenGLRectF rect;
    QRect qrect;
    const int vectorSize = vectorExtraWindows.size() + 1;
    if (vectorSize >= 1 && vectorSize < 6) {
        rect = OpenGLRectF(screenSize.width() - extraWindow.width(),
                           screenSize.height() - vectorSize * extraWindow.height(),
                           extraWindow.width(),
                           extraWindow.height());

        qrect = QRect(screenSize.width() - extraWindow.width(),
                      (vectorSize - 1) * extraWindow.height(),
                      extraWindow.width(),
                      extraWindow.height());
    }
    else if (vectorSize >= 6 && vectorSize <= 10) {
        rect = OpenGLRectF(screenSize.width() - 2 * extraWindow.width(),
                           screenSize.height() - (vectorSize - 5) * extraWindow.height(),
                           extraWindow.width(),
                           extraWindow.height());

        qrect = QRect(screenSize.width() - 2 * extraWindow.width(),
                      (vectorSize - 6) * extraWindow.height(),
                      extraWindow.width(),
                      extraWindow.height());
    }
    ptr_extraWindow->setRect(rect);
    ptr_extraWindow->setQRect(qrect);
    ptr_extraWindow->setUBOInfo(uboIndex, (vectorSize - 1) * 200);
    ptr_extraWindow->prepareExtraWindow();
    ptr_extraWindow->prepareDSP();
    //ptr_extraWindow->simplePrepare();

    if (vectorSize == 1) {
        resizeViewPort(screenSize.width() - extraWindow.width(),
                       screenSize.height());
    }
    else if (vectorSize == 6) {
        resizeViewPort(screenSize.width() - 2 * extraWindow.width(),
                       screenSize.height());
    }

    vectorExtraWindows.push_back(ptr_extraWindow);


    /*resizeViewPort(screenSize.width() - extraWindow.width(),
                   screenSize.height());*/

    //simplePrepare();
}

void Scene::updateInfoInExtraWindow(quint16 id, quint16 h)
{
    if (id >= vectorExtraWindows.size()) {
        qDebug() << "Cant find extra window";
        return;
    }

    vectorExtraWindows.at(id)->addInfo(h);
}

void Scene::changeProjectionSlot(bool flag)
{
    //if (flag) {
        orthoProjection = true;
        m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
                                            sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
                                            sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());
    //}
    /*else {
        orthoProjection = false;
        m_camera->setPerspectiveProjection(40.f,
                                           sceneOptions.aspectRatio,
                                           0.1, 10000);
    }*/
}

void Scene::setBackground(QColor color)
{
    backgroundColor = color;
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.);
}

void Scene::setDistMax(const quint16 value)
{
    sceneOptions.updateMaxDist(value);
    resize(screenSize.width(), screenSize.height());

    grideGL->prepare();
}

void Scene::initSceneProperties(const SceneCustomDataInit &cData)
{
    setBackground(cData.backgroundColor);

    grideGL->setGrideColor(cData.grideColor);
    grideGL->setTextSize(TextSizeAction::Reset, cData.grideTextSize);
    grideGL->setTextColor(cData.grideTextColor);
    grideGL->setAzMarkOnOff(cData.grideAzMark);
    grideGL->setDistMarkOnOff(cData.grideDistMark);

    ktaData->setKTAColor(true, cData.ktaPOIColor);
    ktaData->setKTASize(true, TextSizeAction::Reset, cData.ktaPOISize);
    ktaData->setKTAColor(false, cData.ktaVOIColor);
    ktaData->setKTASize(false, TextSizeAction::Reset, cData.ktaVOISize);

    m_sectorsGLData->setColor(cData.sectorsColor);

    rayData->setColor(cData.rayColor);
    rayData->setMaxDist(cData.rayDistMax);

    traceData->setTraceColor(cData.traceColor);
    traceData->setLogBookColor(cData.traceLBColor);
    traceData->setTextColor(cData.traceLBTextSize);
    traceData->setTextSize(TextSizeAction::Reset, cData.traceLBTextSize);
}

void Scene::setSideSpeedSlot(float vx)
{
    m_v.setX(m_v.x() + vx);
}

void Scene::setForwardSpeedSlot(float vy)
{
    m_v.setY(m_v.y() + vy);
}

void Scene::prepareGrid()
{
    const quint32 freqCircleInKm = 5;
    //const quint32 numCircle = maxDist / freqCircleInKm;
    const quint32 nDimensional = 3;

    quint32 coordsNumber = 0;
    for (quint32 k = freqCircleInKm; k <= sceneOptions.maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        coordsNumber += l * 10;
    }
    const quint32 sizeVertBuf = coordsNumber * nDimensional + 2 * 4 * nDimensional;
    GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

    quint32 posArr = 0;
    QVector<QPointF> vect;
    for (quint32 k = freqCircleInKm; k <= sceneOptions.maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        quint32 segmentation = l * 10;
        double deltaAlpha = 2. * M_PI / static_cast<double>(segmentation);
        //quint32 counter = 0;
        double alpha = 0;
        QVector<QPointF> tvector;
        for (quint32 counter = 0; counter != segmentation; counter++) {
            vertBufGrid[posArr++] = k * cos(alpha);
            vertBufGrid[posArr++] = k * sin(alpha);
            vertBufGrid[posArr++] = 0.;
            tvector << QPointF(vertBufGrid[posArr - 2], vertBufGrid[posArr - 1]);
            alpha += deltaAlpha;
            //            counter++;
        }
        /*vect << tvector;
        if (k > 110) {
            int ie = 5;
            ie++;
        }*/
        if (posArr > sizeVertBuf) {
            qDebug() << "Overflow Grid array";
        }
    }
    for (quint32 i = 0; i < 4; i++) {  // для высоты
        vertBufGrid[posArr++] = sceneOptions.maxDist * cos(i * M_PI_2);
        vertBufGrid[posArr++] = sceneOptions.maxDist * sin(i * M_PI_2);
        vertBufGrid[posArr++] = 0.;

        vertBufGrid[posArr++] = sceneOptions.maxDist * cos(i * M_PI_2);
        vertBufGrid[posArr++] = sceneOptions.maxDist * sin(i * M_PI_2);
        vertBufGrid[posArr++] = sceneOptions.maxDist;
    }


    const quint16 fullTurn = 360, deltaAz = 30;
    const quint16 azCount = fullTurn / deltaAz;
    const qreal coeffDeg2Rad = M_PI / 180.;
    const qreal fullTurnReal = fullTurn * coeffDeg2Rad, deltaAzReal = deltaAz * coeffDeg2Rad;

    const quint32 sizeVertBuf2 = 2 * azCount * nDimensional;
    GLfloat *vertBuf2 = new GLfloat[sizeVertBuf2];

    posArr = 0;
    for (quint16 i = 0; i < azCount; i++) {
        vertBuf2[posArr++] = sceneOptions.maxDist * cos(i * deltaAzReal);
        vertBuf2[posArr++] = sceneOptions.maxDist * sin(i * deltaAzReal);
        vertBuf2[posArr++] = 0.;

        vertBuf2[posArr++] = sceneOptions.maxDist * cos(i * deltaAzReal + M_PI);
        vertBuf2[posArr++] = sceneOptions.maxDist * sin(i * deltaAzReal + M_PI);
        vertBuf2[posArr++] = 0.;
    }

    const quint32 sizeVertBuf3 = 8 * nDimensional;
    GLfloat *vertBuf3 = new GLfloat[sizeVertBuf3];

    posArr = 0;
    for (quint16 i = 0; i < 4; i++) {
        vertBuf3[posArr++] = 20 * sin(i * M_PI_2 + deltaAzReal);
        vertBuf3[posArr++] = 20 * cos(i * M_PI_2 + deltaAzReal);
        vertBuf3[posArr++] = 0.;
    }

    vertBuf3[posArr++] = 20 * sin(deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(2 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(2 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(3 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(3 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;

    m_vboGrid = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboGrid->create();
    m_vboGrid->bind();
    m_vboGrid->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboGrid->allocate(vertBufGrid, (sizeVertBuf + sizeVertBuf2 + sizeVertBuf3) * sizeof(GLfloat));
    m_vboGrid->write(sizeVertBuf * sizeof(GLfloat), vertBuf2, sizeVertBuf2 * sizeof(GLfloat));
    m_vboGrid->write((sizeVertBuf + sizeVertBuf2) * sizeof(GLfloat), vertBuf3, sizeVertBuf3 * sizeof(GLfloat));

    m_vao->bind();
    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    m_vboGrid->release();
    m_vao->release();

    delete [] vertBufGrid;
    delete [] vertBuf2;
    delete [] vertBuf3;
}

void Scene::prepareSectors()
{
    const quint32 nDimensional = 3;
    struct structSector {
        double r, R;
        double az1, az2;
        double ug1, ug2;
    };
    QVector<structSector> SectorsVector = { {50,90, 0,40, 30,50},
                                            /*{25,75, 90,150, 10,45},*/
                                            /*{50,60, 287,297, 0,10}*/
                                            /*{50,60, 340, 360, 55,65}*/
                                            /*{80,110, 130,150, 10,20}*/};

    QVector<QVector3D> triangleVector, verticesUg;
    QVector<quint32> iboSectors;
    for (auto item : SectorsVector) {
        QVector<QVector3D> verticesUg1, verticesUg2;

        double R = item.R, r = item.r,
                az1 = item.az1 * M_PI / 180.0, az2 = item.az2 * M_PI / 180.0,
                ug1 = (90 - item.ug1) * M_PI / 180.0, ug2 = (90 - item.ug2) * M_PI / 180.0,
                seg = 60;
        double dAz = (az2 - az1) / seg;
        for (int i = 0; i < seg + 1; i++) {
            verticesUg1 << QVector3D(r * cos(az1 + i * dAz) * sin(ug1), r * sin(az1 + i * dAz) * sin(ug1), r * cos(ug1))
                        << QVector3D(R * cos(az1 + i * dAz) * sin(ug1), R * sin(az1 + i * dAz) * sin(ug1), R * cos(ug1));
            verticesUg2 << QVector3D(r * cos(az1 + i * dAz) * sin(ug2), r * sin(az1 + i * dAz) * sin(ug2), r * cos(ug2))
                        << QVector3D(R * cos(az1 + i * dAz) * sin(ug2), R * sin(az1 + i * dAz) * sin(ug2), R * cos(ug2));
        }
        verticesUg << verticesUg1 << verticesUg2;

        const quint32   begin = verticesUg.size() - verticesUg1.size() - verticesUg2.size(),
                end = verticesUg.size() - 1;
        const quint32   beginUg1Array = begin,
                endUg1Array = ((end + 1) - begin) / 2 - 1;
        const quint32   beginUg2Array = endUg1Array + 1,
                endUg2Array = end;
        const quint32   verticesNumber = verticesUg1.size() - 1;


        enum Direction {
            CW,
            CCW
        };
        Direction direction = CCW;
        quint16 p1 = 0, p2 = 0, p3 = 0;
        quint32 firstNumber;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CW;
                firstNumber = beginUg1Array;
            }
            else {
                direction = Direction::CCW;
                firstNumber = beginUg2Array;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = 0; index < verticesNumber - 2; index += 2) {
                p1 = firstNumber + index;
                quint16 &refP2 = direction == Direction::CCW ? p2 : p3,
                        &refP3 = direction == Direction::CCW ? p3 : p2;

                refP2 = firstNumber + index + 2;
                refP3 = firstNumber + index + 1;
                iboSectors << p1 << p2 << p3;
                p1++, refP3 += 2;
                iboSectors << p1 << p2 << p3;
            }
        }
        /*QVector<quint32> tiboSectors;
        for (quint16 index = 0; index < verticesUg.size() / 2 - 2; index +=2 ) { //CW
            tiboSectors << index << index + 1 << index + 2
                       << index + 1 << index + 3 << index + 2;
        }
        for (quint16 index = verticesUg.size() / 2; index < verticesUg.size() - 2; index += 2) { //CCW
            tiboSectors << index << index + 2 << index + 1
                       << index + 1 << index + 2 << index + 3;
        }*/

        // Правая грань, Левая грань
        iboSectors << beginUg1Array + 1 << beginUg2Array << beginUg2Array + 1
                   << beginUg1Array + 1 << beginUg1Array << beginUg2Array;
        iboSectors << endUg1Array - 1 << endUg2Array << endUg2Array - 1
                   << endUg1Array - 1 << endUg1Array << endUg2Array;

        /*tiboSectors << 1 << verticesUg.size() / 4 << verticesUg.size() / 4 + 1
                    << 1 << 0 << verticesUg.size() / 4;
        tiboSectors << verticesUg.size() / 4 - 2 << verticesUg.size() / 2 - 1 << verticesUg.size() / 2 - 2
                    << verticesUg.size() / 4 - 2 << verticesUg.size() / 4 - 1 << verticesUg.size() / 2 - 1;*/

        // Лицевая грань, Задняя грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CCW;
                firstNumber = beginUg1Array;
            }
            else {
                direction = Direction::CW;
                firstNumber = beginUg1Array;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = i; index < verticesNumber + i - 2; index += 2) {
                p1 = firstNumber + index;
                quint16 &refP2 = direction == Direction::CCW ? p2 : p3,
                        &refP3 = direction == Direction::CCW ? p3 : p2;

                refP2 = firstNumber + index + 2;
                refP3 = beginUg2Array + index;
                iboSectors << p1 << p2 << p3;
                p1 += 2, refP2 = beginUg2Array + index + 2;
                iboSectors << p1 << p2 << p3;
            }
        }


        //Верхняя грань
        //quint16 p1 = 0, p2 = 0, p3 = 0;
        /*for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = halfVerticesUg + 2 * index;
            p2 = halfVerticesUg + 2 * index + 2;
            p3 = halfVerticesUg + 2 * index + 1;
            iboSectors << p1 << p2 << p3;
            p1 += 2, p2++;
            iboSectors << p1 << p2 << p3;
        }*/
        /*for (quint16 index = halfVerticesUg - 1; index != 1; index--) {
            iboSectors << index << index - 1 << index - 2;
        }*/
        /*for (quint16 index = halfVerticesUg; index != verticesUg1.size() - 2; index++) {
            iboSectors << index << index + 1 << index + 2;
        }*/

        /*for (quint16 index = verticesUg.size() / 4; index < verticesUg.size() / 2 - 2; index += 2) {
            iboSectors << index << index + 2 << index + 1 << index + 1 << index + 2 << index + 3;
        }
        for (quint16 index = 0; index < verticesUg.size() / 4 - 2; index +=2 ) {
            iboSectors << index << index + 1 << index + 2 << index + 1 << index + 3 << index + 2;
        }*/

        /*iboSectors << 1 << verticesUg.size() / 4 << verticesUg.size() / 4 + 1
                   << 1 << 0 << verticesUg.size() / 4;
        iboSectors << verticesUg.size() / 4 - 2 << verticesUg.size() / 2 - 1 << verticesUg.size() / 2 - 2
                   << verticesUg.size() / 4 - 2 << verticesUg.size() / 4 - 1 << verticesUg.size() / 2 - 1;*/

        /*for (quint16 index = 0; index < 120; index +=2 ) {
            iboSectors << index << index + 2 << verticesUg.size() / 4 + index
                       << index + 2 << verticesUg.size() / 4 + 2 + index << verticesUg.size() / 4 + index;
        }
        for (quint16 index = 1; index < 121; index +=2 ) {
            iboSectors << index << verticesUg.size() / 4 + index << index + 2
                       << index + 2 << verticesUg.size() / 4 + index << verticesUg.size() / 4 + 2 + index;
        }*/
        /*for (quint16 index = 3 * verticesUg.size() / 4; index < verticesUg.size() - 2; index += 2) {
            iboSectors << index << index + 2 << index + 1 << index + 1 << index + 2 << index + 3;
        }*/

        /*enum Direction {
            CW,
            CCW
        };
        Direction direction;
        quint32 firstNumber;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CCW;
                firstNumber = 0;
            }
            else {
                direction = Direction::CW;
                firstNumber = halfVerticesUg;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = 0; index != iterationLimit; index++) {
                p1 = firstNumber + 2 * (index + 1);
                quint16 &refP2 = direction == Direction::CW ? p2 : p3,
                        &refP3 = direction == Direction::CW ? p3 : p2;

                refP2 = firstNumber + 2 * index;
                refP3 = firstNumber + 2 * index + 1;
                iboSectors << p1 << refP2 << refP3;
                refP2++, refP3 += 2;
                iboSectors << p1 << refP2 << refP3;

            }
        }*/

        //Левая грань
        /*p1 = 1, p2 = 0, p3 = halfVerticesUg + 1;
        iboSectors << p1 << p2 << p3;
        p1 = 0, p2 = halfVerticesUg, p3 = halfVerticesUg + 1;
        iboSectors << p1 << p2 << p3;
        //Лицевая грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = 2 * index;
            p2 = 2 * index;
            p3 = halfVerticesUg + 2 * index;
            iboSectors << p1 << p2 << p3;
            p1 += 2;
            p2 = p3 + 2;
            iboSectors << p1 << p2 << p3;
        }
        //Правая грань
        p1 = 0, p2 = 1, p3 = halfVerticesUg;
        iboSectors << p1 << p2 << p3;
        p1 = 1, p2 = halfVerticesUg + 1, p3 = halfVerticesUg;
        iboSectors << p1 << p2 << p3;
        //Задняя грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = 2 * index;
            p2 = 2 * index;
            p3 = halfVerticesUg + 2 * index;
            iboSectors << p1 << p2 << p3;
            p1 += 2;
            p2 = p3 + 2;
            iboSectors << p1 << p2 << p3;
        }
        //Нижняя грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 index = 0; index != iterationLimit; index++) {
            p1 = 2 * index + 1;
            p2 = 2 * index + 3;
            p3 = 2 * index;
            iboSectors << p1 << p2 << p3;
            p1 += 2, p2--;
            iboSectors << p1 << p2 << p3;
        }*/


        /*auto iterUg1 = verticesUg1.end() - 2,
                iterUg2 = verticesUg2.end() - 2;
        for (; iterUg1 != verticesUg1.begin() - 2; iterUg1 -= 2, iterUg2 -= 2) {
            triangleVector << *iterUg2;
            triangleVector << *iterUg1;
        }
        iterUg1 = verticesUg1.begin();
        iterUg2 = verticesUg2.begin();
        triangleVector << *iterUg2;
        triangleVector << *iterUg1;
        for (; iterUg1 != verticesUg1.end(); iterUg1++) {
            triangleVector << *iterUg1;
        }
        iterUg2 = verticesUg2.end() - 2;
        for (; iterUg2 != verticesUg2.begin(); iterUg2 -= 2) {
            triangleVector << *iterUg2;
            iterUg2++;
            triangleVector << *iterUg2;
        }
        triangleVector << *iterUg2;
        iterUg2++;
        triangleVector << *iterUg2;
        iterUg1 = verticesUg1.begin();
        triangleVector << *iterUg1;
        iterUg1++;
        triangleVector << *iterUg1;
        for (; iterUg1 != verticesUg1.end() + 1; iterUg1 += 2, iterUg2 += 2) {
            triangleVector << *iterUg1;
            triangleVector << *iterUg2;
        }*/
    }
    sizeVertBuf11 = nDimensional * verticesUg.size();
    GLfloat *vertBuf11 = new GLfloat[sizeVertBuf11];
    quint32 indexBuf11 = 0;
    for (auto i = 0; i != verticesUg.size(); i++) {
        vertBuf11[indexBuf11++] = verticesUg.at(i).x();
        vertBuf11[indexBuf11++] = verticesUg.at(i).y();
        vertBuf11[indexBuf11++] = verticesUg.at(i).z();
    }
    if (indexBuf11 != sizeVertBuf11) {
        qDebug() << "Sectors massiv vertex is invalid";
    }

    sizeIBO12 = iboSectors.size();
    GLuint *iboBuf11 = new GLuint[sizeIBO12];
    quint32 indexIBO11 = 0;
    for (auto i = 0; i != iboSectors.size(); i++) {
        iboBuf11[indexIBO11++] = iboSectors.at(i);
    }
    if (indexIBO11 != sizeIBO12) {
        qDebug() << "Sectors massiv index is invalid";
    }

    /*m_vaoSector = new QOpenGLVertexArrayObject(this);
    m_vaoSector->create();
    m_vaoSector->bind();
    if (!m_vaoSector->isCreated()){
        qDebug() << "Can't use VAO";
        return;
    }

    m_vboSectors = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboSectors->create();
    m_vboSectors->bind();
    m_vboSectors->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vboSectors->allocate(vertBuf11, sizeVertBuf11 * sizeof(GLfloat));

    QOpenGLBuffer ibo3(QOpenGLBuffer::IndexBuffer);
    ibo3.create();
    ibo3.bind();
    ibo3.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    ibo3.allocate(iboBuf11, sizeIBO12 * sizeof(GLuint));

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    m_vboSectors->release();
    m_vaoSector->release();*/

    delete [] vertBuf11;
    delete [] iboBuf11;
}

void Scene::prepareFont()
{
    m_programFont = new QOpenGLShaderProgram(this);

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/ftVertexShader.vert")) {
        qDebug() << m_programFont->log();
        return;
    }

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/ftFragmentShader.frag")) {
        qDebug() << m_programFont->log();
        return;
    }
    if (!m_programFont->link()) {
        qDebug() << m_programFont->log();
        return;
    }

    m_vaoFont = new QOpenGLVertexArrayObject();
    m_vaoFont->create();
    m_vaoFont->bind();
    if (!m_vaoFont->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    customFontDriver = new ftCustom(this);
    customFontDriver->genTexels();

    const quint16 sizeFontPoint = 4;
    const quint16 nDimensionalFont = 2;
    const quint16 buffSizeInByte = sizeFontPoint * nDimensionalFont * sizeof(GLfloat);
    GLfloat fontVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0
    };
    GLfloat texelVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0
    };

    m_vboFont = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboFont->create();
    m_vboFont->bind();
    m_vboFont->allocate(fontVertex, 2 * buffSizeInByte);
    m_vboFont->write(buffSizeInByte, texelVertex, buffSizeInByte);
    m_vboFont->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    m_programFont->enableAttributeArray("vertex");
    m_programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalFont, 0);
    m_programFont->enableAttributeArray("texels");
    m_programFont->setAttributeBuffer("texels", GL_FLOAT, buffSizeInByte, nDimensionalFont, 0);

    m_vboFont->release();
    m_vaoFont->release();
}

void Scene::prepareFontArray()
{
    m_programFont = new QOpenGLShaderProgram(this);

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/ftVertexShader.vert")) {
        qDebug() << m_programFont->log();
        return;
    }

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/ftFragmentShader.frag")) {
        qDebug() << m_programFont->log();
        return;
    }
    if (!m_programFont->link()) {
        qDebug() << m_programFont->log();
        return;
    }
    //GLuint textureArray;
    //glGenTextures( 1, &textureArray );

    customFontDriver = new ftCustom(m_funcs);
    customFontDriver->genTexels();    
}

/*void Scene::prepareExtraWindow()
{
    //extraWindow size Winodw
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;

    //background of window
    sizeBackGroundBuf = pointPerRect;
    GLfloat *backGroundBuf = new GLfloat[sizeBackGroundBuf];

    float zcoord = 0;
    calcRect(OpenGLRectF(0, 0, extraWindow.width(), extraWindow.height()), backGroundBuf, 0, zcoord);

    //back ground of chart HTML color(#2d2f39)
    const quint16 legendHeightWidth = 30, marginOnEdge = 30, chartWidth = 300, chartHeight = 150;
    const QSize legendYSize(legendHeightWidth, extraWindow.height() - legendHeightWidth - marginOnEdge),
            legendXSize(extraWindow.width() - legendHeightWidth - marginOnEdge, legendHeightWidth);
    OpenGLRectF legendXRect(legendHeightWidth, 0, legendXSize.width(), legendXSize.height()),
            legendYRect(0, legendHeightWidth, legendYSize.width(), legendYSize.height());
    OpenGLRectF chartRect(legendXRect.x(),legendYRect.y(), chartWidth, chartHeight);
    sizeBackGroundChartBuf = pointPerRect;
    GLfloat *backGroundChartBuf = new GLfloat[sizeBackGroundChartBuf];

    zcoord += 0.01;
    calcRect(chartRect, backGroundChartBuf, 0, zcoord);

    //axis of chart  HTML color(#86878c)
    const quint16 axisWidth = 3;
    OpenGLRectF xAxisRect(legendXRect.x() - axisWidth,
                          legendXRect.y() + legendXRect.height() - axisWidth,
                          legendXRect.width() + axisWidth,
                          axisWidth),
            yAxisRect(legendYRect.x() + legendYRect.width() - axisWidth,
                      legendYRect.y() - axisWidth,
                      axisWidth,
                      legendYRect.height() + axisWidth);
    sizeAxisChartBuf = 2 * pointPerRect; //two rect for x and y axis
    GLfloat *axisChartBuf = new GLfloat[sizeAxisChartBuf];
    zcoord += 0.01;
    calcRect(xAxisRect, axisChartBuf, 0, zcoord);
    calcRect(yAxisRect, axisChartBuf, pointPerRect, zcoord);

    const quint16 markWidth = 4, simpleLineWidth = 1;
    const quint16 stepBetweenMarksPx = 50;
    const quint16 markOnXCount = xAxisRect.width() / stepBetweenMarksPx,
                  markOnYCount = yAxisRect.height() / stepBetweenMarksPx;

    //two rect for x and y axis for each mark and line grid plus 1 * 2 rect for zero coords
    sizeGridChartBuf = 2 * pointPerRect * (markOnXCount + markOnYCount + 1);
    GLfloat *gridChartBuf = new GLfloat[sizeGridChartBuf];

    //EmpCoeff = + axisWidth - 0.5f
    QVector<OpenGLRectF> vectorOfMark;
    OpenGLRectF zeroXMark(xAxisRect.x() - markWidth / 2 + axisWidth - 0.5f,
                          xAxisRect.y() - markWidth,
                          markWidth / 2, markWidth),
                zeroYMark(yAxisRect.x() - markWidth,
                          yAxisRect.y() - markWidth / 2 + axisWidth - 0.5f,
                          markWidth, markWidth / 2);
    vectorOfMark.push_back(zeroXMark);

    zcoord += 0.01;
    calcRect(zeroXMark, gridChartBuf, 0, zcoord);
    calcRect(zeroYMark, gridChartBuf, pointPerRect, zcoord);

    //EmpCoeff = - 0.5f
    for (quint16 index = 0, indexForPtr = 2; index < markOnXCount + markOnYCount; index++) {
        OpenGLRectF markRect, lineOnGrid;
        if (index == markOnXCount) {
            vectorOfMark.push_back(zeroYMark);
        }
        if (index < markOnXCount) {
            markRect = OpenGLRectF(xAxisRect.x() + stepBetweenMarksPx * (index + 1) - 0.5f,
                                   xAxisRect.y() - markWidth, markWidth / 2, markWidth);
            vectorOfMark.push_back(markRect);
            lineOnGrid = OpenGLRectF(xAxisRect.x() + stepBetweenMarksPx * (index + 1),
                                     xAxisRect.y() + xAxisRect.height(), simpleLineWidth, chartHeight);
        }
        else {
            markRect = OpenGLRectF(yAxisRect.x() - markWidth,
                                   yAxisRect.y() + stepBetweenMarksPx * ((index - markOnXCount) + 1) - 0.5f,
                                   markWidth, markWidth / 2);
            vectorOfMark.push_back(markRect);
            lineOnGrid = OpenGLRectF(yAxisRect.x() + yAxisRect.width(),
                                     yAxisRect.y() + stepBetweenMarksPx * ((index - markOnXCount) + 1),
                                     chartWidth, simpleLineWidth);
        }
        //calcRect(markRect, gridChartBuf + (indexForPtr++ * pointPerRect));
        //calcRect(lineOnGrid, gridChartBuf + (indexForPtr++ * pointPerRect));
        calcRect(markRect, gridChartBuf, indexForPtr * pointPerRect, zcoord);
        indexForPtr++;
        calcRect(lineOnGrid, gridChartBuf, indexForPtr * pointPerRect, zcoord);
        indexForPtr++;
    }

    m_vboChart = new QOpenGLBuffer();
    m_vboChart->create();
    m_vboChart->bind();
    m_vboChart->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboChart->allocate(backGroundBuf, (sizeBackGroundBuf + sizeBackGroundChartBuf + sizeAxisChartBuf + sizeGridChartBuf) * sizeof(GLfloat));
    m_vboChart->write(sizeBackGroundBuf * sizeof(GLfloat),
                      backGroundChartBuf,
                      sizeBackGroundChartBuf * sizeof(GLfloat));
    m_vboChart->write((sizeBackGroundBuf + sizeBackGroundChartBuf) * sizeof(GLfloat),
                      axisChartBuf,
                      sizeAxisChartBuf * sizeof(GLfloat));
    m_vboChart->write((sizeBackGroundBuf + sizeBackGroundChartBuf + sizeAxisChartBuf) * sizeof(GLfloat),
                      gridChartBuf,
                      sizeGridChartBuf * sizeof(GLfloat));

    m_vaoExtraWindow = new QOpenGLVertexArrayObject();
    m_vaoExtraWindow->create();
    m_vaoExtraWindow->bind();
    if (!m_vaoExtraWindow->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboChart->release();
    m_vaoExtraWindow->release();

    delete [] backGroundChartBuf;
    delete [] backGroundBuf;
    delete [] gridChartBuf;
    delete [] axisChartBuf;

    //text for axis
    const quint16 vertexOnTriangles = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 oneBuffSize = vertexOnTriangles * nDimensionalFont;    

    quint32 charsCount = 0;
    QVector<QString> vectorOfString;
    for (quint16 index = 0; index < markOnXCount + 1; index++ ) {
        vectorOfString.push_back(QString::number(index * stepBetweenMarksPx));
        charsCount += vectorOfString.at(index).size();
    }
    for (quint16 index = 0; index < markOnYCount + 1; index++ ) {
        vectorOfString.push_back(QString::number(index * stepBetweenMarksPx));
        charsCount += vectorOfString.at(index).size();
    }
    // DEBUG BEGIN
    //vectorOfString.push_back(QString("012345678910"));
    //charsCount = vectorOfString.at(0).size();
    // DEBUG END

    sizeTextBuf = charsCount * oneBuffSize;
    GLfloat *texelVertex = new GLfloat[charsCount * oneBuffSize];
    GLfloat *uboForText = new GLfloat[charsCount];
    GLfloat *vertexForText = new GLfloat[charsCount * oneBuffSize];

    const GLfloat scale = 0.09;
    quint32 offsetOnArray = 0, indexOfChar = 0;
    for (quint16 index = 0; index < vectorOfString.size(); index++) {
        Qt::Alignment alignment;
        if (index <= markOnXCount) {
            alignment = Qt::AlignTop;
        }
        else if (index > markOnXCount) {
            alignment = Qt::AlignRight;
        }
        customFontDriver->genText(vectorOfString.at(index),
                                  QPointF(vectorOfMark.at(index).x(),
                                  vectorOfMark.at(index).y()),
                                  alignment,
                                  scale,
                                  vertexForText,
                                  texelVertex,
                                  offsetOnArray,
                                  uboForText + indexOfChar);
        indexOfChar += vectorOfString.at(index).size();        
    }    

    if (offsetOnArray > charsCount * oneBuffSize) {
         qDebug() << "VBO and TBO Buffer overhead";
    }

    if (indexOfChar > charsCount) {
        qDebug() << "UBO Buffer overhead";
    }

    m_vboTextForAxis = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboTextForAxis->create();
    m_vboTextForAxis->bind();
    m_vboTextForAxis->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboTextForAxis->allocate(texelVertex, 2 * (oneBuffSize * charsCount) * sizeof(GLfloat));
    m_vboTextForAxis->write((oneBuffSize * charsCount) * sizeof(GLfloat), vertexForText, (oneBuffSize * charsCount) * sizeof(GLfloat));

    m_vaoTextForAxis = new QOpenGLVertexArrayObject();
    m_vaoTextForAxis->create();
    m_vaoTextForAxis->bind();
    if (!m_vaoTextForAxis->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programFont->enableAttributeArray("texels");
    m_programFont->setAttributeBuffer("texels", GL_FLOAT, 0, nDimensionalFont, 0);
    m_programFont->enableAttributeArray("vertex");
    m_programFont->setAttributeBuffer("vertex", GL_FLOAT, (oneBuffSize * charsCount) * sizeof(GLfloat), nDimensionalFont, 0);

    m_vboTextForAxis->release();
    m_vaoTextForAxis->release();

    int maxVUB, maxGUB, maxFUB, maxUBS, UBoffset;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVUB);
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &maxGUB);
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &maxFUB);
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUBS);
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UBoffset);

    glGenBuffers(1, &uboIndex);
    glBindBuffer(GL_UNIFORM_BUFFER, uboIndex);
    glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(GLfloat) * 250, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    uniformBlockIndex = glGetUniformBlockIndex(m_programFont->programId(), "myblock");
    glUniformBlockBinding(m_programFont->programId(), uniformBlockIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboIndex);
    GLfloat* cam_ubo_ptr = (GLfloat*)glMapBufferRange (
      GL_UNIFORM_BUFFER,
      100 * sizeof(GLfloat),
      sizeof(GLfloat) * charsCount,
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );

    memcpy(cam_ubo_ptr, uboForText, sizeof(GLfloat) * charsCount);
    glUnmapBuffer(GL_UNIFORM_BUFFER);
    cam_ubo_ptr = nullptr;

    delete [] uboForText;
    delete [] vertexForText;
    delete [] texelVertex;

    //init buttons
    quint32 charsCountButtons = 0;
    QVector<QString> vectorOfStringButtons;
    vectorOfStringButtons.push_back("h");
    vectorOfStringButtons.push_back("ДСП");
    vectorOfStringButtons.push_back("СЦ");
    const GLfloat scaleTextButt = 0.13;
    QVector<QSizeF> buttonsSize;
    for (quint16 index = 0; index < vectorOfStringButtons.size(); index++) {
        buttonsSize.push_back(customFontDriver->genRectForText(vectorOfStringButtons.at(index),
                                                               scaleTextButt));
        charsCountButtons += vectorOfStringButtons.at(index).size();
    }
    QSizeF buttonSize(0, 0);
    for (auto &item : buttonsSize) {
        if (buttonSize.width() < item.width()) {
            buttonSize.rwidth() = item.width();
        }
        if (buttonSize.height() < item.height()) {
            buttonSize.rheight() = item.height();
        }
    }

    quint16 marginOnTopLeft = 5;
    buttonSize.rwidth() += 2 * marginOnTopLeft;
    buttonSize.rheight() += 2 * marginOnTopLeft;
    buttonAltitudeRect = OpenGLRectF(legendHeightWidth,
                                     extraWindow.height() - buttonSize.height() - marginOnTopLeft,
                                     buttonSize.width(),
                                     buttonSize.height());
    buttonDSPRect = OpenGLRectF(buttonAltitudeRect.x() + buttonAltitudeRect.width() + marginOnTopLeft,
                                extraWindow.height() - buttonSize.height() - marginOnTopLeft,
                                buttonSize.width(),
                                buttonSize.height());
    buttonNTRect = OpenGLRectF(buttonDSPRect.x() + buttonDSPRect.width() + marginOnTopLeft,
                               extraWindow.height() - buttonSize.height() - marginOnTopLeft,
                               buttonSize.width(),
                               buttonSize.height());
//    buttonAltitudeQRect = QRect(m_viewportSize.width() + buttonAltitudeRect.x(),
//                                extraWindow.height() - buttonAltitudeRect.y() - buttonAltitudeRect.height(),
//                                buttonAltitudeRect.width(),
//                                buttonAltitudeRect.height());
//    buttonDSPQRect = QRect(m_viewportSize.width() + buttonDSPRect.x(),
//                           extraWindow.height() - buttonDSPRect.y() - buttonDSPRect.height(),
//                           buttonDSPRect.width(),
//                           buttonDSPRect.height());
//    buttonNTQRect = QRect(m_viewportSize.width() + buttonNTRect.x(),
//                          extraWindow.height() - buttonNTRect.y() - buttonNTRect.height(),
//                          buttonNTRect.width(),
//                          buttonNTRect.height());
    hoveredItem = -1, selectedItem = 0;
    OpenGLRectF buttonAltitudeTextRect(buttonAltitudeRect.x() + marginOnTopLeft,
                                       buttonAltitudeRect.y() + marginOnTopLeft,
                                       buttonAltitudeRect.width() - 2 * marginOnTopLeft,
                                       buttonAltitudeRect.height() - 2 * marginOnTopLeft);
    OpenGLRectF buttonDSPTextRect(buttonDSPRect.x() + marginOnTopLeft,
                                  buttonDSPRect.y() + marginOnTopLeft,
                                  buttonDSPRect.width() - 2 * marginOnTopLeft,
                                  buttonDSPRect.height() - 2 * marginOnTopLeft);
    OpenGLRectF buttonNTTextRect(buttonNTRect.x() + marginOnTopLeft,
                                 buttonNTRect.y() + marginOnTopLeft,
                                 buttonNTRect.width() - 2 * marginOnTopLeft,
                                 buttonNTRect.height() - 2 * marginOnTopLeft);

    sizeButtonsBuff = 3 * pointPerRect; //three rect for three buttons
    GLfloat *buttonsRectBuf = new GLfloat[sizeButtonsBuff];
    zcoord += 0.01;
    calcRect(buttonAltitudeRect, buttonsRectBuf, 0, zcoord);
    calcRect(buttonDSPRect, buttonsRectBuf, pointPerRect, zcoord);
    calcRect(buttonNTRect, buttonsRectBuf, 2 * pointPerRect, zcoord);

    m_vboButtons = new QOpenGLBuffer();
    m_vboButtons->create();
    m_vboButtons->bind();
    m_vboButtons->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboButtons->allocate(buttonsRectBuf, sizeButtonsBuff * sizeof(GLfloat));

    m_vaoButtons = new QOpenGLVertexArrayObject();
    m_vaoButtons->create();
    m_vaoButtons->bind();
    if (!m_vaoButtons->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programButton->enableAttributeArray("posAttr");
    m_programButton->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboButtons->release();
    m_vaoButtons->release();

    delete [] buttonsRectBuf;

    sizeTextForButtons = charsCountButtons * oneBuffSize;
    GLfloat *texelVertexButt = new GLfloat[charsCountButtons * oneBuffSize];
    GLfloat *uboForTextButt = new GLfloat[charsCountButtons];
    GLfloat *vertexForTextButt = new GLfloat[charsCountButtons * oneBuffSize];

    QVector<OpenGLRectF> vectorOfRect;
    vectorOfRect.push_back(buttonAltitudeTextRect);
    vectorOfRect.push_back(buttonDSPTextRect);
    vectorOfRect.push_back(buttonNTTextRect);
    quint32 offsetOnArrayButt = 0, indexOfCharButt = 0;
    for (quint16 index = 0; index < vectorOfStringButtons.size(); index++) {
        customFontDriver->genTextWithRect(vectorOfStringButtons.at(index),
                                          vectorOfRect.at(index),
                                          scaleTextButt,
                                          vertexForTextButt,
                                          texelVertexButt,
                                          offsetOnArrayButt,
                                          uboForTextButt + indexOfCharButt);
        indexOfCharButt += vectorOfStringButtons.at(index).size();
    }

    if (offsetOnArrayButt > charsCountButtons * oneBuffSize) {
         qDebug() << "VBO2 and TBO2 Buffer overhead";
    }

    if (indexOfCharButt > charsCountButtons) {
        qDebug() << "UBO2 Buffer overhead";
    }

    m_vboButtonsText = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboButtonsText->create();
    m_vboButtonsText->bind();
    m_vboButtonsText->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboButtonsText->allocate(texelVertexButt, 2 * (oneBuffSize * charsCountButtons) * sizeof(GLfloat));
    m_vboButtonsText->write((oneBuffSize * charsCountButtons) * sizeof(GLfloat), vertexForTextButt, (oneBuffSize * charsCountButtons) * sizeof(GLfloat));

    m_vaoTextForButtons = new QOpenGLVertexArrayObject();
    m_vaoTextForButtons->create();
    m_vaoTextForButtons->bind();
    if (!m_vaoTextForButtons->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programFont->enableAttributeArray("texels");
    m_programFont->setAttributeBuffer("texels", GL_FLOAT, 0, nDimensionalFont, 0);
    m_programFont->enableAttributeArray("vertex");
    m_programFont->setAttributeBuffer("vertex", GL_FLOAT, (oneBuffSize * charsCountButtons) * sizeof(GLfloat), nDimensionalFont, 0);

    m_vboButtonsText->release();
    m_vaoTextForButtons->release();

    //glUniformBlockBinding(m_programFont->programId(), uniformBlockIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboIndex);
    GLfloat* cam_ubo_ptr2 = (GLfloat*)glMapBufferRange (
      GL_UNIFORM_BUFFER,
      0,
      sizeof(GLfloat) * charsCountButtons,
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );
    memcpy(cam_ubo_ptr2, uboForTextButt, sizeof(GLfloat) * charsCountButtons);
    glUnmapBuffer(GL_UNIFORM_BUFFER);
    cam_ubo_ptr2 = nullptr;

    delete [] uboForTextButt;
    delete [] vertexForTextButt;
    delete [] texelVertexButt;

//    QPointF target(45, 50);
//    quint16 targetWidth = 10;
//    quint16 margin = 5;
//    OpenGLRectF targetRectOnX(legendXRect.x() - targetWidth / 2,
//                              legendXRect.y() + margin + axisWidth,
//                              targetWidth,
//                              legendXRect.height() - margin * 2 - axisWidth);
//    OpenGLRectF rectOfTargetOnX(targetRectOnX);
//    rectOfTargetOnX.moveRight(target.x());
//    OpenGLRectF targetRectOnY(legendYRect.x() + margin + axisWidth,
//                              legendYRect.y() - targetWidth / 2,
//                              legendYRect.width() - margin * 2 - axisWidth,
//                              targetWidth);
//    OpenGLRectF rectOfTargetOnY(targetRectOnY);
//    rectOfTargetOnY.moveTop(target.y());

//    const quint16 rectOfTargetSize = 2 * pointPerRect; //two rect for x and y axis
//    GLfloat *rectOfTargetBuf = new GLfloat[rectOfTargetSize];
//    zcoord += 0.2;
//    calcRect(rectOfTargetOnX, rectOfTargetBuf, 0, zcoord);
//    calcRect(rectOfTargetOnY, rectOfTargetBuf, pointPerRect, zcoord);

//    m_vboTargetRect = new QOpenGLBuffer();
//    m_vboTargetRect->create();
//    m_vboTargetRect->bind();
//    m_vboTargetRect->setUsagePattern(QOpenGLBuffer::DynamicDraw);
//    m_vboTargetRect->allocate(rectOfTargetBuf, rectOfTargetSize * sizeof(GLfloat));

//    m_vaoTargetRect = new QOpenGLVertexArrayObject();
//    m_vaoTargetRect->create();
//    m_vaoTargetRect->bind();
//    if (!m_vaoTargetRect->isCreated()){
//        qDebug() << "Can't use VAO for font";
//        return;
//    }

//    m_programGrid->enableAttributeArray("posAttr");
//    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

//    m_vboTargetRect->release();
//    m_vaoTargetRect->release();

//    delete [] rectOfTargetBuf;
}*/

void Scene::calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord)
{
    //int counter = 0;
    //(left;bottom) - (right;bottom) - (left;top) CCW
    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    //(right;bottom) - (right;top) - (left;top)
    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    *(array + counter) = zcoord;
    counter++;
    //qDebug() << counter;
}

/*void Scene::renderExtraWindow()
{
    float zcoord = 0;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programGrid->bind();
    QMatrix4x4 mvp = m_cameraExtraWindow->projectionMatrix() * m_cameraExtraWindow->viewMatrix() * model;
    m_programGrid->setUniformValue("mvp", mvp);
    m_programGrid->setUniformValue("objectColor", QVector4D(0.05f, 0.05f, 0.05f, 1.0f));
    m_programGrid->setUniformValue("isColorDependenceOnY", false);

    m_vaoExtraWindow->bind();

    glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_programGrid->setUniformValue("objectColor", QVector4D(0.12f, 0.12f, 0.16f, 1.0f));

    glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3, sizeBackGroundChartBuf / 3);

    m_programGrid->setUniformValue("objectColor", QVector4D(0.53f, 0.53f, 0.55f, 0.7f));

    glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3 + sizeBackGroundChartBuf / 3, (sizeAxisChartBuf + sizeGridChartBuf) / 3);

    m_vaoExtraWindow->release();
    m_programGrid->release();

    //int level = 0;
    int uboOffset = 100;
    zcoord += 0.04;
    m_programFont->bind();
    m_programFont->setUniformValue("proj", m_cameraExtraWindow->projectionMatrix());
    m_programFont->setUniformValue("view", m_cameraExtraWindow->viewMatrix());
    m_programFont->setUniformValue("model", model);
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboOffset);
    m_programFont->setUniformValue("textureColor", QVector3D(0.21f,0.69f,0.33f));

    m_vaoTextForAxis->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, customFontDriver->getTextureArray());        

    glDrawArrays(GL_TRIANGLES, 0, sizeTextBuf / 2);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForAxis->release();
    m_programFont->release();

    m_programButton->bind();
    m_vaoButtons->bind();
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("selectedItem", selectedItem);
    m_programButton->setUniformValue("hoveredItem", hoveredItem);
    m_programButton->setUniformValue("ourColor", QVector4D(0.1f, 0.1f, 0.1f, 1.0f));

    glDrawArrays(GL_TRIANGLES, 0, sizeButtonsBuff / 3);

    m_vaoButtons->release();
    m_programButton->release();

    zcoord += 0.04;
    uboOffset = 0;
    m_programFont->bind();
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboOffset);

    m_vaoTextForButtons->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, customFontDriver->getTextureArray());

    glDrawArrays(GL_TRIANGLES, 0, sizeTextForButtons / 2);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForButtons->release();
    m_programFont->release();
}*/



void Scene::prepareDSP()
{
    const quint32 nDimensional = 3;
    const quint8 sideCount = 3,
            //squareCount = 1,
            squarePointNumber = 4;
    const quint32 sizeVertBuf5 = 8 * nDimensional;//nDimensional * sideCount * squareCount * squarePointNumber;
    const int side = 200;
    GLfloat vertBuf5[sizeVertBuf5] = {
        0, 0, 0,
        side, 0, 0,
        side, side, 0,
        0, side, 0,
        0, side, -side,
        0, 0, side,
        side, 0, -side,
        side, 0, 0,
    };

    const quint16 distBound = 300,
            speedBound = 150,
            ampBound = 200;

    const quint16 sideOfPrimitive = 25;
    const quint16 distFragment = distBound / sideOfPrimitive + 1,
            speedFragment = speedBound / sideOfPrimitive + 1,
            ampFragment = ampBound / sideOfPrimitive + 1;
    const quint16 offsetOnAxis1 = 5.f;
    //const quint32 sizeVertBuf6 = nDimensional * 4 * (distFragment + speedFragment + ampFragment);
    const quint32 sizeVertBuf6 = nDimensional * 2 * (distFragment + speedFragment);
    GLfloat *vertBuf6 = new GLfloat[sizeVertBuf6];
    quint16 buf6Pos = 0;

    //along y-axis
    for (int i = 0; i < speedFragment; ++i) { // on YX-planes
        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = -offsetOnAxis1;//0
        vertBuf6[buf6Pos++] = 0;

        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = distBound;
        vertBuf6[buf6Pos++] = 0;
    }

    //along x-axis
    for (int i = 0; i < distFragment; ++i) { // on XY-planes
        vertBuf6[buf6Pos++] = -offsetOnAxis1;//0
        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = 0;

        vertBuf6[buf6Pos++] = speedBound;
        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
        vertBuf6[buf6Pos++] = 0;
    }

    //along z-axis
    //for (int i = 0; i < speedFragment; ++i) { // on ZX-planes
    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = 0;

    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = -distBound;
    //    }
    //    for (int i = 0; i < ampFragment; ++i) { // on ZY-planes
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = 0;

    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = -distBound;
    //    }

    //    //along y-axis
    //    for (int i = 0; i < speedFragment; ++i) { // on YX-planes
    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = -distBound;

    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = ampBound;
    //        vertBuf6[buf6Pos++] = -distBound;
    //    }
    //    for (int i = 0; i < distFragment; ++i) { // on YZ-planes
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;

    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = ampBound;
    //        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;
    //    }
    //    //along x-axis
    //    for (int i = 0; i < ampFragment; ++i) { // on XY-planes
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = -distBound;

    //        vertBuf6[buf6Pos++] = speedBound;
    //        vertBuf6[buf6Pos++] = i * sideOfPrimitive;
    //        vertBuf6[buf6Pos++] = -distBound;
    //    }
    //    for (int i = 0; i < distFragment; ++i) { // on XZ-planes
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;

    //        vertBuf6[buf6Pos++] = speedBound;
    //        vertBuf6[buf6Pos++] = 0;
    //        vertBuf6[buf6Pos++] = -i * sideOfPrimitive;
    //    }

    const quint32 sizeVertBuf7 = nDimensional * distBound * speedBound;
    GLfloat *vertBuf7 = new GLfloat[sizeVertBuf7];
    quint32 vbuf7Pos = 0;
    for (quint16 i = 0; i < distBound; i++) {
        for (quint16 j = 0; j < speedBound; j++) {
            const quint16 a = 30, b = 80; //[a,b]
            vertBuf7[vbuf7Pos++] = j;
            vertBuf7[vbuf7Pos++] = i;
            vertBuf7[vbuf7Pos++] = static_cast<double>(qrand()) * (b-a) / RAND_MAX + a;
        }
    }
    if (sizeVertBuf7 != vbuf7Pos) {
        qDebug() << "Have same problm with vertBuf7";
    }

    const quint16 primitivesPerSquare = 8,
            pointPerPrimitive = 3;
    sizeIndexBuf1 = primitivesPerSquare * pointPerPrimitive * (speedBound / 2 - 1) * (distBound / 2 - 1);
    GLuint *indexBuf1 = new GLuint[sizeIndexBuf1];
    quint32 ibuf1Pos = 0;
    for (quint16 i = 2; i < distBound; i+=2) {
        for (quint16 j = 2; j < speedBound; j+=2) {
            quint16 tj = j, ti = i;
            for (quint16 k = 0; k < primitivesPerSquare; k++) {
                int pos = (i - 1) * speedBound + (j - 1);
                indexBuf1[ibuf1Pos++] = pos;
                if (k == 0 || k == 1) { //x--
                    pos = ti * speedBound + tj--;
                }
                else if (k == 2 || k == 3) { //y--
                    pos = ti-- * speedBound + tj;
                }
                else if (k == 4 || k == 5) { //x++
                    pos = ti * speedBound + tj++;
                }
                else if (k == 6 || k == 7) { //y++
                    pos = ti++ * speedBound + tj;
                }
                indexBuf1[ibuf1Pos++] = pos;
                pos = ti * speedBound + tj;
                indexBuf1[ibuf1Pos++] = pos;
            }
        }
    }
    if (sizeIndexBuf1 != ibuf1Pos) {
        qDebug() << "Have same problm with indexBuf1";
    }

    const quint8 fanNumber = 4;
    const quint16 objectNumber = distFragment + speedFragment;
    const quint32 sizeVertBuf8 = nDimensional * objectNumber * (fanNumber + 1);
    GLfloat *vertBuf8 = new GLfloat[sizeVertBuf8];
    quint32 vbuf8Pos = 0;
    const quint16 offsetOnAxis = offsetOnAxis1 + 2,
            aObject = 10,
            bObject = 5;
    for(quint16 i = 0; i < distFragment; i++) {
        for (quint16 j = 0; j < fanNumber + 1; j++) {
            if (j == 0) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - aObject;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive;
            }
            else if (j == 1) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + bObject;
            }
            else if (j == 2) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * aObject;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + bObject;
            }
            else if (j == 3) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * aObject;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - bObject;
            }
            else if (j == 4) {
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - bObject;
            }
            vertBuf8[vbuf8Pos++] = 0;
        }
    }
    for(quint16 i = 0; i < speedFragment; i++) {
        for (quint16 j = 0; j < fanNumber + 1; j++) {
            if (j == 0) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - bObject;
            }
            else if (j == 1) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
            }
            else if (j == 2) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis;
            }
            else if (j == 3) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive - aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * bObject;
            }
            else if (j == 4) {
                vertBuf8[vbuf8Pos++] = i * sideOfPrimitive + aObject;
                vertBuf8[vbuf8Pos++] = -offsetOnAxis - 2 * bObject;
            }
            vertBuf8[vbuf8Pos++] = 0;
        }
    }

    const quint8 trianglePoint = 3;
    sizeIndexBuf2 = objectNumber * fanNumber * trianglePoint;
    GLuint *indexBuf2 = new GLuint[sizeIndexBuf2];
    quint32 ibuf2Pos = 0;
    for (quint16 i = 0; i < objectNumber; i++) {
        quint32 pos = i * (fanNumber + 1);
        for (quint16 j = 0; j < fanNumber; j++) {
            indexBuf2[ibuf2Pos++] = pos;
            indexBuf2[ibuf2Pos++] = pos + j + 1;
            indexBuf2[ibuf2Pos++] = (j == 3) ? pos + 1 : pos + j + 2;
        }
    }
    if (sizeIndexBuf2 != ibuf2Pos) {
        qDebug() << "Have same problm with indexBuf2";
    }

    m_vboDSP = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboDSP->create();
    m_vboDSP->bind();
    m_vboDSP->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboDSP->allocate(vertBuf5, (sizeVertBuf5 + sizeVertBuf6) * sizeof(GLfloat));
    m_vboDSP->write(sizeVertBuf5 * sizeof(GLfloat), vertBuf6, sizeVertBuf6 * sizeof(GLfloat));

    /*m_vao->bind();
    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);
    m_vboDSP->release();
    m_vao->release();*/

    delete [] vertBuf6;
    delete [] indexBuf1;
    delete [] vertBuf7;
    delete [] vertBuf8;
    delete [] indexBuf2;
}

void Scene::prepareShaders()
{

}

void Scene::prepareTextures()
{

}

void Scene::prepareVertexBuffers( QSize heightMapSize )
{

}

void Scene::prepareVertexArrayObject()
{

}



SectorsGLData::SectorsGLData(QOpenGLFunctions_3_3_Core *func,
                             const Camera *m_camera,
                             const SceneOptions *scOption,
                             QOpenGLShaderProgram *prog, float _depth,
                             QObject *parent) : QObject(parent),
      glFunc(func), camera_ptr(m_camera), sceneOptions(scOption), programSector(prog), depth(_depth),
      lastParameters(), segmentation(60), sectorsCount(maxNumberOfSectors), sectorsState(sectorsCount, ItemState::Empty),
      vao(new QOpenGLVertexArrayObject()), vbo(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
      ibo(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)), gpuMemoryReserved(0),
      sectorColor(QColor::fromRgbF(0.28f, 0.77f, 0.15f, 0.15f)),
      selectedColor(QColor::fromRgbF(0.9f, 0.77f, 0.15f, 0.3f)),
      blinkingColor(QColor::fromRgbF(0.68f, 0.07f, 0.07f, 0.6f)),
      selectedSector(255),
      sectorColors(sectorsCount, sectorColor)
{
    //calc size of one vertex buffer
    vertexPerSector = (segmentation + 1) * 2 * 2;
    nDimensional = 3;
    coordinateValuePerSector = vertexPerSector * nDimensional;

    //calc byte size of all vertex buffer
    const quint32 countCoordinateValueOfAllVBO = coordinateValuePerSector * sectorsCount;
    const quint32 byteSizeOfAllVBO = countCoordinateValueOfAllVBO * sizeof(GLfloat);

    //calc size of one index buffer
    //const quint32 indexPerTopBottomEdges = 2 * (verticesNumber * 3);
    const quint32 indexPerTopBottomEdges = 2 * (segmentation * 2 * 3);
    const quint32 indexPerLeftRightEdges = 2 * (2 * 3);
    const quint32 indexPerFrontBackEdges = indexPerTopBottomEdges;
    indexPerSector = indexPerTopBottomEdges + indexPerLeftRightEdges + indexPerFrontBackEdges;

    //calc byte size of all index buffer
    const quint32 countIndexOfAllIBO = indexPerSector * sectorsCount;
    const quint32 byteSizeOfAllIBO = countIndexOfAllIBO * sizeof(GLushort);

    gpuMemoryReserved = byteSizeOfAllVBO + byteSizeOfAllIBO;

    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use SECTORS VAO";
        return;
    }

    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo->allocate(byteSizeOfAllVBO);

    ibo->create();
    ibo->bind();
    ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo->allocate(byteSizeOfAllIBO);

    calcIBO();

    programSector->enableAttributeArray("posAttr");
    programSector->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();
}

void SectorsGLData::calcDrawVector(QVector<QPair<GLushort, GLushort> > &vector)
{
    vector.clear();
    QPair<GLushort, GLushort> sizeOffset(qMakePair(0,0));
    for (quint32 index = 0; index != sectorsCount; index++) {
        if (sectorsState.at(index) == ItemState::Active && index != selectedSector) {
            sizeOffset.first += indexPerSector;
        }
        else {
            if (sizeOffset.first != 0) {
                vector.append(sizeOffset);
                sizeOffset.second += (sizeOffset.first + indexPerSector) * sizeof(GLushort);
                sizeOffset.first = 0;
            }
            else {
                sizeOffset.second += indexPerSector * sizeof(GLushort);
            }
        }
    }
}

void SectorsGLData::render()
{
    programSector->bind();
    QMatrix4x4 m_modelMatrix;
    m_modelMatrix.setToIdentity();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programSector->setUniformValue("mvp", mvp);
    /*programSector->setUniformValue("objectColor", sectorColor);

    QVector<QPair<GLushort, GLushort> > vector;
    calcDrawVector(vector);
    vao->bind();
    for (auto &item : vector)
        glFunc->glDrawElements(GL_TRIANGLES, item.first, GL_UNSIGNED_SHORT, (void *)item.second);

    if (selectedSector != 255) {
        programSector->setUniformValue("objectColor", selectedColor);
        glFunc->glDrawElements(GL_TRIANGLES, indexPerSector, GL_UNSIGNED_SHORT, (void *)(selectedSector * indexPerSector * sizeof(GLushort)));
    }
    vao->release();*/

    vao->bind();
    for (quint8 index = 0; index < sectorsCount; index++) {
        if (sectorsState.at(index) == ItemState::Active || index == selectedSector) {
            programSector->setUniformValue("objectColor", sectorColors.at(index));
            glFunc->glDrawElements(GL_TRIANGLES, indexPerSector, GL_UNSIGNED_SHORT, (void *)(index * indexPerSector * sizeof(GLushort)));
        }
    }
    vao->release();

    programSector->release();
}

void SectorsGLData::presetSectorSlot(const quint8 index, SharedSectorParameters sharedSector)
{
    SectorParameters sector = *sharedSector;

    QVector<QVector3D> verticesUg1, verticesUg2, verticesUg;

    double az1 = sector.azMin, az2 = sector.azMax;
    if (az1 > az2) {
        az2 += 360.;
    }

    az1 = (90 - az1) * degToRad;
    az2 = (90 - az2) * degToRad;

    double r = sector.distMin, R = sector.distMax,
           //az1 = (90 - sector.azMin) * degToRad, az2 = (90 - sector.azMax) * degToRad,
           ug1 = (90 - sector.ugmMin) * degToRad, ug2 = (90 - sector.ugmMax) * degToRad;

    double dAz = (az2 - az1) / (double)segmentation;
    float zcoord = depth;
    for (quint32 i = 0; i < segmentation + 1; i++) {
        verticesUg1 << QVector3D(r * cos(az1 + i * dAz) * sin(ug1), r * sin(az1 + i * dAz) * sin(ug1), zcoord)//r * cos(ug1))
                    << QVector3D(R * cos(az1 + i * dAz) * sin(ug1), R * sin(az1 + i * dAz) * sin(ug1), zcoord);//R * cos(ug1));
        verticesUg2 << QVector3D(r * cos(az1 + i * dAz) * sin(ug2), r * sin(az1 + i * dAz) * sin(ug2), zcoord)//r * cos(ug2))
                    << QVector3D(R * cos(az1 + i * dAz) * sin(ug2), R * sin(az1 + i * dAz) * sin(ug2), zcoord);//R * cos(ug2));
    }
    verticesUg << verticesUg1 << verticesUg2;

    if (vertexPerSector != verticesUg.size()) {
        qDebug() << QString("Calc Vertex Buffer for Sector №%1 is wrong!!!").arg(index);
    }

    GLfloat *vertBuf = new GLfloat[coordinateValuePerSector];
    quint32 indexBuf = 0;
    for (quint32 i = 0; i != vertexPerSector; i++) {
        vertBuf[indexBuf++] = verticesUg.at(i).x();
        vertBuf[indexBuf++] = verticesUg.at(i).y();
        vertBuf[indexBuf++] = verticesUg.at(i).z();
    }

    vbo->bind();
    vbo->write(coordinateValuePerSector * index * sizeof(GLfloat), vertBuf, coordinateValuePerSector * sizeof(GLfloat));
    vbo->release();

    delete [] vertBuf;
}

void SectorsGLData::excludeSectorSlot(const quint8 index)
{
    sectorsState.replace(index, ItemState::Excluded);

    if (index == selectedSector) {
        sectorColors[index] = selectedColor;
    }
}

void SectorsGLData::addSectorSlot(const quint8 index, SharedSectorParameters sharedSector)
{
    sectorsState.replace(index, ItemState::Active);

    SectorParameters sector = *sharedSector;

    QVector<QVector3D> verticesUg1, verticesUg2, verticesUg;

    double az1 = sector.azMin, az2 = sector.azMax;
    if (az1 > az2) {
        az2 += 360.;
    }

    az1 = (90 - az1) * degToRad;
    az2 = (90 - az2) * degToRad;

    double r = sector.distMin, R = sector.distMax,
           //az1 = (90 - sector.azMin) * degToRad, az2 = (90 - sector.azMax) * degToRad,
           ug1 = (90 - sector.ugmMin) * degToRad, ug2 = (90 - sector.ugmMax) * degToRad;

    double dAz = (az2 - az1) / (double)segmentation;
    float zcoord = depth;
    for (quint32 i = 0; i < segmentation + 1; i++) {
        verticesUg1 << QVector3D(r * cos(az1 + i * dAz) * sin(ug1), r * sin(az1 + i * dAz) * sin(ug1), zcoord)//r * cos(ug1))
                    << QVector3D(R * cos(az1 + i * dAz) * sin(ug1), R * sin(az1 + i * dAz) * sin(ug1), zcoord);//R * cos(ug1));
        verticesUg2 << QVector3D(r * cos(az1 + i * dAz) * sin(ug2), r * sin(az1 + i * dAz) * sin(ug2), zcoord)//r * cos(ug2))
                    << QVector3D(R * cos(az1 + i * dAz) * sin(ug2), R * sin(az1 + i * dAz) * sin(ug2), zcoord);//R * cos(ug2));
    }
    verticesUg << verticesUg1 << verticesUg2;

    if (vertexPerSector != verticesUg.size()) {
        qDebug() << QString("Calc Vertex Buffer for Sector №%1 is wrong!!!").arg(index);
    }

    GLfloat *vertBuf = new GLfloat[coordinateValuePerSector];
    quint32 indexBuf = 0;
    for (quint32 i = 0; i != vertexPerSector; i++) {
        vertBuf[indexBuf++] = verticesUg.at(i).x();
        vertBuf[indexBuf++] = verticesUg.at(i).y();
        vertBuf[indexBuf++] = verticesUg.at(i).z();
    }

    vbo->bind();
    vbo->write(coordinateValuePerSector * index * sizeof(GLfloat), vertBuf, coordinateValuePerSector * sizeof(GLfloat));
    vbo->release();

    delete [] vertBuf;
}

void SectorsGLData::deleteSectorSlot(const quint8 index)
{
    sectorsState.replace(index, ItemState::Empty);
    selectedSector = 255;
}

void SectorsGLData::sectorInFocus(const quint8 index)
{
    if(selectedSector != 255) {
        sectorColors[selectedSector] = sectorColor;
    }
    selectedSector = index;
    sectorColors[selectedSector] = selectedColor;

}

void SectorsGLData::sectorOutFocus()
{
    if(selectedSector != 255)
        sectorColors[selectedSector] = sectorColor;
    selectedSector = 255;    
}

/*void SectorsGLData::bindVAO()
{
    vao->bind();
    //vbo->bind();
}

void SectorsGLData::releaseVAO()
{
    //vbo->release();
    vao->release();
}*/

void SectorsGLData::setColor(const QColor color)
{
    sectorColor = color;

    SectorColors tempSectorColors(sectorsCount, sectorColor);
    sectorColors.swap(tempSectorColors);

    if (selectedSector != 255) {
        sectorColors[selectedSector] = selectedColor;
    }
}

void SectorsGLData::setBlinkingActions(const quint8 index, ActionsWithBlinkingSector action)
{
    if (sectorsState.at(index) == ItemState::Active) {
        if (action == ActionsWithBlinkingSector::Reverse) {
            if (sectorColors.at(index) == sectorColor) {
                sectorColors[index] = blinkingColor;
            }
            else {
                sectorColors[index] = sectorColor;
            }
        }
        else if (action == ActionsWithBlinkingSector::ResetValue) {
            sectorColors[index] = sectorColor;
        }
    }
}

void SectorsGLData::calcIBO()
{
    const quint32 sizeVertBuf = coordinateValuePerSector * sectorsCount;
    GLfloat *vertBuf = new GLfloat[sizeVertBuf];
    quint32 indexBuf = 0;
    for (quint32 i = 0; i != sizeVertBuf; i++) {
        vertBuf[indexBuf++] = 0;
    }
    vbo->write(0, vertBuf, sizeVertBuf * sizeof(GLfloat));

    delete [] vertBuf;

    QVector<quint32> iboSectors;
    for (quint32 index = 0; index < sectorsCount; index++) {

        const quint32   begin = vertexPerSector * index,
                end = vertexPerSector * (index + 1) - 1;
        const quint32   beginUg1Array = begin,
                endUg1Array = begin + vertexPerSector / 2 - 1;
        const quint32   beginUg2Array = endUg1Array + 1,
                endUg2Array = end;
        const quint32   verticesNumber = vertexPerSector / 2;

        enum Direction {
            CW,
            CCW
        };
        Direction direction = CCW;
        quint16 p1 = 0, p2 = 0, p3 = 0;
        quint32 firstNumber;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CW;
                firstNumber = beginUg1Array;
            }
            else {
                direction = Direction::CCW;
                firstNumber = beginUg2Array;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = 0; index < verticesNumber - 2; index += 2) {
                p1 = firstNumber + index;
                quint16 &refP2 = direction == Direction::CCW ? p2 : p3,
                        &refP3 = direction == Direction::CCW ? p3 : p2;

                refP2 = firstNumber + index + 2;
                refP3 = firstNumber + index + 1;
                iboSectors << p1 << p2 << p3;
                p1++, refP3 += 2;
                iboSectors << p1 << p2 << p3;
            }
        }

        // Правая грань, Левая грань
        iboSectors << beginUg1Array + 1 << beginUg2Array << beginUg2Array + 1
                   << beginUg1Array + 1 << beginUg1Array << beginUg2Array;
        iboSectors << endUg1Array - 1 << endUg2Array << endUg2Array - 1
                   << endUg1Array - 1 << endUg1Array << endUg2Array;


        // Лицевая грань, Задняя грань
        p1 = 0, p2 = 0, p3 = 0;
        for (quint16 i = 0; i < 2; i++) {
            if (i == 0) {
                direction = Direction::CCW;
                firstNumber = beginUg1Array;
            }
            else {
                direction = Direction::CW;
                firstNumber = beginUg1Array;
            }
            // 1 = Верхняя грань, 0 = Нижняя грань,
            for (quint16 index = i; index < verticesNumber + i - 2; index += 2) {
                p1 = firstNumber + index;
                quint16 &refP2 = direction == Direction::CCW ? p2 : p3,
                        &refP3 = direction == Direction::CCW ? p3 : p2;

                refP2 = firstNumber + index + 2;
                refP3 = beginUg2Array + index;
                iboSectors << p1 << p2 << p3;
                p1 += 2, refP2 = beginUg2Array + index + 2;
                iboSectors << p1 << p2 << p3;
            }
        }
    }

    GLushort *iboBuf = new GLushort[iboSectors.size()];
    for (auto i = 0; i != iboSectors.size(); i++) {
        iboBuf[i] = iboSectors.at(i);
    }

    ibo->write(0, iboBuf, iboSectors.size() * sizeof(GLushort));

    delete [] iboBuf;
}

void SectorsGLData::deg360TransitionCheck(float &ang)
{
    if (ang > 360) {
        ang -= 360;
    }
    else if (ang < 0) {
        ang += 360;
    }
}

ExtraWindow::ExtraWindow(QOpenGLFunctions_3_3_Core *func, QOpenGLShaderProgram *progFont, QOpenGLShaderProgram *progButton, ftCustom *_fontDriver, QObject *parent) :
    QObject(parent),
    glFunc(func),
    m_programFont(progFont),
    m_programButton(progButton),
    fontDriver(_fontDriver),
    m_camera(new Camera(this)),
    renderType(RenderType::HRender)
{
    m_programDSP = new QOpenGLShaderProgram(this);

    if (!m_programDSP->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/dspVert.vert")) {
        qDebug() << m_programDSP->log();
        return;
    }

    /*if (!m_programDSP->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/dspGeom.gm")) {
        qDebug() << m_programDSP->log();
        return;
    }*/

    if (!m_programDSP->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/dspFrag.frag")) {
        qDebug() << m_programDSP->log();
        return;
    }
    if (!m_programDSP->link()) {
        qDebug() << m_programDSP->log();
        return;
    }

    m_programTrace = new QOpenGLShaderProgram(this);

    if (!m_programTrace->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/chartVertexShader.vert")) {
        qDebug() << m_programTrace->log();
        return;
    }

    if (!m_programTrace->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/chartFragmentShader.frag")) {
        qDebug() << m_programTrace->log();
        return;
    }
    if (!m_programTrace->link()) {
        qDebug() << m_programTrace->log();
        return;
    }
}

void ExtraWindow::setRect(const OpenGLRectF &rect)
{
     extraWindow = rect;
     m_camera->setPosition( QVector3D( 0.0f, 0.0f, 10.0f ) );
     m_camera->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
     m_camera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );
     m_camera->setOrthographicProjection(0, extraWindow.width(),
                                         0, extraWindow.height(),
                                         -100,100);
}

void ExtraWindow::setQRect(const QRect &rect)
{
    windowRect = rect;
}

const QRect &ExtraWindow::getQRect()
{
    return windowRect;
}

void ExtraWindow::prepareExtraWindow()
{
    //extraWindow size Winodw
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;

    //background of window
    sizeBackGroundBuf = pointPerRect;
    GLfloat *backGroundBuf = new GLfloat[sizeBackGroundBuf];

    float zcoord = 0;
    calcRect(OpenGLRectF(0, 0, extraWindow.width(), extraWindow.height()), backGroundBuf, 0, zcoord);

    //back ground of chart HTML color(#2d2f39)
    const quint16 legendHeightWidth = 30, marginOnEdge = 30, chartWidth = 300, chartHeight = 150;
    const QSize legendYSize(legendHeightWidth, extraWindow.height() - legendHeightWidth - marginOnEdge),
            legendXSize(extraWindow.width() - legendHeightWidth - marginOnEdge, legendHeightWidth);
    legendXRect = OpenGLRectF(legendHeightWidth, 0, legendXSize.width(), legendXSize.height());
    legendYRect = OpenGLRectF(0, legendHeightWidth, legendYSize.width(), legendYSize.height());
    chartRect = OpenGLRectF(legendXRect.x(),legendYRect.y(), chartWidth, chartHeight);
    sizeBackGroundChartBuf = pointPerRect;
    GLfloat *backGroundChartBuf = new GLfloat[sizeBackGroundChartBuf];

    zcoord += 0.01;
    calcRect(chartRect, backGroundChartBuf, 0, zcoord);

    //axis of chart  HTML color(#86878c)
    const quint16 axisWidth = 3;
    OpenGLRectF xAxisRect(legendXRect.x() - axisWidth,
                          legendXRect.y() + legendXRect.height() - axisWidth,
                          legendXRect.width() + axisWidth,
                          axisWidth),
            yAxisRect(legendYRect.x() + legendYRect.width() - axisWidth,
                      legendYRect.y() - axisWidth,
                      axisWidth,
                      legendYRect.height() + axisWidth);
    sizeAxisChartBuf = 2 * pointPerRect; //two rect for x and y axis
    GLfloat *axisChartBuf = new GLfloat[sizeAxisChartBuf];
    zcoord += 0.01;
    calcRect(xAxisRect, axisChartBuf, 0, zcoord);
    calcRect(yAxisRect, axisChartBuf, pointPerRect, zcoord);

    const quint16 markWidth = 4, simpleLineWidth = 1;
    const quint16 stepBetweenMarksPx = 50;
    const quint16 markOnXCount = xAxisRect.width() / stepBetweenMarksPx,
                  markOnYCount = yAxisRect.height() / stepBetweenMarksPx;

    //two rect for x and y axis for each mark and line grid plus 1 * 2 rect for zero coords
    sizeGridChartBuf = 2 * pointPerRect * (markOnXCount + markOnYCount + 1);
    GLfloat *gridChartBuf = new GLfloat[sizeGridChartBuf];

    //EmpCoeff = + axisWidth - 0.5f
    QVector<OpenGLRectF> vectorOfMark;
    OpenGLRectF zeroXMark(xAxisRect.x() - markWidth / 2 + axisWidth - 0.5f,
                          xAxisRect.y() - markWidth,
                          markWidth / 2, markWidth),
                zeroYMark(yAxisRect.x() - markWidth,
                          yAxisRect.y() - markWidth / 2 + axisWidth - 0.5f,
                          markWidth, markWidth / 2);
    vectorOfMark.push_back(zeroXMark);

    zcoord += 0.01;
    calcRect(zeroXMark, gridChartBuf, 0, zcoord);
    calcRect(zeroYMark, gridChartBuf, pointPerRect, zcoord);

    //EmpCoeff = - 0.5f
    for (quint16 index = 0, indexForPtr = 2; index < markOnXCount + markOnYCount; index++) {
        OpenGLRectF markRect, lineOnGrid;
        if (index == markOnXCount) {
            vectorOfMark.push_back(zeroYMark);
        }
        if (index < markOnXCount) {
            markRect = OpenGLRectF(xAxisRect.x() + stepBetweenMarksPx * (index + 1) - 0.5f,
                                   xAxisRect.y() - markWidth, markWidth / 2, markWidth);
            vectorOfMark.push_back(markRect);
            lineOnGrid = OpenGLRectF(xAxisRect.x() + stepBetweenMarksPx * (index + 1),
                                     xAxisRect.y() + xAxisRect.height(), simpleLineWidth, chartHeight);
        }
        else {
            markRect = OpenGLRectF(yAxisRect.x() - markWidth,
                                   yAxisRect.y() + stepBetweenMarksPx * ((index - markOnXCount) + 1) - 0.5f,
                                   markWidth, markWidth / 2);
            vectorOfMark.push_back(markRect);
            lineOnGrid = OpenGLRectF(yAxisRect.x() + yAxisRect.width(),
                                     yAxisRect.y() + stepBetweenMarksPx * ((index - markOnXCount) + 1),
                                     chartWidth, simpleLineWidth);
        }
        //calcRect(markRect, gridChartBuf + (indexForPtr++ * pointPerRect));
        //calcRect(lineOnGrid, gridChartBuf + (indexForPtr++ * pointPerRect));
        calcRect(markRect, gridChartBuf, indexForPtr * pointPerRect, zcoord);
        indexForPtr++;
        calcRect(lineOnGrid, gridChartBuf, indexForPtr * pointPerRect, zcoord);
        indexForPtr++;
    }

    m_vboChart = new QOpenGLBuffer();
    m_vboChart->create();
    m_vboChart->bind();
    m_vboChart->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboChart->allocate(backGroundBuf, (sizeBackGroundBuf + sizeBackGroundChartBuf + sizeAxisChartBuf + sizeGridChartBuf) * sizeof(GLfloat));
    m_vboChart->write(sizeBackGroundBuf * sizeof(GLfloat),
                      backGroundChartBuf,
                      sizeBackGroundChartBuf * sizeof(GLfloat));
    m_vboChart->write((sizeBackGroundBuf + sizeBackGroundChartBuf) * sizeof(GLfloat),
                      axisChartBuf,
                      sizeAxisChartBuf * sizeof(GLfloat));
    m_vboChart->write((sizeBackGroundBuf + sizeBackGroundChartBuf + sizeAxisChartBuf) * sizeof(GLfloat),
                      gridChartBuf,
                      sizeGridChartBuf * sizeof(GLfloat));

    m_vaoExtraWindow = new QOpenGLVertexArrayObject();
    m_vaoExtraWindow->create();
    m_vaoExtraWindow->bind();
    if (!m_vaoExtraWindow->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programButton->enableAttributeArray("posAttr");
    m_programButton->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboChart->release();
    m_vaoExtraWindow->release();

    delete [] backGroundChartBuf;
    delete [] backGroundBuf;
    delete [] gridChartBuf;
    delete [] axisChartBuf;

    //text for axis
    const quint16 vertexOnTriangles = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 oneBuffSize = vertexOnTriangles * nDimensionalFont;

    quint32 charsCount = 0;
    QVector<QString> vectorOfString;
    for (quint16 index = 0; index < markOnXCount + 1; index++ ) {
        vectorOfString.push_back(QString::number(index * stepBetweenMarksPx));
        charsCount += vectorOfString.at(index).size();
    }
    for (quint16 index = 0; index < markOnYCount + 1; index++ ) {
        vectorOfString.push_back(QString::number(index * stepBetweenMarksPx));
        charsCount += vectorOfString.at(index).size();
    }
    // DEBUG BEGIN
    //vectorOfString.push_back(QString("012345678910"));
    //charsCount = vectorOfString.at(0).size();
    // DEBUG END

    sizeTextBuf = charsCount * oneBuffSize;
    GLfloat *texelVertex = new GLfloat[charsCount * oneBuffSize];
    GLfloat *uboForText = new GLfloat[charsCount];
    GLfloat *vertexForText = new GLfloat[charsCount * oneBuffSize];

    const GLfloat scale = 0.09;
    quint32 offsetOnArray = 0, indexOfChar = 0;
    for (quint16 index = 0; index < vectorOfString.size(); index++) {
        Qt::Alignment alignment;
        if (index <= markOnXCount) {
            alignment = Qt::AlignTop;
        }
        else if (index > markOnXCount) {
            alignment = Qt::AlignRight;
        }
        fontDriver->genText(vectorOfString.at(index),
                            QPointF(vectorOfMark.at(index).x(),
                                    vectorOfMark.at(index).y()),
                            alignment,
                            scale,
                            vertexForText,
                            texelVertex,
                            offsetOnArray,
                            uboForText + indexOfChar);
        indexOfChar += vectorOfString.at(index).size();
    }

    if (offsetOnArray > charsCount * oneBuffSize) {
         qDebug() << "VBO and TBO Buffer overhead";
    }

    if (indexOfChar > charsCount) {
        qDebug() << "UBO Buffer overhead";
    }

    m_vboTextForAxis = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboTextForAxis->create();
    m_vboTextForAxis->bind();
    m_vboTextForAxis->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboTextForAxis->allocate(texelVertex, 2 * (oneBuffSize * charsCount) * sizeof(GLfloat));
    m_vboTextForAxis->write((oneBuffSize * charsCount) * sizeof(GLfloat), vertexForText, (oneBuffSize * charsCount) * sizeof(GLfloat));

    m_vaoTextForAxis = new QOpenGLVertexArrayObject();
    m_vaoTextForAxis->create();
    m_vaoTextForAxis->bind();
    if (!m_vaoTextForAxis->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programFont->enableAttributeArray("texels");
    m_programFont->setAttributeBuffer("texels", GL_FLOAT, 0, nDimensionalFont, 0);
    m_programFont->enableAttributeArray("vertex");
    m_programFont->setAttributeBuffer("vertex", GL_FLOAT, (oneBuffSize * charsCount) * sizeof(GLfloat), nDimensionalFont, 0);

    m_vboTextForAxis->release();
    m_vaoTextForAxis->release();

    //glGenBuffers(1, &uboIndex);
    //glBindBuffer(GL_UNIFORM_BUFFER, uboIndex);
    //glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(GLfloat) * 250, NULL, GL_DYNAMIC_DRAW);
    //glBindBuffer(GL_UNIFORM_BUFFER, 0);

    //uniformBlockIndex = glGetUniformBlockIndex(m_programFont->programId(), "myblock");
    //glUniformBlockBinding(m_programFont->programId(), uniformBlockIndex, 0);
    glFunc->glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboIndex);
    GLfloat* cam_ubo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_UNIFORM_BUFFER,
      (uboOffset + 100) * sizeof(GLfloat),
      sizeof(GLfloat) * charsCount,
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );

    if (cam_ubo_ptr != nullptr)
        memcpy(cam_ubo_ptr, uboForText, sizeof(GLfloat) * charsCount);
    glFunc->glUnmapBuffer(GL_UNIFORM_BUFFER);
    cam_ubo_ptr = nullptr;

    delete [] uboForText;
    delete [] vertexForText;
    delete [] texelVertex;

    //init buttons
    quint32 charsCountButtons = 0;
    QVector<QString> vectorOfStringButtons;
    vectorOfStringButtons.push_back("h");
    vectorOfStringButtons.push_back("ДСП");
    vectorOfStringButtons.push_back("СЦ");
    const GLfloat scaleTextButt = 0.13;
    QVector<QSizeF> buttonsSize;
    for (quint16 index = 0; index < vectorOfStringButtons.size(); index++) {
        buttonsSize.push_back(fontDriver->genRectForText(vectorOfStringButtons.at(index),
                                                         scaleTextButt));
        charsCountButtons += vectorOfStringButtons.at(index).size();
    }
    QSizeF buttonSize(0, 0);
    for (auto &item : buttonsSize) {
        if (buttonSize.width() < item.width()) {
            buttonSize.rwidth() = item.width();
        }
        if (buttonSize.height() < item.height()) {
            buttonSize.rheight() = item.height();
        }
    }

    quint16 marginOnTopLeft = 5;
    buttonSize.rwidth() += 2 * marginOnTopLeft;
    buttonSize.rheight() += 2 * marginOnTopLeft;
    buttonAltitudeRect = OpenGLRectF(legendHeightWidth,
                                     extraWindow.height() - buttonSize.height() - marginOnTopLeft,
                                     buttonSize.width(),
                                     buttonSize.height());
    buttonDSPRect = OpenGLRectF(buttonAltitudeRect.x() + buttonAltitudeRect.width() + marginOnTopLeft,
                                extraWindow.height() - buttonSize.height() - marginOnTopLeft,
                                buttonSize.width(),
                                buttonSize.height());
    buttonNTRect = OpenGLRectF(buttonDSPRect.x() + buttonDSPRect.width() + marginOnTopLeft,
                               extraWindow.height() - buttonSize.height() - marginOnTopLeft,
                               buttonSize.width(),
                               buttonSize.height());
    buttonAltitudeQRect = QRect(windowRect.x() + marginOnTopLeft,
                                windowRect.y() + marginOnTopLeft,
                                buttonAltitudeRect.width(),
                                buttonAltitudeRect.height());
    buttonDSPQRect = QRect(buttonAltitudeQRect.x() + buttonAltitudeQRect.width() + marginOnTopLeft,
                           buttonAltitudeQRect.y(),
                           buttonAltitudeRect.width(),
                           buttonAltitudeRect.height());
    buttonNTQRect = QRect(buttonDSPQRect.x() + buttonDSPQRect.width() + marginOnTopLeft,
                          buttonAltitudeQRect.y(),
                          buttonAltitudeRect.width(),
                          buttonAltitudeRect.height());
    hoveredItem = -1, selectedItem = 0;
    OpenGLRectF buttonAltitudeTextRect(buttonAltitudeRect.x() + marginOnTopLeft,
                                       buttonAltitudeRect.y() + marginOnTopLeft,
                                       buttonAltitudeRect.width() - 2 * marginOnTopLeft,
                                       buttonAltitudeRect.height() - 2 * marginOnTopLeft);
    OpenGLRectF buttonDSPTextRect(buttonDSPRect.x() + marginOnTopLeft,
                                  buttonDSPRect.y() + marginOnTopLeft,
                                  buttonDSPRect.width() - 2 * marginOnTopLeft,
                                  buttonDSPRect.height() - 2 * marginOnTopLeft);
    OpenGLRectF buttonNTTextRect(buttonNTRect.x() + marginOnTopLeft,
                                 buttonNTRect.y() + marginOnTopLeft,
                                 buttonNTRect.width() - 2 * marginOnTopLeft,
                                 buttonNTRect.height() - 2 * marginOnTopLeft);

    sizeButtonsBuff = 3 * pointPerRect; //three rect for three buttons
    GLfloat *buttonsRectBuf = new GLfloat[sizeButtonsBuff];
    zcoord += 0.01;
    calcRect(buttonAltitudeRect, buttonsRectBuf, 0, zcoord);
    calcRect(buttonDSPRect, buttonsRectBuf, pointPerRect, zcoord);
    calcRect(buttonNTRect, buttonsRectBuf, 2 * pointPerRect, zcoord);

    m_vboButtons = new QOpenGLBuffer();
    m_vboButtons->create();
    m_vboButtons->bind();
    m_vboButtons->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboButtons->allocate(buttonsRectBuf, sizeButtonsBuff * sizeof(GLfloat));

    m_vaoButtons = new QOpenGLVertexArrayObject();
    m_vaoButtons->create();
    m_vaoButtons->bind();
    if (!m_vaoButtons->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programButton->enableAttributeArray("posAttr");
    m_programButton->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboButtons->release();
    m_vaoButtons->release();

    delete [] buttonsRectBuf;

    sizeTextForButtons = charsCountButtons * oneBuffSize;
    GLfloat *texelVertexButt = new GLfloat[charsCountButtons * oneBuffSize];
    GLfloat *uboForTextButt = new GLfloat[charsCountButtons];
    GLfloat *vertexForTextButt = new GLfloat[charsCountButtons * oneBuffSize];

    QVector<OpenGLRectF> vectorOfRect;
    vectorOfRect.push_back(buttonAltitudeTextRect);
    vectorOfRect.push_back(buttonDSPTextRect);
    vectorOfRect.push_back(buttonNTTextRect);
    quint32 offsetOnArrayButt = 0, indexOfCharButt = 0;
    for (quint16 index = 0; index < vectorOfStringButtons.size(); index++) {
        fontDriver->genTextWithRect(vectorOfStringButtons.at(index),
                                          vectorOfRect.at(index),
                                          scaleTextButt,
                                          vertexForTextButt,
                                          texelVertexButt,
                                          offsetOnArrayButt,
                                          uboForTextButt + indexOfCharButt);
        indexOfCharButt += vectorOfStringButtons.at(index).size();
    }

    if (offsetOnArrayButt > charsCountButtons * oneBuffSize) {
         qDebug() << "VBO2 and TBO2 Buffer overhead";
    }

    if (indexOfCharButt > charsCountButtons) {
        qDebug() << "UBO2 Buffer overhead";
    }

    m_vboButtonsText = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboButtonsText->create();
    m_vboButtonsText->bind();
    m_vboButtonsText->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboButtonsText->allocate(texelVertexButt, 2 * (oneBuffSize * charsCountButtons) * sizeof(GLfloat));
    m_vboButtonsText->write((oneBuffSize * charsCountButtons) * sizeof(GLfloat), vertexForTextButt, (oneBuffSize * charsCountButtons) * sizeof(GLfloat));

    m_vaoTextForButtons = new QOpenGLVertexArrayObject();
    m_vaoTextForButtons->create();
    m_vaoTextForButtons->bind();
    if (!m_vaoTextForButtons->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programFont->enableAttributeArray("texels");
    m_programFont->setAttributeBuffer("texels", GL_FLOAT, 0, nDimensionalFont, 0);
    m_programFont->enableAttributeArray("vertex");
    m_programFont->setAttributeBuffer("vertex", GL_FLOAT, (oneBuffSize * charsCountButtons) * sizeof(GLfloat), nDimensionalFont, 0);

    m_vboButtonsText->release();
    m_vaoTextForButtons->release();

    //glUniformBlockBinding(m_programFont->programId(), uniformBlockIndex, 0);
    glFunc->glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboIndex);
    GLfloat* cam_ubo_ptr2 = (GLfloat*)glFunc->glMapBufferRange (
      GL_UNIFORM_BUFFER,
      uboOffset * sizeof(GLfloat),
      sizeof(GLfloat) * charsCountButtons,
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );
    if (cam_ubo_ptr2 != nullptr)
        memcpy(cam_ubo_ptr2, uboForTextButt, sizeof(GLfloat) * charsCountButtons);
    glFunc->glUnmapBuffer(GL_UNIFORM_BUFFER);
    cam_ubo_ptr2 = nullptr;

    delete [] uboForTextButt;
    delete [] vertexForTextButt;
    delete [] texelVertexButt;

    prepareChart();
}

void ExtraWindow::prepareChart()
{
    const quint8 nDimensional = 2;
    const quint16 countPoint = 300;

    quint32 sizeTraceBuff = nDimensional * countPoint;
    /*GLfloat *traceBuff = new GLfloat[sizeTraceBuff];
    for (quint16 index = 0; index != sizeTraceBuff; index++) {
        traceBuff[index] = index;
        index++;
        traceBuff[index] = index * 0.5;
    }*/

    m_vboTrace = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vboTrace->create();
    m_vboTrace->bind();
    m_vboTrace->setUsagePattern(QOpenGLBuffer::StaticDraw);
    //m_vboTrace->allocate(traceBuff, sizeTraceBuff * sizeof(GLfloat));
    m_vboTrace->allocate(sizeTraceBuff * sizeof(GLfloat));

    m_vaoTrace = new QOpenGLVertexArrayObject();
    m_vaoTrace->create();
    m_vaoTrace->bind();
    if (!m_vaoTrace->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    sizeTraceBuffer = 0;

    m_programTrace->enableAttributeArray("posAttr");
    m_programTrace->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboTrace->release();
    m_vaoTrace->release();

    //delete [] traceBuff;
}

void ExtraWindow::prepareDSP()
{
    const quint8 nDimensionalZ = 1;
    //const quint8 nDimensional = 2;
    //const quint8 vertexPerTriangle = 3;
    //const quint8 trianglePerRect = 2;
    //const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;
    //const quint32 pointPerRectZ = nDimensionalZ * vertexPerTriangle * trianglePerRect;

    const quint16 chartWidth = 300, chartHeight = 150;
    sizeDSPZCoords = chartWidth * chartHeight * nDimensionalZ;
    //const quint32 rectCountOnChart = (chartWidth - 1) * (chartHeight - 1); //4 points per rect
    //GLfloat *wiredSurfaceBuf = new GLfloat[rectCountOnChart * pointPerRect];
    GLfloat *zCoordBuff = new GLfloat[sizeDSPZCoords];

    /*for (quint32 i = 0; i < chartWidth - 1; i++) {
        for (quint32 j = 0; j < chartHeight - 1; j++) {
            OpenGLRectF rect(chartRect.x() + i,
                             chartRect.y() + j,
                             1, 1);
            calcRect2d(rect, wiredSurfaceBuf, (i * (chartHeight - 1) + j) * pointPerRect);
        }
    }*/

    for (quint32 index = 0; index < sizeDSPZCoords; index++ ) {
        zCoordBuff[index] = qrand() % 255;
    }

    m_vboDSPZCoord = new QOpenGLBuffer();
    m_vboDSPZCoord->create();
    m_vboDSPZCoord->bind();
    m_vboDSPZCoord->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vboDSPZCoord->allocate(zCoordBuff, sizeDSPZCoords * sizeof(GLfloat));

    delete [] zCoordBuff;

    QVector<quint32> iboRects;
    for (quint32 i = 0; i < chartWidth - 1; i++) {
        for (quint32 j = 0; j < chartHeight - 1; j++) {
            // 0 - 1 - 2 - 1 - 3 - 2
            iboRects << i * chartHeight + j
                     << (i + 1) * chartHeight + j
                     << i * chartHeight + j + 1
                     << (i + 1) * chartHeight + j
                     << (i + 1) * chartHeight + j + 1
                     << i * chartHeight + j + 1;
        }
    }

    m_vaoDSP = new QOpenGLVertexArrayObject(this);
    m_vaoDSP->create();
    m_vaoDSP->bind();
    if (!m_vaoDSP->isCreated()){
        qDebug() << "Can't use VAO";
        return;
    }

    m_programDSP->enableAttributeArray("zCoord");
    m_programDSP->setAttributeBuffer("zCoord", GL_FLOAT, 0, 1, 0);

    m_vboDSPZCoord->release();

    sizeIBODSP = iboRects.size();
    GLushort *iboBuf = new GLushort[sizeIBODSP];
    for (auto i = 0; i != iboRects.size(); i++) {
        iboBuf[i] = iboRects.at(i);
    }

    m_iboDsp = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_iboDsp->create();
    m_iboDsp->bind();
    m_iboDsp->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_iboDsp->allocate(iboBuf, sizeIBODSP * sizeof(GLushort));

    m_vaoDSP->release();

    QTimer::singleShot(20, this, &ExtraWindow::updateDSP);
}

void ExtraWindow::calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord)
{
    //int counter = 0;
    //(left;bottom) - (right;bottom) - (left;top) CCW
    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    //(right;bottom) - (right;top) - (left;top)
    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    *(array + counter) = zcoord;
    counter++;

    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    *(array + counter) = zcoord;
    counter++;
    //qDebug() << counter;
}

void ExtraWindow::calcRect2d(const OpenGLRectF &rect, GLfloat *array, int counter)
{
    //int counter = 0;
    //(left;bottom) - (right;bottom) - (left;top) CCW
    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y();
    counter++;

    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y();
    counter++;

    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;

    //(right;bottom) - (right;top) - (left;top)
    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y();
    counter++;

    *(array + counter) = rect.x() + rect.width();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;

    *(array + counter) = rect.x();
    counter++;
    *(array + counter) = rect.y() + rect.height();
    counter++;
    //qDebug() << counter;
}

void ExtraWindow::renderExtraWindow()
{
    glFunc->glViewport(extraWindow.x(),
                       extraWindow.y(),
                       extraWindow.width(),
                       extraWindow.height());

    float zcoord = 0;
    int butt = -1;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programButton->bind();
    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix() * model;
    m_programButton->setUniformValue("selectedItem", zcoord);
    m_programButton->setUniformValue("hoveredItem", butt);
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("ourColor", QVector4D(0.05f, 0.05f, 0.05f, 1.0f));

    m_vaoExtraWindow->bind();

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_programButton->setUniformValue("ourColor", QVector4D(0.12f, 0.12f, 0.16f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3, sizeBackGroundChartBuf / 3);

    m_programButton->setUniformValue("ourColor", QVector4D(0.53f, 0.53f, 0.55f, 0.7f));

    glFunc->glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3 + sizeBackGroundChartBuf / 3, (sizeAxisChartBuf + sizeGridChartBuf) / 3);

    m_vaoExtraWindow->release();
    m_programButton->release();

    //int level = 0;
    int uboLocalOffset = 100 + uboOffset;
    zcoord += 0.04;
    m_programFont->bind();
    m_programFont->setUniformValue("proj", m_camera->projectionMatrix());
    m_programFont->setUniformValue("view", m_camera->viewMatrix());
    m_programFont->setUniformValue("model", model);
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);
    m_programFont->setUniformValue("textureColor", QVector3D(0.21f,0.69f,0.33f));

    m_vaoTextForAxis->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextBuf / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForAxis->release();
    m_programFont->release();

    m_programButton->bind();
    m_vaoButtons->bind();
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("selectedItem", selectedItem);
    m_programButton->setUniformValue("hoveredItem", hoveredItem);
    m_programButton->setUniformValue("ourColor", QVector4D(0.1f, 0.1f, 0.1f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeButtonsBuff / 3);

    m_vaoButtons->release();
    m_programButton->release();

    zcoord += 0.04;
    uboLocalOffset = uboOffset;
    m_programFont->bind();
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);

    m_vaoTextForButtons->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextForButtons / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForButtons->release();
    m_programFont->release();
}

void ExtraWindow::renderDSP()
{
    glFunc->glViewport(extraWindow.x(),
                       extraWindow.y(),
                       extraWindow.width(),
                       extraWindow.height());

    QMatrix4x4 viewPort;
    viewPort.setToIdentity();
    viewPort.viewport(extraWindow.x(),
                      extraWindow.y(),
                      extraWindow.width(),
                      extraWindow.height());

    float zcoord = 0;
    int butt = -1;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programButton->bind();
    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix() * model;
    m_programButton->setUniformValue("selectedItem", zcoord);
    m_programButton->setUniformValue("hoveredItem", butt);
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("ourColor", QVector4D(0.05f, 0.05f, 0.05f, 1.0f));

    m_vaoExtraWindow->bind();

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_programButton->setUniformValue("ourColor", QVector4D(0.12f, 0.12f, 0.16f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3, sizeBackGroundChartBuf / 3);

    m_programButton->setUniformValue("ourColor", QVector4D(0.53f, 0.53f, 0.55f, 0.7f));

    glFunc->glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3 + sizeBackGroundChartBuf / 3, (sizeAxisChartBuf + sizeGridChartBuf) / 3);

    m_vaoExtraWindow->release();
    m_programButton->release();

    //int level = 0;
    int uboLocalOffset = 100 + uboOffset;
    zcoord += 0.04;
    m_programFont->bind();
    m_programFont->setUniformValue("proj", m_camera->projectionMatrix());
    m_programFont->setUniformValue("view", m_camera->viewMatrix());
    m_programFont->setUniformValue("model", model);
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);
    m_programFont->setUniformValue("textureColor", QVector3D(0.21f,0.69f,0.33f));

    m_vaoTextForAxis->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextBuf / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForAxis->release();
    m_programFont->release();

    m_programButton->bind();
    m_vaoButtons->bind();
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("selectedItem", selectedItem);
    m_programButton->setUniformValue("hoveredItem", hoveredItem);
    m_programButton->setUniformValue("ourColor", QVector4D(0.1f, 0.1f, 0.1f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeButtonsBuff / 3);

    m_vaoButtons->release();
    m_programButton->release();

    zcoord += 0.04;
    uboLocalOffset = uboOffset;
    m_programFont->bind();
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);

    m_vaoTextForButtons->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextForButtons / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForButtons->release();
    m_programFont->release();

    m_programDSP->bind();
    m_programDSP->setUniformValue("mvp", mvp);
    m_programDSP->setUniformValue("ViewportMatrix", viewPort);

    m_vaoDSP->bind();
    glFunc->glDrawElements(GL_TRIANGLES, sizeIBODSP, GL_UNSIGNED_SHORT, 0);
    m_vaoDSP->release();
    m_programDSP->release();
}

void ExtraWindow::renderNT()
{
    glFunc->glViewport(extraWindow.x(),
                       extraWindow.y(),
                       extraWindow.width(),
                       extraWindow.height());

    float zcoord = 0;
    int butt = -1;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programButton->bind();
    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix() * model;
    m_programButton->setUniformValue("selectedItem", zcoord);
    m_programButton->setUniformValue("hoveredItem", butt);
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("ourColor", QVector4D(0.05f, 0.05f, 0.05f, 1.0f));

    m_vaoExtraWindow->bind();

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_vaoExtraWindow->release();
    m_programButton->release();

    m_programButton->bind();
    m_vaoButtons->bind();
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("selectedItem", selectedItem);
    m_programButton->setUniformValue("hoveredItem", hoveredItem);
    m_programButton->setUniformValue("ourColor", QVector4D(0.1f, 0.1f, 0.1f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeButtonsBuff / 3);

    m_vaoButtons->release();
    m_programButton->release();

    zcoord += 0.04;
    int uboLocalOffset  = uboOffset;
    m_programFont->bind();
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);

    m_vaoTextForButtons->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextForButtons / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForButtons->release();
    m_programFont->release();
}

void ExtraWindow::preRender()
{
    /*if (selectedItem == 0) {
        renderExtraWindow();
    }
    else if (selectedItem == 1) {
        renderDSP();
    }
    else {
        renderNT();
    }*/
    render();
}

void ExtraWindow::render()
{
    glFunc->glViewport(extraWindow.x(),
                       extraWindow.y(),
                       extraWindow.width(),
                       extraWindow.height());

    QMatrix4x4 viewPort;
    viewPort.setToIdentity();
    viewPort.viewport(extraWindow.x(),
                      extraWindow.y(),
                      extraWindow.width(),
                      extraWindow.height());

    float zcoord = 0;
    int butt = -1;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programButton->bind();
    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix() * model;
    m_programButton->setUniformValue("selectedItem", zcoord);
    m_programButton->setUniformValue("hoveredItem", butt);
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("ourColor", QVector4D(0.05f, 0.05f, 0.05f, 1.0f));

    m_vaoExtraWindow->bind();

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_programButton->setUniformValue("ourColor", QVector4D(0.12f, 0.12f, 0.16f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3, sizeBackGroundChartBuf / 3);

    m_programButton->setUniformValue("ourColor", QVector4D(0.53f, 0.53f, 0.55f, 0.7f));

    glFunc->glDrawArrays(GL_TRIANGLES, sizeBackGroundBuf / 3 + sizeBackGroundChartBuf / 3, (sizeAxisChartBuf + sizeGridChartBuf) / 3);

    m_vaoExtraWindow->release();
    m_programButton->release();

    //int level = 0;
    int uboLocalOffset = 100 + uboOffset;
    zcoord += 0.04;
    m_programFont->bind();
    m_programFont->setUniformValue("proj", m_camera->projectionMatrix());
    m_programFont->setUniformValue("view", m_camera->viewMatrix());
    m_programFont->setUniformValue("model", model);
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);
    m_programFont->setUniformValue("textureColor", QVector3D(0.21f,0.69f,0.33f));

    m_vaoTextForAxis->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextBuf / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForAxis->release();
    m_programFont->release();

    m_programButton->bind();
    m_vaoButtons->bind();
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("selectedItem", selectedItem);
    m_programButton->setUniformValue("hoveredItem", hoveredItem);
    m_programButton->setUniformValue("ourColor", QVector4D(0.1f, 0.1f, 0.1f, 1.0f));

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeButtonsBuff / 3);

    m_vaoButtons->release();
    m_programButton->release();

    zcoord += 0.04;
    uboLocalOffset = uboOffset;
    m_programFont->bind();
    m_programFont->setUniformValue("zcoord", zcoord);
    m_programFont->setUniformValue("offsetInMyBlock", uboLocalOffset);

    m_vaoTextForButtons->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeTextForButtons / 2);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    m_vaoTextForButtons->release();
    m_programFont->release();

    if (selectedItem == 0) {
        zcoord++;
        QMatrix4x4 model2;
        model2.setToIdentity();
        model2.translate(chartRect.x() + 1, chartRect.y() + 1);
        QMatrix4x4 mvp2 = m_camera->projectionMatrix() * m_camera->viewMatrix() * model2;
        m_programTrace->bind();
        m_programTrace->setUniformValue("mvp", mvp2);
        m_programTrace->setUniformValue("zcoord", zcoord);

        m_vaoTrace->bind();
        glFunc->glDrawArrays(GL_LINE_STRIP, 0, sizeTraceBuffer);

        m_vaoTrace->release();
        m_programTrace->release();
    }

    if (selectedItem == 1) {
        m_programDSP->bind();
        m_programDSP->setUniformValue("mvp", mvp);
        m_programDSP->setUniformValue("ViewportMatrix", viewPort);

        m_vaoDSP->bind();
        glFunc->glDrawElements(GL_TRIANGLES, sizeIBODSP, GL_UNSIGNED_SHORT, 0);
        m_vaoDSP->release();
        m_programDSP->release();
    }
}

void ExtraWindow::simplePrepare()
{
    //extraWindow size Winodw
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;

    //background of window
    sizeBackGroundBuf = pointPerRect;
    GLfloat *backGroundBuf = new GLfloat[sizeBackGroundBuf];

    float zcoord = 0;
    calcRect(OpenGLRectF(0, 0, extraWindow.width(), extraWindow.height()), backGroundBuf, 0, zcoord);

    m_vboChart = new QOpenGLBuffer();
    m_vboChart->create();
    m_vboChart->bind();
    m_vboChart->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboChart->allocate(backGroundBuf, sizeBackGroundBuf * sizeof(GLfloat));

    m_vaoExtraWindow = new QOpenGLVertexArrayObject();
    m_vaoExtraWindow->create();
    m_vaoExtraWindow->bind();
    if (!m_vaoExtraWindow->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programButton->enableAttributeArray("posAttr");
    m_programButton->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboChart->release();
    m_vaoExtraWindow->release();

    delete [] backGroundBuf;
}

void ExtraWindow::simpleRender()
{
    glFunc->glViewport(extraWindow.x(),
                       extraWindow.y(),
                       extraWindow.width(),
                       extraWindow.height());

    float zcoord = 0;
    int butt = -1;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programButton->bind();
    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix() * model;
    m_programButton->setUniformValue("selectedItem", butt);
    m_programButton->setUniformValue("hoveredItem", butt);
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("ourColor", QVector4D(0.0f, 0.7f, 0.0f, 1.0f));

    m_vaoExtraWindow->bind();

    glFunc->glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_vaoExtraWindow->release();
    m_programButton->release();

}

void ExtraWindow::searchHoveredSelectedItem(QPoint point, bool isHovered)
{
    point.setX(point.x() - 15);
    if (isHovered) {
        if (buttonAltitudeQRect.contains(point)) {
            hoveredItem = 0;
        }
        else if (buttonDSPQRect.contains(point)) {
            hoveredItem = 1;
        }
        else if (buttonNTQRect.contains(point)) {
            hoveredItem = 2;
        }
        else {
            hoveredItem = -1;
        }
    }
    else {
        if (buttonAltitudeQRect.contains(point)) {
            selectedItem = 0;
        }
        else if (buttonDSPQRect.contains(point)) {
            selectedItem = 1;
        }
        else if (buttonNTQRect.contains(point)) {
            selectedItem = 2;
        }
    }
}

void ExtraWindow::addInfo(const quint16 h)
{

    if (heightTrace.size() == 300) {
        heightTrace.pop_front();
    }
    heightTrace.push_back(h);

    const quint8 nDimensional = 2;
    quint32 sizeTraceBuff = nDimensional * heightTrace.size();
    GLfloat *tBuff = new GLfloat[sizeTraceBuff];
    quint32 indexBuff = 0;
    for (quint16 index = 0; index != heightTrace.size(); index++) {
        tBuff[indexBuff++] = index;
        tBuff[indexBuff++] = heightTrace.at(index) / 100.;
    }

    glFunc->glBindBuffer(GL_ARRAY_BUFFER,  m_vboTrace->bufferId());
    GLfloat* cam_vbo = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      sizeof(GLfloat) * sizeTraceBuff,
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );
    if (cam_vbo != nullptr)
        memcpy(cam_vbo, tBuff, sizeof(GLfloat) * sizeTraceBuff);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    cam_vbo = nullptr;
    delete [] tBuff;

    sizeTraceBuffer = heightTrace.size();
}

void ExtraWindow::updateDSP()
{
    GLfloat *zCoordBuff = new GLfloat[sizeDSPZCoords];
    for (quint32 index = 0; index < sizeDSPZCoords; index++ ) {
        zCoordBuff[index] = qrand() % 255;
    }

    glFunc->glBindBuffer(GL_ARRAY_BUFFER,  m_vboDSPZCoord->bufferId());
    GLfloat* cam_ubo_ptr2 = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      sizeof(GLfloat) * sizeDSPZCoords,
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );
    if (cam_ubo_ptr2 != nullptr)
        memcpy(cam_ubo_ptr2, zCoordBuff, sizeof(GLfloat) * sizeDSPZCoords);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    cam_ubo_ptr2 = nullptr;
    delete [] zCoordBuff;

    QTimer::singleShot(200, this, &ExtraWindow::updateDSP);
}



void Scene::simplePrepare()
{
    //extraWindow size Winodw
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;

    //background of window
    sizeBackGroundBuf = pointPerRect;
    GLfloat *backGroundBuf = new GLfloat[sizeBackGroundBuf];

    float zcoord = 0;
    calcRect(OpenGLRectF(0, 0, extraWindow.width(), extraWindow.height()), backGroundBuf, 0, zcoord);

    m_vboChart = new QOpenGLBuffer();
    m_vboChart->create();
    m_vboChart->bind();
    m_vboChart->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboChart->allocate(backGroundBuf, sizeBackGroundBuf * sizeof(GLfloat));

    m_vaoExtraWindow = new QOpenGLVertexArrayObject();
    m_vaoExtraWindow->create();
    m_vaoExtraWindow->bind();
    if (!m_vaoExtraWindow->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programButton->enableAttributeArray("posAttr");
    m_programButton->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    m_vboChart->release();
    m_vaoExtraWindow->release();

    delete [] backGroundBuf;

    m_cameraExtraWindow->setPosition( QVector3D( 0.0f, 0.0f, 10.0f ) );
    m_cameraExtraWindow->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
    m_cameraExtraWindow->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );
    m_cameraExtraWindow->setOrthographicProjection(0, extraWindow.width(),
                                                   0, extraWindow.height(),
                                                   -100,100);

    isExtraWindowAdd = true;
}

void Scene::simpleRender()
{
    glViewport(screenSize.width() - extraWindow.width(),
               screenSize.height() - 2 * extraWindow.height(),
               extraWindow.width(),
               extraWindow.height());

    float zcoord = 0;
    int butt = -1;
    QMatrix4x4 model;
    model.setToIdentity();
    m_programButton->bind();
    QMatrix4x4 mvp = m_cameraExtraWindow->projectionMatrix() * m_cameraExtraWindow->viewMatrix() * model;
    m_programButton->setUniformValue("selectedItem", butt);
    m_programButton->setUniformValue("hoveredItem", butt);
    m_programButton->setUniformValue("mvp", mvp);
    m_programButton->setUniformValue("ourColor", QVector4D(0.0f, 0.0f, 7.0f, 1.0f));

    m_vaoExtraWindow->bind();

    glDrawArrays(GL_TRIANGLES, 0, sizeBackGroundBuf / 3);

    m_vaoExtraWindow->release();
    m_programButton->release();

}

void Scene::initRect()
{
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRect = nDimensional * vertexPerTriangle * trianglePerRect;

    //background of window
    sizeRectForSampling = pointPerRect;
    GLfloat *rectForSamplingBuf = new GLfloat[sizeRectForSampling];

    float zcoord = 10;
    calcRect(OpenGLRectF(0, 0, 100, 100), rectForSamplingBuf, 0, zcoord);

    vboRect = new QOpenGLBuffer();
    vboRect->create();
    vboRect->bind();
    vboRect->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboRect->allocate(rectForSamplingBuf, sizeRectForSampling * sizeof(GLfloat));

    vaoRect = new QOpenGLVertexArrayObject();
    vaoRect->create();
    vaoRect->bind();
    if (!vaoRect->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vboRect->release();
    vaoRect->release();

    sizeRectForSampling = 0;

    delete [] rectForSamplingBuf;
}


KTAGLData::KTAGLData(QOpenGLFunctions_3_3_Core *func,  const Camera *m_camera, float _depth, QObject *parent) : QObject(parent),
    glFunc(func), camera_ptr(m_camera), depth(_depth),
    ktaCountMax(10000), timeErase(new QTimer()),
    timeEraseForSampledMark(new QTimer()), timeAlive_msec(7000),
    ktaPOIColor(QColor::fromRgbF(0.15f, 0.56f, 0.15f, 0.4f)),
    ktaVOIColor(QColor::fromRgbF(0.8f, 0.8f, 0.0f, 0.4f)),
    ktaVOIRespondingColor(QColor::fromRgbF(0.8f, 0.8f, 0.8f, 0.4f)),
    ktaPOISize(0.005), ktaVOISize(0.005), sampledMarkSize(0)
{
    qRegisterMetaType<VOIMarkMessage>();
    qRegisterMetaType<POIKtaMessage>();

    programKTA = new QOpenGLShaderProgram(this);

    if (!programKTA->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/KTAVertexSh.vert")) {
        qDebug() << programKTA->log();
        return;
    }

    if (!programKTA->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/KTAFragmentSh.frag")) {
        qDebug() << programKTA->log();
        return;
    }
    if (!programKTA->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/KTAGeometrySh.gs")) {
        qDebug() << programKTA->log();
        return;
    }

    if (!programKTA->link()) {
        qDebug() << programKTA->log();
        return;
    }

    connect(timeErase, &QTimer::timeout, this, &KTAGLData::eraseOldKTA);
    connect(timeEraseForSampledMark, &QTimer::timeout, this, &KTAGLData::eraseOldSampledKTA);
}

void KTAGLData::setSceneOptions(const SceneOptions *sOptions)
{
    sceneOptions = sOptions;
}

void KTAGLData::prepare()
{
    const quint8 nDimensional = 5;

    glFunc->glGenBuffers(1, &vbo);
    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glFunc->glBufferData(GL_ARRAY_BUFFER, nDimensional * sizeof(GLfloat) * ktaCountMax, NULL, GL_STREAM_DRAW);
    //glFunc->glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * nDimensional * sizeof(GLfloat), currentPoint);

    glFunc->glGenVertexArrays(1, &vao);
    glFunc->glBindVertexArray(vao);

    programKTA->enableAttributeArray("posAttr");
    programKTA->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional - 1, nDimensional * sizeof (GLfloat));
    programKTA->enableAttributeArray("msec");
    programKTA->setAttributeBuffer("msec", GL_FLOAT, (nDimensional - 1) * sizeof (GLfloat), 1, nDimensional * sizeof (GLfloat));

    glFunc->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFunc->glBindVertexArray(0);

    vboIndex = 0;
    vboLeftLimit = 0;
    vboRightLimit = 0;

    mapTime.clear();

    /*GLfloat *buffer = new GLfloat[ktaCountMax * nDimensional];
    for (quint16 index = 0; index < ktaCountMax; index++) {
        buffer[index * nDimensional] = index;
        buffer[index * nDimensional + 1] = index;
        buffer[index * nDimensional + 2] = 7.;
        buffer[index * nDimensional + 3] = 0.5;
        buffer[index * nDimensional + 4] = 0;
    }
    sampledMarkSize = ktaCountMax;*/

    vboSampledMark = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboSampledMark->create();
    vboSampledMark->bind();
    vboSampledMark->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboSampledMark->allocate(nDimensional * sizeof(GLfloat) * ktaCountMax);
    //vboSampledMark->allocate(buffer, nDimensional * sizeof(GLfloat) * ktaCountMax);

    //delete [] buffer;

    vaoSampledMark = new QOpenGLVertexArrayObject();
    vaoSampledMark->create();
    vaoSampledMark->bind();
    if (!vaoSampledMark->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programKTA->enableAttributeArray("posAttr");
    programKTA->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional - 1, nDimensional * sizeof (GLfloat));
    programKTA->enableAttributeArray("msec");
    programKTA->setAttributeBuffer("msec", GL_FLOAT, (nDimensional - 1) * sizeof (GLfloat), 1, nDimensional * sizeof (GLfloat));

    vboSampledMark->release();
    vaoSampledMark->release();
}

void KTAGLData::render()
{
    QMatrix4x4 model;
    model.setToIdentity();
    programKTA->bind();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;
    //const QVector3D scale = camera_ptr->viewMatrixScale();
    //GLfloat pointSize = 10; //on nvidia point size is 10
    //GLfloat radius = 0.005; // scale.x();
    GLfloat aspect = sceneOptions->aspectRatio;
    programKTA->setUniformValue("mvp", mvp);
    programKTA->setUniformValue("poiColor", ktaPOIColor);
    programKTA->setUniformValue("voiColor", ktaVOIColor);
    programKTA->setUniformValue("voiRespColor", ktaVOIRespondingColor);
    programKTA->setUniformValue("poiRad", ktaPOISize);
    programKTA->setUniformValue("voiRad", ktaVOISize);
    programKTA->setUniformValue("aspect", aspect );
    programKTA->setUniformValue("current_msec", QTime::currentTime().msecsSinceStartOfDay() );

    glFunc->glBindVertexArray(vao);
    //qVAO->bind();

    quint16 maxKTALimit = 2000;
    if (vboRightLimit > vboLeftLimit) {
        if ((vboRightLimit - vboLeftLimit) > maxKTALimit) {
            quint32 ktaCount = vboRightLimit - vboLeftLimit,
                    ktaLeft = vboLeftLimit;
            while (ktaCount > maxKTALimit) {
                glFunc->glDrawArrays(GL_POINTS, ktaLeft, maxKTALimit);
                ktaCount -= maxKTALimit;
                ktaLeft += maxKTALimit;
            }
            glFunc->glDrawArrays(GL_POINTS, ktaLeft, ktaCount);
            //glFunc->glDrawArrays(GL_POINTS, vboLeftLimit, maxKTALimit);
            //glFunc->glDrawArrays(GL_POINTS, vboLeftLimit + maxKTALimit, vboRightLimit - maxKTALimit);
        }
        else {
            glFunc->glDrawArrays(GL_POINTS, vboLeftLimit, vboRightLimit - vboLeftLimit);
        }
    }
    else if (vboRightLimit < vboLeftLimit) {
        if ((ktaCountMax - vboLeftLimit) > maxKTALimit) {
            //glFunc->glDrawArrays(GL_POINTS, vboLeftLimit, maxKTALimit);
            //glFunc->glDrawArrays(GL_POINTS, vboLeftLimit + maxKTALimit, ktaCountMax - maxKTALimit);
            quint32 ktaCount = ktaCountMax - vboLeftLimit,
                    ktaLeft = vboLeftLimit;
            while (ktaCount > maxKTALimit) {
                glFunc->glDrawArrays(GL_POINTS, ktaLeft, maxKTALimit);
                ktaCount -= maxKTALimit;
                ktaLeft += maxKTALimit;
            }
            glFunc->glDrawArrays(GL_POINTS, ktaLeft, ktaCount);
        }
        else {
            glFunc->glDrawArrays(GL_POINTS, vboLeftLimit, ktaCountMax - vboLeftLimit);
        }
        if (vboRightLimit > maxKTALimit) {
            //glFunc->glDrawArrays(GL_POINTS, 0, maxKTALimit);
            //glFunc->glDrawArrays(GL_POINTS, maxKTALimit, vboRightLimit - maxKTALimit);
            quint32 ktaCount = vboRightLimit,
                    ktaLeft = 0;
            while (ktaCount > maxKTALimit) {
                glFunc->glDrawArrays(GL_POINTS, ktaLeft, maxKTALimit);
                ktaCount -= maxKTALimit;
                ktaLeft += maxKTALimit;
            }
            glFunc->glDrawArrays(GL_POINTS, ktaLeft, ktaCount);
        }
        else {
            glFunc->glDrawArrays(GL_POINTS, 0, vboRightLimit);
        }
    }

    //qVAO->release();

    glFunc->glBindVertexArray(0);
    programKTA->setUniformValue("poiColor", QVector4D(0.8f, 0.0f, 0.0f, 0.66f));
    programKTA->setUniformValue("voiColor", QVector4D(0.8f, 0.0f, 0.0f, 0.66f));
    programKTA->setUniformValue("voiRespColor", QVector4D(0.8f, 0.0f, 0.0f, 0.66f));

    vaoSampledMark->bind();
    if (sampledMarkSize != 0) {
        if (sampledMarkSize > maxKTALimit) {
            quint32 ktaCount = sampledMarkSize,
                    ktaLeft = 0;
            while (ktaCount > maxKTALimit) {
                glFunc->glDrawArrays(GL_POINTS, ktaLeft, maxKTALimit);
                ktaCount -= maxKTALimit;
                ktaLeft += maxKTALimit;
            }
            glFunc->glDrawArrays(GL_POINTS, ktaLeft, ktaCount);
        }
        else
            glFunc->glDrawArrays(GL_POINTS, 0, sampledMarkSize);
        //qDebug() << sampledMarkSize;
    }
    vaoSampledMark->release();

    programKTA->release();
}

void KTAGLData::addVOIMarkSlot(VOIMarkMessage msg)
{
    timeErase->stop();
    if (vboIndex == ktaCountMax) {
        vboIndex = 0;
        //vboRightLimit = 1;
    }

    const quint8 nDimensional = 5;

    GLfloat *currentPoint = new GLfloat[nDimensional];
    float dist = msg.D / 1000.,
          az = 90. - msg.Azm,
          ugm = msg.Ugm;
    if(az < 0) {
        az += 360;
    }
    else if (az >= 360) {
        az -= 360;
    }

    quint32 current_msec = QTime::currentTime().msecsSinceStartOfDay();

    auto duplicateKey = mapTime.find(current_msec);
    if (duplicateKey != mapTime.end()) {
        duplicateKey.value().push_back(vboIndex);
    }
    else {
        mapTime.insert(current_msec, QVector<quint32>({vboIndex}));
    }
    //mapTime.insert(current_msec, vboIndex);

    currentPoint[0] = dist * cosf(az * M_PI / 180.);
    currentPoint[1] = dist * sinf(az * M_PI / 180.);
    currentPoint[2] = depth + 0.5;//6.5f;/* + (dist * sinf(ugm * M_PI / 180.) / 200.);*///6.f;
    //currentPoint[3] = 1.;
    if (msg.flag_answer) {
        currentPoint[3] = 1.5;
    }
    else {
        currentPoint[3] = 1.;
    }

        /*if (msg.numSurv == 1) {
            currentPoint[3] = 1.;
        }
        else
            currentPoint[3] = 1.5;*/

    //currentPoint[3] = isPOI ? 0.5 : msg.numSurv;
    currentPoint[4] = current_msec;

    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      vboIndex * nDimensional * sizeof(GLfloat),
      nDimensional * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, currentPoint, sizeof(GLfloat) * nDimensional);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    delete [] currentPoint;

    quint32 eraseTime = current_msec - timeAlive_msec, realEraseTime = 0;
    auto iterMapTime = mapTime.lowerBound(eraseTime);
    if (iterMapTime != mapTime.end()) {
        if (iterMapTime.key() == eraseTime) {
            realEraseTime = iterMapTime.key();
            quint32 value = iterMapTime.value().back();
            if (value == ktaCountMax) {
                value = 0;
            }
            vboLeftLimit = value;

            auto iterForErase = mapTime.begin();
            while (iterForErase != iterMapTime) {
                iterForErase = mapTime.erase(iterForErase);
            }
        }
    }

    vboIndex++;
    vboRightLimit = vboIndex;

    timeErase->start(timeAlive_msec);
}

void KTAGLData::addPOIMarkSlot(POIKtaMessage msg)
{
    timeErase->stop();
    if (vboIndex == ktaCountMax) {
        vboIndex = 0;
        //vboRightLimit = 1;
    }

    const quint8 nDimensional = 5;

    GLfloat *currentPoint = new GLfloat[nDimensional];

    kta kta_loc = ktaFirst2ktaSecond(kta(0, msg.Amp, Polar(msg.D, msg.Az, msg.Um), msg.Vr));
    Coor3 coor = Polar2Coor3(kta_loc.Pol);
    Coor3 Coor = ChangeSistemCoor_L2G_AzUm_Fast(coor, msg.Az_ant, msg.Um_ant);
    kta_loc.Pol = Coor2Polar(Coor);

    quint32 current_msec = QTime::currentTime().msecsSinceStartOfDay();

    currentPoint[0] = kta_loc.Pol.D / 1000. * cos((90. - kta_loc.Pol.Az) * M_PI / 180.);//Coor.y / 1000;//dist * cosf(az * M_PI / 180.);
    currentPoint[1] = kta_loc.Pol.D / 1000. * sin((90. - kta_loc.Pol.Az) * M_PI / 180.);//Coor.x / 1000;//dist * sinf(az * M_PI / 180.);
    currentPoint[2] = depth;//6.f;/* + (dist * sinf(ugm * M_PI / 180.) / 200.);*///6.f;
    currentPoint[3] = 0.5;
    currentPoint[4] = current_msec;

    auto duplicateKey = mapTime.find(current_msec);
    if (duplicateKey != mapTime.end()) {
        duplicateKey.value().push_back(vboIndex);
    }
    else {
        mapTime.insert(current_msec, QVector<quint32>({vboIndex}));
    }
    //mapTime.insert(current_msec, vboIndex);



    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      vboIndex * nDimensional * sizeof(GLfloat),
      nDimensional * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, currentPoint, sizeof(GLfloat) * nDimensional);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    delete [] currentPoint;

    quint32 eraseTime = current_msec - timeAlive_msec, realEraseTime = 0;
    auto iterMapTime = mapTime.lowerBound(eraseTime);
    if (iterMapTime != mapTime.end()) {
        if (iterMapTime.key() == eraseTime) {
            realEraseTime = iterMapTime.key();
            quint32 value = iterMapTime.value().back();
            if (value == ktaCountMax) {
                value = 0;
            }
            vboLeftLimit = value;

            auto iterForErase = mapTime.begin();
            while (iterForErase != iterMapTime) {
                iterForErase = mapTime.erase(iterForErase);
            }
        }
    }

    vboIndex++;
    vboRightLimit = vboIndex;

    timeErase->start(timeAlive_msec);
}

void KTAGLData::eraseOldKTA()
{
    mapTime.clear();
    vboRightLimit++;
    vboLeftLimit = vboRightLimit;
    timeErase->stop();
}

void KTAGLData::eraseOldSampledKTA()
{
    sampledMarkSize = 0;
    timeEraseForSampledMark->stop();
}

void KTAGLData::setKTAColor(bool isPOI, const QColor color)
{
    if (isPOI) {
        ktaPOIColor = color;
    }
    else {
        ktaVOIColor = color;
    }
}

void KTAGLData::setKTASize(bool isPOI, const TextSizeAction flag, const float value)
{
    float *pValue = nullptr;
    if (isPOI) {
        pValue = &ktaPOISize;
    }
    else {
        pValue = &ktaVOISize;
    }

    switch(flag) {
        case Increas:
        case Decreas:  {
            *pValue += value;
            break;
        }
        case Reset:  {
            *pValue = value;
            break;
        }
    }
}

void KTAGLData::drawSampledMarkSlot(QSharedPointer< QVector<float> > array)
{
    timeEraseForSampledMark->stop();
    const quint8 nDimensional = 5;

    if (array.data()->size() > ktaCountMax * nDimensional) {
        sampledMarkSize = ktaCountMax;
    }
    else
        sampledMarkSize = array.data()->size() / nDimensional;

    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vboSampledMark->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      sampledMarkSize * nDimensional * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, array.data()->data(), sampledMarkSize * nDimensional * sizeof(GLfloat));
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    timeEraseForSampledMark->start(timeAlive_msec);
}

TraceGLData::TraceGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const Camera *m_extraCamera, float _depth, QObject *parent)  : QObject(parent),
    glFunc(func), camera_ptr(m_camera), extraCamera_ptr(m_extraCamera), depth(_depth),
    offsetForLogBook(100000), defaultLogBookSize(50,50), logBookSize(defaultLogBookSize),
    logBookColor(QColor::fromRgbF(0.5,0.5,0.5,0.6)),
    traceColor(QColor::fromRgbF(0.6,0.6,0.6,1.)),
    textColor(QColor::fromRgbF(0.60f,0.55f,0.09f,1)),
    textSize(0.075f),
    distOffsetForAzH(350.),
    maxVerticesOfTrack(2000), maxTrackNumber(10)
{
    qRegisterMetaType<RLSOaimMessage>();
    qRegisterMetaType<ResetTrackMessage>();

    programTrace = new QOpenGLShaderProgram(this);

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/trace2VertexShader.vert")) {
        qDebug() << programTrace->log();
        return;
    }

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/trace2FragmentShader.frag")) {
        qDebug() << programTrace->log();
        return;
    }

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/trace2GeometryShader.geom")) {
        qDebug() << programTrace->log();
        return;
    }
    if (!programTrace->link()) {
        qDebug() << programTrace->log();
        return;
    }

    programFont = new QOpenGLShaderProgram(this);

    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/sftVertexShader.vert")) {
        qDebug() << programFont->log();
        return;
    }

    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/sftFragmentShader.frag")) {
        qDebug() << programFont->log();
        return;
    }
    if (!programFont->link()) {
        qDebug() << programFont->log();
        return;
    }

    programLogBook  = new QOpenGLShaderProgram(this);

    if (!programLogBook->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/logBookVertexShader.vert")) {
        qDebug() << programLogBook->log();
        return;
    }

    if (!programLogBook->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/logBookFragmentShader.frag")) {
        qDebug() << programLogBook->log();
        return;
    }

    /*if (!programLogBook->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/logBookGeometryShader.geom")) {
        qDebug() << programLogBook->log();
        return;
    }*/

    if (!programLogBook->link()) {
        qDebug() << programLogBook->log();
        return;
    }


    programTrack  = new QOpenGLShaderProgram(this);

    if (!programTrack->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/trackVertexShader.vert")) {
        qDebug() << programTrack->log();
        return;
    }

    if (!programTrack->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/trackFragmentShader.frag")) {
        qDebug() << programTrack->log();
        return;
    }

    if (!programTrack->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/trackGeometryShader.geom")) {
        qDebug() << programTrack->log();
        return;
    }

    if (!programTrack->link()) {
        qDebug() << programTrack->log();
        return;
    }

    fontDriver = new ftCustomSimple(this);
    fontDriver->genTexels();

    setOfFreeBufferID = QSet<quint16>({0,1,2,3,4,5,6,7,8,9});

}

void TraceGLData::setSceneOptions(const SceneOptions *sOptions)
{
    sceneOptions = sOptions;
}

void TraceGLData::prepare()
{
    /*float zCoord = 5.;
    //trace element
    const quint8 nDimensional = 3;
    const quint8 circleSegmentation = 10;
    const quint8 vertexPerTriangle = 3;
    const float rad = 1.;
    float alphaGuide = 0;

    for (quint8 index = 0; index < 10; index++) {

        quint32 traceCircleBuffSize = nDimensional * vertexPerTriangle * circleSegmentation;
        GLfloat *traceCircleBuff = new GLfloat[traceCircleBuffSize];
        float deltaAlpha = 2. * M_PI / (float)(circleSegmentation);
        float alpha = 0;
        quint32 posArr = 0;
        for (quint8 index = 0; index != circleSegmentation; index++) {
            traceCircleBuff[posArr++] = 0.;
            traceCircleBuff[posArr++] = 0.;
            traceCircleBuff[posArr++] = zCoord;

            traceCircleBuff[posArr++] = rad * cos(alpha);
            traceCircleBuff[posArr++] = rad * sin(alpha);
            traceCircleBuff[posArr++] = zCoord;

            traceCircleBuff[posArr++] = rad * cos(alpha + deltaAlpha);
            traceCircleBuff[posArr++] = rad * sin(alpha + deltaAlpha);
            traceCircleBuff[posArr++] = zCoord;

            alpha += deltaAlpha;
        }

        //course element
        quint32 traceCourseBuffSize = nDimensional * vertexPerTriangle * 2;
        GLfloat *traceCourseBuff = new GLfloat[traceCourseBuffSize];
        OpenGLRectF courseRect(0, 0.5, 0.1, 2);
        calcRect(courseRect, traceCourseBuff, 0, zCoord);

        //guide line element

        float distOnTrace;
        if (index != 7) {
            distOnTrace = 50 + index * 10;
        }
        else {
            distOnTrace = 50;
        }

        quint32 traceGuideBuffSize = nDimensional * vertexPerTriangle * 2;
        GLfloat *traceGuideBuff = new GLfloat[traceGuideBuffSize];
        OpenGLRectF guideRect(rad * sqrt(2) / 2, rad * sqrt(2) / 2, 0.1, distOnTrace);
        calcRect(guideRect, traceGuideBuff, 0, zCoord, alphaGuide);

        //logbook element
        //QSize logBookSize(40,30);
        quint32 traceLogBookBuffSize = nDimensional * vertexPerTriangle * 2;
        GLfloat *traceLogBookBuff = new GLfloat[traceLogBookBuffSize];
        logBookRect.push_back( OpenGLRectF(guideRect.x() + guideRect.width() * cosf(alphaGuide * M_PI / 180.) - guideRect.height() * sinf(alphaGuide * M_PI / 180.),
                                           guideRect.y() + guideRect.height() * cosf(alphaGuide * M_PI / 180.) + guideRect.width() * sinf(alphaGuide * M_PI / 180.),
                                           logBookSize.width() - 2,
                                           logBookSize.height() - 2));
        calcRect(logBookRect.at(index), traceLogBookBuff, 0, zCoord);

        traceBuffSize = traceCircleBuffSize + traceCourseBuffSize + traceGuideBuffSize + traceLogBookBuffSize;

        vbo.push_back(new QOpenGLBuffer());
        vbo.at(index)->create();
        vbo.at(index)->bind();
        vbo.at(index)->setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.at(index)->allocate(traceCircleBuff, (traceCircleBuffSize + traceCourseBuffSize + traceGuideBuffSize + traceLogBookBuffSize) * sizeof(GLfloat));
        vbo.at(index)->write(traceCircleBuffSize * sizeof(GLfloat),
                          traceCourseBuff,
                          traceCourseBuffSize * sizeof(GLfloat));
        vbo.at(index)->write((traceCircleBuffSize + traceCourseBuffSize) * sizeof(GLfloat),
                          traceGuideBuff,
                          traceGuideBuffSize * sizeof(GLfloat));
        vbo.at(index)->write((traceCircleBuffSize + traceCourseBuffSize + traceGuideBuffSize) * sizeof(GLfloat),
                          traceLogBookBuff,
                          traceLogBookBuffSize * sizeof(GLfloat));

        vao.push_back(new QOpenGLVertexArrayObject());
        vao.at(index)->create();
        vao.at(index)->bind();
        if (!vao.at(index)->isCreated()){
            qDebug() << "Can't use VAO for font";
            return;
        }

        programTrace->enableAttributeArray("posAttr");
        programTrace->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

        vbo.at(index)->release();
        vao.at(index)->release();

        delete [] traceCircleBuff;
        delete [] traceCourseBuff;
        delete [] traceGuideBuff;
        delete [] traceLogBookBuff;

        alphaGuide -= 45;
        if (alphaGuide >= 360)
            alphaGuide -= 360;
        else if (alphaGuide < 0) {
            alphaGuide += 360;
        }

    }*/

    /*vaoFont = new QOpenGLVertexArrayObject();
    vaoFont->create();
    vaoFont->bind();
    if (!vaoFont->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    const quint16 sizeFontPoint = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 buffSizeInByte = sizeFontPoint * nDimensionalFont * sizeof(GLfloat);
    GLfloat fontVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0
    };
    GLfloat texelVertex[sizeFontPoint * nDimensionalFont]
            = { 0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f };

    vboFont = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboFont->create();
    vboFont->bind();
    vboFont->allocate(fontVertex, 2 * buffSizeInByte);
    vboFont->write(buffSizeInByte, texelVertex,buffSizeInByte);
    vboFont->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalFont, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, buffSizeInByte, nDimensionalFont, 0);

    vboFont->release();
    vaoFont->release();*/

}

void TraceGLData::render()
{
    const float distOffset = distOffsetForAzH;
    auto iter = mapTraceMark.begin();
    while (iter != mapTraceMark.end()) {
        float zcoord = depth;
        GLfloat aspect = sceneOptions->aspectRatio;
        QMatrix4x4 model;
        model.setToIdentity();
        const QVector3D scale = camera_ptr->viewMatrixScale();
        //model.scale(1. / scale.x(), 1. / scale.y());
        programTrace->bind();
        QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;
        programTrace->setUniformValue("mvp", mvp);
        programTrace->setUniformValue("zcoord", zcoord);
        programTrace->setUniformValue("aspect", aspect);
        programTrace->setUniformValue("course", iter.value().course);
        programTrace->setUniformValue("edge", iter.value().edge);
        programTrace->setUniformValue("objectColor", traceColor);

        quint8 index = 0;
        GLfloat *buffer = new GLfloat[2*3];
        buffer[index++] = iter.value().xPos;
        buffer[index++] = iter.value().yPos;
        buffer[index++] = zcoord;
        buffer[index++] = iter.value().guideLineEnd.x();
        buffer[index++] = iter.value().guideLineEnd.y();
        buffer[index++] = zcoord;

        tVbo->bind();
        tVbo->write(0, buffer, 2*3*sizeof (GLfloat));
        tVbo->release();

        tVao->bind();
        glFunc->glDrawArrays(GL_LINES,0,2);
        tVao->release();

        float azRad = (90. - iter.value().az) * degToRad;
        index = 0;
        buffer[index++] = distOffset * cos(azRad);
        buffer[index++] = distOffset * sin(azRad) + iter.value().h * 10;
        buffer[index++] = zcoord;
        buffer[index++] = iter.value().guideLineEnd.x();
        buffer[index++] = iter.value().guideLineEnd.y();
        buffer[index++] = zcoord - 2;

        tVbo->bind();
        tVbo->write(0, buffer, 2*3*sizeof (GLfloat));
        tVbo->release();

        tVao->bind();
        glFunc->glDrawArrays(GL_LINES,0,2);
        tVao->release();

        programTrace->release();

        delete [] buffer;

        if (iter.value().showTrack) {
            programTrack->bind();
            programTrack->setUniformValue("mvp", mvp);
            programTrack->setUniformValue("zcoord", zcoord);
            programTrack->setUniformValue("aspect", aspect);
            programTrack->setUniformValue("objectColor", traceColor);

            auto itemOfTrace = mapOfTraceTrack.find(iter.value().id);
            if (itemOfTrace != mapOfTraceTrack.end()) {
                int offsetOfTraceBuffer =  itemOfTrace.value().trackBufferId * maxVerticesOfTrack;

                trackVAO->bind();
                glFunc->glDrawArrays(GL_POINTS, offsetOfTraceBuffer, itemOfTrace.value().vectorOfTrackXY.size());
                trackVAO->release();
            }

            programTrack->release();
        }

        /*QPointF translateLogBook;
        QPointF scaleLogBook(1. / scale.x(), 1. / scale.y());
        if (scale.x() < 1)
            scaleLogBook = QPointF(1.f, 1.f);
        if (iter.value().edge == 0) {  //left bottom
            translateLogBook = QPointF(iter.value().guideLineEnd.x(),
                                       iter.value().guideLineEnd.y());
        }
        else if (iter.value().edge == 1) { //left top
            float yOffset = iter.value().guideLineEnd.y() - logBookSize.height();
            translateLogBook = QPointF(iter.value().guideLineEnd.x(),
                                       yOffset);
        }
        else if (iter.value().edge == 2) { //right top
            float xOffset = iter.value().guideLineEnd.x() - logBookSize.width(),
                  yOffset = iter.value().guideLineEnd.y() - logBookSize.height();
            translateLogBook = QPointF(xOffset,
                                       yOffset);
        }
        else if (iter.value().edge == 3) { //right bottom
            float xOffset = iter.value().guideLineEnd.x() - logBookSize.width();
            translateLogBook = QPointF(xOffset,
                                       iter.value().guideLineEnd.y());
        }*/

        model.translate(iter.value().logBookPosition.column * logBookSize.width(),
                        iter.value().logBookPosition.row * logBookSize.height());
        //model.translate(translateLogBook.x(), translateLogBook.y());
        //if (scale.x() > 1)
        //    model.scale(1. / scale.x(), 1. / scale.y());
        mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;

        programLogBook->bind();
        programLogBook->setUniformValue("mvp", mvp);
        programLogBook->setUniformValue("zcoord", zcoord);
        programLogBook->setUniformValue("objectColor", logBookColor);

        tVao2->bind();
        glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
        tVao2->release();

        programLogBook->release();

        zcoord += 0.15;
        programFont->bind();
        programFont->setUniformValue("mvp", mvp);
        programFont->setUniformValue("zcoord", zcoord);
        programFont->setUniformValue("textureColor", QVector3D(0.60f,0.55f,0.09f));

        programFont->setUniformValue("texture0", 0);
        glFunc->glActiveTexture(GL_TEXTURE0);
        vaoFont->bind();

        quint16 id = iter.key();
        const TraceMark &mark = iter.value();

        QVector<QString> vecOfStr;
        //vecOfStr.push_back(QString(" #00%1 П Д20").arg(id));
        vecOfStr.push_back(QString(" #%1").arg(id));
        vecOfStr.push_back(QString(" %1км").arg(mark.dist, 0, 'f', 2));
        vecOfStr.push_back(QString(" %1°").arg(mark.az, 0, 'f', 1));
        vecOfStr.push_back(QString(" %1км").arg(mark.h, 0, 'f', 3));
        vecOfStr.push_back(QString(" %1м/с").arg(mark.speed, 0, 'f', 2));

        float heightOfText = logBookSize.height() / vecOfStr.size();
        //qDebug() << logBookSize.height() << heightOfText;
        QVector<QPointF> vecOfPoint;
        for (quint16 index = 0; index < vecOfStr.size(); index++) {
            /*vecOfPoint.push_back(QPointF(logBookRect.at(indexBuff).x(),
                                         logBookRect.at(indexBuff).y() + logBookRect.at(indexBuff).height() - (heightOfText * (index + 1)) + 2));*/
            vecOfPoint.push_back(QPointF(0, logBookSize.height()  - (heightOfText * (index + 1)) + (index * heightOfText * 0.1) ));
        }

        float currentFontSize = textSize;
        if (scale.x() > 1)
            currentFontSize = textSize * (1. / scale.x());
        for (quint16 indexV = 0; indexV < vecOfStr.size(); indexV++) {
            const quint16 oneBuffSize = 6 * 2;
            const quint16 oneBuffSizeInByte = oneBuffSize * sizeof(GLfloat);
            GLfloat *vertBuff = new GLfloat[vecOfStr.at(indexV).size() * oneBuffSize];
            sVectorCharacterId charId = fontDriver->genText(vecOfStr.at(indexV),
                                                            vecOfPoint.at(indexV).x(),
                                                            vecOfPoint.at(indexV).y(),
                                                            currentFontSize,
                                                            vertBuff);

            int index = 0;
            for (auto &texture : charId) {
                /*if (indexV == 0 && index > 4) {
                    programFont->setUniformValue("textureColor", QVector3D(0.81f,0.05f,0.09f));
                }
                else {
                    programFont->setUniformValue("textureColor", QVector3D(0.60f,0.55f,0.09f));
                }*/
                texture->bind();
                vboFont->bind();
                vboFont->write(0, (vertBuff + index * oneBuffSize), oneBuffSizeInByte);
                vboFont->release();

                glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
                texture->release();
                index++;
            }

            delete [] vertBuff;
        }

        vaoFont->release();
        programFont->release();

        iter++;
    }
    /*float zcoord = 8.0;
    quint8 indexBuff = 0;
    auto iter = mapTraceMark.begin();
    while (iter != mapTraceMark.end()) {

        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(iter.value().xPos,iter.value().yPos);
        const QVector3D scale = camera_ptr->viewMatrixScale();
        model.scale(1. / scale.x(), 1. / scale.y());
        programTrace->bind();
        QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;
        programTrace->setUniformValue("mvp", mvp);
        programTrace->setUniformValue("zcoord", zcoord);

        vao.at(indexBuff)->bind();
        glFunc->glDrawArrays(GL_TRIANGLES, 0, traceBuffSize / 3);
        vao.at(indexBuff)->release();
        programTrace->release();

        zcoord += 0.15;
        programFont->bind();
        programFont->setUniformValue("mvp", mvp);
        programFont->setUniformValue("zcoord", zcoord);
        programFont->setUniformValue("textureColor", QVector3D(0.60f,0.55f,0.09f));

        programFont->setUniformValue("texture0", 0);
        glFunc->glActiveTexture(GL_TEXTURE0);
        vaoFont->bind();

        quint16 id = iter.key();
        const TraceMark &mark = iter.value();        

        QVector<QString> vecOfStr;
        vecOfStr.push_back(QString("#%1").arg(id));
        vecOfStr.push_back(QString("%1°/%2км").arg(mark.az, 0, 'f', 2).arg(mark.dist, 0, 'f', 2));
        vecOfStr.push_back(QString("%1км").arg(mark.h, 0, 'f', 3));
        vecOfStr.push_back(QString("%1м/с").arg(mark.speed, 0, 'f', 2));

        float heightOfText = logBookRect.at(indexBuff).height() / vecOfStr.size();
        QVector<QPointF> vecOfPoint;
        for (quint16 index = 0; index < vecOfStr.size(); index++) {
            vecOfPoint.push_back(QPointF(logBookRect.at(indexBuff).x(), logBookRect.at(indexBuff).y() + logBookRect.at(indexBuff).height() - (heightOfText * (index + 1)) + 2));
        }

        for (quint16 indexV = 0; indexV < vecOfStr.size(); indexV++) {
            const quint16 oneBuffSize = 6 * 2;
            const quint16 oneBuffSizeInByte = oneBuffSize * sizeof(GLfloat);
            GLfloat *vertBuff = new GLfloat[vecOfStr.at(indexV).size() * oneBuffSize];
            sVectorCharacterId charId = fontDriver->genText(vecOfStr.at(indexV),
                                                            vecOfPoint.at(indexV).x(),
                                                            vecOfPoint.at(indexV).y(),
                                                            0.05f,
                                                            vertBuff);

            int index = 0;
            for (auto &texture : charId) {
                texture->bind();
                vboFont->bind();
                vboFont->write(0, (vertBuff + index * oneBuffSize), oneBuffSizeInByte);
                vboFont->release();

                glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
                texture->release();
                index++;
            }

            delete [] vertBuff;
        }

        vaoFont->release();
        programFont->release();

        iter++;
        zcoord += 0.15;
        indexBuff++;
    }*/

    /*QMatrix4x4 model;
    model.setToIdentity();
    const QVector3D scale = camera_ptr->viewMatrixScale();
    model.scale(1. / scale.x(), 1. / scale.y());
    programTrace->bind();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;
    programTrace->setUniformValue("mvp", mvp);
    programTrace->setUniformValue("zcoord", zcoord);

    tVao->bind();
    glFunc->glDrawArrays(GL_TRIANGLES, 0, traceBuffSize / 3);
    tVao->release();
    programTrace->release();*/
}

void TraceGLData::renderHAz()
{
    const float distOffset = 350.;
    auto iter = mapTraceMark.begin();
    while (iter != mapTraceMark.end()) {
        float zcoord = depth;
        GLfloat aspect = sceneOptions->aspectRatio;
        QMatrix4x4 model;
        model.setToIdentity();
        const QVector3D scale = camera_ptr->viewMatrixScale();
        //model.scale(1. / scale.x(), 1. / scale.y());
        programTrace->bind();
        QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;
        programTrace->setUniformValue("mvp", mvp);
        programTrace->setUniformValue("zcoord", zcoord);
        programTrace->setUniformValue("aspect", aspect);
        programTrace->setUniformValue("course", iter.value().course);
        programTrace->setUniformValue("edge", iter.value().edge);
        programTrace->setUniformValue("objectColor", traceColor);

        float azRad = (90. - iter.value().az) * degToRad;
        quint8 index = 0;
        GLfloat *buffer = new GLfloat[2*3];
        buffer[index++] = distOffset * cos(azRad);
        buffer[index++] = distOffset * sin(azRad) + iter.value().h * 10;
        buffer[index++] = zcoord;
        buffer[index++] = iter.value().guideLineEnd.x();
        buffer[index++] = iter.value().guideLineEnd.y();
        buffer[index++] = zcoord;

        tVbo->bind();
        tVbo->write(0, buffer, 2*3*sizeof (GLfloat));
        tVbo->release();

        tVao->bind();
        glFunc->glDrawArrays(GL_LINES,0,2);
        tVao->release();

        programTrace->release();

        delete [] buffer;

        /*

        //model.translate(iter.value().logBookPosition.column * logBookSize.width(),
        //                iter.value().logBookPosition.row * logBookSize.height());
        model.translate(distOffset * cos(azRad) + 50, distOffset * sin(azRad) + iter.value().h * 10 + 50);
        //model.translate(translateLogBook.x(), translateLogBook.y());
        //if (scale.x() > 1)
        //    model.scale(1. / scale.x(), 1. / scale.y());
        mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;

        programLogBook->bind();
        programLogBook->setUniformValue("mvp", mvp);
        programLogBook->setUniformValue("zcoord", zcoord);
        programLogBook->setUniformValue("objectColor", logBookColor);

        tVao2->bind();
        glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
        tVao2->release();

        programLogBook->release();

        zcoord += 0.15;
        programFont->bind();
        programFont->setUniformValue("mvp", mvp);
        programFont->setUniformValue("zcoord", zcoord);
        programFont->setUniformValue("textureColor", QVector3D(0.60f,0.55f,0.09f));

        programFont->setUniformValue("texture0", 0);
        glFunc->glActiveTexture(GL_TEXTURE0);
        vaoFont->bind();

        quint16 id = iter.key();
        const TraceMark &mark = iter.value();

        QVector<QString> vecOfStr;
        vecOfStr.push_back(QString(" #%1").arg(id));
        vecOfStr.push_back(QString(" %1км").arg(mark.dist, 0, 'f', 2));
        vecOfStr.push_back(QString(" %1°").arg(mark.az, 0, 'f', 1));
        vecOfStr.push_back(QString(" %1км").arg(mark.h, 0, 'f', 3));
        vecOfStr.push_back(QString(" %1м/с").arg(mark.speed, 0, 'f', 2));

        float heightOfText = logBookSize.height() / vecOfStr.size();
        //qDebug() << logBookSize.height() << heightOfText;
        QVector<QPointF> vecOfPoint;
        for (quint16 index = 0; index < vecOfStr.size(); index++) {

            vecOfPoint.push_back(QPointF(0, logBookSize.height()  - (heightOfText * (index + 1)) + (index * heightOfText * 0.1) ));
        }

        float currentFontSize = textSize;
        if (scale.x() > 1)
            currentFontSize = textSize * (1. / scale.x());
        for (quint16 indexV = 0; indexV < vecOfStr.size(); indexV++) {
            const quint16 oneBuffSize = 6 * 2;
            const quint16 oneBuffSizeInByte = oneBuffSize * sizeof(GLfloat);
            GLfloat *vertBuff = new GLfloat[vecOfStr.at(indexV).size() * oneBuffSize];
            sVectorCharacterId charId = fontDriver->genText(vecOfStr.at(indexV),
                                                            vecOfPoint.at(indexV).x(),
                                                            vecOfPoint.at(indexV).y(),
                                                            currentFontSize,
                                                            vertBuff);

            int index = 0;
            for (auto &texture : charId) {
                texture->bind();
                vboFont->bind();
                vboFont->write(0, (vertBuff + index * oneBuffSize), oneBuffSizeInByte);
                vboFont->release();

                glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
                texture->release();
                index++;
            }

            delete [] vertBuff;
        }

        vaoFont->release();
        programFont->release();*/

        iter++;
    }
}

void TraceGLData::addTraceMark(RLSOaimMessage msg)
{
    quint16 id = static_cast<quint32>(msg.trackID);
    auto iter = mapTraceMark.find(id);
    if (iter != mapTraceMark.end()) {
        TraceMark mark = iter.value();

        mark.id = id;
        mark.az = msg.Az;
        mark.dist = msg.D / 1000.;//sqrt(pow(msg.D / 1000., 2) - pow(msg.sAimCoords.h / 1000., 2));
        mark.course = msg.tack;
        mark.speed = msg.vp;
        mark.h = msg.h / 1000.;
        mark.xPos = mark.dist * cosf((90 - mark.az) * M_PI / 180.);
        mark.yPos = mark.dist * sinf((90 - mark.az) * M_PI / 180.);

        //mark.logBookPosition = iter.value().logBookPosition;

        putTraceOnScene(mark, false);
        calcGuideLinePoint(mark);

        iter = mapTraceMark.insert(id, mark);

        //if (mark.priority == 1)
        //    emit traceInfoToExtraWindow(id, msg.h);
    }
    else {
        /*if (mapTraceMark.size() == 10){
            qDebug() << "Too much trace number";
            return;
        }*/

        TraceMark mark;

        mark.id = id;
        mark.az = msg.Az;
        mark.dist = msg.D / 1000.;//sqrt(pow(msg.D / 1000., 2) - pow(msg.sAimCoords.h / 1000., 2));
        mark.course = msg.tack;
        mark.speed = msg.vp;
        mark.h = msg.h / 1000.;
        mark.xPos = mark.dist * cosf((90. - mark.az) * M_PI / 180.);
        mark.yPos = mark.dist * sinf((90. - mark.az) * M_PI / 180.);

        iter = mapTraceMark.insert(id, mark);
        putTraceOnScene(mark, true);
        calcGuideLinePoint(iter.value());
    }

    /*TrackMark mark2;
    float azRad = (90. - iter.value().az) * degToRad;
    mark2.pos = QPointF(iter.value().xPos, iter.value().yPos);
    mark2.course = iter.value().course;
    mark2.posExtended = QPointF(distOffsetForAzH * cos(azRad),
                                distOffsetForAzH * sin(azRad) + iter.value().h * 10);*/
    QVector3D mark2(iter.value().xPos, iter.value().yPos, iter.value().course);
    auto itemOfTrack = mapOfTraceTrack.find(id);
    if (itemOfTrack != mapOfTraceTrack.end()) {
        if (itemOfTrack.value().vectorOfTrackXY.size() == maxVerticesOfTrack) {
            if ((itemOfTrack.value().currentPositionInVector + 1) == maxVerticesOfTrack) {
                itemOfTrack.value().currentPositionInVector = 0;
            }
            else {
                itemOfTrack.value().currentPositionInVector++;
            }
            itemOfTrack.value().vectorOfTrackXY.replace(itemOfTrack.value().currentPositionInVector,
                                                        mark2);
        }
        else {
            itemOfTrack.value().vectorOfTrackXY.push_back(mark2);
            itemOfTrack.value().currentPositionInVector++;
        }


        if (iter.value().showTrack) {
            QVector3D vector(itemOfTrack.value().vectorOfTrackXY.at(itemOfTrack.value().currentPositionInVector));
            GLfloat *bufferForOneTrace = new GLfloat[3];
            bufferForOneTrace[0] = vector.x();
            bufferForOneTrace[1] = vector.y();
            bufferForOneTrace[2] = vector.z();

            trackVBO->bind();
            trackVBO->write((maxVerticesOfTrack * itemOfTrack.value().trackBufferId + itemOfTrack.value().currentPositionInVector) * 3 * sizeof(GLfloat),
                            bufferForOneTrace, 3 * sizeof(GLfloat));
            trackVBO->release();
        }
    }
    else {
        TrackMarkInfo info;
        info.trackBufferId = maxTrackNumber;
        info.vectorOfTrackXY.push_back(mark2);
        info.currentPositionInVector = 0;
        mapOfTraceTrack.insert(id, info);
    }


}


void TraceGLData::eraseOldTrace(quint32 idTrace)
{
    auto iterTrace = mapTraceMark.find(idTrace);
    if (iterTrace != mapTraceMark.end()) {
        auto iterGride = grideOfTraceMark.find(iterTrace.value().tracePosition);
        if (iterGride != grideOfTraceMark.end()) {
            auto iterIdTrace = iterGride.value().find(iterTrace->id);
            if (iterIdTrace != iterGride.value().end()) {
                iterGride.value().erase(iterIdTrace);
                if (iterGride.value().size() == 0){
                    grideOfTraceMark.erase(iterGride);
                }
            }
            else {
                qDebug() << "Missing trace on cell";
            }
        }
        else {
            qDebug() << "Missing cell(trace) to delete in grideOfTraceMark";
        }

        iterGride = grideOfTraceMark.find(iterTrace.value().logBookPosition);
        if (iterGride != grideOfTraceMark.end()) {
            auto iterIdLogBook = iterGride.value().find(iterTrace->id + offsetForLogBook);
            if (iterIdLogBook != iterGride.value().end()) {
                iterGride.value().erase(iterIdLogBook);
                if (iterGride.value().size() == 0){
                    grideOfTraceMark.erase(iterGride);
                }
            }
            else {
                qDebug() << "Missing logBook on cell";
            }
        }
        else {
            qDebug() << "Missing cell(logBook) to delete in grideOfTraceMark";
        }
        auto itemOfTrack = mapOfTraceTrack.find(idTrace);
        if (itemOfTrack != mapOfTraceTrack.end()) {
            if (iterTrace.value().showTrack) {
                setOfFreeBufferID.insert(itemOfTrack.value().trackBufferId);
                mapOfTraceTrack.erase(itemOfTrack);
            }
        }
        mapTraceMark.erase(iterTrace);
    }
    else {
        qDebug() << "Missing trace to delete in mapTraceMark";
    }
}

void TraceGLData::setLogBookColor(const QColor color)
{
    logBookColor = color;
}

void TraceGLData::setTraceColor(const QColor color)
{
    traceColor = color;
}

void TraceGLData::setTextColor(const QColor color)
{
    textColor = color;
}

void TraceGLData::setTextSize(const TextSizeAction flag, const float value)
{
    switch(flag) {
        case Increas:
        case Decreas:  {
            textSize += value;
            break;
        }
        case Reset:  {
            textSize = value;
            break;
        }
    }
}

void TraceGLData::drawTrace(quint32 id, bool isDrawing)
{
    auto iterOfMapOfTrack = mapTraceMark.find(id);
    if (iterOfMapOfTrack != mapTraceMark.end()) {
        iterOfMapOfTrack.value().showTrack = isDrawing;
        auto itemOfMapTrace = mapOfTraceTrack.find(id);
        if (itemOfMapTrace == mapOfTraceTrack.end()) {
            qDebug() << "TraceGLData::drawTrack - Cant find item in mapOfTraceTrack";
            return;
        }
        if (isDrawing) {
            if (setOfFreeBufferID.isEmpty()) {
                itemOfMapTrace.value().trackBufferId = maxTrackNumber;
                iterOfMapOfTrack.value().showTrack = false;
                emit trackDrawingReset();
            }
            else {
                auto itemOfSet = setOfFreeBufferID.begin();
                itemOfMapTrace.value().trackBufferId = *itemOfSet;
                setOfFreeBufferID.erase(itemOfSet);

                trackVBO->bind();
                trackVBO->write(itemOfMapTrace.value().trackBufferId * maxVerticesOfTrack * 3 * sizeof(GLfloat),
                                itemOfMapTrace.value().vectorOfTrackXY.constData(),
                                itemOfMapTrace.value().vectorOfTrackXY.size() * 3 * sizeof(GLfloat));
                trackVBO->release();
            }
        }
        else {
            if (itemOfMapTrace.value().trackBufferId != maxTrackNumber){
                setOfFreeBufferID.insert(itemOfMapTrace.value().trackBufferId);
                itemOfMapTrace.value().trackBufferId = maxTrackNumber;
            }
        }
    }
}

void TraceGLData::reCalcAllTrace()
{
    const QVector3D scale = camera_ptr->viewMatrixScale();
    if (scale.x() > 1) {
        logBookSize.setWidth(defaultLogBookSize.width() * (1 / scale.x()));
        logBookSize.setHeight(defaultLogBookSize.height() * (1 / scale.y()));
    }
    else {
        logBookSize = defaultLogBookSize;
    }

    grideOfTraceMark.clear();
    for (auto &mark : mapTraceMark) {
        putTraceOnScene(mark, true);
        calcGuideLinePoint(mark);
    }

    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerQuad = 2;
    const quint8 pointPerQuad = nDimensional * vertexPerTriangle * trianglePerQuad;
    float zCoord = 10.;
    GLfloat *bufferLogBook = new GLfloat[pointPerQuad];
    OpenGLRectF rect(0, 0, logBookSize.width(), logBookSize.height());
    calcRect(rect, bufferLogBook, 0, zCoord);
    tVbo2->bind();
    tVbo2->write(0, bufferLogBook, pointPerQuad * sizeof (GLfloat));
    tVbo2->release();
}

/*void TraceGLData::interactiveActionsWithTrack(quint32 id, ActionsWithTrack action, quint32 addParameter)
{
    if (action == ActionsWithTrack::Delete) {
        //eraseOldTrace(id);

        DeleteTrackMessage msg;
        msg.aimID = id;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_11);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(RMO_VOI_TRACK_DELETE_MESSAGE);
        out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        emit msgToVOI(arr);
        qDebug() << "RMO_VOI_TRACK_DELETE_MESSAGE";
    }
    else if (action == ActionsWithTrack::Priority) {
        quint8 trackPriority = 0;
        auto iterOfMapOfTrack = mapTraceMark.find(id);
        if (iterOfMapOfTrack != mapTraceMark.end()) {
            if (addParameter == 2) {
                if (iterOfMapOfTrack.value().priority == 0) {
                    iterOfMapOfTrack.value().priority = 1;
                    trackPriority = iterOfMapOfTrack.value().priority;
                }
                else if (iterOfMapOfTrack.value().priority == 1) {
                    iterOfMapOfTrack.value().priority = 0;
                    trackPriority = iterOfMapOfTrack.value().priority;
                }
            }
            else {
                iterOfMapOfTrack.value().priority = addParameter;
            }
        }
        else
            return;

        RMOSetTrackPriority msg;
        msg.aimID = id;
        msg.priority = trackPriority;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_11);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(RMO_VOI_TRACK_PRIORITY_MESSAGE);
        out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        emit msgToVOI(arr);
        qDebug() << "RMO_VOI_TRACK_PRIORITY_MESSAGE";

        //if (iterOfMapOfTrack.value().priority == 1) {
        //    emit addExtraWindowSignal(id);
        //}
    }
    else if (action == ActionsWithTrack::Trace) {
        auto iterOfMapOfTrack = mapTraceMark.find(id);
        if (iterOfMapOfTrack != mapTraceMark.end()) {
            if (!iterOfMapOfTrack.value().showTrack) {
                for (auto &item : mapTraceMark) {
                    item.showTrack = false;
                }
            }
            iterOfMapOfTrack.value().showTrack = !iterOfMapOfTrack.value().showTrack;            
            if (iterOfMapOfTrack.value().showTrack) {
                initTrackBuffer(iterOfMapOfTrack.value().id);
            }
        }
    }
}*/

void TraceGLData::calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord, float alpha)
{
    //if (alpha > 0) {
        float sinA = sinf(alpha * M_PI / 180.),
              cosA = cosf(alpha * M_PI / 180.);
        *(array + counter) = rect.x();
        counter++;
        *(array + counter) = rect.y();
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() + rect.width() * cosA;
        counter++;
        *(array + counter) = rect.y() + rect.width() * sinA;
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() - rect.height() * sinA;
        counter++;
        *(array + counter) = rect.y() + rect.height() * cosA;
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() + rect.width() * cosA;
        counter++;
        *(array + counter) = rect.y() + rect.width() * sinA;
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() + rect.width() * cosA - rect.height() * sinA;
        counter++;
        *(array + counter) = rect.y() + rect.height() * cosA + rect.width() * sinA;
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() - rect.height() * sinA;
        counter++;
        *(array + counter) = rect.y() + rect.height() * cosA;
        counter++;
        *(array + counter) = zcoord;
        counter++;
    /*}
    else {

        //int counter = 0;
        //(left;bottom) - (right;bottom) - (left;top) CCW
        *(array + counter) = rect.x();
        counter++;
        *(array + counter) = rect.y();
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() + rect.width();
        counter++;
        *(array + counter) = rect.y();
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x();
        counter++;
        *(array + counter) = rect.y() + rect.height();
        counter++;
        *(array + counter) = zcoord;
        counter++;

        //(right;bottom) - (right;top) - (left;top)
        *(array + counter) = rect.x() + rect.width();
        counter++;
        *(array + counter) = rect.y();
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x() + rect.width();
        counter++;
        *(array + counter) = rect.y() + rect.height();
        counter++;
        *(array + counter) = zcoord;
        counter++;

        *(array + counter) = rect.x();
        counter++;
        *(array + counter) = rect.y() + rect.height();
        counter++;
        *(array + counter) = zcoord;
        counter++;
        //qDebug() << counter;

    }*/
}

qint32 TraceGLData::getIdByCoordinates(QPointF point)
{
    ColumnRow posInTable(point.x() / logBookSize.width(),
                 point.y() / logBookSize.height()); //Вычисляю ячейку для трассы
    if (point.x() < 0) {
        posInTable.column--;
    }
    if (point.y() < 0) {
        posInTable.row--;
    }

    auto iterGride = grideOfTraceMark.find(posInTable);
    if (iterGride != grideOfTraceMark.end()){
        auto iterOfIdMapInGride = iterGride.value().begin();
        if (iterOfIdMapInGride.key() >= offsetForLogBook) {
            return (iterOfIdMapInGride.key() - offsetForLogBook);
        }
        else
            return -1;
    }
    else {
        return -1;
    }
}

void TraceGLData::putTraceOnScene(TraceMark &mark, bool isNewTrace)
{
    if (isNewTrace) {// трасса уже добавлена в карту трасс. редактировать объект mark безопасно
        ColumnRow point(mark.xPos / logBookSize.width(),
                     mark.yPos / logBookSize.height()); //Вычисляю ячейку для трассы
        if (mark.xPos < 0) {
            point.column--;
        }
        if (mark.yPos < 0) {
            point.row--;
        }
        auto iterGride = grideOfTraceMark.find(point); //Ищу другие вхождения в эту ячейку
        auto iterTrace = mapTraceMark.find(mark.id);
        if (iterGride != grideOfTraceMark.end()) {
            iterGride.value().insert(mark.id, 0); //Добавить трассу
            //auto iterTrace = mapTraceMark.find(mark.id);
            //if (iterTrace != mapTraceMark.end()) {
                iterTrace.value().tracePosition = point;     //Обновил позицию трассы
            //}
            //else {
            //    qDebug() << "Trace not insert in mapTraceMark";
            //}
            auto iterLogBook = iterGride.value().lowerBound(offsetForLogBook); //Если есть вхождения, то посмотреть есть ли формуляры
            if (iterLogBook != iterGride.value().end()) {
                auto iterOldTrace = mapTraceMark.find(iterLogBook.key() - offsetForLogBook);
                if (iterOldTrace != mapTraceMark.end()) {
                    findPlaceForLogBook(iterOldTrace.value()); //Если есть, то искать другое место для формуляра
                    calcGuideLinePoint(iterOldTrace.value());
                    iterGride.value().erase(iterLogBook); //Удалить из этой ячейки формуляр
                }
                else {
                    qDebug() << "Trace not found in mapTraceMark";
                }
            }
            //if (iterTrace != mapTraceMark.end()) {
                findPlaceForLogBook(iterTrace.value()); //Добавить формуляр
            //}
            //else {
            //    qDebug() << "Trace not insert in mapTraceMark";
            //}
        }
        else {
            QMap<quint32, quint8> tMap; //Если нет вхождений, то просто добавть трассу
            tMap.insert(mark.id,0);
            grideOfTraceMark.insert(point, tMap);
            /*if (grideOfTraceMark.size() > 2) {
                qDebug() << "Somethink wrong";
            }*/
            //auto iterTrace = mapTraceMark.find(mark.id);
            //if (iterTrace != mapTraceMark.end()) {
                iterTrace.value().tracePosition = point;     //Обновил позицию трассы
                findPlaceForLogBook(iterTrace.value()); //Добавить формуляр
            //}
            //else {
            //    qDebug() << "Trace not insert in mapTraceMark";
            //}
        }

        //calcGuideLinePoint(iterTrace.value());

    }
    else { //ОСТОРОЖНО: В КАРТЕ mapTraceMark лежит старое значение трассы и оно будет заменено в итоге mark
        auto iterTrace = mapTraceMark.find(mark.id);
        if (iterTrace != mapTraceMark.end()) {
            ColumnRow point(mark.xPos / logBookSize.width(),
                         mark.yPos / logBookSize.height()); //Вычисляю ячейку для трассы
            if (mark.xPos < 0) {
                point.column--;
            }
            if (mark.yPos < 0) {
                point.row--;
            }
            if (iterTrace.value().tracePosition != point) { //Смотрю, трасса была записана в туже ячейку
                //Действия со старой позицией трассы
                auto iterPosOldTrace = grideOfTraceMark.find(iterTrace.value().tracePosition); //Ищу ячейку со старой позицией трассы
                if (iterPosOldTrace != grideOfTraceMark.end()) {
                    auto iterValuePosOldTrace = iterPosOldTrace->find(mark.id); //Если есть такая ячейка, то ищу текущий id
                    if (iterValuePosOldTrace != iterPosOldTrace->end()) {
                        iterPosOldTrace.value().erase(iterValuePosOldTrace); //Если есть такой id, то удаляю
                        if (iterPosOldTrace.value().size() == 0) {
                            grideOfTraceMark.erase(iterPosOldTrace); //Проверю на пустую карту id для текущей ячейки
                        }
                    }
                    else {
                        qDebug() << "Cant find trackId in value map of grideOfTraceMark";
                    }
                }
                else {
                    qDebug() << "Cant find old cell in grideOfTraceMark";
                }
                //Действия со новой позицией трассы
                bool forcedChangeOfPositionFlag = false;
                auto iterPosNewTrace = grideOfTraceMark.find(point); //Ищу ячейку со новой позицией трассы
                if (iterPosNewTrace != grideOfTraceMark.end()) {
                    iterPosNewTrace.value().insert(mark.id, 0); //Добавить трассу в ячейку
                    mark.tracePosition = point;     //Обновил позицию трассы
                    auto iterLogBook = iterPosNewTrace.value().upperBound(offsetForLogBook - 1); //Если есть вхождения, то посмотреть есть ли формуляры
                    if (iterLogBook != iterPosNewTrace.value().end()) {
                        quint32 oldLogBookId = iterLogBook.key() - offsetForLogBook;
                        if (oldLogBookId != mark.id) {
                            auto iterOldLogBook = mapTraceMark.find(oldLogBookId);
                            if (iterOldLogBook != mapTraceMark.end()) {
                                findPlaceForLogBook(iterOldLogBook.value()); //Если есть, то искать другое место для формуляра
                                calcGuideLinePoint(iterOldLogBook.value());
                                iterPosNewTrace.value().erase(iterLogBook); //Удалить из этой ячейки формуляр
                            }
                            else {
                                qDebug() << "Trace not found in mapTraceMark";
                            }
                        }
                        else {
                            forcedChangeOfPositionFlag = true;
                        }
                    }
                }
                else {
                    QMap<quint32, quint8> tMap; //Если нет вхождений, то просто добавть трассу
                    tMap.insert(mark.id,0);
                    grideOfTraceMark.insert(point, tMap);
                    /*if (grideOfTraceMark.size() > 2) {
                        qDebug() << "Somethink wrong";
                    }*/
                    mark.tracePosition = point;     //Обновил позицию трассы
                }

                if (forcedChangeOfPositionFlag ||
                   (abs(mark.logBookPosition.row - mark.tracePosition.row) > 1) ||
                   (abs(mark.logBookPosition.column - mark.tracePosition.column) > 1)) {

                    auto iterOldPositionLogBook = grideOfTraceMark.find(mark.logBookPosition);
                    if (iterOldPositionLogBook != grideOfTraceMark.end()){
                        auto iterOldPositionLogBookId = iterOldPositionLogBook.value().find(offsetForLogBook + mark.id);
                        if (iterOldPositionLogBookId != iterOldPositionLogBook.value().end()){
                            iterOldPositionLogBook.value().erase(iterOldPositionLogBookId);
                            if (iterOldPositionLogBook.value().size() == 0) {
                                grideOfTraceMark.erase(iterOldPositionLogBook);
                            }
                        }
                        else {
                            qDebug() << "Cant find id in old position of logBook";
                        }

                    }
                    else {
                        qDebug() << "Cant find old position of logBook";
                    }

                    findPlaceForLogBook(mark); //Добавить формуляр
                }

                //calcGuideLinePoint(mark);
            }
            else {
                mark.tracePosition = iterTrace.value().tracePosition;
                //calcGuideLinePoint(mark);
            }
        }
        else {
            qDebug() << "Cant find traceId in mapTraceMark";
        }
    }
}

void TraceGLData::findPlaceForLogBook(TraceMark &mark)
{
    ColumnRow startPlace = mark.tracePosition;
    qint16 iterationLimit = 10000;

    quint16 numberOfPasses = 1;
    bool plus = true;
    while (iterationLimit > 0) {
        bool exit = false;
        for (quint16 index = 0; index != numberOfPasses; index++) {
            plus ? startPlace.column++ : startPlace.column--;
            iterationLimit--;

            auto iter = grideOfTraceMark.find(startPlace);
            if (iter == grideOfTraceMark.end()) {
                exit = true;
                break;
            }
        }
        if (exit)
            break;

        for (quint16 index = 0; index != numberOfPasses; index++) {
            plus ? startPlace.row++ : startPlace.row--;
            iterationLimit--;

            auto iter = grideOfTraceMark.find(startPlace);
            if (iter == grideOfTraceMark.end()) {
                exit = true;
                break;
            }
        }
        if (exit)
            break;

        plus = !plus;
        numberOfPasses++;
        //qDebug() << iterationLimit;
    }

    if (iterationLimit > 0) {

        QMap<quint32, quint8> tMap;
        tMap.insert(offsetForLogBook + mark.id,0);
        grideOfTraceMark.insert(startPlace, tMap);
        /*if (grideOfTraceMark.size() > 2) {
            qDebug() << "Somethink wrong";
        }*/
        mark.logBookPosition = startPlace;

        //calcGuideLinePoint(mark);
    }
    else {
        qDebug() << "Cant find a free place for logbook";
    }

}

void TraceGLData::calcGuideLinePoint(TraceMark &mark)
{
    qint16 dRow = mark.logBookPosition.row - mark.tracePosition.row,
           dColumn = mark.logBookPosition.column - mark.tracePosition.column;
    QVector3D scale = camera_ptr->viewMatrixScale();
    if (scale.x() < 1) {
        scale = QVector3D(1.0, 1.0, 1.0);
    }

    if (dColumn > 0 && dRow >= 0) {  //left bottom
        mark.guideLineEnd = QPointF(mark.logBookPosition.column * logBookSize.width(),
                                    mark.logBookPosition.row * logBookSize.height());
        mark.edge = 0;
    }
    else if (dColumn >= 0  && dRow < 0) { //left top
        mark.guideLineEnd = QPointF(mark.logBookPosition.column * logBookSize.width(),
                                    mark.logBookPosition.row * logBookSize.height() + logBookSize.height() /* / scale.y()*/);
        mark.edge = 1;
    }
    else if (dColumn < 0  && dRow <= 0) { //right top
        mark.guideLineEnd = QPointF(mark.logBookPosition.column * logBookSize.width() + logBookSize.width()/* / scale.x()*/,
                                    mark.logBookPosition.row * logBookSize.height() + logBookSize.height()/* / scale.y() */);
        mark.edge = 2;
    }
    else if (dColumn <= 0  && dRow > 0) { //right bottom
        mark.guideLineEnd = QPointF(mark.logBookPosition.column * logBookSize.width() + logBookSize.width()/* / scale.x()*/,
                                    mark.logBookPosition.row * logBookSize.height());
        mark.edge = 3;
    }
}

/*void TraceGLData::initTrackBuffer(quint32 id)
{
    auto itemOfTrack = mapOfTraceTrack.find(id);
    if (itemOfTrack != mapOfTraceTrack.end()) {
        auto &listOfTrack = itemOfTrack.value();
        if (!listOfTrack.isEmpty()) {
            const quint8 nDimensional = 3;
            const quint32 sizeOfBuffer = nDimensional * listOfTrack.size();
            GLfloat *bufferOfTrack = new GLfloat[sizeOfBuffer];

            quint32 offsetOfBuffer = 0;
            for (auto &listItem : listOfTrack) {
                bufferOfTrack[offsetOfBuffer++] = listItem.pos.x();
                bufferOfTrack[offsetOfBuffer++] = listItem.pos.y();
                bufferOfTrack[offsetOfBuffer++] = listItem.course;
            }

            trackVBO->bind();
            trackVBO->write(0, bufferOfTrack, sizeOfBuffer * sizeof(GLfloat));
            trackVBO->release();

            currentValueOfTrackVertices = listOfTrack.size();

            delete [] bufferOfTrack;
        }
        else
            currentValueOfTrackVertices = 0;
    }
}*/

void TraceGLData::prepareGrideForTrace()
{
    /*float zCoord = 5.;
    //trace element
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerQuad = 2;
    const quint8 pointPerQuad = nDimensional * vertexPerTriangle * trianglePerQuad;

    const qint16 rowCount = 100, columCount = 100;
    GLfloat *grideBuffer = new GLfloat[pointPerQuad * rowCount * columCount];


    quint32 offset = 0;
    for (qint16 row = -rowCount / 2; row < rowCount / 2; row++) {
        for (qint16 column = -columCount / 2; column < columCount / 2; column++) {
            OpenGLRectF rect(column * logBookSize.width() + 1,
                             row * logBookSize.height() + 1,
                             logBookSize.width() - 2, logBookSize.height() - 2);
            calcRect(rect, grideBuffer, offset, zCoord);
            offset += pointPerQuad;
        }
    }

    traceBuffSize = pointPerQuad * rowCount * columCount;

    tVbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    tVbo->create();
    tVbo->bind();
    tVbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    tVbo->allocate(grideBuffer, traceBuffSize * sizeof (GLfloat) );

    tVao = new QOpenGLVertexArrayObject();
    tVao->create();
    tVao->bind();
    if (!tVao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programTrace->enableAttributeArray("posAttr");
    programTrace->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    tVbo->release();
    tVao->release();

    delete [] grideBuffer;*/


    tVbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    tVbo->create();
    tVbo->bind();
    tVbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    tVbo->allocate(3 * 3 * sizeof (GLfloat) );

    tVao = new QOpenGLVertexArrayObject();
    tVao->create();
    tVao->bind();
    if (!tVao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programTrace->enableAttributeArray("posAttr");
    programTrace->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 0);

    tVbo->release();
    tVao->release();

    float zCoord = 5.;
    //trace element
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerQuad = 2;
    const quint8 pointPerQuad = nDimensional * vertexPerTriangle * trianglePerQuad;

    GLfloat *buffer = new GLfloat[pointPerQuad];
    OpenGLRectF rect(0, 0, logBookSize.width(), logBookSize.height());
    calcRect(rect, buffer, 0, zCoord);

    tVbo2 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    tVbo2->create();
    tVbo2->bind();
    tVbo2->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    tVbo2->allocate(buffer, pointPerQuad * sizeof (GLfloat) );

    tVao2 = new QOpenGLVertexArrayObject();
    tVao2->create();
    tVao2->bind();
    if (!tVao2->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programLogBook->enableAttributeArray("posAttr");
    programLogBook->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 0);

    tVbo2->release();
    tVao2->release();

    delete []  buffer;

    vaoFont = new QOpenGLVertexArrayObject();
    vaoFont->create();
    vaoFont->bind();
    if (!vaoFont->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    const quint16 sizeFontPoint = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 buffSizeInByte = sizeFontPoint * nDimensionalFont * sizeof(GLfloat);
    GLfloat fontVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0
    };
    GLfloat texelVertex[sizeFontPoint * nDimensionalFont]
            = { 0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f };

    vboFont = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboFont->create();
    vboFont->bind();
    vboFont->allocate(fontVertex, 2 * buffSizeInByte);
    vboFont->write(buffSizeInByte, texelVertex,buffSizeInByte);
    vboFont->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalFont, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, buffSizeInByte, nDimensionalFont, 0);

    vboFont->release();
    vaoFont->release();    

    trackVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    trackVBO->create();
    trackVBO->bind();
    trackVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    trackVBO->allocate(maxTrackNumber * nDimensional * maxVerticesOfTrack * sizeof (GLfloat) );

    trackVAO = new QOpenGLVertexArrayObject();
    trackVAO->create();
    trackVAO->bind();
    if (!trackVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programTrack->enableAttributeArray("posAttr");
    programTrack->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    trackVBO->release();
    trackVAO->release();

}



RayGLData::RayGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, float _depth, QObject *parent)   : QObject(parent),
    glFunc(func), camera_ptr(m_camera), depth(_depth),
    rayNumberMax(100), rayHalfWith(0.7),
    rayColor(QColor::fromRgbF(0.3, 0.3, 0.3, 0.2)), maxDist(300.),
    timeErase(new QTimer()), timeAlive_msec(1000)
{
    qRegisterMetaType<RaySet>();
    programRays = new QOpenGLShaderProgram(this);

    if (!programRays->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/raysVertexShader.vert")) {
        qDebug() << programRays->log();
        return;
    }

    if (!programRays->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/raysFragmentShader.frag")) {
        qDebug() << programRays->log();
        return;
    }
    if (!programRays->link()) {
        qDebug() << programRays->log();
        return;
    }

}

void RayGLData::prepare()
{
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    const quint8 numberOfFaces = 6;
    const quint8 numberOfRays = rayNumberMax;

    quint32 rayBuffSize = nDimensional * vertexPerTriangle * numberOfFaces;
    maxRaysBuffSize = rayBuffSize * numberOfRays;
    GLfloat *rayBuff = new GLfloat[rayBuffSize];

    float az = 120, ugm = 10, degWidth = 1.5, r = 300.;
    az = (90. - az) * M_PI / 180.0;
    ugm = (90. - ugm) * M_PI / 180.0;
    degWidth *= M_PI / 180.0;


    float az1Rad = az - degWidth / 2,
          az2Rad = az + degWidth / 2,
          ugm1Rad = ugm - degWidth / 2,
          ugm2Rad = ugm + degWidth / 2;

    quint32 index = 0;
    //top face
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    rayBuff[index++] = r * cos(az2Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    //right face
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    //bottom face
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;

    rayBuff[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    //left face
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;
    rayBuff[index++] = 0.f;

    rayBuff[index++] = r * cos(az2Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    rayBuff[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    //floor face
    rayBuff[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    rayBuff[index++] = r * cos(az2Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    rayBuff[index++] = r * cos(ugm2Rad);

    rayBuff[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    rayBuff[index++] = r * cos(az1Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * sin(az1Rad) * sin(ugm1Rad);
    rayBuff[index++] = r * cos(ugm1Rad);

    raysBuffSize = rayBuffSize;

    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo->allocate(sizeof(GLfloat) * rayBuffSize * numberOfRays);
    vbo->write(0, rayBuff, sizeof(GLfloat) * rayBuffSize);

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programRays->enableAttributeArray("posAttr");
    programRays->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();

    delete [] rayBuff;

}

void RayGLData::prepareFlatRay()
{
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    //const quint8 numberOfFaces = 6;
    const quint16 numberOfRays = 4 * rayNumberMax;
    const quint32 buffSize = nDimensional * vertexPerTriangle * numberOfRays;

    raysBuffSize = 0;

    vbo = new QOpenGLBuffer();
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo->allocate(sizeof(GLfloat) * buffSize);

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programRays->enableAttributeArray("posAttr");
    programRays->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();
}

void RayGLData::render()
{
    //float zcoord = 3.;
    QMatrix4x4 model;
    model.setToIdentity();
    programRays->bind();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;
    programRays->setUniformValue("mvp", mvp);
    programRays->setUniformValue("objectColor", rayColor);

    vao->bind();
//    if (!vectorOfRayOffsetAndCount.isEmpty())
//        glFunc->glDrawArrays(GL_TRIANGLES, 0, vectorOfRayOffsetAndCount.at(0).second);
    int counter = vectorOfRayOffsetAndCount.size();
    for (auto itemOfRaysMap = vectorOfRayOffsetAndCount.rbegin();
         itemOfRaysMap != vectorOfRayOffsetAndCount.rend();
         itemOfRaysMap++) {
        /*QColor tempColor(rayColor);
        tempColor.setAlphaF(tempColor.alphaF() - 0.1 * (vectorOfRayOffsetAndCount.size() - counter));
        programRays->setUniformValue("objectColor", rayColor);*/
        programRays->setUniformValue("number", counter);
        glFunc->glDrawArrays(GL_TRIANGLES, 3 * rayNumberMax * itemOfRaysMap->first, itemOfRaysMap->second);
        counter--;
    }
    //glFunc->glDrawArrays(GL_TRIANGLES, 0, raysBuffSize / 3);
    vao->release();
    programRays->release();
}

void RayGLData::updateRaySetSlot(RaySet set)
{
    raySet.swap(set);

    /*if (raySet.size() > rayNumberMax) {
        qDebug() << QString("Rays set size is %1. That is error").arg(raySet.size());
        return;
    }    */

    /*auto sectorItem = raySet.find(-1);
    if (sectorItem == raySet.end()){
        qDebug() << "No Sector Rays ";
    }*/

    quint32 rayCount = 0;
    for (auto itemOfRaysMap = raySet.begin();
         itemOfRaysMap != raySet.end();
         itemOfRaysMap++) {
        if (itemOfRaysMap.key() > -11)
            rayCount += itemOfRaysMap.value().size();
        /*if (itemOfRaysMap.key() > -11 && itemOfRaysMap.key() < 0) {
            if(itemOfRaysMap.value().size() == 0) {
                qDebug() << "No Rays in " << itemOfRaysMap.key();
            }
        }*/
    }

    quint8 erasedIndex = 0;
    if (vectorOfRayOffsetAndCount.size() == 4) {
        erasedIndex = vectorOfRayOffsetAndCount.at(0).first;
        vectorOfRayOffsetAndCount.pop_front();
    }
    else {
        erasedIndex = vectorOfRayOffsetAndCount.size();
    }
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    quint32 rayBuffSize = nDimensional * vertexPerTriangle * rayCount;

    //qDebug() << erasedIndex << rayCount;
    vectorOfRayOffsetAndCount.push_back(qMakePair(erasedIndex, rayCount * vertexPerTriangle));

    GLfloat *rayBuff = new GLfloat[rayBuffSize];

    quint32 counter = 0;
    float zcoord = depth;
    for (auto itemOfRaysMap = raySet.begin();
         itemOfRaysMap != raySet.end();
         itemOfRaysMap++) {
        if (itemOfRaysMap.key() > -11) {
            for (auto iterOfVectorOfRayInfo = itemOfRaysMap.value().begin();
                 iterOfVectorOfRayInfo != itemOfRaysMap.value().end();
                 iterOfVectorOfRayInfo++) {
                calcFlatRay(rayBuff, counter, iterOfVectorOfRayInfo->az, zcoord);
            }
        }
    }

    /*QVector< QPair<float, float> > azMinAzMax;
    int rayCount = 0;
    for (auto itemOfRaysMap = raySet.begin();
         itemOfRaysMap != raySet.end();
         itemOfRaysMap++) {
        //if (itemOfRaysMap.key() < 0) {
            QMap <float, char> sortAz;
            for (auto iterOfVectorOfRayInfo = itemOfRaysMap.value().begin();
                 iterOfVectorOfRayInfo != itemOfRaysMap.value().end();
                 iterOfVectorOfRayInfo++) {
                sortAz.insert(iterOfVectorOfRayInfo->az, 0);
            }

            float azMin = sortAz.begin().key() - 0.7,
                    azMax = sortAz.begin().key() + 0.7;
            for (auto iterOfAzMap = sortAz.begin() + 1;
                 iterOfAzMap != sortAz.end();
                 iterOfAzMap++) {

                if (azMax > (iterOfAzMap.key() - 0.7)) {
                    azMax = iterOfAzMap.key() + 0.7;
                }
                else {
                    azMinAzMax.push_back(qMakePair(azMin, azMax));
                    rayCount += qCeil((azMax - azMin) / 0.7);
                    azMin = iterOfAzMap.key() - 0.7;
                    azMax = iterOfAzMap.key() + 0.7;
                }
            }
            azMinAzMax.push_back(qMakePair(azMin, azMax));
            rayCount += qCeil((azMax - azMin) / 0.7);
        //}
    }

    //const quint8 numberOfRays = rayCount;
    const quint8 nDimensional = 3;
    const quint8 vertexPerTriangle = 3;
    //const quint8 numberOfFaces = 6;

    quint32 rayBuffSize = nDimensional * vertexPerTriangle * rayCount;
    GLfloat *rayBuff = new GLfloat[rayBuffSize];

    quint32 counter = 0;
    float zcoord = 3.5;

    for (auto iterOfVectorOfAz = azMinAzMax.begin();
         iterOfVectorOfAz != azMinAzMax.end();
         iterOfVectorOfAz++) {
        float degWidth = 0.7, r = maxDist;
        int segment = qCeil((iterOfVectorOfAz->second - iterOfVectorOfAz->first) / degWidth);
        float taz = (90. - iterOfVectorOfAz->first) * M_PI / 180.0;
        degWidth *= M_PI / 180.0;

        for (int i = 0; i < segment; i++) {
            //top face
            rayBuff[counter++] = 0.f;
            rayBuff[counter++] = 0.f;
            rayBuff[counter++] = zcoord;

            rayBuff[counter++] = r * cos(taz + degWidth * i);
            rayBuff[counter++] = r * sin(taz + degWidth * i);
            rayBuff[counter++] = zcoord;

            rayBuff[counter++] = r * cos(taz + degWidth * (i + 1));
            rayBuff[counter++] = r * sin(taz + degWidth * (i + 1));
            rayBuff[counter++] = zcoord;
        }
    }*/

    /*for (quint16 index = 0; index != numberOfRays; index++) {
        calcRay(rayBuff, counter, raySet.at(index).first, raySet.at(index).second, zcoord);
        zcoord += 0.02;
    }*/

    if (counter != rayBuffSize) {
        qDebug() << "Rays buffer is incorrect";
    }

    raysBuffSize = counter;

    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      nDimensional * vertexPerTriangle * erasedIndex * rayNumberMax * sizeof(GLfloat),
      rayBuffSize * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, rayBuff, sizeof(GLfloat) * rayBuffSize);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    delete [] rayBuff;
}

float RayGLData::deg360TransitionCheck(float ang) {
    if (ang > 360) {
        ang -= 360;
    }
    else if (ang < 0) {
        ang += 360;
    }
    return ang;
}

void RayGLData::setColor(const QColor color)
{
    rayColor = color;
}

void RayGLData::setMaxDist(const float value)
{
    if (value > 10 && value <= 300)
        maxDist = value;
}

void RayGLData::calcRay(GLfloat *array, quint32 &counter, const float &az,const float &ugm, const float zcoord)
{
    float degWidth = 0.8, r = maxDist;
    float taz = (90. - az) * M_PI / 180.0;
    float tugm = (90. - ugm) * M_PI / 180.0;
    degWidth *= M_PI / 180.0;


    float az1Rad = taz - degWidth / 2,
          az2Rad = taz + degWidth / 2,
          ugm1Rad = tugm - degWidth / 2,
          ugm2Rad = tugm + degWidth / 2;

    quint32 &index = counter;
    //top face
    array[index++] = 0.f;
    array[index++] = 0.f;
    array[index++] = zcoord;//0.f;

    array[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    array[index++] = r * cos(az2Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    //right face
    array[index++] = 0.f;
    array[index++] = 0.f;
    array[index++] = zcoord;//0.f;

    array[index++] = r * cos(az1Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);

    array[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    //bottom face
    array[index++] = 0.f;
    array[index++] = 0.f;
    array[index++] = zcoord;//0.f;

    array[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);

    array[index++] = r * cos(az1Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);

    //left face
    array[index++] = 0.f;
    array[index++] = 0.f;
    array[index++] = zcoord;//0.f;

    array[index++] = r * cos(az2Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    array[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);

    //floor face
    array[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);

    array[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    array[index++] = r * cos(az2Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    array[index++] = r * cos(az1Rad) * sin(ugm2Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm2Rad);
    array[index++] = zcoord;//r * cos(ugm2Rad);

    array[index++] = r * cos(az2Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az2Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);

    array[index++] = r * cos(az1Rad) * sin(ugm1Rad);
    array[index++] = r * sin(az1Rad) * sin(ugm1Rad);
    array[index++] = zcoord;//r * cos(ugm1Rad);
}

void RayGLData::calcFlatRay(GLfloat *array, quint32 &counter, const float &az, const float zcoord)
{
    float degWidth = 0.7, r = maxDist;
    float taz = (90. - az) * M_PI / 180.0;
    degWidth *= M_PI / 180.0;

    //top face
    array[counter++] = 0.f;
    array[counter++] = 0.f;
    array[counter++] = zcoord;

    array[counter++] = r * cos(taz - degWidth);
    array[counter++] = r * sin(taz - degWidth);
    array[counter++] = zcoord;

    array[counter++] = r * cos(taz + degWidth);
    array[counter++] = r * sin(taz + degWidth);
    array[counter++] = zcoord;

}

GrideGL::GrideGL(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const Camera *m_extraCamera, const SceneOptions *scOption, QOpenGLShaderProgram *prog, ftCustom *font, float _depth, QObject *parent) : QObject(parent),
    glFunc(func), camera_ptr(m_camera), extraCamera_ptr(m_extraCamera),
    sceneOptions(scOption), programGride(prog),
    fontDriver(font), depth(_depth),
    grideColor(QColor::fromRgbF(0.4f, 0.4f, 0.4f, 0.6f)), textColor(QColor::fromRgbF(0.60f, 0.55f, 0.09f, 0.7)),
    scaleText(0.1f),
    koeffAz(10), centerAz(0)
{
    programFont = new QOpenGLShaderProgram(this);
    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/grideFontVertexShader.vert")) {
        qDebug() << programFont->log();
        return;
    }

    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/grideFontFragmentShader.frag")) {
        qDebug() << programFont->log();
        return;
    }
    if (!programFont->link()) {
        qDebug() << programFont->log();
        return;
    }

    distStepDependOnScaleLevelVector.push_back(50);
    distStepDependOnScaleLevelVector.push_back(10);
    distStepDependOnScaleLevelVector.push_back(5);
    distStepDependOnScaleLevelVector.push_back(1);
}

void GrideGL::prepare()
{
    //const quint32 freqCircleInKm = 5;
    //const float freqCircleInKm = 50;
    //const quint32 numCircle = maxDist / freqCircleInKm;
    const quint32 nDimensional = 3;

    quint16 index = 0;
    for (auto iterDistStep = distStepDependOnScaleLevelVector.begin();
         iterDistStep != distStepDependOnScaleLevelVector.end();
         iterDistStep++) {
        quint32 coordsNumber = 0;
        for (quint32 k = *iterDistStep; k <= sceneOptions->maxDist; k += *iterDistStep) {
            quint32 l = k * 2 * M_PI;
            if (k > 200)
                coordsNumber += 2 * (l / 16);
            else if (k <= 200 && k > 100)
                coordsNumber += 2 * (l / 4);
            else if (k <= 100 && k > 50)
                coordsNumber += 2 * (l / 2);
            else if (k <= 50 && k > 25)
                coordsNumber += 2 * (l);
            else if (k <= 25 && k > 10)
                coordsNumber += 2 * (4 * l);
            else if (k <= 10)
                coordsNumber += 2 * (8 * l);
        }
        grideBufferSize.push_back(coordsNumber);
        const quint32 sizeVertBuf = coordsNumber * nDimensional;
        GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

        quint32 posArr = 0;
        for (quint32 k = *iterDistStep; k <= sceneOptions->maxDist; k += *iterDistStep) {
            quint32 l = k * 2 * M_PI;
            quint32 segmentation = 0;
            if (k > 200)
                segmentation = (l / 16);
            else if (k <= 200 && k > 100)
                segmentation = (l / 4);
            else if (k <= 100 && k > 50)
                segmentation = (l / 2);
            else if (k <= 50 && k > 25)
                segmentation = (l);
            else if (k <= 25 && k > 10)
                segmentation = (4 * l);
            else if (k <= 10)
                segmentation = (8 * l);

            double deltaAlpha = 2. * M_PI / static_cast<double>(segmentation);

            double alpha = 0;
            for (quint32 counter = 0; counter != segmentation; counter++) {
                vertBufGrid[posArr++] = k * cos(alpha);
                vertBufGrid[posArr++] = k * sin(alpha);
                vertBufGrid[posArr++] = depth;
                alpha += deltaAlpha;
                vertBufGrid[posArr++] = k * cos(alpha);
                vertBufGrid[posArr++] = k * sin(alpha);
                vertBufGrid[posArr++] = depth;
            }
        }

        if (posArr != sizeVertBuf) {
            qDebug() << "Gride Array not filled correctly";
        }

        vboDependOnScaleLevel.push_back(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
        vboDependOnScaleLevel.at(index)->create();
        vboDependOnScaleLevel.at(index)->bind();
        vboDependOnScaleLevel.at(index)->setUsagePattern(QOpenGLBuffer::StaticDraw);
        vboDependOnScaleLevel.at(index)->allocate(vertBufGrid, sizeVertBuf * sizeof(GLfloat));

        vaoDependOnScaleLevel.push_back(new QOpenGLVertexArrayObject(this));
        vaoDependOnScaleLevel.at(index)->create();
        vaoDependOnScaleLevel.at(index)->bind();
        if (!vaoDependOnScaleLevel.at(index)->isCreated()){
            qDebug() << "Can't use VAO";
            return;
        }

        programGride->enableAttributeArray("posAttr");
        programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

        vboDependOnScaleLevel.at(index)->release();
        vaoDependOnScaleLevel.at(index)->release();

        delete [] vertBufGrid;

        index++;
    }

    const quint8 azLineCount = 6;
    const quint8 pointInLine = 2;
    const quint32 sizeVertBufAz = azLineCount * pointInLine * nDimensional;
    azGrideBufferSize = azLineCount * pointInLine;
    GLfloat *vertBufAzGrid = new GLfloat[sizeVertBufAz];

    float deltaAz = M_PI / azLineCount;
    quint32 azGrideOffset = 0;
    float tDist = sceneOptions->maxDist;
    for (quint8 index = 0; index < azLineCount; index++) {
        vertBufAzGrid[azGrideOffset++] = tDist * cos(M_PI_2 - deltaAz * index);
        vertBufAzGrid[azGrideOffset++] = tDist * sin(M_PI_2 - deltaAz * index);
        vertBufAzGrid[azGrideOffset++] = depth;
        vertBufAzGrid[azGrideOffset++] = tDist * cos(-deltaAz * index - M_PI_2);
        vertBufAzGrid[azGrideOffset++] = tDist * sin(-deltaAz * index - M_PI_2);
        vertBufAzGrid[azGrideOffset++] = depth;
    }

    vaoAzGride = new QOpenGLVertexArrayObject();
    vaoAzGride->create();
    vaoAzGride->bind();
    if (!vaoAzGride->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    vboAzGride = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboAzGride->create();
    vboAzGride->bind();
    vboAzGride->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboAzGride->allocate(vertBufAzGrid, sizeVertBufAz * sizeof(GLfloat));

    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vboAzGride->release();
    vaoAzGride->release();

    delete [] vertBufAzGrid;


    /*quint32 coordsNumber = 0;
    for (quint32 k = freqCircleInKm; k <= sceneOptions->maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        coordsNumber += l * 10;
    }
    const quint32 sizeVertBuf = coordsNumber * nDimensional + 2 * 4 * nDimensional;
    GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

    quint32 posArr = 0;
    QVector<QPointF> vect;
    for (quint32 k = freqCircleInKm; k <= sceneOptions->maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        quint32 segmentation = l * 10;
        double deltaAlpha = 2. * M_PI / static_cast<double>(segmentation);
        //quint32 counter = 0;
        double alpha = 0;
        QVector<QPointF> tvector;
        for (quint32 counter = 0; counter != segmentation; counter++) {
            vertBufGrid[posArr++] = k * cos(alpha);
            vertBufGrid[posArr++] = k * sin(alpha);
            vertBufGrid[posArr++] = 0.;
            tvector << QPointF(vertBufGrid[posArr - 2], vertBufGrid[posArr - 1]);
            alpha += deltaAlpha;
            //            counter++;
        }
//        vect << tvector;
//        if (k > 110) {
//            int ie = 5;
//            ie++;
//        }
        if (posArr > sizeVertBuf) {
            qDebug() << "Overflow Grid array";
        }
    }
    for (quint32 i = 0; i < 4; i++) {  // для высоты
        vertBufGrid[posArr++] = sceneOptions->maxDist * cos(i * M_PI_2);
        vertBufGrid[posArr++] = sceneOptions->maxDist * sin(i * M_PI_2);
        vertBufGrid[posArr++] = 0.;

        vertBufGrid[posArr++] = sceneOptions->maxDist * cos(i * M_PI_2);
        vertBufGrid[posArr++] = sceneOptions->maxDist * sin(i * M_PI_2);
        vertBufGrid[posArr++] = sceneOptions->maxDist;
    }


    const quint16 fullTurn = 360, deltaAz = 30;
    const quint16 azCount = fullTurn / deltaAz;
    const qreal coeffDeg2Rad = M_PI / 180.;
    const qreal fullTurnReal = fullTurn * coeffDeg2Rad, deltaAzReal = deltaAz * coeffDeg2Rad;

    const quint32 sizeVertBuf2 = 2 * azCount * nDimensional;
    GLfloat *vertBuf2 = new GLfloat[sizeVertBuf2];

    posArr = 0;
    for (quint16 i = 0; i < azCount; i++) {
        vertBuf2[posArr++] = sceneOptions->maxDist * cos(i * deltaAzReal);
        vertBuf2[posArr++] = sceneOptions->maxDist * sin(i * deltaAzReal);
        vertBuf2[posArr++] = 0.;

        vertBuf2[posArr++] = sceneOptions->maxDist * cos(i * deltaAzReal + M_PI);
        vertBuf2[posArr++] = sceneOptions->maxDist * sin(i * deltaAzReal + M_PI);
        vertBuf2[posArr++] = 0.;
    }

    const quint32 sizeVertBuf3 = 8 * nDimensional;
    GLfloat *vertBuf3 = new GLfloat[sizeVertBuf3];

    posArr = 0;
    for (quint16 i = 0; i < 4; i++) {
        vertBuf3[posArr++] = 20 * sin(i * M_PI_2 + deltaAzReal);
        vertBuf3[posArr++] = 20 * cos(i * M_PI_2 + deltaAzReal);
        vertBuf3[posArr++] = 0.;
    }

    vertBuf3[posArr++] = 20 * sin(deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(2 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(2 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;
    vertBuf3[posArr++] = 20 * sin(3 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 20 * cos(3 * M_PI_2 + deltaAzReal);
    vertBuf3[posArr++] = 0.;

    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(vertBufGrid, (sizeVertBuf + sizeVertBuf2 + sizeVertBuf3) * sizeof(GLfloat));
    vbo->write(sizeVertBuf * sizeof(GLfloat), vertBuf2, sizeVertBuf2 * sizeof(GLfloat));
    vbo->write((sizeVertBuf + sizeVertBuf2) * sizeof(GLfloat), vertBuf3, sizeVertBuf3 * sizeof(GLfloat));

    vao = new QOpenGLVertexArrayObject(this);
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO";
        return;
    }

    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();

    //delete [] vertBufGrid;
    //delete [] vertBuf2;
    //delete [] vertBuf3;*/

    const quint16 markNumber = 12;
    const quint32 nDimensionalMark = 2;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRectVert = nDimensionalMark * vertexPerTriangle * trianglePerRect;
    const quint32 pointPerRectTexel = nDimensional * vertexPerTriangle * trianglePerRect;

    quint32 ftOffset = 0, txOffset = 0;
    //const GLfloat scaleText = 0.1;
    const float dAz = 360. /  static_cast<float>(markNumber);
    const float convers = M_PI / 180.;

    charCount = 0;
    for (quint16 index = 0; index < markNumber; index++) {
        QString str(QString::number(dAz * index));
        vectorOfText.push_back(str);
        charCount += str.size();
    }
    fontBufferSize = charCount * vertexPerTriangle * trianglePerRect;

    quint32 bufferMarkSize = charCount * pointPerRectVert,
            bufferTexelSize = charCount * pointPerRectTexel;

    GLfloat *bufferMark = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel = new GLfloat[bufferTexelSize]; //texels
    for (quint16 index = 0; index < markNumber; index++) {
        /*QSizeF rectSize = fontDriver->genRectForText(vectorOfText.at(index), scaleText);
        OpenGLRectF rect((sceneOptions->maxDist + rectSize.width() / 2 + 5) * cos(M_PI_2 - (index * dAz * convers)) - rectSize.width() / 2,
                         (sceneOptions->maxDist + rectSize.width() / 2 + 5) * sin(M_PI_2 - (index * dAz * convers)) - rectSize.height() / 2,
                         rectSize.width(), rectSize.height());*/
        QPointF point((sceneOptions->maxDist + 10) * cos(M_PI_2 - (index * dAz * convers)),
                      (sceneOptions->maxDist + 10) * sin(M_PI_2 - (index * dAz * convers)));
        centerOfText.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText.at(index), point, scaleText,
                                            bufferMark, ftOffset,
                                            bufferTexel, txOffset);
    }

    vaoFont = new QOpenGLVertexArrayObject();
    vaoFont->create();
    vaoFont->bind();
    if (!vaoFont->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    vboFont = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboFont->create();
    vboFont->bind();
    vboFont->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboFont->allocate(bufferMark, (bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    vboFont->write(bufferMarkSize * sizeof(GLfloat), bufferTexel, bufferTexelSize * sizeof(GLfloat));

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    vboFont->release();
    vaoFont->release();

    delete []  bufferMark;
    delete []  bufferTexel;

    ftOffset = 0, txOffset = 0;
    const quint8 distStep = 1;
    const quint32 distCount = sceneOptions->maxDist / distStep;

    charCount2 = 0;
    for (quint16 index = 1; index < distCount; index++) {
        QString str(QString::number(distStep * index));
        vectorOfText2.push_back(str);
        charCount2 += str.size();
    }
    fontBufferSize2 = charCount2 * vertexPerTriangle * trianglePerRect;

    bufferMarkSize = charCount2 * pointPerRectVert,
    bufferTexelSize = charCount2 * pointPerRectTexel;

    GLfloat *bufferMark2 = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel2 = new GLfloat[bufferTexelSize]; //texels

    for (quint16 index = 1; index < distCount; index++) {
        /*QSizeF rectSize = fontDriver->genRectForText(vectorOfText2.at(index - 1), scaleText);
        OpenGLRectF rect((distStep * index) * cos(M_PI_2) - rectSize.width() / 2,
                         (distStep * index) * sin(M_PI_2) - rectSize.height() / 2,
                         rectSize.width(), rectSize.height());*/
        QPointF point((distStep * index) * cos(M_PI_2),
                      (distStep * index) * sin(M_PI_2));
        centerOfText2.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText2.at(index - 1), point, scaleText,
                                            bufferMark2, ftOffset,
                                            bufferTexel2, txOffset);
    }

    vboFont2 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboFont2->create();
    vboFont2->bind();
    vboFont2->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboFont2->allocate((bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    vboFont2->write(0, bufferMark2, bufferMarkSize * sizeof(GLfloat));
    vboFont2->write(bufferMarkSize * sizeof(GLfloat), bufferTexel2, bufferTexelSize * sizeof(GLfloat));

    vaoFont2 = new QOpenGLVertexArrayObject();
    vaoFont2->create();
    vaoFont2->bind();
    if (!vaoFont2->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    vboFont2->release();
    vaoFont2->release();

    delete []  bufferMark2;
    delete []  bufferTexel2;

    prepareAzH();
}

void GrideGL::prepareAzH()
{
    //xz plot
    const quint8 nDimensional = 3;
    const quint32 distStepH = 10;
    const float lArc = 90.;
    const quint16 distOffset = 350;
    const quint8 pointInLineH = 2;
    const quint16 countRibs = sceneOptions->maxDist / distStepH + 1;

    quint32 l = distOffset * M_PI_2; // 90 deg
    quint32 coordsNumber = 2 * (l / 16) * countRibs;
    //for (quint32 k = 0; k <= sceneOptions->maxDist; k += distStepH) {
    //     quint32 l = (distOffset + k) * M_PI_2; // 90 deg
    //     coordsNumber += 2 * (l / 16);
    //}

    const quint32 sizeVertBuf = coordsNumber * nDimensional;
    GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

    hGrideIndicesCount = coordsNumber;

    quint32 posArr = 0;
    quint32 segmentation1 = (l / 16);
    float deltaAlpha1 = M_PI_2 / static_cast<float>(segmentation1);
    for (quint32 k = 0; k <= sceneOptions->maxDist; k += distStepH) {
        float alpha1 = M_PI_2 + M_PI_4;
        for (quint32 counter = 0; counter != segmentation1; counter++) {
            vertBufGrid[posArr++] = distOffset * cos(alpha1);
            vertBufGrid[posArr++] = distOffset * sin(alpha1) + k;
            vertBufGrid[posArr++] = 0.;

            alpha1 -= deltaAlpha1;
            vertBufGrid[posArr++] = distOffset * cos(alpha1);
            vertBufGrid[posArr++] = distOffset * sin(alpha1) + k;
            vertBufGrid[posArr++] = 0.;

        }

    }

    if (posArr != sizeVertBuf) {
        qDebug() << "Gride Array not filled correctly";
    }

    const quint8 azHLineCount = 6;
    const float azDelta = M_PI_2 / (float)azHLineCount;
    const quint32 sizeVertBufAzH = (azHLineCount + 1) * pointInLineH * nDimensional;
    azGrideIndicesCount = sizeVertBufAzH / nDimensional;
    GLfloat *vertBufAzHGrid = new GLfloat[sizeVertBufAzH];

    quint32 azHGrideOffset = 0;
    float alpha = M_PI_2 + M_PI_4;
    for (quint8 index = 0; index < (azHLineCount + 1); index++) {
        vertBufAzHGrid[azHGrideOffset++] = (distOffset) * cos(alpha - azDelta * index);
        vertBufAzHGrid[azHGrideOffset++] = (distOffset) * sin(alpha - azDelta * index);
        vertBufAzHGrid[azHGrideOffset++] = depth;
        vertBufAzHGrid[azHGrideOffset++] = (distOffset) * cos(alpha - azDelta * index);
        vertBufAzHGrid[azHGrideOffset++] = (distOffset) * sin(alpha - azDelta * index) + sceneOptions->maxDist; //* sin(alpha - azDelta * index);
        vertBufAzHGrid[azHGrideOffset++] = depth;
    }

    azHPlotVAO = new QOpenGLVertexArrayObject();
    azHPlotVAO->create();
    azHPlotVAO->bind();
    if (!azHPlotVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    azHPlotVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    azHPlotVBO->create();
    azHPlotVBO->bind();
    azHPlotVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    azHPlotVBO->allocate(vertBufGrid, (sizeVertBufAzH + sizeVertBuf) * sizeof(GLfloat));
    azHPlotVBO->write(sizeVertBuf * sizeof(GLfloat), vertBufAzHGrid, sizeVertBufAzH * sizeof(GLfloat));

    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    azHPlotVBO->release();
    azHPlotVAO->release();

    delete [] vertBufAzHGrid;
    delete [] vertBufGrid;

    const quint16 markNumber = 12;
    const quint32 nDimensionalMark = 2;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRectVert = nDimensionalMark * vertexPerTriangle * trianglePerRect;
    const quint32 pointPerRectTexel = nDimensional * vertexPerTriangle * trianglePerRect;

    quint32 ftOffset = 0, txOffset = 0;

    quint32 charCount11 = 0;
    quint8 dAz = 30;
    QVector<QString> vectorOfText11;
    for (quint16 index = 0; index < markNumber; index++) {
        QString str(QString::number(dAz * index));
        vectorOfText11.push_back(str);
        charCount11 += str.size();
    }
    azFontIndicesCount = charCount11 * vertexPerTriangle * trianglePerRect;

    quint32 bufferMarkSize = charCount11 * pointPerRectVert,
            bufferTexelSize = charCount11 * pointPerRectTexel;

    GLfloat *bufferMark = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel = new GLfloat[bufferTexelSize]; //texels
    for (quint16 index = 0; index < markNumber; index++) {

        QPointF point(index * dAz * koeffAz,
                      -5);
        //centerOfText.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText11.at(index), point, scaleText,
                                            bufferMark, ftOffset,
                                            bufferTexel, txOffset);
    }

    azFontVAO = new QOpenGLVertexArrayObject();
    azFontVAO->create();
    azFontVAO->bind();
    if (!azFontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    azFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    azFontVBO->create();
    azFontVBO->bind();
    azFontVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    azFontVBO->allocate(bufferMark, (bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    azFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel, bufferTexelSize * sizeof(GLfloat));

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    azFontVBO->release();
    azFontVAO->release();

    delete []  bufferMark;
    delete []  bufferTexel;

    ftOffset = 0, txOffset = 0;
    const quint8 distStep = 1;
    const quint32 distCount = sceneOptions->maxDist / (distStep * 10) + 1;

    quint32 charCount22 = 0;
    QVector<QString> vectorOfText22;
    for (quint16 index = 1; index < distCount; index++) {
        QString str(QString::number(distStep * index));
        vectorOfText22.push_back(str);
        charCount22 += str.size();
    }
    hFontIndicesCount = charCount22 * vertexPerTriangle * trianglePerRect;

    bufferMarkSize = charCount22 * pointPerRectVert,
    bufferTexelSize = charCount22 * pointPerRectTexel;

    GLfloat *bufferMark2 = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel2 = new GLfloat[bufferTexelSize]; //texels

    for (quint16 index = 1; index < distCount; index++) {

        QPointF point(0,
                      distOffset + (distStep * 10 * index));
        //centerOfText2.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText22.at(index - 1), point, scaleText,
                                            bufferMark2, ftOffset,
                                            bufferTexel2, txOffset);
    }

    hFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    hFontVBO->create();
    hFontVBO->bind();
    hFontVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    hFontVBO->allocate((bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    hFontVBO->write(0, bufferMark2, bufferMarkSize * sizeof(GLfloat));
    hFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel2, bufferTexelSize * sizeof(GLfloat));

    hFontVAO = new QOpenGLVertexArrayObject();
    hFontVAO->create();
    hFontVAO->bind();
    if (!hFontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    hFontVBO->release();
    hFontVAO->release();

    delete []  bufferMark2;
    delete []  bufferTexel2;
}

/*void GrideGL::prepareAzH()
{
    //xz plot
    const quint8 nDimensional = 3;
    const quint32 distStepH = 10;
    const float lArc = 180. * koeffAz;
    const quint8 pointInLineH = 2;

    const quint32 sizeVertBuf = (sceneOptions->maxDist / distStepH) * pointInLineH * nDimensional;
    GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

    hGrideIndicesCount = sizeVertBuf / nDimensional;

    quint32 posArr = 0;
    for (quint32 k = distStepH; k <= sceneOptions->maxDist; k += distStepH) {

            vertBufGrid[posArr++] = -lArc / 2.;
            vertBufGrid[posArr++] = k;
            vertBufGrid[posArr++] = 0.;

            vertBufGrid[posArr++] = lArc / 2.;
            vertBufGrid[posArr++] = k;
            vertBufGrid[posArr++] = 0.;

    }

    if (posArr != sizeVertBuf) {
        qDebug() << "Gride Array not filled correctly";
    }

    const quint8 azHLineCount = 6;
    const float azDelta = lArc / (float)azHLineCount;
    const quint32 sizeVertBufAzH = (azHLineCount + 1) * pointInLineH * nDimensional;
    azGrideIndicesCount = (azHLineCount + 1) * pointInLineH;
    GLfloat *vertBufAzHGrid = new GLfloat[sizeVertBufAzH];

    quint32 azHGrideOffset = 0;
    for (quint8 index = 0; index < (azHLineCount + 1); index++) {
        vertBufAzHGrid[azHGrideOffset++] = (-lArc / 2.) + azDelta * index;
        vertBufAzHGrid[azHGrideOffset++] = 0;
        vertBufAzHGrid[azHGrideOffset++] = 0.1;
        vertBufAzHGrid[azHGrideOffset++] = (-lArc / 2.) + azDelta * index;
        vertBufAzHGrid[azHGrideOffset++] = sceneOptions->maxDist;
        vertBufAzHGrid[azHGrideOffset++] = 0.1;
    }

    azHPlotVAO = new QOpenGLVertexArrayObject();
    azHPlotVAO->create();
    azHPlotVAO->bind();
    if (!azHPlotVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    azHPlotVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    azHPlotVBO->create();
    azHPlotVBO->bind();
    azHPlotVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    azHPlotVBO->allocate(vertBufGrid, (sizeVertBufAzH + sizeVertBuf) * sizeof(GLfloat));
    azHPlotVBO->write(sizeVertBuf * sizeof(GLfloat), vertBufAzHGrid, sizeVertBufAzH * sizeof(GLfloat));

    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    azHPlotVBO->release();
    azHPlotVAO->release();

    delete [] vertBufAzHGrid;
    delete [] vertBufGrid;

    const quint16 markNumber = 12;
    const quint32 nDimensionalMark = 2;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRectVert = nDimensionalMark * vertexPerTriangle * trianglePerRect;
    const quint32 pointPerRectTexel = nDimensional * vertexPerTriangle * trianglePerRect;

    quint32 ftOffset = 0, txOffset = 0;

    quint32 charCount11 = 0;
    quint8 dAz = 30;
    QVector<QString> vectorOfText11;
    for (quint16 index = 0; index < markNumber; index++) {
        QString str(QString::number(dAz * index));
        vectorOfText11.push_back(str);
        charCount11 += str.size();
    }
    azFontIndicesCount = charCount11 * vertexPerTriangle * trianglePerRect;

    quint32 bufferMarkSize = charCount11 * pointPerRectVert,
            bufferTexelSize = charCount11 * pointPerRectTexel;

    GLfloat *bufferMark = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel = new GLfloat[bufferTexelSize]; //texels
    for (quint16 index = 0; index < markNumber; index++) {

        QPointF point(index * dAz * koeffAz,
                      -5);
        //centerOfText.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText11.at(index), point, scaleText,
                                            bufferMark, ftOffset,
                                            bufferTexel, txOffset);
    }

    azFontVAO = new QOpenGLVertexArrayObject();
    azFontVAO->create();
    azFontVAO->bind();
    if (!azFontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    azFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    azFontVBO->create();
    azFontVBO->bind();
    azFontVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    azFontVBO->allocate(bufferMark, (bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    azFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel, bufferTexelSize * sizeof(GLfloat));

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    azFontVBO->release();
    azFontVAO->release();

    delete []  bufferMark;
    delete []  bufferTexel;

    ftOffset = 0, txOffset = 0;
    const quint8 distStep = 1;
    const quint32 distCount = sceneOptions->maxDist / (distStep * 10);

    quint32 charCount22 = 0;
    QVector<QString> vectorOfText22;
    for (quint16 index = 1; index < distCount; index++) {
        QString str(QString::number(distStep * index));
        vectorOfText22.push_back(str);
        charCount22 += str.size();
    }
    hFontIndicesCount = charCount22 * vertexPerTriangle * trianglePerRect;

    bufferMarkSize = charCount22 * pointPerRectVert,
    bufferTexelSize = charCount22 * pointPerRectTexel;

    GLfloat *bufferMark2 = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel2 = new GLfloat[bufferTexelSize]; //texels

    for (quint16 index = 1; index < distCount; index++) {

        QPointF point(0,
                      (distStep * 10 * index));
        //centerOfText2.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText22.at(index - 1), point, scaleText,
                                            bufferMark2, ftOffset,
                                            bufferTexel2, txOffset);
    }

    hFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    hFontVBO->create();
    hFontVBO->bind();
    hFontVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    hFontVBO->allocate((bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    hFontVBO->write(0, bufferMark2, bufferMarkSize * sizeof(GLfloat));
    hFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel2, bufferTexelSize * sizeof(GLfloat));

    hFontVAO = new QOpenGLVertexArrayObject();
    hFontVAO->create();
    hFontVAO->bind();
    if (!vaoFont2->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    hFontVBO->release();
    hFontVAO->release();

    delete []  bufferMark2;
    delete []  bufferTexel2;
}*/

void GrideGL::render()
{
    programGride->bind();
    QMatrix4x4 m_modelMatrix;
    m_modelMatrix.setToIdentity();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programGride->setUniformValue("mvp", mvp);
    programGride->setUniformValue("objectColor", grideColor);

    /*vao->bind();
    GLsizei counter = 0;
    const float freqCircleInKm = 50;
    for (quint32 k = freqCircleInKm; k <= sceneOptions->maxDist; k+=freqCircleInKm) {
        quint32 l = k * 2 * M_PI;
        GLsizei segmentation = l * 10;

        glFunc->glDrawArrays(GL_LINE_LOOP, counter, segmentation);
        counter += segmentation;
    }

    glFunc->glDrawArrays(GL_LINES, counter, 4 * 2 + 12 * 2);
    counter += 24 * 3;
    vao->release();

    programGride->release();*/

    QVector2D tVecKM(sceneOptions->sceneRect.width() / camera_ptr->viewMatrixScale().x(),
                     sceneOptions->sceneRect.height() / camera_ptr->viewMatrixScale().y());
    //qDebug() << "KM - " << tVecKM;
    QVector2D tVecPix(sceneOptions->screenRect.width() / tVecKM.x(),
                      sceneOptions->screenRect.height() / tVecKM.y());
    //qDebug() << "KM - " << tVecKM << " PIX - " << tVecPix;
    const QVector3D viewCenter(camera_ptr->viewCenter());
    OpenGLRectF rectViewMatrix(viewCenter.x() - tVecKM.x() / 2.,
                               viewCenter.y() - tVecKM.y() / 2.,
                               tVecKM.x(), tVecKM.y());
    quint16 index = 0;
    if (tVecPix.x() < 5)
        index = 0;
    else if (tVecPix.x() > 5 && tVecPix.x() < 25)
        index = 1;
    else if (tVecPix.x() > 25 && tVecPix.x() < 50)
        index = 2;
    else if (tVecPix.x() > 50)
        index = 3;

    vaoDependOnScaleLevel.at(index)->bind();
    glFunc->glDrawArrays(GL_LINES, 0, grideBufferSize.at(index));
    vaoDependOnScaleLevel.at(index)->release();

    vaoAzGride->bind();
    glFunc->glDrawArrays(GL_LINES, 0, azGrideBufferSize);
    vaoAzGride->release();

    QMatrix4x4 model;
    //model.rotate(12, 1,1,0);
    mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix();
    programGride->setUniformValue("mvp", mvp);

    azHPlotVAO->bind();
    glFunc->glDrawArrays(GL_LINES, 0, hGrideIndicesCount);
    glFunc->glDrawArrays(GL_LINES, hGrideIndicesCount, azGrideIndicesCount);
    azHPlotVAO->release();

    programGride->release();

    m_modelMatrix.setToIdentity();
    //m_modelMatrix.rotate(15, 0, 0, 1);
    float zForGrideText = depth + 1.0;
    //const QVector3D scale = camera_ptr->viewMatrixScale();
    //m_modelMatrix.scale(1. / scale.x(), 1. / scale.y());
    mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programFont->bind();
    programFont->setUniformValue("mvp", mvp);
    programFont->setUniformValue("textureColor", textColor);
    programFont->setUniformValue("zcoord", zForGrideText);

    if (distMarkOn) {
        vaoFont2->bind();
        glFunc->glActiveTexture(GL_TEXTURE0);
        glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

        QVector<QPair<quint32, quint32> > vectorOfOffsetAndCount;
        calcCharPosition(index, rectViewMatrix, vectorOfOffsetAndCount);
        for (auto iter = vectorOfOffsetAndCount.begin();
             iter != vectorOfOffsetAndCount.end();
             iter++)
            glFunc->glDrawArrays(GL_TRIANGLES, iter->first, iter->second);

        glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        vaoFont2->release();
    }

    programFont->setUniformValue("textureColor", QColor::fromRgbF(0.36f, 0.31f, 0.80f, 0.7));
    if (azMarkOn) {
        vaoFont->bind();
        glFunc->glActiveTexture(GL_TEXTURE0);
        glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

        glFunc->glDrawArrays(GL_TRIANGLES, 0, fontBufferSize);

        glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        vaoFont->release();
    }

    programFont->setUniformValue("textureColor", QColor::fromRgbF(0.90f, 0.31f, 0.42f, 1.));

    hFontVAO->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());


    glFunc->glDrawArrays(GL_TRIANGLES, 0, hFontIndicesCount);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    hFontVAO->release();


    programFont->release();
}

void GrideGL::renderAzH()
{
    QMatrix4x4 mvp = extraCamera_ptr->projectionMatrix() * extraCamera_ptr->viewMatrix();
    programGride->bind();
    programGride->setUniformValue("mvp", mvp);
    programGride->setUniformValue("objectColor", grideColor);

    azHPlotVAO->bind();

    glFunc->glDrawArrays(GL_LINES, 0, hGrideIndicesCount);
    glFunc->glDrawArrays(GL_LINES, hGrideIndicesCount, azGrideIndicesCount);

    azHPlotVAO->release();

    programGride->release();

    float zForGrideText = depth + 1.0;
    programFont->bind();
    programFont->setUniformValue("mvp", mvp);
    programFont->setUniformValue("textureColor", QColor::fromRgbF(0.90f, 0.31f, 0.42f, 1.));
    programFont->setUniformValue("zcoord", zForGrideText);

    hFontVAO->bind();
    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());


    glFunc->glDrawArrays(GL_TRIANGLES, 0, hFontIndicesCount);

    //glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    hFontVAO->release();

    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(-90 * koeffAz,0);
    programFont->setUniformValue("mvp", extraCamera_ptr->projectionMatrix() * extraCamera_ptr->viewMatrix() * model);
    programFont->setUniformValue("textureColor", QColor::fromRgbF(0.36f, 0.31f, 0.80f, 0.7));

    azFontVAO->bind();
    //glFunc->glActiveTexture(GL_TEXTURE0);
    //glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, azFontIndicesCount);

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    azFontVAO->release();

    programFont->release();
}



void GrideGL::updateText(const float &horizontalScale)
{
    const QVector3D scale = camera_ptr->viewMatrixScale();

    //if (scale.x() > 1 || qFuzzyCompare(horizontalScale, 1.0f)) {
        //scaleText /= horizontalScale;
        qDebug() << scaleText;
    //}
    //else
    //    return;

    const quint32 nDimensionalMark = 2;
    GLfloat *bufferMark = new GLfloat[nDimensionalMark * fontBufferSize];

    quint32 offset = 0;
    float scaleOnText = scaleText / scale.x();
    qDebug() << scaleOnText;
    for (quint16 index = 0; index != vectorOfText.size(); index++) {
        fontDriver->updateVertexArrayForTextAtCurrentPosition(vectorOfText.at(index), centerOfText.at(index),
                                                              scaleOnText,
                                                              bufferMark, offset);
    }

    /*glFunc->glBindBuffer(GL_ARRAY_BUFFER, vboFont->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      nDimensionalMark * fontBufferSize * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    memcpy(vbo_ptr, bufferMark, sizeof(GLfloat) * nDimensionalMark * fontBufferSize);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;*/

    vboFont->bind();
    vboFont->write(0, bufferMark, sizeof(GLfloat) * nDimensionalMark * fontBufferSize);
    vboFont->release();

    delete [] bufferMark;

    /*bufferMark = new GLfloat[nDimensionalMark * fontBufferSize2];

    offset = 0;
    for (quint16 index = 0; index != vectorOfText2.size(); index++) {
        fontDriver->updateVertexArrayForTextAtCurrentPosition(vectorOfText2.at(index), centerOfText2.at(index), scaleText,
                                             bufferMark, offset);
    }

    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vboFont2->bufferId());
    vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      nDimensionalMark * fontBufferSize2 * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    memcpy(vbo_ptr, bufferMark, sizeof(GLfloat) * nDimensionalMark * fontBufferSize2);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    delete [] bufferMark;*/

    updateMoveText();
}

void GrideGL::updateMoveText()
{
    const QVector3D scale = camera_ptr->viewMatrixScale();
    const QVector3D viewCenter = camera_ptr->viewCenter();
    float angleRad = atan2(viewCenter.y(), viewCenter.x()) - ((M_PI / 6) * (2 / scale.x()));

    const quint32 nDimensionalMark = 2;
    GLfloat *bufferMark = new GLfloat[nDimensionalMark * fontBufferSize2];

    quint32 offset = 0;
    float scaleOnText = scaleText / scale.x();
    qDebug() << scaleOnText;
    QVector<QPointF> vecPoint;
    for (quint16 index = 0; index != vectorOfText2.size(); index++) {
        QPointF point(centerOfText2.at(index).y() * cos(angleRad),
                      centerOfText2.at(index).y() * sin(angleRad));
        vecPoint.push_back(point);
        fontDriver->updateVertexArrayForTextAtCurrentPosition(vectorOfText2.at(index), point,
                                                              scaleOnText,
                                                              bufferMark, offset);
    }

    /*glFunc->glBindBuffer(GL_ARRAY_BUFFER, vboFont2->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      nDimensionalMark * fontBufferSize2 * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    memcpy(vbo_ptr, bufferMark, sizeof(GLfloat) * nDimensionalMark * fontBufferSize2);
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;*/

    vboFont2->bind();
    vboFont2->write(0, bufferMark, sizeof(GLfloat) * nDimensionalMark * fontBufferSize2);
    vboFont2->release();

    delete [] bufferMark;
}

void GrideGL::setGrideColor(QColor color)
{
    grideColor = color;
}

void GrideGL::setTextColor(QColor color)
{
    textColor = color;
}

void GrideGL::setDistDiscret(const quint16 value)
{

}

void GrideGL::setAzDiscret(const quint16 value)
{

}

void GrideGL::setTextSize(const TextSizeAction flag, const float value)
{
    switch(flag) {
        case Increas:
        case Decreas:  {
            scaleText += value;
            break;
        }
        case Reset:  {
            scaleText = value;
            break;
        }
    }

    updateText(1.f);
}

void GrideGL::setAzMarkOnOff(bool flag)
{
    azMarkOn = flag;
}

void GrideGL::setDistMarkOnOff(bool flag)
{
    distMarkOn = flag;
}

void GrideGL::resetCameraSlot()
{
    updateText(1.);
}

void GrideGL::calcCharPosition(quint16 &index, OpenGLRectF &rectOfViewMatrix, QVector< QPair<quint32, quint32> > &resultVector)
{
    qint32 startPoint = 0, finishPoint = 0;
    qint32 x = rectOfViewMatrix.x(), y = rectOfViewMatrix.y();
    qint32 rightEdgeOfRect = rectOfViewMatrix.x() + rectOfViewMatrix.width();
    qint32 topEdgeOfRect = rectOfViewMatrix.y() + rectOfViewMatrix.height();
    QVector<qint32> radius;
    radius.push_back(sqrt(pow(x, 2) + pow(y, 2)));
    radius.push_back(sqrt(pow(x, 2) + pow(topEdgeOfRect, 2)));
    radius.push_back(sqrt(pow(rightEdgeOfRect, 2) + pow(topEdgeOfRect, 2)));
    radius.push_back(sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2)));
    quint16 max = 0, min = radius.front();
    for (auto iterRad = radius.begin(); iterRad != radius.end(); iterRad++) {
        if (*iterRad > max) {
            max = *iterRad;
        }
        if (*iterRad < min) {
            min = *iterRad;
        }
    }
    startPoint = min, finishPoint = max;

    if(x < 0 && rightEdgeOfRect < 0) {
        if (startPoint > abs(rightEdgeOfRect))
            startPoint = abs(rightEdgeOfRect);
    }
    else if (x > 0 && rightEdgeOfRect > 0) {
        if (startPoint > abs(x))
            startPoint = abs(x);
    }
    else if (x <= 0 && rightEdgeOfRect >= 0) {
        startPoint = 0;
    }


    /*if (x >= 0 && y >= 0) {
        startPoint = sqrt(pow(x, 2) + pow(y, 2));
        finishPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(topEdgeOfRect, 2));
    }
    else if (x >= 0 && y < 0) {
        startPoint = sqrt(pow(x, 2) + pow(topEdgeOfRect, 2));
        finishPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2));
    }
    else if (x < 0 && y >= 0) {
        if (rightEdgeOfRect < 0) {
            startPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2));
            finishPoint = sqrt(pow(x, 2) + pow(topEdgeOfRect, 2));
        }
        else {
            startPoint = 0;
            finishPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2));
        }
    }
    else if (x < 0 && y < 0) {
        if (rightEdgeOfRect >= 0 && topEdgeOfRect >= 0) {
            if (rightEdgeOfRect > topEdgeOfRect) {
                startPoint = sqrt(pow(x, 2) + pow(y, 2));
                finishPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(topEdgeOfRect, 2));
            }

        }
        else if (rightEdgeOfRect >= 0 && topEdgeOfRect < 0) {
            startPoint = sqrt(pow(x, 2) + pow(topEdgeOfRect, 2));
            finishPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2));
        }
        else if (rightEdgeOfRect < 0 && topEdgeOfRect>= 0) {
            if (rightEdgeOfRect < 0) {
                startPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2));
                finishPoint = sqrt(pow(x, 2) + pow(topEdgeOfRect, 2));
            }
            else {
                startPoint = 0;
                finishPoint = sqrt(pow(rightEdgeOfRect, 2) + pow(y, 2));
            }
        }
        else if (rightEdgeOfRect < 0 && topEdgeOfRect < 0) {

        }
    }*/
    /*if (rectOfViewMatrix.x() < 0 ) {
        if (leftEdgeOfRect <= 0) {
            startPoint = abs(leftEdgeOfRect);
            finishPoint = abs(rectOfViewMatrix.x());
        }
        else {
            if (leftEdgeOfRect > abs(rectOfViewMatrix.x())) {
                startPoint = 0;
                finishPoint = leftEdgeOfRect;
            }
            else {
                startPoint = 0;
                finishPoint = abs(rectOfViewMatrix.x());
            }
        }
    }
    else {
        startPoint = rectOfViewMatrix.x();
        finishPoint = leftEdgeOfRect;
    }*/

    /*quint16 topEdgeOfRect = abs(rectOfViewMatrix.y() + rectOfViewMatrix.height());
    if (topEdgeOfRect > finishPoint) {
        finishPoint = topEdgeOfRect;
    }*/

    quint16 discret = distStepDependOnScaleLevelVector.at(index);
    QVector<quint16> incomingCharacters;
    for (quint16 step = discret; step != sceneOptions->maxDist; step += discret) {
        if (step >= startPoint && step <= finishPoint) {
            incomingCharacters.push_back(step);
        }
    }

    resultVector.clear();
    quint16 lastItem = 0, counter = 0, previousItemInSequence = 0;
    for (auto iterIncomingCh = incomingCharacters.begin();
         iterIncomingCh != incomingCharacters.end();
         iterIncomingCh++) {

        if (iterIncomingCh == incomingCharacters.begin()) {
            lastItem = *iterIncomingCh;
            previousItemInSequence = lastItem;
            continue;
        }

        if (*iterIncomingCh == (lastItem + 1)) {
            if (lastItem < 10) {
                counter++;
                lastItem = *iterIncomingCh;
            }
            else if (lastItem >= 10 && lastItem < 100) {
                counter+=2;
                lastItem = *iterIncomingCh;
            }
            else {
                counter+=3;
                lastItem = *iterIncomingCh;
            }
        }
        else {
            quint32 offset = 0;
            if (lastItem < 10) {
                counter++;
            }
            else if (lastItem >= 10 && lastItem < 100) {
                counter+=2;
            }
            else {
                counter+=3;
            }
            if (previousItemInSequence < 10) {
                offset = previousItemInSequence - 1;
            }
            else if (previousItemInSequence >= 10 && previousItemInSequence < 100) {
                offset = (previousItemInSequence - 10) * 2 + 9;
            }
            else {
                offset = (previousItemInSequence - 100) * 3 + 90 * 2 + 9;
            }
            resultVector.push_back(qMakePair(offset * 6, counter * 6));
            counter = 0;
            previousItemInSequence = *iterIncomingCh;
            lastItem = *iterIncomingCh;
        }
    }

    quint32 offset = 0;
    if (lastItem < 10) {
        counter++;
    }
    else if (lastItem >= 10 && lastItem < 100) {
        counter+=2;
    }
    else {
        counter+=3;
    }
    if (previousItemInSequence < 10) {
        offset = previousItemInSequence - 1;
    }
    else if (previousItemInSequence >= 10 && previousItemInSequence < 100) {
        offset = (previousItemInSequence - 10) * 2 + 9;
    }
    else {
        offset = (previousItemInSequence - 100) * 3 + 90 * 2 + 9;
    }
    resultVector.push_back(qMakePair(offset * 6, counter * 6));
}

Test3D::Test3D(QOpenGLFunctions_3_3_Core *func, QOpenGLShaderProgram *prog, ftCustom *font, QObject *parent) :
    QObject(parent),
    glFunc(func), programGride(prog), camera3D(new Camera(this)),
    fontDriver(font),
    textSize(0.075f), grideTextSize(0.1f)
{    
    qRegisterMetaType<RLSOaimMessage>();

    camera3D->setPosition( QVector3D( 0.0f, 0.0f, 100.0f ) );
    camera3D->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
    camera3D->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );

    camera3D->resetScaleOfViewMatrix();

    pitchC = -90;
    rollC = 0;
    yawC = 0;
    cameraDist = 200;

    programTrace = new QOpenGLShaderProgram(this);

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/trace3DVertexShader.vert")) {
        qDebug() << programTrace->log();
        return;
    }

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/trace3DFragmentShader.frag")) {
        qDebug() << programTrace->log();
        return;
    }

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/trace3DGeometryShader.geom")) {
        qDebug() << programTrace->log();
        return;
    }
    if (!programTrace->link()) {
        qDebug() << programTrace->log();
        return;
    }

    programFont = new QOpenGLShaderProgram(this);
    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/sftVertexShader.vert")) {
        qDebug() << programFont->log();
        return;
    }

    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/sftFragmentShader.frag")) {
        qDebug() << programFont->log();
        return;
    }
    if (!programFont->link()) {
        qDebug() << programFont->log();
        return;
    }

    programFont3D = new QOpenGLShaderProgram(this);
    if (!programFont3D->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/sft3DVertexShader.vert")) {
        qDebug() << programFont3D->log();
        return;
    }

    if (!programFont3D->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/sft3DFragmentShader.frag")) {
        qDebug() << programFont3D->log();
        return;
    }
    if (!programFont3D->link()) {
        qDebug() << programFont3D->log();
        return;
    }

    programGrideFont = new QOpenGLShaderProgram(this);
    if (!programGrideFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/grideFontVertexShader.vert")) {
        qDebug() << programGrideFont->log();
        return;
    }

    if (!programGrideFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/grideFontFragmentShader.frag")) {
        qDebug() << programGrideFont->log();
        return;
    }
    if (!programGrideFont->link()) {
        qDebug() << programGrideFont->log();
        return;
    }

    programGride3DFont = new QOpenGLShaderProgram(this);
    if (!programGride3DFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/gride3DFontVertexShader.vert")) {
        qDebug() << programGride3DFont->log();
        return;
    }

    if (!programGride3DFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/gride3DFontFragmentShader.frag")) {
        qDebug() << programGride3DFont->log();
        return;
    }
    if (!programGride3DFont->link()) {
        qDebug() << programGride3DFont->log();
        return;
    }

    float alpha = 255 * 0.9;
    colors.push_back(QColor(240,163,10, alpha));
    colors.push_back(QColor(130,90,44, alpha));
    colors.push_back(QColor(0,80,239, alpha));
    colors.push_back(QColor(162,0,37, alpha));
    colors.push_back(QColor(27,161,226, alpha));

    colors.push_back(QColor(216,0,115, alpha));
    colors.push_back(QColor(164,196,0, alpha));
    colors.push_back(QColor(106,0,255, alpha));
    colors.push_back(QColor(96,169,23, alpha));
    colors.push_back(QColor(0,138,0, alpha));

    colors.push_back(QColor(118,96,138, alpha));
    colors.push_back(QColor(109,135,100, alpha));
    colors.push_back(QColor(250,104,0, alpha));
    colors.push_back(QColor(244,114,208, alpha));
    colors.push_back(QColor(229,20,0, alpha));

    colors.push_back(QColor(122,59,63, alpha));
    colors.push_back(QColor(100,118,135, alpha));
    colors.push_back(QColor(0,171,169, alpha));
    colors.push_back(QColor(170,0,255, alpha));
    colors.push_back(QColor(216,193,0, alpha));

    simpleFontDriver = new ftCustomSimple(this);
    simpleFontDriver->genTexels();
}

void Test3D::prepare()
{
    const quint32 nDimensional = 3;

    quint32 distStep = 10, maxDist = 300;

    quint32 coordsNumber = 0;
    for (quint32 k = distStep; k <= maxDist; k += distStep) {
        quint32 l = k * 2 * M_PI;
        if (k > 200)
            coordsNumber += 2 * (l / 16);
        else if (k <= 200 && k > 100)
            coordsNumber += 2 * (l / 4);
        else if (k <= 100 && k > 50)
            coordsNumber += 2 * (l / 2);
        else if (k <= 50 && k > 25)
            coordsNumber += 2 * (l);
        else if (k <= 25 && k > 10)
            coordsNumber += 2 * (4 * l);
        else if (k <= 10)
            coordsNumber += 2 * (8 * l);
    }
    firstBufferSize = coordsNumber;


    for (quint32 k = distStep; k <= maxDist; k += distStep) {
        quint32 l = (maxDist - k) * 2 * M_PI;
        coordsNumber += 2 * (l / 16);
    }

    secondBufferSize = coordsNumber - firstBufferSize;


    const quint32 sizeVertBuf = coordsNumber * nDimensional;
    GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

    quint32 posArr = 0;
    for (quint32 k = distStep; k <= maxDist; k += distStep) {
        quint32 l = k * 2 * M_PI;
        quint32 segmentation = 0;
        if (k > 200)
            segmentation = (l / 16);
        else if (k <= 200 && k > 100)
            segmentation = (l / 4);
        else if (k <= 100 && k > 50)
            segmentation = (l / 2);
        else if (k <= 50 && k > 25)
            segmentation = (l);
        else if (k <= 25 && k > 10)
            segmentation = (4 * l);
        else if (k <= 10)
            segmentation = (8 * l);

        double deltaAlpha = 2. * M_PI / static_cast<double>(segmentation);

        double alpha = 0;
        for (quint32 counter = 0; counter != segmentation; counter++) {
            vertBufGrid[posArr++] = k * cos(alpha);
            vertBufGrid[posArr++] = k * sin(alpha);
            vertBufGrid[posArr++] = 0.;
            alpha += deltaAlpha;
            vertBufGrid[posArr++] = k * cos(alpha);
            vertBufGrid[posArr++] = k * sin(alpha);
            vertBufGrid[posArr++] = 0.;
        }
    }

    for (quint32 k = distStep; k <= maxDist; k += distStep) {
        quint32 l = (maxDist - k) * 2 * M_PI;
        quint32 segmentation = (l / 16);

        quint32 segmentationMax = ((maxDist * 2 * M_PI) / 16);
        double deltaAlpha = 2. * M_PI / static_cast<double>(segmentationMax);

        float partOfK = k / (2. * maxDist);
        partOfK *= 360.;
        double alpha = (270. - partOfK) * degToRad;
        for (quint32 counter = 0; counter != segmentation; counter++) {
            vertBufGrid[posArr++] = maxDist * cos(alpha);
            vertBufGrid[posArr++] = maxDist * sin(alpha);
            vertBufGrid[posArr++] = k;
            alpha -= deltaAlpha;
            vertBufGrid[posArr++] = maxDist * cos(alpha);
            vertBufGrid[posArr++] = maxDist * sin(alpha);
            vertBufGrid[posArr++] = k;
        }
    }

    if (posArr != sizeVertBuf) {
        qDebug() << "Gride Array not filled correctly";
    }

    /*float position = 5;
    GLfloat vertices[] = {
            -0.5f + position, -0.5f + position, -0.f,
             0.5f + position, -0.5f + position, -0.f,
             0.5f + position,  0.5f + position, -0.f,
             0.5f + position,  0.5f + position, -0.f,
            -0.5f + position,  0.5f + position, -0.f,
            -0.5f + position, -0.5f + position, -0.f,
    };

    const quint32 sizeVertBuf = 4 * nDimensional;
    GLfloat *vertBufGrid = new GLfloat[sizeVertBuf];

    quint32 pos = 0;
    vertBufGrid[pos++] = 0;
    vertBufGrid[pos++] = -10;
    vertBufGrid[pos++] = 0.;

    vertBufGrid[pos++] = 0;
    vertBufGrid[pos++] = 10;
    vertBufGrid[pos++] = 0.;

    vertBufGrid[pos++] = 30;
    vertBufGrid[pos++] = 30;
    vertBufGrid[pos++] = 0.;

    vertBufGrid[pos++] = 40;
    vertBufGrid[pos++] = 40;
    vertBufGrid[pos++] = 0;*/

    //azGrideBufferSize = sizeVertBuf / nDimensional;

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    //vbo->allocate(vertices, sizeof(vertices));
    vbo->allocate(vertBufGrid, sizeVertBuf * sizeof(GLfloat));

    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();

    delete[] vertBufGrid;





    GLfloat tempVertex[] = {0, 0, 50};

    traceVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    traceVBO->create();
    traceVBO->bind();
    traceVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    traceVBO->allocate(nDimensional * sizeof (GLfloat));
    //traceVBO->allocate(tempVertex, nDimensional * sizeof (GLfloat));

    traceVAO = new QOpenGLVertexArrayObject();
    traceVAO->create();
    traceVAO->bind();
    if (!traceVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programTrace->enableAttributeArray("posAttr");
    programTrace->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    traceVBO->release();
    traceVAO->release();


    float radMark = 2;
    //float lMark = radMark * 2 * M_PI;
    //quint32 coordsNumberForTrackMark = 2 * (4 * lMark);
    quint16 segmentationForMark = 40;
    quint32 coordsNumberForMark = segmentationForMark * nDimensional;
    quint16 numberOfBuffers = 2;
    GLfloat *bufferForTrackMark = new GLfloat[numberOfBuffers * coordsNumberForMark];

    double deltaAlpha = 2. * M_PI / static_cast<double>(segmentationForMark);

    double alpha = 0;
    quint32 offsetForBufferMark = 0;
    for (quint32 counter = 0; counter != segmentationForMark; counter++) {
        bufferForTrackMark[offsetForBufferMark++] = radMark * cos(alpha);
        bufferForTrackMark[offsetForBufferMark++] = radMark * sin(alpha);
        bufferForTrackMark[offsetForBufferMark++] = 0.1;
        alpha += deltaAlpha;
    }

    alpha = 0;
    for (quint32 counter = 0; counter != segmentationForMark; counter++) {
        bufferForTrackMark[offsetForBufferMark++] = radMark * cos(alpha);
        bufferForTrackMark[offsetForBufferMark++] = 0;
        bufferForTrackMark[offsetForBufferMark++] = radMark * sin(alpha);
        alpha += deltaAlpha;
    }

    segmentationForAxisMark = segmentationForMark;

    trackMarkOnAxisVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    trackMarkOnAxisVBO->create();
    trackMarkOnAxisVBO->bind();
    trackMarkOnAxisVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    trackMarkOnAxisVBO->allocate(bufferForTrackMark, numberOfBuffers * coordsNumberForMark * sizeof (GLfloat));

    trackMarkOnAxisVAO = new QOpenGLVertexArrayObject();
    trackMarkOnAxisVAO->create();
    trackMarkOnAxisVAO->bind();
    if (!trackMarkOnAxisVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    trackMarkOnAxisVBO->release();
    trackMarkOnAxisVAO->release();

    delete [] bufferForTrackMark;






    const quint16 pointInTriangle = 3,
                  trianglesInRect = 2,
                  numberOfBuffersOfTextRect = 4;
    const quint32 bufferForTextRectSize = nDimensional * pointInTriangle * trianglesInRect * numberOfBuffersOfTextRect;
    GLfloat *bufferForTextRect = new GLfloat[bufferForTextRectSize];

    numberOfIndicesInTextRect = pointInTriangle * trianglesInRect;

    quint16 rectWidth = 60, rectHeight = 10, markWidth = 4;
    const OpenGLRectF rectLeft(0, 0,
                           markWidth, rectHeight),
            rectRight(markWidth, 0,
                      rectWidth - markWidth, rectHeight);
    // XY RECT
    float zForXYRect = 6.;
    quint16 indexInBufferForText = 0;
    // left rect
    bufferForTextRect[indexInBufferForText++] = rectLeft.x();
    bufferForTextRect[indexInBufferForText++] = rectLeft.y();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectLeft.x() + rectLeft.width();
    bufferForTextRect[indexInBufferForText++] = rectLeft.y();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectLeft.x();
    bufferForTextRect[indexInBufferForText++] = rectLeft.y() + rectLeft.height();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectLeft.x() + rectLeft.width();
    bufferForTextRect[indexInBufferForText++] = rectLeft.y();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectLeft.x() + rectLeft.width();
    bufferForTextRect[indexInBufferForText++] = rectLeft.y() + rectLeft.height();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectLeft.x();
    bufferForTextRect[indexInBufferForText++] = rectLeft.y() + rectLeft.height();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    // right rect
    bufferForTextRect[indexInBufferForText++] = rectRight.x();
    bufferForTextRect[indexInBufferForText++] = rectRight.y();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectRight.x() + rectRight.width();
    bufferForTextRect[indexInBufferForText++] = rectRight.y();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectRight.x();
    bufferForTextRect[indexInBufferForText++] = rectRight.y() + rectRight.height();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectRight.x() + rectRight.width();
    bufferForTextRect[indexInBufferForText++] = rectRight.y();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectRight.x() + rectRight.width();
    bufferForTextRect[indexInBufferForText++] = rectRight.y() + rectRight.height();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    bufferForTextRect[indexInBufferForText++] = rectRight.x();
    bufferForTextRect[indexInBufferForText++] = rectRight.y() + rectRight.height();
    bufferForTextRect[indexInBufferForText++] = zForXYRect;

    // XZ RECT
    bufferForTextRect[indexInBufferForText++] = rectLeft.x();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectLeft.y();

    bufferForTextRect[indexInBufferForText++] = rectLeft.x() + rectLeft.width();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectLeft.y();

    bufferForTextRect[indexInBufferForText++] = rectLeft.x();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectLeft.y() + rectLeft.height();

    bufferForTextRect[indexInBufferForText++] = rectLeft.x() + rectLeft.width();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectLeft.y();

    bufferForTextRect[indexInBufferForText++] = rectLeft.x() + rectLeft.width();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectLeft.y() + rectLeft.height();

    bufferForTextRect[indexInBufferForText++] = rectLeft.x();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectLeft.y() + rectLeft.height();

    // right rect
    bufferForTextRect[indexInBufferForText++] = rectRight.x();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectRight.y();

    bufferForTextRect[indexInBufferForText++] = rectRight.x() + rectRight.width();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectRight.y();

    bufferForTextRect[indexInBufferForText++] = rectRight.x();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectRight.y() + rectRight.height();

    bufferForTextRect[indexInBufferForText++] = rectRight.x() + rectRight.width();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectRight.y();

    bufferForTextRect[indexInBufferForText++] = rectRight.x() + rectRight.width();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectRight.y() + rectRight.height();

    bufferForTextRect[indexInBufferForText++] = rectRight.x();
    bufferForTextRect[indexInBufferForText++] = 0;
    bufferForTextRect[indexInBufferForText++] = rectRight.y() + rectRight.height();

    textRect = rectRight;

    textRectVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    textRectVBO->create();
    textRectVBO->bind();
    textRectVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    textRectVBO->allocate(bufferForTextRect, bufferForTextRectSize * sizeof (GLfloat));

    textRectVAO = new QOpenGLVertexArrayObject();
    textRectVAO->create();
    textRectVAO->bind();
    if (!textRectVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    textRectVBO->release();
    textRectVAO->release();

    delete[] bufferForTextRect;






    fontVAO = new QOpenGLVertexArrayObject();
    fontVAO->create();
    fontVAO->bind();
    if (!fontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    const quint16 sizeFontPoint = 6;
    const quint16 nDimensionalFont = 2;
    const quint16 buffSizeInByte = sizeFontPoint * nDimensionalFont * sizeof(GLfloat);
    GLfloat fontVertex[sizeFontPoint * nDimensionalFont] = {
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0
    };
    GLfloat texelVertex[sizeFontPoint * nDimensionalFont]
            = { 0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f };

    fontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    fontVBO->create();
    fontVBO->bind();
    fontVBO->allocate(fontVertex, 2 * buffSizeInByte);
    fontVBO->write(buffSizeInByte, texelVertex,buffSizeInByte);
    fontVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);

    programFont->enableAttributeArray("vertex");
    programFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalFont, 0);
    programFont->enableAttributeArray("texels");
    programFont->setAttributeBuffer("texels", GL_FLOAT, buffSizeInByte, nDimensionalFont, 0);

    fontVBO->release();
    fontVAO->release();



    fontHVAO = new QOpenGLVertexArrayObject();
    fontHVAO->create();
    fontHVAO->bind();
    if (!fontHVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    const quint16 fontVertexSize = sizeFontPoint * nDimensional;
    GLfloat fontVertex2[] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    };

    fontHVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    fontHVBO->create();
    fontHVBO->bind();
    fontHVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    fontHVBO->allocate(fontVertex2, (fontVertexSize + sizeFontPoint * nDimensionalFont) * sizeof(GLfloat));
    fontHVBO->write(fontVertexSize * sizeof(GLfloat), texelVertex, sizeFontPoint * nDimensionalFont * sizeof(GLfloat));

    programFont3D->enableAttributeArray("vertex");
    programFont3D->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensional, 0);
    programFont3D->enableAttributeArray("texels");
    programFont3D->setAttributeBuffer("texels", GL_FLOAT, fontVertexSize * sizeof(GLfloat), nDimensionalFont, 0);

    fontHVBO->release();
    fontHVAO->release();



    const quint16 markNumber = 12;
    const quint32 nDimensionalMark = 2;
    const quint8 vertexPerTriangle = 3;
    const quint8 trianglePerRect = 2;
    const quint32 pointPerRectVert = nDimensionalMark * vertexPerTriangle * trianglePerRect;
    const quint32 pointPerRectTexel = nDimensional * vertexPerTriangle * trianglePerRect;

    quint32 ftOffset = 0, txOffset = 0;
    //const GLfloat scaleText = 0.1;
    const float dAz = 360. /  static_cast<float>(markNumber);
    const float convers = M_PI / 180.;

    quint32 charCount = 0;
    QVector<QString> vectorOfText;
    for (quint16 index = 0; index < markNumber; index++) {
        QString str(QString::number(dAz * index));
        vectorOfText.push_back(str);
        charCount += str.size();
    }
    numberOfIndicesOfGrideAzText = charCount * vertexPerTriangle * trianglePerRect;

    quint32 bufferMarkSize = charCount * pointPerRectVert,
            bufferTexelSize = charCount * pointPerRectTexel;

    GLfloat *bufferMark = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel = new GLfloat[bufferTexelSize]; //texels
    for (quint16 index = 0; index < markNumber; index++) {
        /*QSizeF rectSize = fontDriver->genRectForText(vectorOfText.at(index), scaleText);
        OpenGLRectF rect((sceneOptions->maxDist + rectSize.width() / 2 + 5) * cos(M_PI_2 - (index * dAz * convers)) - rectSize.width() / 2,
                         (sceneOptions->maxDist + rectSize.width() / 2 + 5) * sin(M_PI_2 - (index * dAz * convers)) - rectSize.height() / 2,
                         rectSize.width(), rectSize.height());*/
        QPointF point((maxDist + 10) * cos(M_PI_2 - (index * dAz * convers)),
                      (maxDist + 10) * sin(M_PI_2 - (index * dAz * convers)));
        //centerOfText.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText.at(index), point, grideTextSize,
                                            bufferMark, ftOffset,
                                            bufferTexel, txOffset);
    }

    grideAzFontVAO = new QOpenGLVertexArrayObject();
    grideAzFontVAO->create();
    grideAzFontVAO->bind();
    if (!grideAzFontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    grideAzFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    grideAzFontVBO->create();
    grideAzFontVBO->bind();
    grideAzFontVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    grideAzFontVBO->allocate(bufferMark, (bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    grideAzFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel, bufferTexelSize * sizeof(GLfloat));

    programGrideFont->enableAttributeArray("vertex");
    programGrideFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programGrideFont->enableAttributeArray("texels");
    programGrideFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    grideAzFontVBO->release();
    grideAzFontVAO->release();

    delete []  bufferMark;
    delete []  bufferTexel;


    const quint32 distCount = maxDist / distStep;
    ftOffset = 0, txOffset = 0;
    quint32 charCount2 = 0;
    QVector<QString> vectorOfText2;
    for (quint16 index = 1; index < distCount; index++) {
        QString str(QString::number(distStep * index));
        vectorOfText2.push_back(str);
        charCount2 += str.size();
    }
    numberOfIndicesOfGrideDistText = charCount2 * vertexPerTriangle * trianglePerRect;

    bufferMarkSize = charCount2 * pointPerRectVert,
    bufferTexelSize = charCount2 * pointPerRectTexel;

    GLfloat *bufferMark2 = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel2 = new GLfloat[bufferTexelSize]; //texels

    for (quint16 index = 1; index < distCount; index++) {
        QPointF point((distStep * index) * cos(M_PI_2),
                      (distStep * index) * sin(M_PI_2));
        //centerOfText2.push_back(point);
        fontDriver->genTextAtCurrentPosition(vectorOfText2.at(index - 1), point, grideTextSize,
                                            bufferMark2, ftOffset,
                                            bufferTexel2, txOffset);
    }

    grideDistFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    grideDistFontVBO->create();
    grideDistFontVBO->bind();
    grideDistFontVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    grideDistFontVBO->allocate((bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    grideDistFontVBO->write(0, bufferMark2, bufferMarkSize * sizeof(GLfloat));
    grideDistFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel2, bufferTexelSize * sizeof(GLfloat));

    grideDistFontVAO = new QOpenGLVertexArrayObject();
    grideDistFontVAO->create();
    grideDistFontVAO->bind();
    if (!grideDistFontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programGrideFont->enableAttributeArray("vertex");
    programGrideFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalMark, 0);
    programGrideFont->enableAttributeArray("texels");
    programGrideFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    grideDistFontVBO->release();
    grideDistFontVAO->release();

    delete []  bufferMark2;
    delete []  bufferTexel2;


    quint32 charCount3 = 0;
    QVector<QString> vectorOfText3;
    quint16 distStep2 = 1;
    for (quint16 index = 1; index < distCount; index++) {
        QString str(QString::number(distStep2 * index));
        vectorOfText3.push_back(str);
        charCount3 += str.size();
    }
    numberOfIndicesOfGrideHText = charCount3 * vertexPerTriangle * trianglePerRect;
    ftOffset = 0, txOffset = 0;
    bufferMarkSize = charCount3 * pointPerRectTexel,
    bufferTexelSize = charCount3 * pointPerRectTexel;

    GLfloat *bufferMark3 = new GLfloat[bufferMarkSize]; //vertex
    GLfloat *bufferTexel3 = new GLfloat[bufferTexelSize]; //texels

    //distStep = 1;
    for (quint16 index = 1; index < distCount; index++) {
        /*QPointF point((distStep * index) * cos(M_PI_2),
                      (distStep * index) * sin(M_PI_2));*/
        QVector3D point(0, maxDist - 3., (distStep * index));
        //centerOfText2.push_back(point);
        fontDriver->genTextAtCurrentVerticalPosition(vectorOfText3.at(index - 1), point, grideTextSize,
                                                     bufferMark3, ftOffset,
                                                     bufferTexel3, txOffset);
    }

    grideHFontVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    grideHFontVBO->create();
    grideHFontVBO->bind();
    grideHFontVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    grideHFontVBO->allocate((bufferMarkSize + bufferTexelSize) * sizeof(GLfloat));
    grideHFontVBO->write(0, bufferMark3, bufferMarkSize * sizeof(GLfloat));
    grideHFontVBO->write(bufferMarkSize * sizeof(GLfloat), bufferTexel3, bufferTexelSize * sizeof(GLfloat));

    grideHFontVAO = new QOpenGLVertexArrayObject();
    grideHFontVAO->create();
    grideHFontVAO->bind();
    if (!grideHFontVAO->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programGride3DFont->enableAttributeArray("vertex");
    programGride3DFont->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensional, 0);
    programGride3DFont->enableAttributeArray("texels");
    programGride3DFont->setAttributeBuffer("texels", GL_FLOAT, bufferMarkSize * sizeof (GLfloat), nDimensional, 0);

    grideHFontVBO->release();
    grideHFontVAO->release();

    delete []  bufferMark3;
    delete []  bufferTexel3;
}

void Test3D::updateScaleOfView(const float &horizontalScale)
{
    camera3D->updateScaleOfViewMatrix(horizontalScale);
    cameraDist *= horizontalScale;
}

void Test3D::updateEulerAngels(float yaw, float pitch, float roll)
{
    if ( !qFuzzyIsNull( yaw ) )
    {
        //m_camera->yaw( m_yawAngle, QVector3D( 0.0f, 1.0f, 0.0f ) );
        camera3D->yawAboutViewCenter(yaw);
    }

    if ( !qFuzzyIsNull( pitch ) )
    {
        //m_camera->pitch( m_pitchAngle );
        camera3D->pitchAboutViewCenter(pitch);
    }

    if ( !qFuzzyIsNull( roll ) )
    {
        //m_camera->roll( m_rollAngle );
        camera3D->rollAboutViewCenter(roll);
    }

    yawC += yaw;
    pitchC += pitch;
    rollC += roll;
    if (pitchC < -80) {
        pitchC = -80;
    }
    else if (pitchC > 0) {
        pitchC = 0;
    }
    qDebug() << pitchC << yawC << rollC;
}

void Test3D::addTraceMark(RLSOaimMessage msg)
{
    quint16 id = static_cast<quint32>(msg.trackID);
    auto iter = mapTraceMark.find(id);
    if (iter != mapTraceMark.end()) {
        TraceMark mark = iter.value();

        mark.id = id;
        mark.az = msg.Az;
        mark.dist = msg.D / 1000.;//sqrt(pow(msg.D / 1000., 2) - pow(msg.sAimCoords.h / 1000., 2));
        mark.course = msg.tack;
        mark.speed = msg.vp;
        mark.h = msg.h / 1000.;
        float hypotenuseDist = sqrt(pow(mark.dist, 2) + pow(mark.h, 2));
        float tita  = M_PI_4 - atan2(mark.h, mark.dist);
        float fi = (90. - mark.az) * degToRad;
        mark.xPos = hypotenuseDist * sin(tita) * cos(fi);
        mark.yPos = hypotenuseDist * sin(tita) * sin(fi);
        //mark.xPos = mark.dist * cosf((90 - mark.az) * M_PI / 180.);
        //mark.yPos = mark.dist * sinf((90 - mark.az) * M_PI / 180.);

        mapTraceMark.insert(id, mark);
    }
    else {

        TraceMark mark;

        mark.id = id;
        mark.az = msg.Az;
        mark.dist = msg.D / 1000.;//sqrt(pow(msg.D / 1000., 2) - pow(msg.sAimCoords.h / 1000., 2));
        mark.course = msg.tack;
        mark.speed = msg.vp;
        mark.h = msg.h / 1000.;
        float hypotenuseDist = sqrt(pow(mark.dist, 2) + pow(mark.h, 2));
        float tita  = M_PI_4 - atan2(mark.h, mark.dist);
        float fi = (90. - mark.az) * degToRad;
        mark.xPos = hypotenuseDist * sin(tita) * cos(fi);
        mark.yPos = hypotenuseDist * sin(tita) * sin(fi);
        //mark.xPos = mark.dist * cosf((90 - mark.az) * M_PI / 180.);
        //mark.yPos = mark.dist * sinf((90 - mark.az) * M_PI / 180.);

        mapTraceMark.insert(id, mark);
    }
}


void Test3D::render()
{
    float vpY = 1040 * 0.65;
    float vpH = 1040 * 0.35;
    glFunc->glViewport(0,
                       vpY,
                       1920,
                       vpH);

   /* camera3D->setPerspectiveProjection(45.f,
                                       960. / 1010.,
                                       0.1, 5000);

    QMatrix4x4 mvp = camera3D->projectionMatrix() * camera3D->viewMatrix();


    QVector3D posCamera = camera3D->position();
    QVector3D upVector = camera3D->upVector();
    QVector3D viewCenter = camera3D->viewCenter();*/

    GLfloat aspect = 1900 / vpH;
    QMatrix4x4 proj, view;
    proj.perspective(40.f,
                     aspect,
                     0.1, 5000);
    float maxDist = 300;
    /*proj.ortho(-maxDist * aspect, maxDist * aspect,
               -maxDist, maxDist,
               -maxDist, maxDist);*/
    QQuaternion quaternion(QQuaternion::fromEulerAngles(pitchC, yawC, rollC));
    QVector3D eulerAngles = quaternion.toEulerAngles();
    view.lookAt(QVector3D(cameraDist * sin(eulerAngles.x() * degToRad) * cos(90. * degToRad),
                          cameraDist * sin(eulerAngles.x() * degToRad) * sin(90. * degToRad),
                          cameraDist * cos(eulerAngles.x() * degToRad)),
                QVector3D(0,150,100),
                QVector3D(0,1,0));
    /*view.lookAt(QVector3D(0,2,-1),
                QVector3D(0,0,0),
                QVector3D(0,1,0));*/



    programGride->bind();
    programGride->setUniformValue("mvp", proj * view);
    //programGride->setUniformValue("mvp", mvp);

    vao->bind();

    //programGride->setUniformValue("objectColor", QColor::fromRgbF(0.4f, 0.4f, 0.4f, 0.4f));
    //glFunc->glDrawArrays(GL_LINES, 0, firstBufferSize);
    programGride->setUniformValue("objectColor", QColor::fromRgbF(0.6f, 0.6f, 0.6f, 0.4f));
    glFunc->glDrawArrays(GL_LINES, firstBufferSize, secondBufferSize);

    vao->release();
    programGride->release();



    float zForGrideText = 2.0;
    programGrideFont->bind();
    programGrideFont->setUniformValue("mvp", proj * view);
    programGrideFont->setUniformValue("textureColor", QColor::fromRgbF(0.60f, 0.55f, 0.09f, 0.7));
    programGrideFont->setUniformValue("zcoord", zForGrideText);


    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    /*grideDistFontVAO->bind();
    //glFunc->glActiveTexture(GL_TEXTURE0);
    //glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, numberOfIndicesOfGrideDistText);
    grideDistFontVAO->release();*/

    view.rotate(eulerAngles.z(),0,0,1.);
    programGrideFont->setUniformValue("mvp", proj * view);
    programGrideFont->setUniformValue("textureColor", QColor::fromRgbF(0.36f, 0.31f, 0.80f, 0.7));

    grideAzFontVAO->bind();
    glFunc->glDrawArrays(GL_TRIANGLES, 0, numberOfIndicesOfGrideAzText);
    //glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    grideAzFontVAO->release();

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    programGrideFont->release();


    programGride3DFont->bind();
    programGride3DFont->setUniformValue("mvp", proj * view);
    programGride3DFont->setUniformValue("textureColor", QColor::fromRgbF(0.80f, 0.31f, 0.42f, 0.7));


    glFunc->glActiveTexture(GL_TEXTURE0);
    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, fontDriver->getTextureArray());

    grideHFontVAO->bind();
    glFunc->glDrawArrays(GL_TRIANGLES, 0, numberOfIndicesOfGrideDistText);
    grideHFontVAO->release();

    glFunc->glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    programGride3DFont->release();


    quint8 indexOfMark = 0;
    /*programTrace->bind();
    programTrace->setUniformValue("mvp", proj * view);
    programTrace->setUniformValue("aspect", aspect);
    //programTrace->setUniformValue("objectColor", QColor::fromRgbF(1.,1.,1.,1.));

    for (auto &itemOfTraceMap : mapTraceMark) {

        //programTrace->setUniformValue("course", itemOfTraceMap.course);

        programTrace->setUniformValue("objectColor", colors.at(indexOfMark++));
        quint8 index = 0;
        GLfloat *buffer = new GLfloat[3];
        buffer[index++] = itemOfTraceMap.xPos;
        buffer[index++] = itemOfTraceMap.yPos;
        buffer[index++] = itemOfTraceMap.h * 10;

        traceVBO->bind();
        traceVBO->write(0, buffer, 3*sizeof (GLfloat));
        traceVBO->release();

        traceVAO->bind();
        glFunc->glDrawArrays(GL_POINTS,0,1);
        traceVAO->release();

        delete [] buffer;
    }
    programTrace->release();*/

    programGride->bind();
    //programGride->setUniformValue("objectColor", QColor::fromRgbF(1.f, 1.f, 1.f, 0.6f));

    indexOfMark = 0;
    trackMarkOnAxisVAO->bind();
    for (auto &itemOfTraceMap : mapTraceMark) {
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(itemOfTraceMap.xPos, itemOfTraceMap.yPos, 0.);

        QColor reducedAlpha = colors.at(indexOfMark++);
        reducedAlpha.setAlphaF(reducedAlpha.alphaF() - 0.3);

        //programGride->setUniformValue("mvp", proj * view * model);
        programGride->setUniformValue("objectColor", reducedAlpha);


        //glFunc->glDrawArrays(GL_LINE_STRIP, 0, segmentationForAxisMark);

        float alpha = atan2(itemOfTraceMap.yPos, itemOfTraceMap.xPos);
        float maxDist = 300;
        model.setToIdentity();
        model.translate(maxDist * cos(alpha),
                        maxDist * sin(alpha),
                        itemOfTraceMap.h * 10);
        //model.rotate(-alpha * 180. / M_PI, 0.,0.,1.);


        programGride->setUniformValue("mvp", proj * view * model);
        glFunc->glDrawArrays(GL_LINE_STRIP, segmentationForAxisMark, segmentationForAxisMark);

    }

    trackMarkOnAxisVAO->release();

    /*textRectVAO->bind();
    indexOfMark = 0;
    programGride->setUniformValue("objectColor", QColor::fromRgbF(0.35,0.35,0.35,0.8));
    for (auto &itemOfTraceMap : mapTraceMark) {
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(itemOfTraceMap.xPos + 5, itemOfTraceMap.yPos, 0.);
        model.rotate(-pitchC, 1., 0., 0.);

        QColor reducedAlpha = colors.at(indexOfMark++);
        reducedAlpha.setAlphaF(reducedAlpha.alphaF() - 0.2);

        programGride->setUniformValue("objectColor", QColor::fromRgbF(0.35,0.35,0.35,0.8));
        programGride->setUniformValue("mvp", proj * view * model);
        //programGride->setUniformValue("objectColor", reducedAlpha);

        glFunc->glDrawArrays(GL_TRIANGLES, numberOfIndicesInTextRect, numberOfIndicesInTextRect);

        programGride->setUniformValue("objectColor", reducedAlpha);
        glFunc->glDrawArrays(GL_TRIANGLES, 0, numberOfIndicesInTextRect);
    }*/

    indexOfMark = 0;
    for (auto &itemOfTraceMap : mapTraceMark) {
        float alpha = atan2(itemOfTraceMap.yPos, itemOfTraceMap.xPos);
        float maxDist = 292;
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(maxDist * cos(alpha) + 5.,
                        maxDist * sin(alpha) + 5.,
                        itemOfTraceMap.h * 10);
        model.rotate(-rollC, 0., 0., 1.);

        QColor reducedAlpha = colors.at(indexOfMark++);
        reducedAlpha.setAlphaF(reducedAlpha.alphaF() - 0.2);

        programGride->setUniformValue("mvp", proj * view * model);
        programGride->setUniformValue("objectColor", QColor::fromRgbF(0.35,0.35,0.35,0.8));
        //programGride->setUniformValue("objectColor", reducedAlpha);


        glFunc->glDrawArrays(GL_TRIANGLES,  3 * numberOfIndicesInTextRect, numberOfIndicesInTextRect);

        programGride->setUniformValue("objectColor", reducedAlpha);
        glFunc->glDrawArrays(GL_TRIANGLES, 2 * numberOfIndicesInTextRect, numberOfIndicesInTextRect);

    }
    textRectVAO->release();

    programGride->release();

    /*float zcoord = 7.;
    programFont->bind();
    //programFont->setUniformValue("mvp", mvp);
    programFont->setUniformValue("zcoord", zcoord);
    programFont->setUniformValue("textureColor", QVector3D(0.60f,0.55f,0.09f));

    programFont->setUniformValue("texture0", 0);
    glFunc->glActiveTexture(GL_TEXTURE0);
    fontVAO->bind();

    for (auto &itemOfTraceMap : mapTraceMark) {
        quint16 id = itemOfTraceMap.id;
        const TraceMark &mark = itemOfTraceMap;

       QMatrix4x4 model;
        model.setToIdentity();
        model.translate(itemOfTraceMap.xPos + 5, itemOfTraceMap.yPos, 0.);
        model.rotate(-pitchC, 1., 0., 0.);
        programFont->setUniformValue("mvp", proj * view * model);

        float iDist = sqrt(pow(mark.xPos, 2) + pow(mark.yPos, 2));
        QVector<QString> vecOfStr;
        vecOfStr.push_back(QString("  #%1:%2км").arg(id).arg(iDist, 0, 'f', 2));
        //vecOfStr.push_back(QString(" #%1").arg(id));
        //vecOfStr.push_back(QString(" %1км").arg(mark.dist, 0, 'f', 2));
        //vecOfStr.push_back(QString(" %1°").arg(mark.az, 0, 'f', 1));
        //vecOfStr.push_back(QString(" %1км").arg(mark.h, 0, 'f', 3));
        //vecOfStr.push_back(QString(" %1м/с").arg(mark.speed, 0, 'f', 2));

        float heightOfText = textRect.height() / vecOfStr.size();
        //qDebug() << logBookSize.height() << heightOfText;
        QVector<QPointF> vecOfPoint;
        for (quint16 index = 0; index < vecOfStr.size(); index++) {            
            vecOfPoint.push_back(QPointF(0, textRect.height()  - (heightOfText * (index + 1)) + (index * heightOfText * 0.2) + 2 ));
        }

        float currentFontSize = textSize;

        for (quint16 indexV = 0; indexV < vecOfStr.size(); indexV++) {
            const quint16 oneBuffSize = 6 * 2;
            const quint16 oneBuffSizeInByte = oneBuffSize * sizeof(GLfloat);
            GLfloat *vertBuff = new GLfloat[vecOfStr.at(indexV).size() * oneBuffSize];
            sVectorCharacterId charId = simpleFontDriver->genText(vecOfStr.at(indexV),
                                                                  vecOfPoint.at(indexV).x(),
                                                                  vecOfPoint.at(indexV).y(),
                                                                  currentFontSize,
                                                                  vertBuff);

            int index = 0;
            for (auto &texture : charId) {
                texture->bind();
                fontVBO->bind();
                fontVBO->write(0, (vertBuff + index * oneBuffSize), oneBuffSizeInByte);
                fontVBO->release();

                glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
                texture->release();
                index++;
            }

            delete [] vertBuff;
        }
    }

    fontVAO->release();
    programFont->release();*/


    programFont3D->bind();
    //programFont->setUniformValue("mvp", mvp);
    programFont3D->setUniformValue("textureColor", QColor::fromRgbF(0.90f, 0.31f, 0.42f, 1.));

    programFont3D->setUniformValue("texture0", 0);
    glFunc->glActiveTexture(GL_TEXTURE0);
    fontHVAO->bind();

    for (auto &itemOfTraceMap : mapTraceMark) {
        quint16 id = itemOfTraceMap.id;
        const TraceMark &mark = itemOfTraceMap;

        float alpha = atan2(itemOfTraceMap.yPos, itemOfTraceMap.xPos);
        float maxDist = 290;

        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(maxDist * cos(alpha) + 5.,
                        maxDist * sin(alpha) + 5.,
                        itemOfTraceMap.h * 10);
        model.rotate(-rollC, 0., 0., 1.);

        programFont3D->setUniformValue("mvp", proj * view * model);

        QVector<QString> vecOfStr;
        vecOfStr.push_back(QString("  #%1:%2км").arg(id).arg(mark.h, 0, 'f', 3));
        //vecOfStr.push_back(QString(" #%1").arg(id));
        //vecOfStr.push_back(QString(" %1км").arg(mark.dist, 0, 'f', 2));
        //vecOfStr.push_back(QString(" %1°").arg(mark.az, 0, 'f', 1));
        //vecOfStr.push_back(QString(" %1км").arg(mark.h, 0, 'f', 3));
        //vecOfStr.push_back(QString(" %1м/с").arg(mark.speed, 0, 'f', 2));

        float heightOfText = textRect.height() / vecOfStr.size();
        //qDebug() << logBookSize.height() << heightOfText;
        QVector<QVector3D> vecOfPoint;
        for (quint16 index = 0; index < vecOfStr.size(); index++) {
            /*vecOfPoint.push_back(QPointF(logBookRect.at(indexBuff).x(),
                                     logBookRect.at(indexBuff).y() + logBookRect.at(indexBuff).height() - (heightOfText * (index + 1)) + 2));*/
            //vecOfPoint.push_back(QPointF(0, textRect.height()  - (heightOfText * (index + 1)) + (index * heightOfText * 0.2) + 1 ));
            vecOfPoint.push_back(QVector3D(0, textRect.height()  - (heightOfText * (index + 1)) + (index * heightOfText * 0.2), 1));
        }

        float currentFontSize = textSize * 1.3;

        for (quint16 indexV = 0; indexV < vecOfStr.size(); indexV++) {
            const quint16 oneBuffSize = 6 * 3;
            const quint16 oneBuffSizeInByte = oneBuffSize * sizeof(GLfloat);
            GLfloat *vertBuff = new GLfloat[vecOfStr.at(indexV).size() * oneBuffSize];
            sVectorCharacterId charId = simpleFontDriver->genVerticalText(vecOfStr.at(indexV),
                                                                          vecOfPoint.at(indexV),
                                                                          currentFontSize,
                                                                          vertBuff);

            int index = 0;
            for (auto &texture : charId) {
                texture->bind();
                fontHVBO->bind();
                fontHVBO->write(0, (vertBuff + index * oneBuffSize), oneBuffSizeInByte);
                fontHVBO->release();

                glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);
                texture->release();
                index++;
            }

            delete [] vertBuff;
        }
    }

    fontHVAO->release();
    programFont3D->release();

}

DSPGLData::DSPGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const SceneOptions *sceneOption, float _depth, QObject *parent) : QObject(parent),
    glFunc(func), camera_ptr(m_camera), sceneOptions(sceneOption), depth(_depth),
    nDimensional(3),
    maxNumberOfImpulses(5656), maxNumberOfBuffer(10),
    distStep(49.507 / 1000.), pointSize(2),
    vectorOfColors({QColor("#13ed1b"), QColor("#f8f008"), QColor("#fb0505") }),
    vectorOfRanges( {0, 50, 100} ),
    decreaseAlpha_msec(50), eraseDSP_msec(3000),
    startAlpha(0.7f), alpha(startAlpha)
{
    programDSP = new QOpenGLShaderProgram(this);

    if (!programDSP->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/dsp2Vert.vert")) {
        qDebug() << programDSP->log();
        return;
    }

    if (!programDSP->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/dsp2Frag.frag")) {
        qDebug() << programDSP->log();
        return;
    }
    /*if (!programDSP->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/dsp2Geom.gm")) {
        qDebug() << programDSP->log();
        return;
    }*/

    if (!programDSP->link()) {
        qDebug() << programDSP->log();
        return;
    }

    timeToDecreaseAlpha = new QTimer();
    timeToDecreaseAlpha->setInterval(decreaseAlpha_msec);
    connect(timeToDecreaseAlpha, &QTimer::timeout, this, &DSPGLData::decreaseAlpha);
}

void DSPGLData::preapre()
{
    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo->allocate(nDimensional * sizeof(GLfloat) * maxNumberOfImpulses * maxNumberOfBuffer);

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    programDSP->enableAttributeArray("posAttr");
    programDSP->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    const quint8 pointsPerTringle = 3;
    const quint32 byteSizeOfAllIBO = (maxNumberOfImpulses - 2) * 18 * pointsPerTringle * sizeof(GLushort);

    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ibo->create();
    ibo->bind();
    ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo->allocate(byteSizeOfAllIBO);

    calcIBO(ibo);

    vbo->release();
    vao->release();

    vbo2 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo2->create();
    vbo2->bind();
    vbo2->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo2->allocate(nDimensional * sizeof(GLfloat) * maxNumberOfImpulses * maxNumberOfBuffer);

    vao2 = new QOpenGLVertexArrayObject();
    vao2->create();
    vao2->bind();
    if (!vao2->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    programDSP->enableAttributeArray("posAttr");
    programDSP->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    ibo2 = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ibo2->create();
    ibo2->bind();
    ibo2->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo2->allocate(byteSizeOfAllIBO);

    calcIBO(ibo2);

    vbo2->release();
    vao2->release();

    freeBufferObjectsVector.push_back(qMakePair(vbo, vao));
    freeBufferObjectsVector.push_back(qMakePair(vbo2, vao2));    


    VectorOfAmpGL dataToScene;
    quint32 counter = 0;
    float az = 45., azDelta = 0.25;
    quint32 N = maxNumberOfImpulses, Ntarget = 3000;

    /*DSPGLInfo glData(vbo, vao);
    glData.numberOfQuanta = N;
    glData.arrivalNewDataTime = QTime::currentTime().msecsSinceStartOfDay();
    glData.alpha = startAlpha;

    dspInfo.insert(-1, glData);*/

    for (quint16 index = 0; index != maxNumberOfBuffer; index++) {
        quint32 randDuration = QRandomGenerator::global()->bounded(500,1500);
        for (quint32 indexArray = 0; indexArray != N; indexArray++) {
            float x = indexArray * distStep * cos((90. - az) * M_PI / 180.),
                    y = indexArray * distStep * sin((90. - az) * M_PI / 180.);
            dataToScene << x << y;
            if (indexArray > Ntarget && indexArray < (Ntarget + randDuration)) {
                dataToScene.push_back(QRandomGenerator::global()->bounded(50,100));
            }
            else {
                dataToScene.push_back(QRandomGenerator::global()->bounded(0,50));
            }
        }

        counter += N;
        az += azDelta;
    }
    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      dataToScene.size() * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, dataToScene.data(), dataToScene.size() * sizeof(GLfloat));
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;



    VectorOfAmpGL dataToScene2;
    az = 315., azDelta = 0.25;
    //N = maxNumberOfImpulses, Ntarget = 3000;
    for (quint16 index = 0; index != maxNumberOfBuffer; index++) {
        quint32 randDuration = QRandomGenerator::global()->bounded(500,1500);
        for (quint32 indexArray = 0; indexArray != N; indexArray++) {
            float x = indexArray * distStep * cos((90. - az) * M_PI / 180.),
                    y = indexArray * distStep * sin((90. - az) * M_PI / 180.);
            dataToScene2 << x << y;
            if (indexArray > Ntarget && indexArray < (Ntarget + randDuration)) {
                dataToScene2.push_back(QRandomGenerator::global()->bounded(50,100));
            }
            else {
                dataToScene2.push_back(QRandomGenerator::global()->bounded(0,50));
            }
        }

        counter += N;
        az += azDelta;
    }
    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo2->bufferId());
    GLfloat* vbo_ptr2 = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      dataToScene2.size() * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    if (vbo_ptr2 != nullptr)
        memcpy(vbo_ptr2, dataToScene2.data(), dataToScene2.size() * sizeof(GLfloat));
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr2 = nullptr;   

    //timeToDecreaseAlpha->start();
}

void DSPGLData::render()
{
    if (dspInfo.isEmpty())
        return;

    QMatrix4x4 model;
    model.setToIdentity();
    programDSP->bind();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;

    QVector4D colorArray[4];
    GLfloat rangeArray[4];
    /*qint16 index = 0;
    for (; index != vectorOfColors.size(); index++) {
        const auto &color = vectorOfColors.at(index);
        colorArray[index] = QVector4D(color.redF(), color.greenF(), color.blueF(), 0.7);
        rangeArray[index] = vectorOfRanges.at(index);
    }
    for (; index != 4; index++) {
        const auto &color = vectorOfColors.at(vectorOfColors.size() - 1);
        const float &range = vectorOfRanges.at(vectorOfRanges.size() - 1);
        colorArray[index] = QVector4D(color.redF(), color.greenF(), color.blueF(), 0.7);
        rangeArray[index] = range;
    }*/

    programDSP->setUniformValue("mvp", mvp);
    programDSP->setUniformValue("z", depth);

    //programDSP->setUniformValue("alpha", alpha);
    //programDSP->setUniformValue("pointSize", pointSize);
    //programDSP->setUniformValue("distStep", distStep);
    //programDSP->setUniformValueArray("ranges", rangeArray, 4, 1);
    //programDSP->setUniformValueArray("colors", colorArray, 4);
    //programDSP->setUniformValueArray("az", currentAzVector.data(), 10, 1);
    //programDSP->setUniformValue("N", vectorOfInfo.first().numberOfQuanta);

    auto itemOfMap = dspInfo.begin();
    while (itemOfMap != dspInfo.end()) {
        qint16 indexInVector = 0;
        for (; indexInVector != itemOfMap.value().vectorOfColors.size(); indexInVector++) {
            const auto &color = itemOfMap.value().vectorOfColors.at(indexInVector);
            colorArray[indexInVector] = QVector4D(color.redF(), color.greenF(), color.blueF(), startAlpha);
            rangeArray[indexInVector] = itemOfMap.value().vectorOfRanges.at(indexInVector);
        }
        for (; indexInVector != 4; indexInVector++) {
            const auto &color = itemOfMap.value().vectorOfColors.last();//.at(itemOfMap.value().vectorOfColors.size() - 1);
            const float &range = itemOfMap.value().vectorOfRanges.last();//.at(itemOfMap.value().vectorOfRanges.size() - 1);
            colorArray[indexInVector] = QVector4D(color.redF(), color.greenF(), color.blueF(), startAlpha);
            rangeArray[indexInVector] = range;
        }

        programDSP->setUniformValue("alpha", itemOfMap.value().alpha);
        programDSP->setUniformValueArray("ranges", rangeArray, 4, 1);
        programDSP->setUniformValueArray("colors", colorArray, 4);
        itemOfMap.value().vaoPtr->bind();
        glFunc->glDrawElements(GL_TRIANGLES, (itemOfMap.value().numberOfQuanta - 2) * 18 * nDimensional, GL_UNSIGNED_SHORT, 0 );
        itemOfMap.value().vaoPtr->release();
        itemOfMap++;
    }

    /*vao->bind();
    glFunc->glDrawElements(GL_TRIANGLES, (maxNumberOfImpulses - 2) * 18 * nDimensional, GL_UNSIGNED_SHORT, 0 );
    vao->release();

    vao2->bind();
    glFunc->glDrawElements(GL_TRIANGLES, (maxNumberOfImpulses - 2) * 18 * nDimensional, GL_UNSIGNED_SHORT, 0 );
    vao2->release();*/

    programDSP->release();
}

void DSPGLData::nextData(qint32 id, QSharedPointer<QVector<DSPData> > sharedVector)
{
    auto itemOfDSP = dspInfo.find(id);
    if (itemOfDSP == dspInfo.end()) {
        if (!freeBufferObjectsVector.isEmpty()) {
            auto takePair = freeBufferObjectsVector.takeFirst();
            DSPGLInfo glInfo(takePair.first, takePair.second);
            itemOfDSP = dspInfo.insert(id, glInfo);
        }
        else {
            qDebug() << "DSPGLData::nextData - No free GL buffers";
            return;
        }
    }

    itemOfDSP.value().numberOfQuanta = sharedVector.data()->first().N;
    itemOfDSP.value().arrivalNewDataTime = QTime::currentTime().msecsSinceStartOfDay();
    itemOfDSP.value().alpha = startAlpha;

    //vectorOfInfo.clear();
    //currentAzVector.clear();

    VectorOfAmpGL dataToScene;
    //quint32 counter = 0;
    QMap <float, quint16> azIndexPair;
    for (quint16 index = 0; index != sharedVector.data()->size(); index++) {
        azIndexPair.insert(sharedVector.data()->at(index).azm, index);
    }

    float azMin = azIndexPair.first(),
          azMax = azIndexPair.last();
    if (azMin > azMax) {
        QMap <float, quint16> tempAzIndexPair;
        for (auto itemOfMap = azIndexPair.begin(); itemOfMap != azIndexPair.end(); itemOfMap++) {
            if (itemOfMap.key() > 330) {
                tempAzIndexPair.insert(360. - itemOfMap.key(), itemOfMap.value());
            }
            else {
                tempAzIndexPair.insert(itemOfMap.key(), itemOfMap.value());
            }
        }
        azIndexPair.swap(tempAzIndexPair);
    }

    for (auto itemOfMap = azIndexPair.begin(); itemOfMap != azIndexPair.end(); itemOfMap++) {

        auto &ampData = sharedVector.data()->at(itemOfMap.value()).dataGL;
        float currentCos = cos((90. - sharedVector.data()->at(itemOfMap.value()).azm) * M_PI / 180.),
              currentSin = sin((90. - sharedVector.data()->at(itemOfMap.value()).azm) * M_PI / 180.);
        for (quint32 indexAmp = 0; indexAmp < ampData.size(); indexAmp++) {
            float x = indexAmp * distStep * currentCos,
                    y = indexAmp * distStep * currentSin;
            dataToScene << x << y << ampData.at(indexAmp);
        }

        const quint32 emptyVectorSize = maxNumberOfImpulses - sharedVector.data()->at(itemOfMap.value()).N;
        VectorOfAmpGL emptyVector(emptyVectorSize, 0.);
        dataToScene << emptyVector;

    }
    glFunc->glBindBuffer(GL_ARRAY_BUFFER, itemOfDSP.value().vboPrt->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      dataToScene.size() * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, dataToScene.data(), dataToScene.size() * sizeof(GLfloat));
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;

    if (!timeToDecreaseAlpha->isActive())
        timeToDecreaseAlpha->start();
}

void DSPGLData::eraseDSPData(qint32 id)
{
    auto itemOfDSP = dspInfo.find(id);
    if (itemOfDSP != dspInfo.end()) {
        freeBufferObjectsVector.push_back(qMakePair(itemOfDSP.value().vboPrt, itemOfDSP.value().vaoPtr));
        dspInfo.erase(itemOfDSP);
    }
    else {
        qDebug() << "DSPGLData::eraseDSPData - Can't find item in map";
    }
}

void DSPGLData::calcIBO(QOpenGLBuffer *iboBuffer)
{
    QVector<GLushort> iboVector;
    for (quint32 indexN = 1; indexN != maxNumberOfImpulses - 1; indexN++) {
        for (quint8 indexB = 0; indexB != maxNumberOfBuffer - 1; indexB++) {
            quint16 index1 = maxNumberOfImpulses * indexB + indexN,
                    index2 = maxNumberOfImpulses * indexB + indexN + 1,
                    index3 = maxNumberOfImpulses * (indexB + 1) + indexN,
                    index4 = maxNumberOfImpulses * (indexB + 1) + indexN + 1;
            iboVector << index1 << index3 << index2;
            iboVector << index3 << index4 << index2;
        }
    }

    glFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer->bufferId());
    GLfloat* ibo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ELEMENT_ARRAY_BUFFER,
      0,
      iboVector.size() * sizeof(GLushort),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    );

    if (ibo_ptr != nullptr)
        memcpy(ibo_ptr, iboVector.data(), iboVector.size() * sizeof(GLushort));
    glFunc->glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    ibo_ptr = nullptr;
    //ibo->write(0, iboVector.data(), iboVector.size() * sizeof(GLushort));
}

void DSPGLData::decreaseAlpha()
{
    if (dspInfo.isEmpty()) {
        timeToDecreaseAlpha->stop();
        return;
    }
    qint32 currentTime = QTime::currentTime().msecsSinceStartOfDay();

    QVector<qint32> keyToErase;
    auto mapItem = dspInfo.begin();
    while (mapItem != dspInfo.end()) {
        qint32 deltaTime = currentTime - mapItem.value().arrivalNewDataTime;
        if (deltaTime > eraseDSP_msec) {
            keyToErase.push_back(mapItem.key());
        }
        else {
            mapItem.value().alpha = startAlpha * (1. - deltaTime / eraseDSP_msec);
        }
    }

    for (quint16 index = 0; index != keyToErase.size(); index++) {
        eraseDSPData(keyToErase.at(index));
    }

    if (dspInfo.isEmpty()) {
        timeToDecreaseAlpha->stop();
    }
}

void DSPGLData::setColorRanges(qint32 id, ColorRanges colorRanges)
{
    auto mapItem = dspInfo.find(id);
    if (mapItem == dspInfo.end()) {
        if (!freeBufferObjectsVector.isEmpty()) {
            auto takePair = freeBufferObjectsVector.takeFirst();
            DSPGLInfo glInfo(takePair.first, takePair.second);
            mapItem = dspInfo.insert(id, glInfo);

            mapItem.value().numberOfQuanta = maxNumberOfImpulses;
            mapItem.value().arrivalNewDataTime = QTime::currentTime().msecsSinceStartOfDay();
            mapItem.value().alpha = startAlpha;
        }
        else {
            qDebug() << "DSPGLData::setColorRanges - No free GL buffers";
            return;
        }
    }

    mapItem.value().vectorOfColors.swap(colorRanges.colorsForGradientLabel);
    mapItem.value().vectorOfRanges.swap(colorRanges.rangesForRangeSlider);
}

NewGrideGL::NewGrideGL(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const SceneOptions *sceneOption, float _depth, QObject *parent) : QObject(parent),
    glFunc(func), camera_ptr(m_camera),
    sceneOptions(sceneOption),
    depth(_depth),
    grideColor(QColor::fromRgbF(0.4f, 0.4f, 0.4f, 0.6f)),
    nDimensional(2)
{
    programGride = new QOpenGLShaderProgram(this);
    if (!programGride->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/azGrideVert.vert")) {
        qDebug() << programGride->log();
        return;
    }

    /*if (!programGride->addShaderFromSourceFile(QOpenGLShader::Geometry,":/source/azGrideGeom.gm")) {
        qDebug() << programGride->log();
        return;
    }*/

    if (!programGride->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/azGrideFrag.frag")) {
        qDebug() << programGride->log();
        return;
    }
    if (!programGride->link()) {
        qDebug() << programGride->log();
        return;
    }
}

void NewGrideGL::render()
{
    programGride->bind();
    QMatrix4x4 m_modelMatrix;
    m_modelMatrix.setToIdentity();
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programGride->setUniformValue("mvp", mvp);
    programGride->setUniformValue("objectColor", QColor(Qt::white));

    vao->bind();
    glFunc->glDrawArrays(GL_POINTS, 0, 2);
    vao->release();

    programGride->release();
}

void NewGrideGL::prepare()
{
    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    const quint16 sizeVertBufAz = 2;
    GLfloat *vertBufAzGrid = new GLfloat[sizeVertBufAz];
    vertBufAzGrid[0] = 50.;
    vertBufAzGrid[1] = 350.;

    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(vertBufAzGrid, sizeVertBufAz * sizeof(GLfloat));

    programGride->enableAttributeArray("posAttr");
    programGride->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();

    delete vertBufAzGrid;
}

MapGL::MapGL(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const SceneOptions *sceneOption, float _depth, QObject *parent)  : QObject(parent),
    glFunc(func), camera_ptr(m_camera),
    sceneOptions(sceneOption),
    depth(_depth),
    placementPoint(56.120382, 43.546127)
{
    programGLSL = new QOpenGLShaderProgram(this);
    if (!programGLSL->addShaderFromSourceFile(QOpenGLShader::Vertex,":/source/mapShader.vert")) {
        qDebug() << programGLSL->log();
        return;
    }

    if (!programGLSL->addShaderFromSourceFile(QOpenGLShader::Fragment,":/source/mapShader.frag")) {
        qDebug() << programGLSL->log();
        return;
    }
    if (!programGLSL->link()) {
        qDebug() << programGLSL->log();
        return;
    }

    connect(m_camera, &Camera::translateCamera, this, &MapGL::translateSlot);
}

void MapGL::prepare()
{    
    QStringList list;
    list << "side1.png"
         << "side2.png"
         << "side3.png"
         << "side4.png"
         << "side5.png"
         << "side6.png"
         << "side1.png"
         << "side2.png"
         << "side3.png";
    tileSize = QImage(list.first()).size();

    /*for (quint8 index = 0; index != 9; index++) {
        QOpenGLTexture *glTexture = new QOpenGLTexture(QImage(list.at(index)), QOpenGLTexture::DontGenerateMipMaps);

        vectorOfTexture.push_back(glTexture);
    }*/

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    if (!vao->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }
    const quint16 vertexOnTriangles = 6;
    const quint16 nDimensional = 2;
    const quint16 buffSize = vertexOnTriangles * nDimensional;
    const quint16 tilesCount = 9;

    QVector<GLfloat>  textureData;
    //vertex
    for (quint16 indexTiles = 0; indexTiles != tilesCount; indexTiles++) {
        /*textureData << 0.0 << 0.0
                    << 0.0 << 0.0
                    << 0.0 << 0.0
                    << 0.0 << 0.0
                    << 0.0 << 0.0
                    << 0.0 << 0.0;*/
        GLfloat xpos = (indexTiles % 3) * tileSize.width(),
                ypos = (indexTiles / 3) * tileSize.height();
        textureData << xpos << ypos
                    << xpos + tileSize.width() << ypos
                    << xpos + tileSize.width() << ypos + tileSize.height()
                    << xpos << ypos
                    << xpos + tileSize.width() << ypos + tileSize.height()
                    << xpos << ypos + tileSize.height();
    }
    //texels
    for (quint16 indexTiles = 0; indexTiles != tilesCount; indexTiles++) {
        textureData << 0.0 << 1.0
                    << 1.0 << 1.0
                    << 1.0 << 0.0
                    << 0.0 << 1.0
                    << 1.0 << 0.0
                    << 0.0 << 0.0;
    }

    /*GLfloat fontVertex[buffSize * tilesCount] = {
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0,
        0.0, 0.0
    };
    GLfloat texelVertex[buffSize * tilesCount]
            = { 0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f };*/

    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(textureData.data(), textureData.size() * sizeof(GLfloat));
    //vbo->allocate(fontVertex, 2 * buffSize * sizeof(GLfloat));
    //vbo->write(buffSize * sizeof(GLfloat), texelVertex, buffSize * sizeof(GLfloat));
    vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);

//    programGLSL->enableAttributeArray("vertex");
//    programGLSL->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensionalFont, 0);
//    programGLSL->enableAttributeArray("texels");
//    programGLSL->setAttributeBuffer("texels", GL_FLOAT, buffSizeInByte, nDimensionalFont, 0);

    programGLSL->enableAttributeArray("vertex");
    programGLSL->setAttributeBuffer("vertex", GL_FLOAT, 0, nDimensional, 0);
    programGLSL->enableAttributeArray("texels");
    programGLSL->setAttributeBuffer("texels", GL_FLOAT, tilesCount * buffSize * sizeof(GLfloat), nDimensional, 0);

    vbo->release();
    vao->release();
}

void MapGL::update(QJsonDocument doc)
{
    QJsonObject json = doc.object();

    QStringList filePaths;

    if (json.contains("filePaths") && json["filePaths"].isArray()) {
        filePaths = json["filePaths"].toVariant().toStringList();
    }
    QSizeF firstTileSize, secondTileSize, thirdTileSize;
    float lat4;
    if (json.contains("w1") && json["w1"].isDouble()) {
        firstTileSize.setWidth(json["w1"].toDouble());
    }
    if (json.contains("h1") && json["h1"].isDouble()) {
        firstTileSize.setHeight(json["h1"].toDouble());
    }
    if (json.contains("w2") && json["w2"].isDouble()) {
        secondTileSize.setWidth(json["w2"].toDouble());
    }
    if (json.contains("h2") && json["h2"].isDouble()) {
        secondTileSize.setHeight(json["h2"].toDouble());
    }
    if (json.contains("w3") && json["w3"].isDouble()) {
        thirdTileSize.setWidth(json["w3"].toDouble());
    }
    if (json.contains("h3") && json["h3"].isDouble()) {
        thirdTileSize.setHeight(json["h3"].toDouble());
    }
    if (json.contains("w4") && json["w4"].isDouble()) {
        lat4 = json["w4"].toDouble();
    }

    for(quint16 vectorIndex = 0; vectorIndex != vectorOfTexture.size(); vectorIndex++) {
        delete vectorOfTexture.at(vectorIndex);
    }
    vectorOfTexture.clear();

//    if(filePaths.size() != 9)
//        return;
    for (quint8 index = 0; index != 9; index++) {
        QOpenGLTexture *glTexture = new QOpenGLTexture(QImage(filePaths.at(index)), QOpenGLTexture::GenerateMipMaps);
        glTexture->setMinificationFilter(QOpenGLTexture::Linear);
        glTexture->setMagnificationFilter(QOpenGLTexture::Linear);
        glTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
        glTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
        vectorOfTexture.push_back(glTexture);
    }

    QVector<GLfloat> resultVector;
    QVector3D vectorOfCenterView = camera_ptr->viewCenter();
    QPointF leftBottom, leftTop, rightBottom, rightTop;

    //1
    leftBottom.setX(vectorOfCenterView.x() - 3. * firstTileSize.width() / 2.);
    leftBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    leftTop.setX(vectorOfCenterView.x() - 3 * secondTileSize.width() / 2.);
    leftTop.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    rightBottom.setX(vectorOfCenterView.x() - firstTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(vectorOfCenterView.x() - secondTileSize.width() / 2.);
    rightTop.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //2
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(vectorOfCenterView.x() + firstTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(vectorOfCenterView.x() + secondTileSize.width() / 2.);
    rightTop.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //3
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(vectorOfCenterView.x() + 3. * firstTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(vectorOfCenterView.x() + 3. * secondTileSize.width() / 2.);
    rightTop.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //4
    leftBottom.setX(vectorOfCenterView.x() - 3. * secondTileSize.width() / 2.);
    leftBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    leftTop.setX(vectorOfCenterView.x() - 3 * thirdTileSize.width() / 2.);
    leftTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    rightBottom.setX(vectorOfCenterView.x() - secondTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(vectorOfCenterView.x() - thirdTileSize.width() / 2.);
    rightTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //5
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(vectorOfCenterView.x() + secondTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(vectorOfCenterView.x() + thirdTileSize.width() / 2.);
    rightTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //6
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(vectorOfCenterView.x() + 3. * secondTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(vectorOfCenterView.x() + 3. * thirdTileSize.width() / 2.);
    rightTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //7
    leftBottom.setX(vectorOfCenterView.x() - 3. * thirdTileSize.width() / 2.);
    leftBottom.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    leftTop.setX(vectorOfCenterView.x() - 3 * lat4 / 2.);
    leftTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2. + thirdTileSize.height());

    rightBottom.setX(vectorOfCenterView.x() - thirdTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(vectorOfCenterView.x() - lat4 / 2.);
    rightTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //8
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(vectorOfCenterView.x() + thirdTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(vectorOfCenterView.x() + lat4 / 2.);
    rightTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //9
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(vectorOfCenterView.x() + 3. * thirdTileSize.width() / 2.);
    rightBottom.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(vectorOfCenterView.x() + 3. * lat4 / 2.);
    rightTop.setY(vectorOfCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
      GL_ARRAY_BUFFER,
      0,
      resultVector.size() * sizeof(GLfloat),
      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
    );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, resultVector.data(), sizeof(GLfloat) * resultVector.size());
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;
}

void MapGL::translateSlot()
{
    QJsonObject json;

    json["x"] = placementPoint.x();
    json["y"] = placementPoint.y();
    json["layer"] = 10;
    json["az"] = 0;
    json["repaint"] = false;

    QJsonDocument doc(json);

    emit getNewMap(doc);
}

void MapGL::render()
{
    float zcoord = 1.f;
    programGLSL->bind();
    QMatrix4x4 m_modelMatrix;
    m_modelMatrix.setToIdentity();
    m_modelMatrix.translate(-camera_ptr->viewCenter());
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programGLSL->setUniformValue("mvp", mvp);
    programGLSL->setUniformValue("zcoord", depth);
    programGLSL->setUniformValue("texture0", 0);
    glFunc->glActiveTexture(GL_TEXTURE0);
    vao->bind();

    for (quint8 index = 0; index != vectorOfTexture.size(); index++) {
        vectorOfTexture.at(index)->bind();
        glFunc->glDrawArrays(GL_TRIANGLES, index * 6, 6);
        vectorOfTexture.at(index)->release();
    }

    vao->release();
    programGLSL->release();
}

