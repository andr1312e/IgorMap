#include "widget.h"

#include <QDir>
#include <QKeyEvent>
#include <QtMath>
#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>
#include <QQuaternion>
#include <QElapsedTimer>
#include <QPainter>
#include <QPaintEngine>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QOpenGLFramebufferObjectFormat>
#include <QCursor>
#include <QPainter>
#include <QAction>
#include <QApplication>
#include <QScreen>
#include <QtPlatformHeaders/QWindowsWindowFunctions>

Widget::Widget(QScreen* screen)
    :   QWindow(screen),
        m_context(nullptr),
        m_device(nullptr),
        m_scene(new Scene(this)),
        m_programGrid(nullptr),
        m_programFont(nullptr),
        m_programKTA(nullptr),
        traceMenu(new QMenu()),
        renderFlag(true)
{
    setSurfaceType(OpenGLSurface);

    setGeometry(screen->geometry());

    setFormat(QSurfaceFormat::defaultFormat());    
    setVisibility(QWindow::Maximized);

    const quint8 windowsCount = 2;
    widthPort = height() / windowsCount;
    heightPort = height() / windowsCount;

    mainMenu = new QMenu();

    m_context = new QOpenGLContext(this);
    m_context->setFormat(format());
    m_context->create();

    if (!m_context->makeCurrent(this)) {
        qDebug() << "makeCurrent() failed";
        return;
    }

    //showFullScreen();

    m_scene->setContext(m_context);
    resizeGL();
    m_scene->initialize();    

    connect(m_scene, &Scene::resizeRequest, this, &Widget::resizeMainGL);

    qDebug() << requestedFormat().version().first << requestedFormat().version().second << requestedFormat().profile();  

    timerForForceKeyRelease = new QTimer();
    timerForForceKeyRelease->setSingleShot(true);
    connect(timerForForceKeyRelease, &QTimer::timeout, this, &Widget::forceKeyRelease);

    //QWindowsWindowFunctions::setWindowActivationBehavior(QWindowsWindowFunctions::AlwaysActivateWindow);

    QTimer::singleShot(20, this, &Widget::forceUpdate);

    initTraceMenu();
}

void Widget::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (m_context == nullptr) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(format());
        m_context->create();

        needsInitialize = true;
    }

    if (!m_context->makeCurrent(this)) {
        qDebug() << "makeCurrent() failed";
        return;
    }

    if (needsInitialize) {
        m_scene->setContext(m_context);
        m_scene->initialize();
        resizeGL();

        qDebug() << requestedFormat().version().first << requestedFormat().version().second << requestedFormat().profile();
    }

    //qDebug() << isActive();


    m_scene->render();

    m_context->swapBuffers(this);

    //requestUpdate();

}

void Widget::resizeGL()
{
    m_context->makeCurrent(this);
    //QSize sz = size();
    m_scene->resize(width(), height()/*, x(), y()*/);
}

void Widget::forceKeyRelease()
{
    if (keyPressed.key_Ctrl) {
        keyPressed.key_Ctrl = false;
    }
}

void Widget::addSectorTriggered()
{
//    emit openSectorAddWidget( mousePressPos );
}

void Widget::initTraceMenu()
{
}

void Widget::focusInEvent(QFocusEvent *ev)
{
}

void Widget::focusOutEvent(QFocusEvent *ev)
{
}

void Widget::resizeMainGL(const QSize size)
{
//    m_context->makeCurrent(this);
//    //QSize sz = size();
//    m_scene->resize(size.width(), size.height());
}

void Widget::forceUpdate()
{
    requestUpdate();

    QTimer::singleShot(40, this, &Widget::forceUpdate);
}


bool Widget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        //qDebug() << "QEvent::UpdateRequest";
        return QWindow::event(event);;
    default:
        return QWindow::event(event);
    }
}

