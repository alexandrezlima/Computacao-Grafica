#include "openglwidget.h"
#include <stdlib.h>
#include <QApplication>
#include <QKeyEvent>

using namespace std;

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

   createShaders();

   m_randomEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());

   restart();
}

void OpenGLWidget::restart()
{
    m_gameData.m_state = State::Playing; //Sinaliza que o jogo está rodando.

    m_player.create(m_objectsProgram); //Cria o player.
}

void OpenGLWidget::resizeGL(int w, int h)
{
}

//Responsável pela atualização da posição dos objetos.
void OpenGLWidget::update()
{
    //auto const deltaTime{static_cast<float>(getDeltaTime())}; //delta time, importante para animações.
    auto const deltaTime = 1;  //Ajustar o delta time.

    m_player.update(m_gameData, deltaTime);
}

void OpenGLWidget::paintGL()
{
    update();
    updateGameStatus();

    glClear(GL_COLOR_BUFFER_BIT);

    //Sinaliza a possibilidade do uso dos shaders.
    //glUseProgram(m_objectsProgram);

    m_player.paint(m_gameData);


    //glBindVertexArray(m_VAO);
    //drawHouseBase();
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //drawHouseRoof();
    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    //drawHouseWindow();
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //glDrawArrays(GL_TRIANGLE_FAN, 0, steps);

    //Boa prática de programação desativá-los logo após o seu uso.
    glBindVertexArray(0);
    glUseProgram(0);
}

void OpenGLWidget::updateGameStatus()
{
    switch (m_gameData.m_state)
    {
        case (State::GameOver):
            //Altera texto para lose.
            //Mostra o texto na tela
            break;
        case (State::Win):
            //Altera o texto para win.
            //Mostra o texto na tela.
            break;
        case (State::Playing):
            //remove o texto da tela.
            break;
    }
}

//Marca quais keys estão em uso.
void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case (Qt::Key_Escape):
            QApplication::quit();
            break;
        case (Qt::Key_W):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Up));
            break;
        case(Qt::Key_S):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Down));
            break;
        case(Qt::Key_Space):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Fire));
            break;
        case (Qt::Key_E):
            m_gameData.m_input.set(static_cast<std::size_t>(Input::Shield));
            break;
    }
}

//Desmarca as keys soltas.
void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case (Qt::Key_Escape):
            QApplication::quit();
            break;
        case (Qt::Key_W):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Up));
            break;
        case(Qt::Key_S):
            m_gameData.m_input.reset(static_cast<std::size_t>(Input::Down));
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
}

