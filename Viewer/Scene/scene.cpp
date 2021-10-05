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

    //prepareFont();
    prepareFontArray();

    float grideDepth = 0.1;


    float sectorDepth = 2;
    m_sectorsGLData = new SectorsGLData(m_funcs, m_camera, &sceneOptions, m_programGrid, sectorDepth, sharedSceneData);

    float dspDepth = 8;
    dspData = new DSPGLData(m_funcs, m_camera, &sceneOptions, dspDepth);
    dspData->preapre();




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
    QElapsedTimer frame;
    frame.start();

    //if (!m_v.isNull()) {
    updateCamera(); //TODO: вынести по сигналу
    //}

    QPointF centerView = m_camera->viewCenter().toPointF();
    QVector2D tVecKM(sceneOptions.sceneRect.width() / m_camera->viewMatrixScale().x(),
                     sceneOptions.sceneRect.height() / m_camera->viewMatrixScale().y());
    QVector2D tVecPix(sceneOptions.screenRect.width() / tVecKM.x(),
                      sceneOptions.screenRect.height() / tVecKM.y());
    tVecKM /= 2.;
    QPointF topLeft = QPointF(centerView.x() - tVecKM.x(),
                              centerView.y() + tVecKM.y()),
            bottomLeft = QPointF(centerView.x() - tVecKM.x(),
                                 centerView.y() - tVecKM.y()),
            topRight = QPointF(centerView.x() + tVecKM.x(),
                               centerView.y() + tVecKM.y()),
            bottomRight = QPointF(centerView.x() + tVecKM.x(),
                                  centerView.y() - tVecKM.y());
    tVecKM *= 2.;
    OpenGLRectF rectOfViewArea(centerView.x() - tVecKM.x() / 2.,
                               centerView.y() - tVecKM.y() / 2.,
                               tVecKM.x(), tVecKM.y());


    static float m_angle = 0;
    static GLfloat deltaTime = 0;
    static qint64 lastTime = 0;
    static quint64 currentTime = 0;
    static quint64 frameFull = 0;
    static bool firstEntery = true;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(mainViewPort.x(), mainViewPort.y(), mainViewPort.width(), mainViewPort.height());

    QMatrix4x4 mvp = m_camera->projectionMatrix() * m_camera->viewMatrix();




    //grideGL->render();
    mapGL->render();


    m_sectorsGLData->render();




    m_programGrid->bind();
    m_programGrid->setUniformValue("mvp", mvp);
    m_programGrid->setUniformValue("objectColor", QVector4D(0.0f, 0.1f, 0.45f, 0.8f));

    vaoRect->bind();
    m_funcs->glDrawArrays(GL_TRIANGLES, 0, sizeRectForSampling / 3);
    vaoRect->release();

    m_programGrid->release();

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(QVector3D(centerView.x(), centerView.y(), 0.));
    modelMatrix.scale(1 / m_camera->viewMatrixScale().x());
    mvp *= modelMatrix;
    m_programGrid->bind();
    m_programGrid->setUniformValue("mvp", mvp);
    m_programGrid->setUniformValue("objectColor", QVector4D(1.0f, 0.0f, 0.0f, 1.0f));

    vaoRect2->bind();
    m_funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
    vaoRect2->release();

    m_programGrid->release();



    currentTime = frame.nsecsElapsed() / 1000;


    frameFull += currentTime;
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

    //grideGL->prepare();
}

