#include "openglwidget.h"
#include <QTimer>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent),
    m_scene(new Scene(this)),
    timer(new QTimer)
{
    setFormat(QSurfaceFormat::defaultFormat());

    showFullScreen();

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16);
}

void OpenGLWidget::initializeGL()
{
    m_scene->setContext(QOpenGLContext::currentContext());
    m_scene->initialize();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    m_scene->resize(width(), height(), x(), y());
}

void OpenGLWidget::paintGL()
{
    m_scene->render();
}
