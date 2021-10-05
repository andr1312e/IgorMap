#include "scene.h"
#include "camera.h"

#include <QImage>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QElapsedTimer>
#include <QOpenGLPixelTransferOptions>

#define _USE_MATH_DEFINES
#include <math.h>
#include <QTimer>
#include <QTime>
#include <QSet>
#include <QRandomGenerator>
#include <QFile>
#include <qjsonobject.h>

const qreal degToRad =  M_PI / 180.0 ;
const qreal radToDeg =  180.0  / M_PI;

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

    m_programGrid = new QOpenGLShaderProgram(this);

    if (!m_programGrid->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/vertShGrid.vert")) {
        qDebug() << m_programGrid->log();
        return;
    }

    if (!m_programGrid->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/fragShGrid.frag")) {
        qDebug() << m_programGrid->log();
        return;
    }
    if (!m_programGrid->link()) {
        qDebug() << m_programGrid->log();
        return;
    }

    m_programButton = new QOpenGLShaderProgram(this);

    if (!m_programButton->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/buttonVert.vert")) {
        qDebug() << m_programButton->log();
        return;
    }

    if (!m_programButton->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/buttonFrag.frag")) {
        qDebug() << m_programButton->log();
        return;
    }
    if (!m_programButton->link()) {
        qDebug() << m_programButton->log();
        return;
    }
    prepareFontArray();


    float sectorDepth = 2;
    m_sectorsGLData = new SectorsGLData(m_funcs, m_camera, &sceneOptions, m_programGrid, sectorDepth, sharedSceneData);




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


    float mapDepth = 0;
    mapGL = new MapGL(m_funcs, m_camera, &sceneOptions, mapDepth);
    mapGL->prepare();

    initRect();
}

void Scene::render()
{
   updateCamera(); //TODO: вынести по сигналу
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(mainViewPort.x(), mainViewPort.y(), mainViewPort.width(), mainViewPort.height());
    mapGL->render();

}

void Scene::resize(int w, int h, int x, int y)
{
    float mainOccupiedSpace = 1.;//0.65;
    float hMain = h * mainOccupiedSpace,
            hExtra = h * (1 - mainOccupiedSpace);
    screenSize = QSize(w, h);
    mainViewPort = OpenGLRectF(x, y, w, hMain);
    extraViewPort = OpenGLRectF(x, hMain, w, hExtra);
    sceneOptions.setScreenRect(qreal(w), hMain, x, y);

    extraSceneOptions.maxDist = 180;
    extraSceneOptions.initialRect = OpenGLRectF(-extraSceneOptions.maxDist, -10,
                                                extraSceneOptions.maxDist * 2, sceneOptions.maxDist + 10);
    extraSceneOptions.setScreenRect(w, hExtra, x, hMain);
    m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
                                        sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
                                        sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());
    m_extraCamera->setOrthographicProjection(extraSceneOptions.sceneRect.left(), extraSceneOptions.sceneRect.right(),
                                             extraSceneOptions.sceneRect.bottom(), extraSceneOptions.sceneRect.top(),
                                             extraSceneOptions.farNearPlane.x(), extraSceneOptions.farNearPlane.y());
}

void Scene::resizeViewPort(int w, int h) {
    mainViewPort = OpenGLRectF(0, 0, w, h);
    sceneOptions.setScreenRect(qreal(w), qreal(h));

    m_camera->setOrthographicProjection(sceneOptions.sceneRect.left(), sceneOptions.sceneRect.right(),
                                        sceneOptions.sceneRect.bottom(), sceneOptions.sceneRect.top(),
                                        sceneOptions.farNearPlane.x(), sceneOptions.farNearPlane.y());

}

void Scene::setTerrainHorizontalScale(const float &horizontalScale)
{
    m_extraCamera->updateScaleOfViewMatrix(horizontalScale);
}

