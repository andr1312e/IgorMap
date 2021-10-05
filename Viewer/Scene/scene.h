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
#include <QOpenGLTexture>

#include <CommonEntities/global.h>

#include "camera.h"
#include "Math/bMath.h"

class QOpenGLContext;


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

struct SharedSceneData{
    SharedSceneData() : maxDistance(300), indentBetweenGrids(4/3.),
        ugmGridStep(2.4),
        azSensor(0), ugmSensor(),
        inclXAngle(0), inclYAngle(0),
        inclDirNew(0), inclUmNew(0),
        ugmCenter(0) {}

    quint32 maxDistance;
    float indentBetweenGrids;

    float ugmGridStep;

    float azSensor, ugmSensor;

    float inclXAngle, inclYAngle;
    qreal inclDirNew, inclUmNew;

    float ugmCenter;
};

class MapGL : public QObject {
    Q_OBJECT

    enum SideOfQuadrangle {
        LeftBottom,
        RightBottom,
        LeftTop,
        RightTop
    };

    struct PrivateMapData {
        struct IsoscelesTrapezoid {
            IsoscelesTrapezoid()
                : left(0), bottom(0), top(0) {}
            IsoscelesTrapezoid(float _left, float _bottom, float _top)
                : left(_left), bottom(_bottom), top(_top) {}
            float left;
            float bottom;
            float top;
        };
        PrivateMapData() :
        bottomGeometry(), centerGeometry(), topGeometry(),
        filePaths(9), center(){}
        IsoscelesTrapezoid bottomGeometry, centerGeometry, topGeometry;
        QVector<QString> filePaths;
        QPointF center;
    };

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
    void updateViewCenterGeo(QPointF _centerGeo);
    void translateSlot();
    void clearAllTiles();
    void updateMap(QStringList paths, QVector<GLfloat> points);

signals:
    void getNewMap(QJsonDocument doc);

private:
    void checkFiles();

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programGLSL;
    const float depth;

    const quint8 tilesCount;

    QVector<QOpenGLTexture *> vectorOfTexture;
    QVector<QString> filePathsVector;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;

    QSize tileSize;

    QPointF placementPoint;
    quint8 currentLayer;

    PrivateMapData privateMapData;

    QPointF centerGeo;
    Conversion localConversion;

    SideOfQuadrangle sideOrientation;
    QPointF localPointOfSideOfCenterRect, geoPointOfSideOfCenterRect;

    QSet<quint8> lazyLoadingPng;

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

//public slots:
//    void nextData(qint32 id, QSharedPointer<QVector<DSPData>> sharedVector);
//    void setColorRanges(qint32 id, ColorRanges colorRanges);

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
                           const SharedSceneData &sharedData,
                           QObject *parent = nullptr);

    void calcDrawVector(QVector<QPair<GLushort, GLushort> > &vector);
    void render();

signals:
    void setStateSignal(const quint8 index, const ItemState &state);
    void addSectorViewer(const quint8 size);

public slots:
//    void presetSectorSlot(const quint8 index, SharedSectorParameters sharedSector);
    void excludeSectorSlot(const quint8 index);
//    void addSectorSlot(const quint8 index, SharedSectorParameters sharedSector);
    void deleteSectorSlot(const quint8 index);

    void sectorInFocus(const quint8 index);
    void sectorOutFocus();

    void setColor(const QColor color);

    void maxDistanceChangedSlot();


private:
    void calcIBO(QOpenGLBuffer *iboBuffer);
    void deg360TransitionCheck(float &ang);

    void updateUgmSectors();
    void sensorsValueCheck();

private:
    QOpenGLFunctions_3_3_Core *glFunc;
    const Camera *camera_ptr;
    const SceneOptions *sceneOptions;
    QOpenGLShaderProgram *programSector;
    const quint32 segmentation, sectorsCount;
    StateOfSectors sectorsState;
    QOpenGLVertexArrayObject *vao, *vaoAzUgm;
    QOpenGLBuffer *vbo, *vboAzUgm;
    QOpenGLBuffer *ibo, *iboAzUgm;
    quint32 gpuMemoryReserved;
    quint32 indexPerSector, vertexPerSector, coordinateValuePerSector, nDimensional;

    QColor sectorColor;
    QColor selectedColor;
    QColor blinkingColor;
    quint8 selectedSector;
    SectorColors sectorColors;
    const float depth;
    quint32 azUgmCounter;

    const SharedSceneData &shdData;
    quint16 storedAzValue, thresholdOfSensorsUpdate;
    qint16 storedUgmValue;
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
    MapGL *mapGLData() const { return mapGL; }

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
    void changeProjectionSlot(bool);
    void setBackground(QColor color);
    void setDistMax(const quint16 value);

    void initSceneProperties(const SceneCustomDataInit &cData);

    void setForwardSpeedSlot( float vy );
    void setSideSpeedSlot(float vx );

    void viewCenterRequest();

    void programmUpdateScaling();

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



    QOpenGLBuffer *vboRect, *vboRect2;
    QOpenGLVertexArrayObject *vaoRect, *vaoRect2;
    quint32 sizeRectForSampling;

    SharedSceneData sharedSceneData;

    MapGL *mapGL;

    QColor backgroundColor;
};

#endif // SCENE_H
