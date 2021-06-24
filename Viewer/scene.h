#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QStringList>
#include <QOpenGLFunctions_3_3_Core>
#include <QMultiMap>
#include <QJsonDocument>

#include "camera.h"
#include "datahandler.h"
#include "ftcustom.h"
#include "TcpHandler/datamessage.h"
#include "dspwidget.h"

class QOpenGLContext;

/*struct TrackMark {
    float xPos;
    float yPos;
    float zPos;
    float course;
    float speed;
    float az;
    float dist;
    float h;
    timeval time;
};*/


enum WindowType {
    MainWindow,
    ExtraWindow4,

};

struct ColumnRow {
    ColumnRow() : column(0), row(0) {}
    ColumnRow(qint32 c, qint32 r) : column(c), row(r) {}
    friend bool operator<(const ColumnRow &l, const ColumnRow &r)
    {
        if (l.column < r.column)
            return true;
        else if (l.column == r.column) {
            if (l.row < r.row)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    friend bool operator!=(const ColumnRow &l, const ColumnRow &r)
    {
        if (l.column != r.column || l.row != r.row)
            return true;
        else
            return false;
    }
    friend bool operator==(const ColumnRow &l, const ColumnRow &r)
    {
        if ((l.column == r.column) && (l.row == r.row))
            return true;
        else
            return false;
    }



    qint32 column;
    qint32 row;
};



struct SceneOptions {
    SceneOptions() :
        maxDist(300),
        initialRect( -maxDist, -maxDist, 2 * maxDist, 2 * maxDist),
        farNearPlane(-maxDist, maxDist),
        sceneRect(),
        screenRect(),
        aspectRatio(),
        aspectRatioScreenWithScene()
    {
        //setInitialSize();
    }
    void updateMaxDist(quint16 value) {
        maxDist = value;
        initialRect = OpenGLRectF(-maxDist, -maxDist, 2 * maxDist, 2 * maxDist);
    }
    void setScreenRect(qreal width, qreal height, qreal x = 0., qreal y = 0.) {
        screenRect = QRectF(x, y, width, height);
        aspectRatio = width / height;
        sceneRect = OpenGLRectF(initialRect.x() * aspectRatio,
                                initialRect.y(),
                                initialRect.width() * aspectRatio,
                                initialRect.height());
        aspectRatioScreenWithScene = QPointF(sceneRect.width() / screenRect.width(),
                                             sceneRect.height() / screenRect.height());

    }    

    quint16 maxDist;
    OpenGLRectF initialRect;
    const QPointF farNearPlane;

    OpenGLRectF sceneRect;
    QRectF screenRect;
    qreal aspectRatio;
    QPointF aspectRatioScreenWithScene;
};


class GrideGL : public QObject {
    Q_OBJECT
public:
    explicit GrideGL(QOpenGLFunctions_3_3_Core *func,
                     const Camera *m_camera,
                     const Camera *m_extraCamera,
                     const SceneOptions *sceneOption,
                     QOpenGLShaderProgram *prog,
                     ftCustom *font,
                     float _depth,
                     QObject *parent = nullptr);
    void render();
    void renderAzH();
    void prepare();
    void prepareAzH();
    void updateText(const float &horizontalScale);
    void updateMoveText();

public slots:
    void setGrideColor(QColor color);
    void setTextColor(QColor color);

    void setDistDiscret(const quint16 value);
    void setAzDiscret(const quint16 value);
    void setTextSize(const TextSizeAction flag, const float value);
    void setAzMarkOnOff(bool flag);
    void setDistMarkOnOff(bool flag);

    void resetCameraSlot();

private:
    void calcCharPosition(quint16 &mode, OpenGLRectF &rectOfViewMatrix, QVector<QPair<quint32, quint32> > &resultVector);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr, *extraCamera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programGride, *programFont;
    ftCustom *fontDriver;
    const float depth;

    QOpenGLVertexArrayObject *vao, *vaoFont, *vaoFont2;
    QOpenGLBuffer *vbo, *vboFont, *vboFont2;

    quint32 fontBufferSize, fontBufferSize2,
            charCount, charCount2;

    QColor grideColor, textColor;

    QVector<QPointF> centerOfText, centerOfText2;
    QVector<QString> vectorOfText, vectorOfText2;

    QVector<quint16> distStepDependOnScaleLevelVector;
    QVector<QOpenGLVertexArrayObject*> vaoDependOnScaleLevel;
    QVector<QOpenGLBuffer*> vboDependOnScaleLevel;
    QVector<quint32> grideBufferSize;

    QOpenGLVertexArrayObject *vaoAzGride;
    QOpenGLBuffer *vboAzGride;
    quint32 azGrideBufferSize;

    GLfloat scaleText;
    bool azMarkOn, distMarkOn;

    quint32 hGrideIndicesCount, azGrideIndicesCount, hFontIndicesCount, azFontIndicesCount;
    QOpenGLVertexArrayObject *azHPlotVAO, *azFontVAO, *hFontVAO;
    QOpenGLBuffer *azHPlotVBO, *azFontVBO, *hFontVBO;

    const float koeffAz;
    float centerAz;
};

class MapGL : public QObject {
    Q_OBJECT
public:
    explicit MapGL(QOpenGLFunctions_3_3_Core *func,
                   const Camera *m_camera,
                   const SceneOptions *sceneOption,
                   float _depth,
                   QObject *parent = nullptr);
    void render();
    void prepare();

public slots:
    void update(QJsonDocument doc);
    void translateSlot();

signals:
    void getNewMap(QJsonDocument doc);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programGLSL;
    const float depth;

    QVector<QOpenGLTexture *> vectorOfTexture;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;

    QSize tileSize;

    QPointF placementPoint;
};

class NewGrideGL : public QObject {
    Q_OBJECT
public:
    explicit NewGrideGL(QOpenGLFunctions_3_3_Core *func,
                     const Camera *m_camera,
                     const SceneOptions *sceneOption,
                     float _depth,
                     QObject *parent = nullptr);
    void render();
    void prepare();

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programGride;
    const float depth;

    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;

    QColor grideColor;

    const quint8 nDimensional;
};

struct DSPGLInfo {
    DSPGLInfo() : numberOfQuanta(0), alpha(0.7),
                  vboPrt(nullptr), vaoPtr(nullptr),
                  vectorOfColors({QColor("#13ed1b"), QColor("#f8f008"), QColor("#fb0505") }),
                  vectorOfRanges( {0, 50, 100} )
    {}
    DSPGLInfo(QOpenGLBuffer *vbo, QOpenGLVertexArrayObject *vao) :
        numberOfQuanta(0), alpha(0.7),
        vboPrt(vbo), vaoPtr(vao),
        vectorOfColors({QColor("#13ed1b"), QColor("#f8f008"), QColor("#fb0505") }),
        vectorOfRanges( {0, 50, 100} )
    {}

    quint32 numberOfQuanta;
    float alpha;
    quint32 arrivalNewDataTime;

    QOpenGLBuffer *vboPrt;
    QOpenGLVertexArrayObject *vaoPtr;

    QVector<QColor> vectorOfColors;
    QVector<int> vectorOfRanges;
};

class DSPGLData : public QObject {
    Q_OBJECT
public:
    explicit DSPGLData(QOpenGLFunctions_3_3_Core *func,
                       const Camera *m_camera,
                       const SceneOptions *sceneOption,
                       float _depth,
                       QObject *parent = nullptr);

    void calcDrawVector(QVector<QPair<GLushort, GLushort> > &vector);
    void preapre();
    void render();

public slots:
    void nextData(qint32 id, QSharedPointer<QVector<DSPData>> sharedVector);
    void setColorRanges(qint32 id, ColorRanges colorRanges);

    void eraseDSPData(qint32 id);

private:
    void calcIBO(QOpenGLBuffer *iboBuffer);
    void decreaseAlpha();

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programDSP;
    const float depth;

    QOpenGLBuffer *vbo, *vbo2, *ibo, *ibo2;
    QOpenGLVertexArrayObject *vao, *vao2;

    //QMap<float, DSPGLInfo> vectorOfInfo;
    QMap<qint32, DSPGLInfo> dspInfo;

    const quint8 nDimensional;

    const quint16 maxNumberOfImpulses, maxNumberOfBuffer;
    const float distStep, pointSize;
    QVector<float> currentAzVector;

    QVector<QColor> vectorOfColors;
    QVector<int> vectorOfRanges;

    QTimer *timeToDecreaseAlpha;
    quint16 decreaseAlpha_msec, eraseDSP_msec;
    const float startAlpha;
    float alpha;

    QVector<QPair<QOpenGLBuffer*, QOpenGLVertexArrayObject*> > freeBufferObjectsVector;
};


using StateOfSectors = QVector< ItemState >;
using SectorVBOs = QVector<QOpenGLBuffer>;
using SectorColors = QVector<QColor>;

class SectorsGLData : public QObject {
    Q_OBJECT
public:
    explicit SectorsGLData(QOpenGLFunctions_3_3_Core *func,
                           const Camera *m_camera,
                           const SceneOptions *sceneOption,
                           QOpenGLShaderProgram *prog,
                           float _depth,
                           QObject *parent = nullptr);

    void calcDrawVector(QVector<QPair<GLushort, GLushort> > &vector);
    void render();

signals:
    void setStateSignal(const quint8 index, const ItemState &state);
    void addSectorViewer(const quint8 size);

public slots:
    void presetSectorSlot(const quint8 index, SharedSectorParameters sharedSector);
    void excludeSectorSlot(const quint8 index);
    void addSectorSlot(const quint8 index, SharedSectorParameters sharedSector);
    void deleteSectorSlot(const quint8 index);

    void sectorInFocus(const quint8 index);
    void sectorOutFocus();

    void setColor(const QColor color);
    void setBlinkingActions(const quint8 index, ActionsWithBlinkingSector action);

private:
    void calcIBO();
    void deg360TransitionCheck(float &ang);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programSector;
    SectorParameters lastParameters;
    const quint32 segmentation, sectorsCount;
    StateOfSectors sectorsState;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *ibo;
    quint32 gpuMemoryReserved;
    quint32 indexPerSector, vertexPerSector, coordinateValuePerSector, nDimensional;

    QColor sectorColor;
    QColor selectedColor;
    QColor blinkingColor;
    quint8 selectedSector;
    SectorColors sectorColors;
    const float depth;
};

class KTAGLData : public QObject {
    Q_OBJECT
public:
    explicit KTAGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, float _depth, QObject *parent = nullptr);
    void setSceneOptions(const SceneOptions *sOptions);
    void prepare();
    void render();

public slots:
    void addPOIMarkSlot(POIKtaMessage msg);
    void addVOIMarkSlot(VOIMarkMessage msg);
    void eraseOldKTA();
    void eraseOldSampledKTA();

    void setKTAColor(bool isPOI, const QColor color);
    void setKTASize(bool isPOI, const TextSizeAction flag, const float value);

    void drawSampledMarkSlot(QSharedPointer<QVector<float> > array);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const float depth;

    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programKTA;
    QOpenGLBuffer *vboSampledMark;
    QOpenGLVertexArrayObject *vaoSampledMark;
    GLuint vbo, vao;

    quint32 vboIndex;
    quint32 vboLeftLimit, vboRightLimit;

    QMap<quint32, QVector<quint32> > mapTime;

    const quint32 ktaCountMax;
    QTimer *timeErase, *timeEraseForSampledMark;
    quint32 timeAlive_msec;

    QColor ktaPOIColor, ktaVOIColor, ktaVOIRespondingColor;
    float ktaPOISize, ktaVOISize;

    quint32 sampledMarkSize;
};

struct TraceMark {
    TraceMark() : id(0), xPos(0), yPos(0),
        course(0), speed(0),
        az(0), dist(0), h(0),
        tracePosition(), logBookPosition(),
        guideLineEnd(), edge(0), priority(0),
        showTrack(false) {}