void Scene::userScaling(const float &horizontalScale, bool centerOnMouseCursor, QPointF mouseCursor)
{
    float minScalef = 0.003, maxScalef = 9550;
//     minScalef = 1.f;


    if ((m_camera->viewMatrixScale().x() < minScalef && horizontalScale < 1) ||
            (m_camera->viewMatrixScale().x() > maxScalef && horizontalScale > 1))
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

    if (preScale.x() > maxScalef) {
        float maxScale = maxScalef / m_camera->viewMatrixScale().x();
        m_camera->updateScaleOfViewMatrix(maxScale);
        //grideGL->updateText(maxScale);
    }
    else if (preScale.x() < minScalef) {
        float minScale = minScalef / m_camera->viewMatrixScale().x();
        m_camera->updateScaleOfViewMatrix(minScale);
        //grideGL->updateText(minScale);
    }
    else {
        m_camera->updateScaleOfViewMatrix(horizontalScale);
        //grideGL->updateText(horizontalScale);
    }

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
        m_v.setX(m_v.x() / m_camera->viewMatrixScale().x());
        m_v.setY(m_v.y() / m_camera->viewMatrixScale().y());

        //m_v.setX(m_v.x() * sceneOptions.aspectRatioScreenWithScene.x() / m_camera->viewMatrixScale().x());
        //m_v.setY(m_v.y() * sceneOptions.aspectRatioScreenWithScene.y() / m_camera->viewMatrixScale().y());
        m_camera->translate( m_v, option );
        m_v = QVector3D();


        //emit cameraIsUpdate(m_camera->viewCenter());
    }
}

void Scene::resetCamera()
{
    m_modelMatrix.setToIdentity();

    // Initialize the camera position and orientation
    m_camera->setPosition( QVector3D( 0.0f, 290.0f, 100.0f ) ); //y - 290
    m_camera->setViewCenter( QVector3D( 0.0f, 290.0f, 0.0f ) ); //y - 290
    m_camera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );

    m_camera->resetScaleOfViewMatrix();
}

void Scene::resetScaling()
{
    resetCamera();
//    traceData->reCalcAllTrace();
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

}

void Scene::mouseRelease(const QPointF &point)
{

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
    //grideGL->updateMoveText();
}

void Scene::KTASampling(const QPointF &point1, const QPointF &point2)
{
//    QVector3D vector1(screenToScene(point1)),
//            vector2(screenToScene(point2));

//    QPointF leftBottom, rightTop;
//    if (vector1.x() < vector2.x()) {
//        leftBottom.rx() = vector1.x();
//        rightTop.rx() = vector2.x();
//    }
//    else {
//        leftBottom.rx() = vector2.x();
//        rightTop.rx() = vector1.x();
//    }
//    if (vector1.y() < vector2.y()) {
//        leftBottom.ry() = vector1.y();
//        rightTop.ry() = vector2.y();
//    }
//    else {
//        leftBottom.ry() = vector2.y();
//        rightTop.ry() = vector1.y();
//    }
//    qDebug() << leftBottom;

//    emit KTASamplingRequest(leftBottom, rightTop);

//    sizeRectForSampling = 0;
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



void Scene::changeProjectionSlot(bool flag)
{

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

    //grideGL->prepare();
}

void Scene::initSceneProperties(const SceneCustomDataInit &cData)
{
    setBackground(cData.backgroundColor);

}

void Scene::setSideSpeedSlot(float vx)
{
    m_v.setX(m_v.x() + vx);
}

void Scene::viewCenterRequest()
{
    m_camera->viewCenterRequestCamera();
}

void Scene::programmUpdateScaling()
{
    userScaling(1.);
}

void Scene::setForwardSpeedSlot(float vy)
{
    m_v.setY(m_v.y() + vy);
}

void Scene::prepareGrid()
{

}

void Scene::prepareSectors()
{

}

void Scene::prepareFont()
{
}

void Scene::prepareFontArray()
{
    m_programFont = new QOpenGLShaderProgram(this);

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/ftVertexShader.vert")) {
        qDebug() << m_programFont->log();
        return;
    }

    if (!m_programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/ftFragmentShader.frag")) {
        qDebug() << m_programFont->log();
        return;
    }
    if (!m_programFont->link()) {
        qDebug() << m_programFont->log();
        return;
    }
    //GLuint textureArray;
    //glGenTextures( 1, &textureArray );

//    customFontDriver = new ftCustom(m_funcs);
//    customFontDriver->genTexels();
}

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