void Widget::exposeEvent(QExposeEvent *)
{
    if (isExposed()) {
        renderNow();
       //qDebug() << "exposeEvent";
    }
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    const float speed = 5.f;
    switch (e->key()) {
    case Qt::Key_Escape:
        m_scene->resetScaling();
        break;
    case Qt::Key_F12:
        QApplication::instance()->quit();
        break;
    case Qt::Key_Up :
        keyPressed.Up = true;
        m_scene->setForwardSpeed( speed );
        break;
    case Qt::Key_Down :        
        keyPressed.Down = true;
        m_scene->setForwardSpeed( -speed );
        break;
    case Qt::Key_Right :
        keyPressed.Right = true;
        m_scene->setSideSpeed( speed );
        break;
    case Qt::Key_Left :
        keyPressed.Left = true;
        m_scene->setSideSpeed( -speed );
        break;
    /*case Qt::Key_PageUp:
        m_scene->setVerticalSpeed( speed );
        break;
    case Qt::Key_PageDown:
        m_scene->setVerticalSpeed( -speed );
        break;*/
    case Qt::Key_Control :
        keyPressed.key_Ctrl = true;
        timerForForceKeyRelease->start(7000);
        break;
    case Qt::Key_8 :
        keyPressed.key_8 = true;
        m_scene->test3DCamera(0,1,0);
        break;
    case Qt::Key_5 :
        keyPressed.key_5 = true;
        m_scene->test3DCamera(0,-1,0);
        break;
    case Qt::Key_4 :
        keyPressed.key_4 = true;
        m_scene->test3DCamera(0,0,1);
        break;
    case Qt::Key_6 :
        keyPressed.key_6 = true;
        m_scene->test3DCamera(0,0,-1);
        break;
    case Qt::Key_Plus :
        keyPressed.key_Plus = true;
        m_scene->setTerrainHorizontalScale( 1.05 );
        break;
    case Qt::Key_Minus :
        keyPressed.key_Minus = true;
        m_scene->setTerrainHorizontalScale( 0.95 );
        break;
    case Qt::Key_Home:
        //m_scene->roll( -speed / 2 );

        break;
    case Qt::Key_End:

        //m_scene->roll( speed / 2 );
        break;
    case Qt::Key_F :
        keyPressed.key_F = true;
        break;
    case Qt::Key_1:
        if (e->modifiers() == Qt::ControlModifier)
            keyPressed.key_1 = true;
        break;
    //default:
    //    QWindow::keyPressEvent( e );
    }
    QWindow::keyPressEvent( e );
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Up :
        keyPressed.Up = false;
        //m_scene->setForwardSpeed( 0.0f );
        break;
    case Qt::Key_Down :
        keyPressed.Down = false;
        //m_scene->setForwardSpeed( 0.0f );
        break;
    case Qt::Key_Right :
        keyPressed.Right = false;
        //m_scene->setSideSpeed( 0.0f );
        break;
    case Qt::Key_Left :
        keyPressed.Left = false;
        //m_scene->setSideSpeed( 0.0f );
        break;
    /*case Qt::Key_PageUp:
    case Qt::Key_PageDown:
        m_scene->setVerticalSpeed( 0.0f );
        break;*/
    case Qt::Key_Control :
        timerForForceKeyRelease->stop();
        keyPressed.key_Ctrl = false;
        break;
    case Qt::Key_8 :
        keyPressed.key_8 = false;
        break;
    case Qt::Key_5 :
        keyPressed.key_5 = false;
        break;
    case Qt::Key_4 :
        keyPressed.key_4 = false;
        break;
    case Qt::Key_6 :
        keyPressed.key_6 = false;
        break;
    case Qt::Key_Plus :
        keyPressed.key_Plus = false;
        break;
    case Qt::Key_Minus :
        keyPressed.key_Minus = false;
        break;
    case Qt::Key_F :
        keyPressed.key_F = false;
        break;
    case Qt::Key_1:
        if (e->modifiers() == Qt::ControlModifier)
            keyPressed.key_1 = true;
        break;
    //default:
    //    QWindow::keyReleaseEvent( e );
    }
    QWindow::keyReleaseEvent( e );
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mousePressPos = event->screenPos();
    mousePressOldPos = event->screenPos();

    isMouseMove = false;
    QWindow::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent* event)
{
    //m_scene->mouseTracking(event->screenPos());

    //for win32/64
    /*if (!isActive()) {
        requestActivate();
    }*/

    //qDebug() << event->screenPos();

    if (!isContextMenuVisible) {
        if (event->buttons() & Qt::RightButton) { //find KTA
            QPointF offset = event->screenPos() - mousePressPos;
            qreal sensitivity = 0.5;
            offset *= sensitivity;

            m_scene->updateRect(mousePressOldPos, event->screenPos());
            //qDebug() << event->screenPos();

        }
        else if (event->buttons() & Qt::LeftButton) { //drug
            QPointF offset = event->globalPos() - mousePressPos;
            m_scene->setForwardSpeed(offset.ry());
            m_scene->setSideSpeed(-offset.rx());
            m_scene->mouseMoveGride();
        }
        QPointF dPoint(mousePressPos - event->screenPos());
        if (!dPoint.isNull()) {
            isMouseMove = true;
        }
        else
            isMouseMove = false;
        //    qDebug() << isMouseMove;
        mousePressPos = event->screenPos();
    }


    QWindow::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{    
    if (!isMouseMove) {
        if (keyPressed.key_Ctrl) {
            if (event->button() == Qt::LeftButton) {
                if (!isDoubleClick) {
                    qDebug() << "CTRL + one click";
                    m_scene->targetingAdd(event->screenPos());                    
                }
                else
                    isDoubleClick = false;
            }
            else if (event->button() == Qt::RightButton) {
                m_scene->targetingExclude(event->screenPos());
                qDebug() << "CTRL + one right click";
            }
        }
        else if (event->button() == Qt::RightButton) {
//            QVector3D tempVector = m_scene->screenToScene(event->screenPos());
//            qint32 idTrace = m_scene->traceGLData()->getIdByCoordinates(QPointF(tempVector.x(), tempVector.y()));
//            if (idTrace != -1) {
//                clickedTraceNumber = idTrace;
//                auto actionList = traceMenu->actions();
//                if (!actionList.isEmpty()) {
//                    actionList.at(0)->setText(QString("Трасса №%1").arg(clickedTraceNumber));
//                }
//                traceMenu->move(event->globalPos());
//                traceMenu->show();
//                isContextMenuVisible = true;
//                preHiddingContextMenu = false;
//                //qDebug() << "Click on LogBook of trace" << idTrace;
//            }

        }
    }
    else if (isMouseMove) {
        if (event->button() == Qt::RightButton) {
            m_scene->KTASampling(mousePressOldPos, event->screenPos());
        }
        isMouseMove = false;
    }

    if (preHiddingContextMenu) {
        isContextMenuVisible = false;
        preHiddingContextMenu = false;
    }

    mousePressPos = event->screenPos();
    QWindow::mouseReleaseEvent(event);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (keyPressed.key_Ctrl) {
            qDebug() << "CTRL + two click";
            m_scene->targetingAddQuick(event->screenPos());
            isDoubleClick = true;            
        }
        else {
            //m_scene->setTerrainHorizontalScale(2);
            m_scene->userScaling(2, true, event->screenPos());
        }
    }
    else if (event->buttons() & Qt::RightButton) {

        m_scene->userScaling(0.5, true, event->screenPos());
        //m_scene->setTerrainHorizontalScale(0.5);

    }
    QWindow::mouseDoubleClickEvent(event);
}


void Widget::wheelEvent(QWheelEvent *event)
{

    float delta=event->delta();
    if (delta>0)
    {
        delta=1.05;
    }
    else
    {
        delta =0.95;
    }
    m_scene->userScaling(delta);
//    m_scene->userScaling(event->delta() > 0 ? 1.05 : 0.95);
    wheelPress = true;

    QWindow::wheelEvent(event);
}