void Scene::initSceneProperties(const SceneCustomDataInit &cData)
{
    setBackground(cData.backgroundColor);



    m_sectorsGLData->setColor(cData.sectorsColor);

    traceData->setTraceColor(cData.traceColor);
    traceData->setLogBookColor(cData.traceLBColor);
    traceData->setTextColor(cData.traceLBTextSize);
    traceData->setTextSize(TextSizeAction::Reset, cData.traceLBTextSize);
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

    m_vaoFont = new QOpenGLVertexArrayObject();
    m_vaoFont->create();
    m_vaoFont->bind();
    if (!m_vaoFont->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

//    customFontDriver = new ftCustom(this);
//    customFontDriver->genTexels();

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
                             QOpenGLShaderProgram *prog, float _depth, const SharedSceneData &sharedData,
                             QObject *parent) : QObject(parent),
    glFunc(func), camera_ptr(m_camera), sceneOptions(scOption), programSector(prog), depth(_depth),
    lastParameters(), segmentation(60), sectorsCount(maxNumberOfSectors), sectorsState(sectorsCount, ItemState::Empty),
    vao(new QOpenGLVertexArrayObject()), vaoAzUgm(new QOpenGLVertexArrayObject()),
    vbo(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)), vboAzUgm(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
    ibo(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)), iboAzUgm(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)),
    gpuMemoryReserved(0),
    sectorColor(QColor::fromRgbF(0.28f, 0.77f, 0.15f, 0.15f)),
    selectedColor(QColor::fromRgbF(0.9f, 0.77f, 0.15f, 0.3f)),
    blinkingColor(QColor::fromRgbF(0.68f, 0.07f, 0.07f, 0.6f)),
    selectedSector(255),
    sectorColors(sectorsCount, sectorColor),
    shdData(sharedData),
    polarVertices(maxNumberOfSectors),
    storedAzValue(0), storedUgmValue(0), thresholdOfSensorsUpdate(1)
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

    calcIBO(ibo);

    programSector->enableAttributeArray("posAttr");
    programSector->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vbo->release();
    vao->release();

    vaoAzUgm->create();
    vaoAzUgm->bind();
    if (!vaoAzUgm->isCreated()){
        qDebug() << "Can't use SECTORS VAO";
        return;
    }

    quint32 trianglesCount = segmentation * 2, //in quad 2 triangles
            vertexCount = trianglesCount * 3, //in triangles 3 vertex
            valuesCount = vertexCount * nDimensional;

    quint32 bufferSize = sectorsCount * valuesCount * sizeof(GLfloat);

    vboAzUgm->create();
    vboAzUgm->bind();
    vboAzUgm->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboAzUgm->allocate(bufferSize);


    programSector->enableAttributeArray("posAttr");
    programSector->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vboAzUgm->release();
    vaoAzUgm->release();
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
    m_modelMatrix.rotate(shdData.azSensor, 0.,0.,1.);
    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programSector->setUniformValue("mvp", mvp);
    programSector->setUniformValue("upOnZ", false);
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

    m_modelMatrix.setToIdentity();
    mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * m_modelMatrix;
    programSector->setUniformValue("mvp", mvp);

    vaoAzUgm->bind();
    for (quint8 index = 0; index < sectorsCount; index++) {
        if (sectorsState.at(index) == ItemState::Active || index == selectedSector) {
            programSector->setUniformValue("objectColor", sectorColors.at(index));
            if (index == selectedSector)
                programSector->setUniformValue("upOnZ", true);
            glFunc->glDrawArrays(GL_TRIANGLES, azUgmCounter * index, azUgmCounter);
            if (index == selectedSector)
                programSector->setUniformValue("upOnZ", false);
        }
    }
    vaoAzUgm->release();

    programSector->release();

    sensorsValueCheck();
}