void Scene::prepareDSP()
{

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
                             QOpenGLShaderProgram *prog, float _depth, const SharedSceneData &sharedData,
                             QObject *parent) : QObject(parent),
    glFunc(func), camera_ptr(m_camera), sceneOptions(scOption), programSector(prog), depth(_depth), segmentation(60),  sectorsCount(maxNumberOfSectors),
    shdData(sharedData),
    storedAzValue(0), storedUgmValue(0), thresholdOfSensorsUpdate(1)
{

}

void SectorsGLData::calcDrawVector(QVector<QPair<GLushort, GLushort> > &vector)
{


}

void SectorsGLData::render()
{

}


void SectorsGLData::excludeSectorSlot(const quint8 index)
{

}


void SectorsGLData::deleteSectorSlot(const quint8 index)
{

}

void SectorsGLData::sectorInFocus(const quint8 index)
{


}

void SectorsGLData::sectorOutFocus()
{

}

void SectorsGLData::setColor(const QColor color)
{

}

void SectorsGLData::maxDistanceChangedSlot()
{

}

void SectorsGLData::calcIBO(QOpenGLBuffer *iboBuffer)
{

}

void SectorsGLData::deg360TransitionCheck(float &ang)
{

}

void SectorsGLData::updateUgmSectors()
{

}

void SectorsGLData::sensorsValueCheck()
{

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


}

void Scene::initRect()
{

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

}

void DSPGLData::preapre()
{

}

void DSPGLData::render()
{

}

void DSPGLData::calcIBO(QOpenGLBuffer *iboBuffer)
{

}

void DSPGLData::decreaseAlpha()
{
}

MapGL::MapGL(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const SceneOptions *sceneOption, float _depth, QObject *parent)  : QObject(parent),
    glFunc(func), camera_ptr(m_camera),
    sceneOptions(sceneOption),
    depth(_depth),
    tilesCount(9),
    vectorOfTexture(tilesCount, nullptr),
    filePathsVector(tilesCount, QString()),
    placementPoint(56.120382, 43.546127)

