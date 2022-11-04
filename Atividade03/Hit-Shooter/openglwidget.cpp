#include "openglwidget.h"
#include <stdlib.h>
#include <QApplication>
#include <QKeyEvent>
#include <qDebug>
#include <stdio.h>
#include <iostream>

//Construtor da classe OpenGLWidget.
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

//Destrutor da classe OpenGLWidget.
OpenGLWidget::~OpenGLWidget()
{
    destroy();
}

//Função chamada uma vez, na inicialização do programa. Correspondente ao onCreate().
void OpenGLWidget::initializeGL()
{
   initializeOpenGLFunctions();

   //Inicializa a cor de fundo do widget do openGL. A estrutura segue o formato float (red, green, blue, alpha).
   glClearColor(0,0,0,1);



   connect(&timer, &QTimer::timeout, this, &OpenGLWidget::animate);
   timer.start(0);

   elapsedTimer.start();
   fpsElapsedTimer.start();
   hitDamageElapsedTimer.start();

   createShaders();

   m_randomEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());

   restart();
}

//Reseta player e enemy.
void OpenGLWidget::restart()
{
    m_gameData.m_state = State::Playing; //Sinaliza que o jogo está rodando.

    emit updateEndGameVisibility(false);
    emit updateRestartButton(false);

    m_player.create(m_objectsProgram); //Cria o player.

    m_enemy.create(m_objectsProgram); //Cria o inimigo.

    showingEndGame = false;
}

void OpenGLWidget::resizeGL(int w, int h)
{
}



void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Sinaliza a possibilidade do uso dos shaders.
    glUseProgram(m_objectsProgram);

    m_player.paint(m_gameData);

    m_enemy.paint(m_gameData);


    glBindVertexArray(0);
    glUseProgram(0);
}

//Atualiza texto do jogo (se jogador perdeu ou ganhou, mostra mensagem; ou não mostra mensagem).
void OpenGLWidget::updateGame()
{
    switch (m_gameData.m_state)
    {
        case (State::GameOver):
            if (!showingEndGame)
            {
                showingEndGame = true;
                emit updateEndGameLabel(QString("YOU LOSE!"));
                emit updateEndGameVisibility(true);
                updateRestartButton(true);
            }
            //Mostra o texto na tela
            break;
        case (State::Win):
        if (!showingEndGame)
            {
                showingEndGame = true;
                emit updateEndGameLabel(QString("YOU WIN!"));
                emit updateEndGameVisibility(true);
                updateRestartButton(true);
            }
            //Altera o texto para win.
            //Mostra o texto na tela.
            break;
        case (State::Playing):
            if (showingEndGame)
            {
                showingEndGame = false;
                emit updateEndGameLabel(QString("PLAYING..."));
                emit updateEndGameVisibility(false);
                updateRestartButton(false);
            }
            break;
    }

    m_player.updateGame(m_gameData, getDeltaTime());

    m_enemy.updateGame(m_gameData, getDeltaTime());


    if (m_gameData.m_state == State::Playing) {
        checkCollisions();
        checkWinCondition();
    }
}

void OpenGLWidget::checkCollisions()
{
    if (hitDamageElapsedTimer.elapsed() > 100)
        updateBackground(0);

    //Verificação dos tiros do player.
    if (m_player.getIsShooting())
    {
        //Analisa inicialmente a altura do tiro e do inimigo. Verifica se estão próximos.
        float distY = abs(m_player.getBulletPosition()[1]-m_enemy.getPosition()[1]);
        if (distY < 0.125f)
        {
            //Em caso positivo, verifica a distância horizontal.
            float distX = abs(m_player.getBulletPosition()[0]-m_enemy.getPosition()[0]);
            if (distX < 0.125f)
            {
                //Caso a distância seja próxima o suficiente, adiciona o hit ao contador e sinaliza a interrupção do render do tiro.
                m_player.addHit();
                m_player.stopShooting();
                updateBackground(1);
            }
        }
    }

    if (m_enemy.getIsShooting())
    {
        //Analisa inicialmente a altura do tiro e do inimigo. Verifica se estão próximos.
        float distY = abs(m_enemy.getBulletPosition()[1]-m_player.getPosition()[1]);
        if (distY < 0.125f)
        {
            //Em caso positivo, verifica a distância horizontal.
            float distX = abs(m_enemy.getBulletPosition()[0]-m_player.getPosition()[0]);
            if (distX < 0.125f)
            {
                //Caso a distância seja próxima o suficiente, adiciona o hit ao contador e sinaliza a interrupção do render do tiro.
                m_enemy.addHit();
                m_enemy.stopShooting();
                updateBackground(2);
            }
        }
    }

}

void OpenGLWidget::checkWinCondition()
{
    if (m_player.getTotalHits() >= 10)
        m_gameData.m_state = State::Win;

    if (m_enemy.getTotalHits() >= 10)
        m_gameData.m_state = State::GameOver;
}