void SectorsGLData::presetSectorSlot(const quint8 index, SharedSectorParameters sharedSector)
{
    SectorParameters sector = *sharedSector;

    qreal azWidth = sector.azMax, az = sector.azMin,
            ugmWidth = sector.ugmMax, ugm = sector.ugmMin;

    QVector<Polar2> vectorOfCoor;
    Coor3 coor = Polar2Coor3(Polar(1. , -azWidth / 2, -ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));
    coor = Polar2Coor3(Polar(1. , -azWidth / 2, ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));
    coor = Polar2Coor3(Polar(1. , azWidth / 2, ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));
    coor = Polar2Coor3(Polar(1. , azWidth / 2, -ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));

    polarVertices[index].leftBottom = vectorOfCoor.at(0);
    polarVertices[index].leftTop = vectorOfCoor.at(1);
    polarVertices[index].rightTop = vectorOfCoor.at(2);
    polarVertices[index].rightBottom = vectorOfCoor.at(3);

    QVector<QVector3D> verticesUg1, verticesUg2, verticesUg;

    double az1 = vectorOfCoor.at(0).Az, az2 = vectorOfCoor.at(2).Az;
    if (az1 > az2) {
        az2 += 360.;
    }

    az1 = (90 - az1) * degToRad;
    az2 = (90 - az2) * degToRad;

    double r = sector.distMin, R = sector.distMax,
            //az1 = (90 - sector.azMin) * degToRad, az2 = (90 - sector.azMax) * degToRad,
            //ug1 = (90 - sector.ugmMin) * degToRad, ug2 = (90 - sector.ugmMax) * degToRad;
            ug1 = (90 - 0) * degToRad, ug2 = (90 - 2) * degToRad;

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


    //delete [] vertBuf;
    qreal distUgmGrid = shdData.maxDistance * shdData.indentBetweenGrids;
    qreal offsetBeetwenLine = shdData.ugmGridStep;
    float zeroUgmPosition = shdData.ugmSensor - 45.;

    qreal bottomLeftAz = CorrectPlus(vectorOfCoor.at(0).Az, - shdData.azSensor),
            bottomLeftUgm = vectorOfCoor.at(0).Um - zeroUgmPosition,
          bottomRightAz = CorrectPlus(vectorOfCoor.at(3).Az, - shdData.azSensor),
            bottomRightUgm = vectorOfCoor.at(3).Um - zeroUgmPosition,
          topLeftAz = CorrectPlus(vectorOfCoor.at(1).Az, - shdData.azSensor),
            topLeftUgm = vectorOfCoor.at(1).Um - zeroUgmPosition,
          topRightAz = CorrectPlus(vectorOfCoor.at(2).Az, - shdData.azSensor),
            topRightUgm = vectorOfCoor.at(2).Um - zeroUgmPosition;

    if (bottomLeftAz > bottomRightAz) {
        bottomRightAz += 360.;
    }

    bottomLeftAz = (90 - bottomLeftAz) * degToRad;
    bottomRightAz = (90 - bottomRightAz) * degToRad;

    if (topLeftAz > topRightAz) {
        topRightAz += 360.;
    }

    topLeftAz = (90 - topLeftAz) * degToRad;
    topRightAz = (90 - topRightAz) * degToRad;

    QVector<QVector3D> verticesAzUgm;

    qreal segmentationForUgm = segmentation / 2.;
    qreal bottomDAz = (bottomRightAz - bottomLeftAz) / (double)segmentationForUgm,
            topDAz = (topRightAz - topLeftAz) / (double)segmentationForUgm,
            bottomDUgm = (bottomLeftUgm - bottomRightUgm) / (double)segmentationForUgm,
            topDUgm = (topLeftUgm - topRightUgm) / (double)segmentationForUgm;
    for (quint32 i = 0; i < segmentationForUgm; i++) {
        QVector3D point1 = QVector3D(distUgmGrid * cos(bottomLeftAz + i * bottomDAz),
                                     distUgmGrid * sin(bottomLeftAz + i * bottomDAz) + offsetBeetwenLine * (bottomLeftUgm + i * bottomDUgm), zcoord),
                point2 = QVector3D(distUgmGrid * cos(topLeftAz + i * topDAz),
                                   distUgmGrid * sin(topLeftAz + i * topDAz) + offsetBeetwenLine * (topLeftUgm + i * topDUgm), zcoord),
                point3 = QVector3D(distUgmGrid * cos(bottomLeftAz + (i + 1) * bottomDAz),
                                   distUgmGrid * sin(bottomLeftAz + (i + 1) * bottomDAz) + offsetBeetwenLine * (bottomLeftUgm + (i + 1) * bottomDUgm), zcoord),
                point4 = QVector3D(distUgmGrid * cos(topLeftAz + (i + 1) * topDAz),
                                   distUgmGrid * sin(topLeftAz + (i + 1) * topDAz) + offsetBeetwenLine * (topLeftUgm + (i + 1) * topDUgm), zcoord);

        verticesAzUgm << point1 << point3 << point2
                      << point3 << point4 << point2;
    }


    //if (vertexPerSector != verticesUg.size()) {
    //    qDebug() << QString("Calc Vertex Buffer for Sector №%1 is wrong!!!").arg(index);
    //}

    const quint32 azUgmBufferSize = verticesAzUgm.size() * nDimensional;
    GLfloat *azUgmBuffer = new GLfloat[azUgmBufferSize];

    azUgmCounter = verticesAzUgm.size();

    indexBuf = 0;
    for (quint32 i = 0; i != verticesAzUgm.size(); i++) {
        azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).x();
        azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).y();
        azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).z();
    }

    vboAzUgm->bind();
    vboAzUgm->write(azUgmBufferSize * index * sizeof(GLfloat), azUgmBuffer, azUgmBufferSize * sizeof(GLfloat));
    vboAzUgm->release();

    delete[] azUgmBuffer;
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

    SectorParameters sector = *sharedSector;

    qreal azWidth = sector.azMax, az = sector.azMin,
            ugmWidth = sector.ugmMax, ugm = sector.ugmMin;

    QVector<Polar2> vectorOfCoor;
    Coor3 coor = Polar2Coor3(Polar(1. , -azWidth / 2, -ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));
    coor = Polar2Coor3(Polar(1. , -azWidth / 2, ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));
    coor = Polar2Coor3(Polar(1. , azWidth / 2, ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));
    coor = Polar2Coor3(Polar(1. , azWidth / 2, -ugmWidth / 2));
    vectorOfCoor.push_back(Coor2Polar2(SistemCoor_L2G_fast(coor, Polar2(shdData.inclDirNew, shdData.inclUmNew), Polar2(az, ugm))));

    polarVertices[index].leftBottom = vectorOfCoor.at(0);
    polarVertices[index].leftTop = vectorOfCoor.at(1);
    polarVertices[index].rightTop = vectorOfCoor.at(2);
    polarVertices[index].rightBottom = vectorOfCoor.at(3);

    sectorsState.replace(index, ItemState::Active);    

    QVector<QVector3D> verticesUg1, verticesUg2, verticesUg;

    double az1 = vectorOfCoor.at(0).Az, az2 = vectorOfCoor.at(2).Az;
    if (az1 > az2) {
        az2 += 360.;
    }

    az1 = (90 - az1) * degToRad;
    az2 = (90 - az2) * degToRad;

    double r = sector.distMin, R = sector.distMax,
            //az1 = (90 - sector.azMin) * degToRad, az2 = (90 - sector.azMax) * degToRad,
            //ug1 = (90 - sector.ugmMin) * degToRad, ug2 = (90 - sector.ugmMax) * degToRad;
            ug1 = (90 - 0) * degToRad, ug2 = (90 - 2) * degToRad;

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


    //delete [] vertBuf;
    qreal distUgmGrid = shdData.maxDistance * shdData.indentBetweenGrids;
    qreal offsetBeetwenLine = shdData.ugmGridStep;
    float zeroUgmPosition = shdData.ugmSensor - 45.;

    qreal bottomLeftAz = CorrectPlus(vectorOfCoor.at(0).Az, - shdData.azSensor),
            bottomLeftUgm = vectorOfCoor.at(0).Um - zeroUgmPosition,
          bottomRightAz = CorrectPlus(vectorOfCoor.at(3).Az, - shdData.azSensor),
            bottomRightUgm = vectorOfCoor.at(3).Um - zeroUgmPosition,
          topLeftAz = CorrectPlus(vectorOfCoor.at(1).Az, - shdData.azSensor),
            topLeftUgm = vectorOfCoor.at(1).Um - zeroUgmPosition,
          topRightAz = CorrectPlus(vectorOfCoor.at(2).Az, - shdData.azSensor),
            topRightUgm = vectorOfCoor.at(2).Um - zeroUgmPosition;

    if (bottomLeftAz > bottomRightAz) {
        bottomRightAz += 360.;
    }

    bottomLeftAz = (90 - bottomLeftAz) * degToRad;
    bottomRightAz = (90 - bottomRightAz) * degToRad;

    if (topLeftAz > topRightAz) {
        topRightAz += 360.;
    }

    topLeftAz = (90 - topLeftAz) * degToRad;
    topRightAz = (90 - topRightAz) * degToRad;

    QVector<QVector3D> verticesAzUgm;

    qreal segmentationForUgm = segmentation / 2.;
    qreal bottomDAz = (bottomRightAz - bottomLeftAz) / (double)segmentationForUgm,
            topDAz = (topRightAz - topLeftAz) / (double)segmentationForUgm,
            bottomDUgm = (bottomLeftUgm - bottomRightUgm) / (double)segmentationForUgm,
            topDUgm = (topLeftUgm - topRightUgm) / (double)segmentationForUgm;
    for (quint32 i = 0; i < segmentationForUgm; i++) {
        QVector3D point1 = QVector3D(distUgmGrid * cos(bottomLeftAz + i * bottomDAz),
                                     distUgmGrid * sin(bottomLeftAz + i * bottomDAz) + offsetBeetwenLine * (bottomLeftUgm + i * bottomDUgm), zcoord),
                point2 = QVector3D(distUgmGrid * cos(topLeftAz + i * topDAz),
                                   distUgmGrid * sin(topLeftAz + i * topDAz) + offsetBeetwenLine * (topLeftUgm + i * topDUgm), zcoord),
                point3 = QVector3D(distUgmGrid * cos(bottomLeftAz + (i + 1) * bottomDAz),
                                   distUgmGrid * sin(bottomLeftAz + (i + 1) * bottomDAz) + offsetBeetwenLine * (bottomLeftUgm + (i + 1) * bottomDUgm), zcoord),
                point4 = QVector3D(distUgmGrid * cos(topLeftAz + (i + 1) * topDAz),
                                   distUgmGrid * sin(topLeftAz + (i + 1) * topDAz) + offsetBeetwenLine * (topLeftUgm + (i + 1) * topDUgm), zcoord);

        verticesAzUgm << point1 << point3 << point2
                      << point3 << point4 << point2;
    }


    //if (vertexPerSector != verticesUg.size()) {
    //    qDebug() << QString("Calc Vertex Buffer for Sector №%1 is wrong!!!").arg(index);
    //}

    const quint32 azUgmBufferSize = verticesAzUgm.size() * nDimensional;
    GLfloat *azUgmBuffer = new GLfloat[azUgmBufferSize];

    azUgmCounter = verticesAzUgm.size();

    indexBuf = 0;
    for (quint32 i = 0; i != verticesAzUgm.size(); i++) {
        azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).x();
        azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).y();
        azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).z();
    }

    vboAzUgm->bind();
    vboAzUgm->write(azUgmBufferSize * index * sizeof(GLfloat), azUgmBuffer, azUgmBufferSize * sizeof(GLfloat));
    vboAzUgm->release();

    delete[] azUgmBuffer;
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