{
    programGLSL = new QOpenGLShaderProgram(this);
    if (!programGLSL->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/mapShader.vert")) {
        qDebug() << programGLSL->log();
        return;
    }

    if (!programGLSL->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/mapShader.frag")) {
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
    if (doc.isEmpty())
        return;

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

    QPointF leftBottomCenterRect, rightBottomCenterRect, leftTopCenterRect, rightTopCenterRect;
    if (json.contains("p1_lat") && json["p1_lat"].isDouble()) {
        leftBottomCenterRect.setX(json["p1_lat"].toDouble());
    }
    if (json.contains("p1_long") && json["p1_long"].isDouble()) {
        leftBottomCenterRect.setY(json["p1_long"].toDouble());
    }
    if (json.contains("p2_lat") && json["p2_lat"].isDouble()) {
        rightTopCenterRect.setX(json["p2_lat"].toDouble());
    }
    if (json.contains("p2_long") && json["p2_long"].isDouble()) {
        rightTopCenterRect.setY(json["p2_long"].toDouble());
    }
    /*if (json.contains("p3_lat") && json["p3_lat"].isDouble()) {
        leftTopCenterRect.setX(json["p3_lat"].toDouble());
    }
    if (json.contains("p3_long") && json["p3_long"].isDouble()) {
        leftTopCenterRect.setY(json["p3_long"].toDouble());
    }
    if (json.contains("p4_lat") && json["p4_lat"].isDouble()) {
        rightTopCenterRect.setX(json["p4_lat"].toDouble());
    }
    if (json.contains("p4_long") && json["p4_long"].isDouble()) {
        rightTopCenterRect.setY(json["p4_long"].toDouble());
    }*/
    rightBottomCenterRect.rx() = rightTopCenterRect.x();
    rightBottomCenterRect.ry() = leftBottomCenterRect.y();
    leftTopCenterRect.rx() = leftBottomCenterRect.x();
    leftTopCenterRect.ry() = rightTopCenterRect.y();

    /*for (quint8 index = 0; index != tilesCount; index++) {
        if (filePathsVector.at(index) != filePaths.at(index)) {
            if (vectorOfTexture.at(index) != nullptr) {
                delete vectorOfTexture.at(index);
                vectorOfTexture[index] = nullptr;
            }
            if (!QFile::exists(filePaths.at(index))) {
                lazyLoadingPng.insert(index);
            }
            else {
                QOpenGLTexture *glTexture = new QOpenGLTexture(QImage(filePaths.at(index)), QOpenGLTexture::GenerateMipMaps);
                glTexture->setMinificationFilter(QOpenGLTexture::Linear);
                glTexture->setMagnificationFilter(QOpenGLTexture::Linear);
                glTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
                glTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
                vectorOfTexture[index] = glTexture;

                auto oldKey = lazyLoadingPng.find(index);
                if (oldKey != lazyLoadingPng.end()){
                    lazyLoadingPng.erase(oldKey);
                }
            }
            filePathsVector[index] = filePaths.at(index);
        }
    }*/

    for (quint8 index = 0; index != tilesCount; index++) {
        if (vectorOfTexture.at(index) != nullptr) {
            delete vectorOfTexture.at(index);
            vectorOfTexture[index] = nullptr;
        }
        if (!QFile::exists(filePaths.at(index))) {
            lazyLoadingPng.insert(index);
        }
        else {
            QOpenGLTexture *glTexture = new QOpenGLTexture(QImage(filePaths.at(index)), QOpenGLTexture::GenerateMipMaps);
            glTexture->setMinificationFilter(QOpenGLTexture::Linear);
            glTexture->setMagnificationFilter(QOpenGLTexture::Linear);
            glTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
            glTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
            vectorOfTexture[index] = glTexture;

            auto oldKey = lazyLoadingPng.find(index);
            if (oldKey != lazyLoadingPng.end()){
                lazyLoadingPng.erase(oldKey);
            }
        }
        filePathsVector[index] = filePaths.at(index);
    }


    QPointF leftBottomCenterRectGauss(localConversion.GeoToGauss(leftBottomCenterRect.x(), leftBottomCenterRect.y())),
            rightBottomCenterRectGauss(localConversion.GeoToGauss(rightBottomCenterRect.x(), rightBottomCenterRect.y())),
            leftTopCenterRectGauss(localConversion.GeoToGauss(leftTopCenterRect.x(), leftTopCenterRect.y())),
            rightTopCenterRectGauss(localConversion.GeoToGauss(rightTopCenterRect.x(), rightTopCenterRect.y()));
    quint8 leftBottomCenterRectGaussZone = qFloor(leftBottomCenterRectGauss.y() / 1000000),
            rightBottomCenterRectGaussZone = qFloor(rightBottomCenterRectGauss.y() / 1000000),
            leftTopCenterRectGaussZone = qFloor(leftTopCenterRectGauss.y() / 1000000),
            rightTopCenterRectGaussZone = qFloor(rightTopCenterRectGauss.y() / 1000000),
            viewCenterGaussZone = qFloor(localConversion.Gen_point_gauss.y() / 1000000);
    //quint8 differenceInZone = 0;
    //while (true) {
        //if (abs(viewCenterGaussZone - leftBottomCenterRectGaussZone) == differenceInZone) {
            sideOrientation = SideOfQuadrangle::LeftBottom;
            geoPointOfSideOfCenterRect = leftBottomCenterRect;
            localPointOfSideOfCenterRect = localConversion.Gauss2LocUpdate(leftBottomCenterRectGauss);
//            break;
//        }
//        else if (abs(viewCenterGaussZone - rightBottomCenterRectGaussZone) == differenceInZone) {
//            sideOrientation = SideOfQuadrangle::RightBottom;
//            geoPointOfSideOfCenterRect = rightBottomCenterRect;
//            localPointOfSideOfCenterRect = localConversion.Gauss2LocUpdate(rightBottomCenterRectGauss);
//            break;
//        }
//        else if (abs(viewCenterGaussZone - leftTopCenterRectGaussZone) == differenceInZone) {
//            sideOrientation = SideOfQuadrangle::LeftTop;
//            geoPointOfSideOfCenterRect = leftTopCenterRect;
//            localPointOfSideOfCenterRect = localConversion.Gauss2LocUpdate(leftTopCenterRectGauss);
//            break;
//        }
//        else if (abs(viewCenterGaussZone - rightTopCenterRectGaussZone) == differenceInZone) {
//            sideOrientation = SideOfQuadrangle::RightTop;
//            geoPointOfSideOfCenterRect = rightTopCenterRect;
//            localPointOfSideOfCenterRect = localConversion.Gauss2LocUpdate(rightTopCenterRectGauss);
//            break;
//        }
//        differenceInZone++;
//    }

    QVector<GLfloat> resultVector;
    QVector3D vectorOfCenterView = camera_ptr->viewCenter();
    //QPointF recalcCenterView(vectorOfCenterView.x(), vectorOfCenterView.y());
    QPointF recalcCenterView(vectorOfCenterView.x() + localPointOfSideOfCenterRect.y() / 1000.,
                             vectorOfCenterView.y() - localPointOfSideOfCenterRect.x() / 1000.);

    if (sideOrientation == SideOfQuadrangle::LeftBottom) {
        recalcCenterView = QPointF(recalcCenterView.x() + secondTileSize.width() / 2.,
                                   recalcCenterView.y() + secondTileSize.height() / 2.);
    }
    else if (sideOrientation == SideOfQuadrangle::RightBottom) {
        recalcCenterView = QPointF(recalcCenterView.x() - secondTileSize.width() / 2.,
                                   recalcCenterView.y() + secondTileSize.height() / 2.);
    }
    else if (sideOrientation == SideOfQuadrangle::LeftTop) {
        recalcCenterView = QPointF(recalcCenterView.x() + thirdTileSize.width() / 2.,
                                   recalcCenterView.y() + secondTileSize.height() / 2.);
    }
    else if (sideOrientation == SideOfQuadrangle::RightTop) {
        recalcCenterView = QPointF(recalcCenterView.x() - thirdTileSize.width() / 2.,
                                   recalcCenterView.y() + secondTileSize.height() / 2.);
    }


    QPointF leftBottom, leftTop, rightBottom, rightTop;

    //1
    leftBottom.setX(recalcCenterView.x() - 3. * firstTileSize.width() / 2.);
    leftBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    leftTop.setX(recalcCenterView.x() - 3 * secondTileSize.width() / 2.);
    leftTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightBottom.setX(recalcCenterView.x() - firstTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(recalcCenterView.x() - secondTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //2
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + firstTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(recalcCenterView.x() + secondTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //3
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + 3. * firstTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(recalcCenterView.x() + 3. * secondTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //4
    leftBottom.setX(recalcCenterView.x() - 3. * secondTileSize.width() / 2.);
    leftBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    leftTop.setX(recalcCenterView.x() - 3 * thirdTileSize.width() / 2.);
    leftTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightBottom.setX(recalcCenterView.x() - secondTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() - thirdTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //5
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + secondTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + thirdTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //6
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + 3. * secondTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + 3. * thirdTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //7
    leftBottom.setX(recalcCenterView.x() - 3. * thirdTileSize.width() / 2.);
    leftBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    leftTop.setX(recalcCenterView.x() - 3 * lat4 / 2.);
    leftTop.setY(recalcCenterView.y() + secondTileSize.height() / 2. + thirdTileSize.height());

    rightBottom.setX(recalcCenterView.x() - thirdTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() - lat4 / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //8
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + thirdTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + lat4 / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //9
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + 3. * thirdTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + 3. * lat4 / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

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

void MapGL::updateViewCenterGeo(QPointF _centerGeo)
{
    centerGeo = _centerGeo;

    localConversion.Gen_point_grad = centerGeo;
    localConversion.Gen_point_gauss = localConversion.GeoToGauss(centerGeo.x(), centerGeo.y());
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

void MapGL::clearAllTiles()
{
    lazyLoadingPng.clear();

    for (quint8 index = 0; index != tilesCount; index++) {
        if (vectorOfTexture.at(index) != nullptr) {
            delete vectorOfTexture.at(index);
            vectorOfTexture[index] = nullptr;
        }
        filePathsVector[index] = QString();
    }

}

void MapGL::updateMap(QStringList paths, QVector<GLfloat> points)
{
    for (quint8 index = 0; index != tilesCount; index++) {
        if (filePathsVector.at(index) != paths.at(index)) {
            if (vectorOfTexture.at(index) != nullptr) {
                delete vectorOfTexture.at(index);
                vectorOfTexture[index] = nullptr;
            }
            if (!QFile::exists(paths.at(index))) {
                lazyLoadingPng.insert(index);
            }
            else {
                QOpenGLTexture *glTexture = new QOpenGLTexture(QImage(paths.at(index)), QOpenGLTexture::GenerateMipMaps);
                glTexture->setMinificationFilter(QOpenGLTexture::Linear);
                glTexture->setMagnificationFilter(QOpenGLTexture::Linear);
                glTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
                glTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
                vectorOfTexture[index] = glTexture;

                auto oldKey = lazyLoadingPng.find(index);
                if (oldKey != lazyLoadingPng.end()){
                    lazyLoadingPng.erase(oldKey);
                }
            }
            filePathsVector[index] = paths.at(index);
        }
    }


    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo->bufferId());
    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
                GL_ARRAY_BUFFER,
                0,
                points.size() * sizeof(GLfloat),
                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
                );

    if (vbo_ptr != nullptr)
        memcpy(vbo_ptr, points.data(), sizeof(GLfloat) * points.size());
    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo_ptr = nullptr;
}

void MapGL::checkFiles()
{
    auto iter = lazyLoadingPng.begin();
    while (iter != lazyLoadingPng.end()) {
        if (QFile::exists(filePathsVector.at(*iter))) {

            if (vectorOfTexture.at(*iter) != nullptr) {
                delete vectorOfTexture.at(*iter);
                vectorOfTexture[*iter] = nullptr;
            }

            QImage image(filePathsVector.at(*iter));
            if (image.isNull()) {
                iter++;
                qDebug() << "skip null image";
                continue;

            }
            QOpenGLTexture *glTexture = new QOpenGLTexture(image, QOpenGLTexture::GenerateMipMaps);
            glTexture->setMinificationFilter(QOpenGLTexture::Linear);
            glTexture->setMagnificationFilter(QOpenGLTexture::Linear);
            glTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
            glTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
            vectorOfTexture[*iter] = glTexture;

            iter = lazyLoadingPng.erase(iter);
        }
        else
            iter++;
    }
}

void MapGL::render()
{    
    programGLSL->bind();
    QMatrix4x4 m_modelMatrix;
    m_modelMatrix.setToIdentity();
    //m_modelMatrix.translate(-camera_ptr->viewCenter());
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programGLSL->setUniformValue("mvp", mvp);
    programGLSL->setUniformValue("zcoord", depth);
    programGLSL->setUniformValue("texture0", 0);
    glFunc->glActiveTexture(GL_TEXTURE0);
    vao->bind();

    for (quint8 index = 0; index != vectorOfTexture.size(); index++) {
        if (vectorOfTexture.at(index) == nullptr)
            continue;
        //if (index == 4 || index == 0 || index == 8) {
            vectorOfTexture.at(index)->bind();
            glFunc->glDrawArrays(GL_TRIANGLES, index * 6, 6);
            vectorOfTexture.at(index)->release();
        //}

    }

    vao->release();
    programGLSL->release();

    checkFiles();
}