    quint32 id;
    float xPos;
    float yPos;
    float course;
    float speed;
    float az;
    float dist;
    float h;

    ColumnRow tracePosition;
    ColumnRow logBookPosition;
    QPointF guideLineEnd;
    quint8 edge;

    quint8 priority;
    bool showTrack;
};

struct TrackMark
{
    TrackMark() : pos(0,0), posExtended(0,0), course(0) {}

    QPointF pos;
    QPointF posExtended;
    float course;
};

struct TrackMarkInfo {
    quint16 trackBufferId;
    quint16 currentPositionInVector;
    QVector<QVector3D> vectorOfTrackXY;
};

using MapOfTraceMark = QMap< quint32, TraceMark >;
using MapOfTraceTrack = QMap <quint32, TrackMarkInfo >;
using MapOfGrideOfTraceMark = QMap< ColumnRow, QMap<quint32, quint8> >;

class TraceGLData : public QObject {
    Q_OBJECT
public:
    explicit TraceGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, const Camera *m_extraCamera, float _depth, QObject *parent = nullptr);
    void setSceneOptions(const SceneOptions *sOptions);
    void prepare();
    void render();
    void renderHAz();
    void prepareGrideForTrace();
    qint32 getIdByCoordinates(QPointF point);

signals:
    void traceInfoToExtraWindow(quint16 id, quint16 h);
    void addExtraWindowSignal(quint16 id);
    void msgToVOI(QByteArray msg);
    void trackDrawingReset();

public slots:
    void addTraceMark(RLSOaimMessage msg);
    //void eraseOldTraceFromVOI(quint32 idTrace);
    void eraseOldTrace(quint32 idTrace);