void SectorsGLData::maxDistanceChangedSlot()
{
    updateUgmSectors();
}

void SectorsGLData::calcIBO(QOpenGLBuffer *iboBuffer)
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

    iboBuffer->write(0, iboBuf, iboSectors.size() * sizeof(GLushort));

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

void SectorsGLData::updateUgmSectors()
{
    qreal distUgmGrid = shdData.maxDistance * shdData.indentBetweenGrids;
    qreal offsetBeetwenLine = shdData.ugmGridStep;
    float zeroUgmPosition = shdData.ugmSensor - 45.;

    for (quint8 index = 0; index != polarVertices.size(); index++) {

        if (sectorsState.at(index) == ItemState::Empty) {
            continue;
        }

        qreal bottomLeftAz = CorrectPlus(polarVertices.at(index).leftBottom.Az, - shdData.azSensor),
                bottomLeftUgm = polarVertices.at(index).leftBottom.Um - zeroUgmPosition,
                bottomRightAz = CorrectPlus(polarVertices.at(index).rightBottom.Az, - shdData.azSensor),
                bottomRightUgm = polarVertices.at(index).rightBottom.Um - zeroUgmPosition,
                topLeftAz = CorrectPlus(polarVertices.at(index).leftTop.Az, - shdData.azSensor),
                topLeftUgm = polarVertices.at(index).leftTop.Um - zeroUgmPosition,
                topRightAz = CorrectPlus(polarVertices.at(index).rightTop.Az, - shdData.azSensor),
                topRightUgm = polarVertices.at(index).rightTop.Um - zeroUgmPosition;

        if (bottomLeftAz > bottomRightAz) {
            bottomRightAz += 360.;
        }

        bottomLeftAz = (90 - bottomLeftAz) * degToRad;
        bottomRightAz = (90 - bottomRightAz) * degToRad;

        if (topLeftAz > topRightAz) {
            topRightAz += 360.;
        }

        topLeftAz = (90 - topLeftAz) * degToRad;
        topRightAz = (90 - topRightAz) * degToRad;

        QVector<QVector3D> verticesAzUgm;

        qreal segmentationForUgm = segmentation / 2.;
        qreal bottomDAz = (bottomRightAz - bottomLeftAz) / (double)segmentationForUgm,
                topDAz = (topRightAz - topLeftAz) / (double)segmentationForUgm,
                bottomDUgm = (bottomLeftUgm - bottomRightUgm) / (double)segmentationForUgm,
                topDUgm = (topLeftUgm - topRightUgm) / (double)segmentationForUgm;
        for (quint32 i = 0; i < segmentationForUgm; i++) {
            QVector3D point1 = QVector3D(distUgmGrid * cos(bottomLeftAz + i * bottomDAz),
                                         distUgmGrid * sin(bottomLeftAz + i * bottomDAz) + offsetBeetwenLine * (bottomLeftUgm + i * bottomDUgm), depth),
                    point2 = QVector3D(distUgmGrid * cos(topLeftAz + i * topDAz),
                                       distUgmGrid * sin(topLeftAz + i * topDAz) + offsetBeetwenLine * (topLeftUgm + i * topDUgm), depth),
                    point3 = QVector3D(distUgmGrid * cos(bottomLeftAz + (i + 1) * bottomDAz),
                                       distUgmGrid * sin(bottomLeftAz + (i + 1) * bottomDAz) + offsetBeetwenLine * (bottomLeftUgm + (i + 1) * bottomDUgm), depth),
                    point4 = QVector3D(distUgmGrid * cos(topLeftAz + (i + 1) * topDAz),
                                       distUgmGrid * sin(topLeftAz + (i + 1) * topDAz) + offsetBeetwenLine * (topLeftUgm + (i + 1) * topDUgm), depth);

            verticesAzUgm << point1 << point3 << point2
                          << point3 << point4 << point2;
        }


        //if (vertexPerSector != verticesUg.size()) {
        //    qDebug() << QString("Calc Vertex Buffer for Sector №%1 is wrong!!!").arg(index);
        //}

        const quint32 azUgmBufferSize = verticesAzUgm.size() * nDimensional;
        GLfloat *azUgmBuffer = new GLfloat[azUgmBufferSize];

        azUgmCounter = verticesAzUgm.size();

        quint32 indexBuf = 0;
        for (quint32 i = 0; i != verticesAzUgm.size(); i++) {
            azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).x();
            azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).y();
            azUgmBuffer[indexBuf++] = verticesAzUgm.at(i).z();
        }

        vboAzUgm->bind();
        vboAzUgm->write(azUgmBufferSize * index * sizeof(GLfloat), azUgmBuffer, azUgmBufferSize * sizeof(GLfloat));
        vboAzUgm->release();

        delete[] azUgmBuffer;
    }
}

