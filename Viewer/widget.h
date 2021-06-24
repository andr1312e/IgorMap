#ifndef WIDGET_H
#define WIDGET_H

#include <QWindow>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QtMath>
#include <QMenu>
#include <QOpenGLPaintDevice>
#include <QTimer>
#include "scene.h"

QT_BEGIN_NAMESPACE
class QOpenGLContext;
class QOpenGLPaintDevice;
class QOpenGLBuffer;
class QOpenGLTexture;
class QOpenGLFramebufferObject;
QT_END_NAMESPACE


struct KeyPressed
{
    KeyPressed() {}
    bool Up = false;
    bool Down = false;
    bool Right = false;
    bool Left = false;
    bool key_8 = false;
    bool key_5 = false;
    bool key_4 = false;
    bool key_6 = false;
    bool key_Plus = false;
    bool key_Minus = false;
    bool key_F = false;
    bool key_Ctrl = false;
    bool key_1 = false;

    bool MouseLeft = false;
    bool MouseRight = false;
};

struct EulerAngles {
    qreal pitch = 0.0f;
    qreal yaw = -M_PI_2 + 0.01;
    qreal roll = 0.0f;
};

struct MousePosition {
    float lastX = 0;
    float lastY = 0;
    bool firstGetMouse = false;
};

class Widget : public QWindow
{
    Q_OBJECT

public:
    Widget(QScreen* screen = nullptr);

    void initialize();
    void render();
    Scene* getSceneRef() const { return m_scene; }
    QOpenGLContext* getSharedContextRef() { return m_context->shareContext(); }
    void doNotRender(bool flag) {renderFlag = flag;}

signals:
    void openSectorAddWidget(QPointF point);
    void KTASampled();
    void activatedActionWithTrack(quint32 id, ActionsWithTrack action);

public slots:
    void resizeMainGL(const QSize size);

protected slots:
    void renderNow();
    void resizeGL();
    void forceKeyRelease();


private slots:
    void addSectorTriggered();


private:
    void initTraceMenu();

private:
    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
    Scene* m_scene;

    KeyPressed keyPressed;
    EulerAngles eulerAngles, eulerAnglesForPort;

    GLfloat persent = 1;
    QVector3D rotateVector, rotateVector2;

    QOpenGLShaderProgram *m_programGrid, *m_programFont, *m_programKTA; //*m_programYellow;
    QOpenGLVertexArrayObject *m_vao, *m_vaoFont, *m_vao2, *m_vaoKTA, *m_vao3;
    QOpenGLBuffer *vboPtr, *eboPtr, *vboFont, *vboPtr2, *vboKTA;
    //QOpenGLTexture *texture2, *textureColorBufferMultiSampled;
    QOpenGLFramebufferObject *frameBufferObj;

    QVector<QOpenGLVertexArrayObject *> vectorVAO;

    SceneOptions sceneOptions, sceneOptions2;

    //ftCustom *customFontDriver;
    unsigned int intermediateFBO, screenTexture, rbo, textureColorBufferMultiSampled, framebuffer;
    bool wheelPress = false;

    const int KTAcount = 10000;
    GLfloat *vertBuf4;
    quint32 sizeIndexBuf1, sizeIndexBuf2;
    GLsizei widthPort, heightPort;

    QMenu *mainMenu, *traceMenu;

    QPointF mousePressPos, mousePressOldPos;
    bool isMouseMove = false;
    bool isContextMenuVisible = false;
    bool preHiddingContextMenu;
    bool isDoubleClick = false;

    QTimer *timerForForceKeyRelease;

    quint32 clickedTraceNumber;
    bool renderFlag;


protected:
    bool event(QEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *ev) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

};

#endif // WIDGET_H