    void setLogBookColor(const QColor color);
    void setTraceColor(const QColor color);
    void setTextColor(const QColor color);
    void setTextSize(const TextSizeAction flag, const float value);

    void reCalcAllTrace();

    //void interactiveActionsWithTrack(quint32 id, ActionsWithTrack action, quint32 addParameter);
    void drawTrace(quint32 id, bool isDrawing);

private:
    void calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord, float alpha = 0);
    void putTraceOnScene(TraceMark &mark, bool isNewTrace = true);
    void findPlaceForLogBook(TraceMark &mark);
    void calcGuideLinePoint(TraceMark &mark);

    //void initTrackBuffer(quint32 id);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr, *extraCamera_ptr;
    const float depth;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programTrace, *programFont, *programLogBook, *programTrack;
    QOpenGLBuffer *vboFont, *tVbo, *tVbo2, *trackVBO;
    QOpenGLVertexArrayObject *vaoFont, *tVao, *tVao2, *trackVAO;

    //QVector<QOpenGLBuffer *> vbo;
    //QVector<QOpenGLVertexArrayObject*> vao;
    //QVector<OpenGLRectF> logBookRect;

    quint32 traceBuffSize;

    MapOfTraceMark mapTraceMark;
    MapOfGrideOfTraceMark grideOfTraceMark;
    const quint32 offsetForLogBook;

    ftCustomSimple *fontDriver;

    const QSizeF defaultLogBookSize;    
    QSizeF logBookSize;
    OpenGLRectF grideRect;

    QColor logBookColor, traceColor, textColor;
    float textSize;

    const float distOffsetForAzH;
    QMap<quint16, quint32> mapOfTrackBufferId;
    QSet<quint16> setOfFreeBufferID;
    MapOfTraceTrack mapOfTraceTrack;
    const quint32 maxVerticesOfTrack, maxTrackNumber;
    quint32 currentValueOfTrackVertices;
};