void SectorsGLData::sensorsValueCheck()
{
    bool needToUpdate = false;
    quint16 storedValue = storedAzValue + 360, sensorValue = shdData.azSensor + 360;
    if (abs(storedValue - sensorValue) >= thresholdOfSensorsUpdate) {
        storedAzValue = qFloor(shdData.azSensor);
        needToUpdate = true;
    }

    if (qFloor(fabs(storedUgmValue - shdData.ugmSensor)) >= thresholdOfSensorsUpdate) {
        storedUgmValue = qFloor(shdData.ugmSensor);
        needToUpdate = true;
    }

    if (needToUpdate)
        updateUgmSectors();
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



    calcRect(OpenGLRectF(-1, -1, 2, 2), rectForSamplingBuf, 0, zcoord);

    vboRect2 = new QOpenGLBuffer();
    vboRect2->create();
    vboRect2->bind();
    vboRect2->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboRect2->allocate(rectForSamplingBuf, sizeRectForSampling * sizeof(GLfloat));

    vaoRect2 = new QOpenGLVertexArrayObject();
    vaoRect2->create();
    vaoRect2->bind();
    if (!vaoRect2->isCreated()){
        qDebug() << "Can't use VAO for font";
        return;
    }

    m_programGrid->enableAttributeArray("posAttr");
    m_programGrid->setAttributeBuffer("posAttr", GL_FLOAT, 0, nDimensional, 0);

    vboRect2->release();
    vaoRect2->release();

    sizeRectForSampling = 0;

    delete [] rectForSamplingBuf;
}

