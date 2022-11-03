#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>
#include <QVector4D>
#include <QElapsedTimer>
#include <vector>
#include <QFile>
#include <random>


#include "gamedata.h"
#include "player.h"
#include "enemy.h"
#include "bullets.h"
#include "power.h"
#include "starlayers.h"

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT

public:
    //Cabeçalho das funções.
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    float getDeltaTime();
    void createShaders();
    void destroy();
    void restart(); //Para reiniciar o jogo.

protected:
   void initializeGL(); //Chamado uma vez antes das outras funções abaixo.
   void resizeGL(int w, int h);
   void paintGL();
   //bool event(QEvent *e) override;
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);
   void updateGame();

   //onPaintUI: executado uma vez logo após a inicialização.
   //onPaint: executado a todo frame.

private:
    QTimer timer;
    QElapsedTimer elapsedTimer;

    GLuint m_objectsProgram{0};  //Identificador do par de shaders objects frag e vert.

    GameData m_gameData;
    Player m_player;
    Enemy m_enemy;

    bool showingEndGame{false};

    std::default_random_engine m_randomEngine;
    float deltaTime{0};

signals:
    void updateEndGameLabel(QString);
    void updateEndGameVisibility(bool);

public slots:
    void animate();
};


#endif // OPENGLWIDGET_H