//Cria VBOs
void OpenGLWidget::createVBOs(GLuint &theVAO, GLuint &theVBO, GLuint &theColors, GLuint &theEBO)
{
    makeCurrent();

    //Libera os VBOs atuais, caso já tenham sido criados. Importante para não consumir toda memória da GPU.
    destroyVBOs();

    //Cria VAO
    glGenVertexArrays(1, &theVAO);
    //Associa atributos vertex ao VAO atual
    glBindVertexArray(theVAO);

    //Gera VBO de posições (vértices)
    glGenBuffers(1, &theVBO);
    glBindBuffer(GL_ARRAY_BUFFER, theVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Gera VBO de cores
    glGenBuffers(1, &theColors);
    glBindBuffer(GL_ARRAY_BUFFER, theColors);
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(QVector4D), colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &theEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

//Destrói VBOs
void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();
}


//Desenha a base da casa.
void OpenGLWidget::drawHouseBase()
{

    array vertice{ array{-02.5f, +12.5f, 0.0f, 1.0f}
                    , array{-15.5f, +02.5f, 0.0f, 1.0f}
                    , array{-15.5f, -12.5f, 0.0f, 1.0f}
                    , array{-09.5f, -07.5f, 0.0f, 1.0f}
                    , array{-03.5f, -12.5f, 0.0f, 1.0f}
                    , array{+03.5f, -12.5f, 0.0f, 1.0f}
                    , array{+09.5f, -07.5f, 0.0f, 1.0f}
                    , array{+15.5f, -12.5f, 0.0f, 1.0f}
                    , array{+15.5f, +02.5f, 0.0f, 1.0f}
                    , array{+02.5f, +12.5f, 0.0f, 1.0f}

                      // Cannon (left)
                    , array{-12.5f, +10.5f, 0.0f, 1.0f}
                    , array{-12.5f, +04.0f, 0.0f, 1.0f}
                    , array{-09.5f, +04.0f, 0.0f, 1.0f}
                    , array{-09.5f, +10.5f, 0.0f, 1.0f}

                      // Cannon (right)
                    , array{+09.5f, +10.5f, 0.0f, 1.0f}
                    , array{+09.5f, +04.0f, 0.0f, 1.0f}
                    , array{+12.5f, +04.0f, 0.0f, 1.0f}
                    , array{+12.5f, +10.5f, 0.0f, 1.0f}

                      // Thruster trail (left)
                    , array{-12.0f, -07.5f, 0.0f, 1.0f}
                    , array{-09.5f, -18.0f, 0.0f, 1.0f}
                    , array{-07.0f, -07.5f, 0.0f, 1.0f}

                      // Thruster trail (right)
                    , array{+07.0f, -07.5f, 0.0f, 1.0f}
                    , array{+09.5f, -18.0f, 0.0f, 1.0f}
                    , array{+12.0f, -07.5f, 0.0f, 1.0f}
                   };

    array colored{
                         array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}

                 };

    // Normalização para o intervalo [-1,1]
    for (auto &position : vertice) {
        position[0] /= 30.5f;
        position[1] /= 30.5f;
    }

    array const indice{0, 1, 3,
                       1, 2, 3,
                       0, 3, 4,
                       0, 4, 5,
                       9, 0, 5,
                       9, 5, 6,
                       9, 6, 8,
                       8, 6, 7,
                       // Cannons
                       10, 11, 12,
                       10, 12, 13,
                       14, 15, 16,
                       14, 16, 17,
                       // Thruster trails
                       18, 19, 20,
                       21, 22, 23};

    //createVBOs(m_VAO, vboHB, vboColorHB, eboHB);

    makeCurrent();

    //Libera os VBOs atuais, caso já tenham sido criados. Importante para não consumir toda memória da GPU.
    destroyVBOs();

    //Cria VAO
    glGenVertexArrays(1, &m_VAO);
    //Associa atributos vertex ao VAO atual
    glBindVertexArray(m_VAO);

    //Gera VBO de posições (vértices)
    glGenBuffers(1, &vboHB);
    glBindBuffer(GL_ARRAY_BUFFER, vboHB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Gera VBO de cores
    glGenBuffers(1, &vboColorHB);
    glBindBuffer(GL_ARRAY_BUFFER, vboColorHB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colored), colored.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &eboHB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice.data(), GL_STATIC_DRAW);
}

//Desenha o telhado da casa.
void OpenGLWidget::drawHouseRoof()
{
    //reconfigura o array de vértices, colors e índices.
    vertices.resize(3);
    colors.resize(3);
    indices.resize(3); //1*3 -> um triângulo.

    //Define a posição dos vértices, inserindo-as no array.
    vertices[0] = QVector4D(-0.9, 0.01, 0, 1);
    vertices[1] = QVector4D(0, 0.01, 0, 1);
    vertices[2] = QVector4D(-0.425, 0.5, 0, 1);


    //Cria as cores para os vértices.
    colors[0] = QVector4D(1, 0.5, 0.5, 1);
    colors[1] = QVector4D(1, 0.5, 0.5, 1);
    colors[2] = QVector4D(1, 0.5, 0.5, 1);

    //Gera a topologia do retângulo.
    indices[0] = 0; indices[1] = 1; indices[2] = 2;

    createVBOs(m_VAO, vboHF, vboColorHF, eboHF);

}

void OpenGLWidget::drawHouseWindow()
{
    //reconfigura o array de vértices, colors e índices.
    vertices.resize(4);
    colors.resize(4);
    indices.resize(6); //2*3 -> dois triângulos.

    //Define a posição dos vértices, inserindo-as no array.
    vertices[0] = QVector4D(-0.1, -0.5, 0, 1);
    vertices[1] = QVector4D(-0.3, -0.5, 0, 1);
    vertices[2] = QVector4D(-0.3, -0.2, 0, 1);
    vertices[3] = QVector4D(-0.1, -0.2, 0, 1);


    if (isDay) {
        //Cria as cores para os vértices.
        colors[0] = QVector4D(1, 1, 1, 1);
        colors[1] = QVector4D(1, 1, 1, 1);
        colors[2] = QVector4D(1, 1, 1, 1);
        colors[3] = QVector4D(1, 1, 1, 1);
    } else {
        //Cria as cores para os vértices.
        colors[0] = QVector4D(1, 1, 0, 1);
        colors[1] = QVector4D(1, 1, 0, 1);
        colors[2] = QVector4D(1, 1, 0, 1);
        colors[3] = QVector4D(1, 1, 0, 1);
    }


    //Gera a topologia do retângulo.
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    createVBOs(m_VAO, vboHW, vboColorHW, eboHW);

}