using VectorOfColor = QVector<QColor>;
class Test3D : public QObject {
    Q_OBJECT
public:
    explicit Test3D(QOpenGLFunctions_3_3_Core *func,
                    QOpenGLShaderProgram *prog,
                    ftCustom *font,
                    QObject *parent = nullptr);
    void render();
    void prepare();
    void updateScaleOfView(const float &horizontalScale);
    void updateEulerAngels(float yaw, float pitch, float roll);

public slots:
    void addTraceMark(RLSOaimMessage msg);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    QOpenGLShaderProgram *programGride, *programTrace, *programFont,
                         *programGrideFont, *programGride3DFont, *programFont3D;
    Camera *camera3D;
    ftCustomSimple *simpleFontDriver;
    ftCustom *fontDriver;

    QOpenGLVertexArrayObject *vao, *traceVAO, *trackMarkOnAxisVAO, *textRectVAO, *fontVAO, *grideDistFontVAO,
                            *grideAzFontVAO, *grideHFontVAO, *fontHVAO;
    QOpenGLBuffer *vbo, *traceVBO, *trackMarkOnAxisVBO, *textRectVBO, *fontVBO, *grideDistFontVBO,
                   *grideAzFontVBO, *grideHFontVBO, *fontHVBO;
    quint32 firstBufferSize, secondBufferSize;
    float pitchC, rollC, yawC, cameraDist;