TraceGLData::TraceGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const Camera *m_extraCamera, float _depth, SharedSceneData &sharedSceneData, QObject *parent)  : QObject(parent),
    glFunc(func), camera_ptr(m_camera), extraCamera_ptr(m_extraCamera), depth(_depth),
    nDimensional(3),
    offsetForLogBook(100000), offsetForLogBookUgm(1000000),
    defaultLogBookSize(50,50), logBookSize(defaultLogBookSize),
    logBookColor(QColor::fromRgbF(0.5,0.5,0.5,0.6)),
    traceColor(QColor::fromRgbF(0.6,0.6,0.6,1.)),
    textColor(QColor::fromRgbF(0.60f,0.55f,0.09f,1)),
    textSize(0.075f),
    distOffsetForAzH(350.),
    maxVerticesOfTrack(2000), maxTrackNumber(10),
    shdData(sharedSceneData)
{

    programTrace = new QOpenGLShaderProgram(this);

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/trace2VertexShader.vert")) {
        qDebug() << programTrace->log();
        return;
    }

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/trace2FragmentShader.frag")) {
        qDebug() << programTrace->log();
        return;
    }

    if (!programTrace->addShaderFromSourceFile(QOpenGLShader::Geometry,":/glsl/Shaders/trace2GeometryShader.geom")) {
        qDebug() << programTrace->log();
        return;
    }
    if (!programTrace->link()) {
        qDebug() << programTrace->log();
        return;
    }

    programFont = new QOpenGLShaderProgram(this);

    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/sftVertexShader.vert")) {
        qDebug() << programFont->log();
        return;
    }

    if (!programFont->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/sftFragmentShader.frag")) {
        qDebug() << programFont->log();
        return;
    }
    if (!programFont->link()) {
        qDebug() << programFont->log();
        return;
    }

    programLogBook  = new QOpenGLShaderProgram(this);

    if (!programLogBook->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/logBookVertexShader.vert")) {
        qDebug() << programLogBook->log();
        return;
    }

    if (!programLogBook->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/logBookFragmentShader.frag")) {
        qDebug() << programLogBook->log();
        return;
    }

    /*if (!programLogBook->addShaderFromSourceFile(QOpenGLShader::Geometry,":/glsl/Shaders/logBookGeometryShader.geom")) {
        qDebug() << programLogBook->log();
        return;
    }*/

    if (!programLogBook->link()) {
        qDebug() << programLogBook->log();
        return;
    }


    programTrack  = new QOpenGLShaderProgram(this);

    if (!programTrack->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/trackVertexShader.vert")) {
        qDebug() << programTrack->log();
        return;
    }

    if (!programTrack->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/trackFragmentShader.frag")) {
        qDebug() << programTrack->log();
        return;
    }

    if (!programTrack->addShaderFromSourceFile(QOpenGLShader::Geometry,":/glsl/Shaders/trackGeometryShader.geom")) {
        qDebug() << programTrack->log();
        return;
    }

    if (!programTrack->link()) {
        qDebug() << programTrack->log();
        return;
    }