//Marca quais keys estão em uso.
void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case (Qt::Key_Escape):
            QApplication::quit();
            break;
        case (Qt::Key_D):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Right));
            break;
        case (Qt::Key_Right):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Right));
            break;
        case(Qt::Key_A):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Left));
            break;
        case (Qt::Key_Left):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Left));
            break;
        case (Qt::Key_S):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Down));
            break;
        case (Qt::Key_Down):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Down));
            break;
        case(Qt::Key_W):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Up));
            break;
        case (Qt::Key_Up):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Up));
            break;
        case(Qt::Key_Space):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Fire));
            break;
        case (Qt::Key_E):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Shield));
            break;
    }
}

//Desmarca as keys que deixaram de ser usadas.
void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case (Qt::Key_Escape):
            QApplication::quit();
            break;
        case (Qt::Key_D):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Right));
            break;
        case (Qt::Key_Right):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Right));
            break;
        case(Qt::Key_A):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Left));
            break;
        case (Qt::Key_Left):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Left));
            break;
        case (Qt::Key_S):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Down));
            break;
        case (Qt::Key_Down):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Down));
            break;
        case(Qt::Key_W):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Up));
            break;
        case (Qt::Key_Up):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Up));
            break;
        case(Qt::Key_Space):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Fire));
        break;
        case (Qt::Key_E):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Shield));
            break;
    }
}

//Criação dos shaders, usando os resources vertex shaders e fragment shaders.
void OpenGLWidget::createShaders()
{
    makeCurrent();
    destroy();

    //Lê vertex shader e fragment shaders.
    QFile vs(":/shaders/objects.vert");
    QFile fs(":/shaders/objects.frag");

    //Apresenta errors caso os arquivos não sejam encontrados.
    if(!vs.open(QFile::ReadOnly | QFile::Text)) return;
    if(!fs.open(QFile::ReadOnly | QFile::Text)) return;


    auto byteArrayVs{vs.readAll()};
    auto byteArrayFs{fs.readAll()};
    const char *c_strVs{byteArrayVs};
    const char *c_strFs{byteArrayFs};

    //Fecha os arquivos abertos anteriormente.
    vs.close();
    fs.close();

    //Cria vertex shader a partir dos dados lidos do resource vertex shader.
    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &c_strVs,0);
    glCompileShader(vertexShader);
    GLint isCompiled{0};

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength{0};
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteShader(vertexShader);
        return;
    }

    //Cria fragment shader a partir dos dados lidos do resource fragment shader.
    GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &c_strFs, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE)
    {
        GLint maxLength{0};
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    //Cria shader program, inteiro que identifica o programa de shader composto pelo par de vertex/fragment shader.
    m_objectsProgram = glCreateProgram();
    glAttachShader(m_objectsProgram, vertexShader);
    glAttachShader(m_objectsProgram, fragmentShader);
    glLinkProgram(m_objectsProgram);

    GLint isLinked{0};
    glGetProgramiv(m_objectsProgram,GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint maxLength{0};
        glGetProgramiv(m_objectsProgram,GL_INFO_LOG_LENGTH,&maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_objectsProgram,maxLength,&maxLength, &infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteProgram(m_objectsProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }


    glDetachShader(m_objectsProgram,vertexShader);
    glDetachShader(m_objectsProgram,fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//Destrói os shaders.
void OpenGLWidget::destroy()
{
    makeCurrent();
    glDeleteProgram(m_objectsProgram);

    m_player.destroy();
    m_enemy.destroy();
}

void OpenGLWidget::animate()
{
    //se getEnemyBulletPos in range Player.GetPosition (pegar bounds do player)


    if(++frameCount==100)
    {
        QString str = QString("<html><head/><body><p>%1 FPS<br/>%2 P. Hits<br/>%3 E. Hits</p></body></html>").arg(QString::number(frameCount/(fpsElapsedTimer.restart()/1000.0f), 'f', 0), QString::number(m_player.getTotalHits()), QString::number(m_enemy.getTotalHits()));
        emit updateFPSHit(str);
        frameCount=0;

    }

    deltaTime = elapsedTimer.restart()/1000.0f;

    updateGame();

    update();
}

float OpenGLWidget::getDeltaTime()
{
    return deltaTime;
}


void OpenGLWidget::restartButton()
{
    restart();
}

void OpenGLWidget::updateBackground(int type)
{
    makeCurrent();

    switch (type)
    {
        case 0:
            if(!normalBackground)
            {
                glClearColor(0,0,0,1);
                hitDamageElapsedTimer.restart();
                normalBackground = true;
            }
            break;
        case 1:
            glClearColor(0.1,0.1,0.7,1);
            hitDamageElapsedTimer.restart();
            normalBackground = false;
            break;
        case 2:
            glClearColor(0.7,0.1,0.1,1);
            hitDamageElapsedTimer.restart();
            normalBackground = false;
            break;
    }
}