    MapOfTraceMark mapTraceMark;
    quint32 segmentationForAxisMark, numberOfIndicesInTextRect,
            numberOfIndicesOfGrideDistText, numberOfIndicesOfGrideAzText,
            numberOfIndicesOfGrideHText;

    VectorOfColor colors;

    OpenGLRectF textRect;
    float textSize, grideTextSize;
};

struct PrivateRayInfo {
    PrivateRayInfo() : azMin(0), azMax(0), ugm(0), distMin(0), distMax(0) {}
    PrivateRayInfo(float _azMin, float _azMax, float _ugm, float _distMin, float _distMax) :
        azMin(_azMin), azMax(_azMax), ugm(_ugm), distMin(_distMin), distMax(_distMax) {}
    float azMin;
    float azMax;
    float ugm;
    float distMin;
    float distMax;
};


using ListOfOffsetAndCountRays = QList<QPair <quint8, quint32> >;

class RayGLData : public QObject {
    Q_OBJECT
public:
    explicit RayGLData(QOpenGLFunctions_3_3_Core *func, const Camera *m_camera, float _depth, QObject *parent = nullptr);
    void prepare();
    void prepareFlatRay();
    void render();

public slots:
    void updateRaySetSlot(RaySet set);

    void setColor(const QColor color);
    void setMaxDist(const float value);

private:
    void calcRay(GLfloat *array, quint32 &counter, const float &az, const float &ugm, const float zcoord);
    void calcFlatRay(GLfloat *array, quint32 &counter, const float &az, const float zcoord);
    float deg360TransitionCheck(float ang);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const float depth;

    QOpenGLShaderProgram *programRays;
    QOpenGLBuffer *vbo;
    QOpenGLVertexArrayObject *vao;

    quint32 raysBuffSize, maxRaysBuffSize;

    ListOfOffsetAndCountRays vectorOfRayOffsetAndCount;
    RaySet raySet;

    const quint16 rayNumberMax;
    const float rayHalfWith;

    QColor rayColor;
    float maxDist;

    QTimer *timeErase;
    quint32 timeAlive_msec;
};

class ExtraWindow : public QObject{
    Q_OBJECT

    enum RenderType {
        HRender,
        DSPRender,
        NTRender
    };

public:
    explicit ExtraWindow(QOpenGLFunctions_3_3_Core *func,
                         QOpenGLShaderProgram *progFont, QOpenGLShaderProgram *progButton,
                         ftCustom *_fontDriver,
                         QObject *parent = nullptr);
    void setRect(const OpenGLRectF &rect);
    void setQRect(const QRect &rect);
    const QRect &getQRect();
    void setUBOInfo(GLuint index, quint32 offset) { uboIndex = index;  uboOffset = offset; }
    void prepareExtraWindow();
    void prepareChart();
    void prepareDSP();
    void renderExtraWindow();
    void renderDSP();
    void renderNT();
    void preRender();
    void render();

    void simplePrepare();
    void simpleRender();
    void searchHoveredSelectedItem(QPoint point, bool isHovered = false);

    void addInfo(const quint16 h);


private slots:

    void updateDSP();

private:

    void calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord);
    void calcRect2d(const OpenGLRectF &rect, GLfloat *array, int counter);

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    QOpenGLShaderProgram *m_programFont, *m_programButton, *m_programDSP;
    ftCustom *fontDriver;

    Camera* m_camera;

    OpenGLRectF extraWindow;
    QRect windowRect;

    OpenGLRectF legendXRect, legendYRect, chartRect;


    OpenGLRectF buttonAltitudeRect, buttonDSPRect, buttonNTRect;
    QRect buttonAltitudeQRect, buttonDSPQRect, buttonNTQRect;

    QOpenGLBuffer *m_vboBackGroundWindow, *m_vboBackGroundChart,
                  *m_vboAxis, *m_vboChart, *m_vboTextForAxis, *m_vboTargetRect, *m_vboButtons, *m_vboButtonsText;

    QOpenGLVertexArrayObject *m_vaoExtraWindow, *m_vaoTextForAxis, *m_vaoTargetRect, *m_vaoButtons, *m_vaoTextForButtons;

    quint32 sizeBackGroundBuf, sizeBackGroundChartBuf, sizeAxisChartBuf, sizeGridChartBuf, sizeTextBuf,
            sizeButtonsBuff, sizeTextForButtons;

    GLuint uboIndex;
    quint32 uboOffset;

    int hoveredItem, selectedItem;

    RenderType renderType;

    QOpenGLBuffer *m_vboDSPZCoord, *m_iboDsp;
    QOpenGLVertexArrayObject *m_vaoDSP;
    quint32 sizeDSPZCoords, sizeIBODSP;
    QVector<quint16> heightTrace;

    QOpenGLShaderProgram *m_programTrace;
    QOpenGLBuffer *m_vboTrace;
    QOpenGLVertexArrayObject *m_vaoTrace;
    quint32 sizeTraceBuffer;
};



class Scene : public QObject, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void initialize();
    void update(float t);
    void render();
    void resize(int w, int h , int x = 0, int y = 0);

    // Camera motion control
    void setSideSpeed( float vx ) { m_v.setX(m_v.x() + vx); }
    void setVerticalSpeed( float vz ) { m_v.setZ(m_v.z() + vz); }
    void setForwardSpeed( float vy ) { m_v.setY(m_v.y() + vy); }
    void setViewCenterFixed( bool b ) { m_viewCenterFixed = b; }

    // Terrain scales
    void setTerrainHorizontalScale(const float& horizontalScale );
    float terrainHorizontalScale() const { return m_horizontalScale; }
    //void setTerrainVerticalScale( float verticalScale ) { m_verticalScale = verticalScale; }
    //float terrainVerticalScale() const { return m_verticalScale; }
    void userScaling(const float& horizontalScale, bool centerOnMouseCursor = false, QPointF mouseCursor = QPointF());


    void setContext( QOpenGLContext* context ) { m_context = context; }
    QOpenGLContext* context() const { return m_context; }

    // Camera orientation control
    void pitch( float angle ) { m_pitchAngle = angle; }
    void yaw( float angle ) { m_yawAngle = angle; }
    void roll(float angle) { m_rollAngle = angle; }

    void updateCamera();
    void resetCamera();
    void resetScaling();

    void resetExtraCamera();

    QOpenGLShaderProgram* shaderProgram() const { return m_programGrid; }
    SectorsGLData* sectorsGLData() const { return m_sectorsGLData; }
    KTAGLData* ktaGLData() const { return ktaData; }
    TraceGLData* traceGLData() const { return traceData; }
    RayGLData* rayGLData() const { return rayData; }
    GrideGL* grideData() const { return grideGL; }
    DSPGLData *dspGLData() const { return dspData; }
    MapGL *mapGLData() const { return mapGL; }
    //Test3D* test3DData() const { return test3D; }

    Camera *getCameraPtr() const { return m_camera; }

    void mouseTracking(const QPointF &point);
    void mouseRelease(const QPointF &point);

    QVector3D screenToScene(const QPointF& point);
    QVector3D screenToSceneDxDy(const QPointF& point);

    void mouseMoveGride();
    void KTASampling(const QPointF &point1, const QPointF &point2);
    void updateRect(const QPointF &point1, const QPointF &point2);

    void targetingAdd(const QPointF &point);
    void targetingAddQuick(const QPointF &point);
    void targetingExclude(const QPointF &point);

    void test3DCamera(float yaw, float pitch, float roll);

signals:
    void resizeRequest(const QSize size);
    void KTASamplingRequest(const QPointF leftBottom, const QPointF rightTop);
    void targetingAddRequest(const QPointF point, bool isQuick);
    void targetingExcludeRequest(const QPointF point);

public slots:
    void addExtraWindow(const quint8 size);
    void updateInfoInExtraWindow(quint16 id, quint16 h);

    void changeProjectionSlot(bool);
    void setBackground(QColor color);
    void setDistMax(const quint16 value);

    void initSceneProperties(const SceneCustomDataInit &cData);

    void setForwardSpeedSlot( float vy );
    void setSideSpeedSlot(float vx );