//    fontDriver = new ftCustomSimple(this);
//    fontDriver->genTexels();

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

}

void TraceGLData::renderHAz()
{

}


void TraceGLData::eraseOldTrace(quint32 idTrace)
{

}

void TraceGLData::setLogBookColor(const QColor color)
{

}

void TraceGLData::setTraceColor(const QColor color)
{

}

void TraceGLData::setTextColor(const QColor color)
{

}

void TraceGLData::setTextSize(const TextSizeAction flag, const float value)
{

}

void TraceGLData::drawTrace(quint32 id, bool isDrawing)
{

}

void TraceGLData::reCalcAllTrace()
{

}

void TraceGLData::calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord, float alpha)
{

}

qint32 TraceGLData::getIdByCoordinates(QPointF point)
{
   return -1;
}

void TraceGLData::putTraceOnScene(TraceMark &mark, bool isNewTrace)
{

}

void TraceGLData::findPlaceForLogBook(TraceMark &mark, const quint32 offsetLB)
{

}

void TraceGLData::calcGuideLinePoint(TraceMark &mark, const quint32 offset)
{

}

void TraceGLData::prepareGrideForTrace()
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
    programDSP = new QOpenGLShaderProgram(this);

    if (!programDSP->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/Shaders/dsp2Vert.vert")) {
        qDebug() << programDSP->log();
        return;
    }

    if (!programDSP->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/Shaders/dsp2Frag.frag")) {
        qDebug() << programDSP->log();
        return;
    }
    /*if (!programDSP->addShaderFromSourceFile(QOpenGLShader::Geometry,":/glsl/Shaders/dsp2Geom.gm")) {
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


//    VectorOfAmpGL dataToScene;
    quint32 counter = 0;
    float az = 45., azDelta = 0.25;
    quint32 N = maxNumberOfImpulses, Ntarget = 3000;

    /*DSPGLInfo glData(vbo, vao);
    glData.numberOfQuanta = N;
    glData.arrivalNewDataTime = QTime::currentTime().msecsSinceStartOfDay();
    glData.alpha = startAlpha;

    dspInfo.insert(-1, glData);*/

//    for (quint16 index = 0; index != maxNumberOfBuffer; index++) {
//        quint32 randDuration = QRandomGenerator::global()->bounded(500,1500);
//        for (quint32 indexArray = 0; indexArray != N; indexArray++) {
//            float x = indexArray * distStep * cos((90. - az) * M_PI / 180.),
//                    y = indexArray * distStep * sin((90. - az) * M_PI / 180.);
//            dataToScene << x << y;
//            if (indexArray > Ntarget && indexArray < (Ntarget + randDuration)) {
//                dataToScene.push_back(QRandomGenerator::global()->bounded(50,100));
//            }
//            else {
//                dataToScene.push_back(QRandomGenerator::global()->bounded(0,50));
//            }
//        }

//        counter += N;
//        az += azDelta;
//    }
//    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo->bufferId());
//    GLfloat* vbo_ptr = (GLfloat*)glFunc->glMapBufferRange (
//                GL_ARRAY_BUFFER,
//                0,
//                dataToScene.size() * sizeof(GLfloat),
//                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
//                );

//    if (vbo_ptr != nullptr)
//        memcpy(vbo_ptr, dataToScene.data(), dataToScene.size() * sizeof(GLfloat));
//    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
//    vbo_ptr = nullptr;



//    VectorOfAmpGL dataToScene2;
//    az = 315., azDelta = 0.25;
//    //N = maxNumberOfImpulses, Ntarget = 3000;
//    for (quint16 index = 0; index != maxNumberOfBuffer; index++) {
//        quint32 randDuration = QRandomGenerator::global()->bounded(500,1500);
//        for (quint32 indexArray = 0; indexArray != N; indexArray++) {
//            float x = indexArray * distStep * cos((90. - az) * M_PI / 180.),
//                    y = indexArray * distStep * sin((90. - az) * M_PI / 180.);
//            dataToScene2 << x << y;
//            if (indexArray > Ntarget && indexArray < (Ntarget + randDuration)) {
//                dataToScene2.push_back(QRandomGenerator::global()->bounded(50,100));
//            }
//            else {
//                dataToScene2.push_back(QRandomGenerator::global()->bounded(0,50));
//            }
//        }

