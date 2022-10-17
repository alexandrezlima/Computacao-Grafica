#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
private:
    QTimer timer;    
    bool blinkFlag{false};

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

signals:

public slots:
    void toggleDarkMode(bool);

protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();

};

#endif // OPENGLWIDGET_H