private:
    void resizeViewPort(int w, int h);

    void prepareShaders();
    void prepareTextures();
    void prepareVertexBuffers( QSize heightMapSize );
    void prepareVertexArrayObject();

    void prepareGrid();
    void prepareDSP();

    void prepareSectors();
    void prepareFont();
    void prepareFontArray();
    void prepareExtraWindow();

    bool calcSector(SharedSectorParameters sharedSector);

    void renderExtraWindow();
    void calcRect(const OpenGLRectF &rect, GLfloat *array, int counter, float &zcoord);

    void simplePrepare();
    void simpleRender();

    void initRect();

private:

    bool isExtraWindowAdd = false;


    QOpenGLContext* m_context;
    QOpenGLShaderProgram *m_programGrid, *m_programFont, *m_programButton; //*m_programKTA;

    Camera *m_camera, *m_extraCamera;
    QVector3D m_v;
    bool m_viewCenterFixed;
    float m_pitchAngle;
    float m_yawAngle;
    float m_rollAngle;

    QMatrix4x4 m_viewportMatrix;
    QSize screenSize;
    OpenGLRectF mainViewPort, extraViewPort;

    QOpenGLVertexArrayObject *m_vao, *m_vaoSector, *m_vaoFont;
    QOpenGLBuffer *m_vbo, *m_vboSectors, *m_vboGrid, *m_vboDSP, *m_vboFont;
    QOpenGLBuffer m_patchBuffer;
    int m_patchCount;
    float m_screenSpaceError;
    bool orthoProjection = true;

    QMatrix4x4 m_modelMatrix;
    float m_horizontalScale;
    float m_verticalScale;

    float m_time;
    QStringList m_displayModeNames;
    QVector<GLuint> m_displayModeSubroutines;

    QOpenGLFunctions_3_3_Core* m_funcs;
    QSize m_heightMapSize;

    SceneOptions sceneOptions, extraSceneOptions;
    GLfloat *vertBuf4;
    quint32 sizeIndexBuf1, sizeIndexBuf2, sizeVertBuf11, sizeIBO12;

    SectorsGLData *m_sectorsGLData;

    const QSize extraWindow;
    ftCustom *customFontDriver;

    Camera* m_cameraExtraWindow;
    QOpenGLBuffer *m_vboBackGroundWindow, *m_vboBackGroundChart,
                  *m_vboAxis, *m_vboChart, *m_vboTextForAxis, *m_vboTargetRect, *m_vboButtons, *m_vboButtonsText;
    QOpenGLTexture *m_textureForTextAxes;
    QOpenGLVertexArrayObject *m_vaoExtraWindow, *m_vaoTextForAxis, *m_vaoTargetRect, *m_vaoButtons, *m_vaoTextForButtons;
    quint32 sizeBackGroundBuf, sizeBackGroundChartBuf, sizeAxisChartBuf, sizeGridChartBuf, sizeTextBuf,
            sizeButtonsBuff, sizeTextForButtons;

    GLuint uboIndex, uniformBlockIndex, uboIndexButtons, uniformBlockIndexButtons;

    OpenGLRectF buttonAltitudeRect, buttonDSPRect, buttonNTRect;
    QRect buttonAltitudeQRect, buttonDSPQRect, buttonNTQRect;
    int hoveredItem, selectedItem;

    QVector<ExtraWindow*> vectorExtraWindows;

    QOpenGLBuffer *vboRect;
    QOpenGLVertexArrayObject *vaoRect;
    quint32 sizeRectForSampling;

    GrideGL *grideGL;
    KTAGLData *ktaData;
    TraceGLData *traceData;
    RayGLData *rayData;
    DSPGLData *dspData;
    NewGrideGL *ngrideGL;
    MapGL *mapGL;
    //Test3D *test3D;
    //QOpenGLVertexArrayObject *qVAO;
    //QOpenGLBuffer *qVBO;

    QColor backgroundColor;
};

Q_DECLARE_METATYPE(POIKtaMessage)
Q_DECLARE_METATYPE(VOIMarkMessage)
Q_DECLARE_METATYPE(RLSOaimMessage)
Q_DECLARE_METATYPE(RaySet)
Q_DECLARE_METATYPE(ResetTrackMessage)

#endif // SCENE_H