//        counter += N;
//        az += azDelta;
//    }
//    glFunc->glBindBuffer(GL_ARRAY_BUFFER, vbo2->bufferId());
//    GLfloat* vbo_ptr2 = (GLfloat*)glFunc->glMapBufferRange (
//                GL_ARRAY_BUFFER,
//                0,
//                dataToScene2.size() * sizeof(GLfloat),
//                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
//                );

//    if (vbo_ptr2 != nullptr)
//        memcpy(vbo_ptr2, dataToScene2.data(), dataToScene2.size() * sizeof(GLfloat));
//    glFunc->glUnmapBuffer(GL_ARRAY_BUFFER);
//    vbo_ptr2 = nullptr;

    //timeToDecreaseAlpha->start();
}

void DSPGLData::render()
{
//    if (dspInfo.isEmpty())
//        return;

//    QMatrix4x4 model;
//    model.setToIdentity();
//    programDSP->bind();
//    QMatrix4x4 mvp = camera_ptr->projectionMatrix() * camera_ptr->viewMatrix() * model;

//    QVector4D colorArray[4];
//    GLfloat rangeArray[4];
//    /*qint16 index = 0;
//    for (; index != vectorOfColors.size(); index++) {
//        const auto &color = vectorOfColors.at(index);
//        colorArray[index] = QVector4D(color.redF(), color.greenF(), color.blueF(), 0.7);
//        rangeArray[index] = vectorOfRanges.at(index);
//    }
//    for (; index != 4; index++) {
//        const auto &color = vectorOfColors.at(vectorOfColors.size() - 1);
//        const float &range = vectorOfRanges.at(vectorOfRanges.size() - 1);
//        colorArray[index] = QVector4D(color.redF(), color.greenF(), color.blueF(), 0.7);
//        rangeArray[index] = range;
//    }*/

//    programDSP->setUniformValue("mvp", mvp);
//    programDSP->setUniformValue("z", depth);

//    //programDSP->setUniformValue("alpha", alpha);
//    //programDSP->setUniformValue("pointSize", pointSize);
//    //programDSP->setUniformValue("distStep", distStep);
//    //programDSP->setUniformValueArray("ranges", rangeArray, 4, 1);
//    //programDSP->setUniformValueArray("colors", colorArray, 4);
//    //programDSP->setUniformValueArray("az", currentAzVector.data(), 10, 1);
//    //programDSP->setUniformValue("N", vectorOfInfo.first().numberOfQuanta);

//    auto itemOfMap = dspInfo.begin();
//    while (itemOfMap != dspInfo.end()) {
//        qint16 indexInVector = 0;
//        for (; indexInVector != itemOfMap.value().vectorOfColors.size(); indexInVector++) {
//            const auto &color = itemOfMap.value().vectorOfColors.at(indexInVector);
//            colorArray[indexInVector] = QVector4D(color.redF(), color.greenF(), color.blueF(), startAlpha);
//            rangeArray[indexInVector] = itemOfMap.value().vectorOfRanges.at(indexInVector);
//        }
//        for (; indexInVector != 4; indexInVector++) {
//            const auto &color = itemOfMap.value().vectorOfColors.last();//.at(itemOfMap.value().vectorOfColors.size() - 1);
//            const float &range = itemOfMap.value().vectorOfRanges.last();//.at(itemOfMap.value().vectorOfRanges.size() - 1);
//            colorArray[indexInVector] = QVector4D(color.redF(), color.greenF(), color.blueF(), startAlpha);
//            rangeArray[indexInVector] = range;
//        }

//        programDSP->setUniformValue("alpha", itemOfMap.value().alpha);
//        programDSP->setUniformValueArray("ranges", rangeArray, 4, 1);
//        programDSP->setUniformValueArray("colors", colorArray, 4);
//        itemOfMap.value().vaoPtr->bind();
//        glFunc->glDrawElements(GL_TRIANGLES, (itemOfMap.value().numberOfQuanta - 2) * 18 * nDimensional, GL_UNSIGNED_SHORT, 0 );
//        itemOfMap.value().vaoPtr->release();
//        itemOfMap++;
//    }

//    /*vao->bind();
//    glFunc->glDrawElements(GL_TRIANGLES, (maxNumberOfImpulses - 2) * 18 * nDimensional, GL_UNSIGNED_SHORT, 0 );
//    vao->release();

//    vao2->bind();
//    glFunc->glDrawElements(GL_TRIANGLES, (maxNumberOfImpulses - 2) * 18 * nDimensional, GL_UNSIGNED_SHORT, 0 );
//    vao2->release();*/

//    programDSP->release();
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

//    for (quint16 index = 0; index != keyToErase.size(); index++) {
//        eraseDSPData(keyToErase.at(index));
//    }

    if (dspInfo.isEmpty()) {
        timeToDecreaseAlpha->stop();
    }
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
