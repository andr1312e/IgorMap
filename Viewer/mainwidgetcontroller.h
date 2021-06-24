#ifndef MAINWIDGETCONTROLLER_H
#define MAINWIDGETCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void setTitle(QString title);

signals:
    void resizeSignal();

private:
    const QRect headerRect, mainBodyRect;
    QPixmap *hideWindowIcon;
    QPixmap *showWindowIcon;

private slots:
    void resize();

protected:
    QString wndTitle;
    bool isOpened = false;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

class MainWidgetController : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidgetController(QWidget *parent = nullptr);

signals:

private:
    MainWidget *mainWidget;

};

#endif // MAINWIDGETCONTROLLER_H
