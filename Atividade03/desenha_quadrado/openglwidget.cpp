#include "openglwidget.h"
#include <stdlib.h>
#include <QApplication>
#include <QKeyEvent>

//Construtor da classe OpenGLWidget.
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

//Destrutor da classe OpenGLWidget.
OpenGLWidget::~OpenGLWidget()
{

    destroyVBOs();
    destroyShaders();

}

//Função chamada uma vez, na inicialização do programa. Correspondente ao onCreate().
void OpenGLWidget::initializeGL()
{
   initializeOpenGLFunctions();

   //Inicializa a cor de fundo do widget do openGL. A estrutura segue o formato float (red, green, blue, alpha).
   glClearColor(0,0.8,0.9,1);

   createShaders();
   //createVBOs();
   setupModels();
}

void OpenGLWidget::resizeGL(int w, int h)
{
}

void OpenGLWidget::paintGL()
{

    //glClear(GL_COLOR_BUFFER_BIT);
    //setupModels();

    //Sinaliza a possibilidade do uso dos shaders.
    glUseProgram(m_program);
    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void OpenGLWidget::setupModels()
{

    glDeleteBuffers(1, &m_VBOPositions);
    glDeleteBuffers(1, &m_VBOColors);
    glDeleteVertexArrays(1, &m_VAO);

    std::vector<QVector4D>  i_vertices;
    std::vector<QVector4D>  i_colors;
    std::vector<GLuint>     i_indices;

    i_vertices.resize(4);
    i_colors.resize(4);
    i_indices.resize(6);

    i_vertices[0] = QVector4D(-0.5, -0.5 , 0, 1);
    i_vertices[1] = QVector4D( 0.5, -0.5 , 0, 1);
    i_vertices[2] = QVector4D( 0.5, 0.5 , 0, 1);
    i_vertices[3] = QVector4D(-0.5, 0.5 , 0, 1);

    // Generate VBO of positions
    glGenBuffers(1, &m_VBOPositions);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(i_vertices), i_vertices.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Cria as cores para os vértices.
    i_colors[0] = QVector4D(1, 0, 0, 1); // Red
    i_colors[1] = QVector4D(0, 1, 0, 1); // Green
    i_colors[2] = QVector4D(0, 0, 1, 1); // Blue
    i_colors[3] = QVector4D(1, 1, 0, 1); // Yellow

    // Generate VBO of colors
    glGenBuffers(1, &m_VBOColors);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(i_colors), i_colors.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Get location of attributes in the program
    auto const positionAttribute{glGetAttribLocation(m_program, "vPosition")};
    auto const colorAttribute{glGetAttribLocation(m_program, "vColors")};

    // Create VAO
    glGenVertexArrays(1, &m_VAO);

    // Bind vertex attributes to current VAO
    glBindVertexArray(m_VAO);

    glEnableVertexAttribArray(positionAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositions);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                                  nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(colorAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOColors);
    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0,
                                  nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

//Criação dos shaders, usando os resources vertex shaders e fragment shaders.
void OpenGLWidget::createShaders()
{
    makeCurrent();
    destroyShaders();

    //Lê vertex shader e fragment shaders.
    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");

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
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);



    GLint isLinked{0};
    glGetProgramiv(m_program,GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint maxLength{0};
        glGetProgramiv(m_program,GL_INFO_LOG_LENGTH,&maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_program,maxLength,&maxLength, &infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteProgram(m_program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }


    glDetachShader(m_program,vertexShader);
    glDetachShader(m_program,fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//Destrói os shaders.
void OpenGLWidget::destroyShaders()
{
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

//Cria VBOs
void OpenGLWidget::createVBOs()
{
    makeCurrent();

    //Libera os VBOs atuais, caso já tenham sido criados. Importante para não consumir toda memória da GPU.
    destroyVBOs();

    //reconfigura o array de vértices, colors e índices.
    vertices.resize(4);
    colors.resize(4);
    indices.resize(6); //2*3 -> dois triângulos.

    //Define a posição dos vértices, inserindo-as no array.
    vertices[0] = QVector4D(-0.5, -0.5 , 0, 1);
    vertices[1] = QVector4D( 0.5, -0.5 , 0, 1);
    vertices[2] = QVector4D( 0.5, 0.5 , 0, 1);
    vertices[3] = QVector4D(-0.5, 0.5 , 0, 1);


    //Cria as cores para os vértices.
    colors[0] = QVector4D(1, 0, 0, 1); // Red
    colors[1] = QVector4D(0, 1, 0, 1); // Green
    colors[2] = QVector4D(0, 0, 1, 1); // Blue
    colors[3] = QVector4D(1, 1, 0, 1); // Yellow

    //Gera a topologia do retângulo.
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    //Cria VAO
    glGenVertexArrays(1, &vao);
    //Associa atributos vertex ao VAO atual
    glBindVertexArray(vao);

    //Gera VBO de posições (vértices)
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Gera VBO de cores
    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER, vboColors);
    glBufferData (GL_ARRAY_BUFFER, colors.size()*sizeof(QVector4D), colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, eboIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

//Destrói VBOs
void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();

    //Deleta buffers.
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboColors);
    glDeleteBuffers(1, &eboIndices);

    //Deleta vértices.
    glDeleteVertexArrays(1, &vao);

    //Reseta variáveis.
    vboVertices=0;
    eboIndices=0;
    vboColors=0;
    vao=0;
}

//Altera alguns elementos da cena, como céu sol/lua e a janela da casa.
void OpenGLWidget::toggleDarkMode(bool changeToDarkMode)
{
    makeCurrent();
    isDay = !changeToDarkMode;


    if(changeToDarkMode)
    {
        //Céu escuro. Noite.
        glClearColor(0,0.2,0.6,1);
    }
    else
    {
        //Céu claro. Dia.
        glClearColor(0,0.8,0.9,1);
    }
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            QApplication::quit();
            break;
    }
}

void OpenGLWidget::drawSunMoon()
{
    std::vector<QVector4D> vertices2;
    std::vector<QVector4D> colors2;
    std::vector<GLuint> indices2;

    //Declaração dos VBOs e VAOs
    GLuint vboVertices2{0};
    GLuint vboColors2{0};
    GLuint eboIndices2{0};
    GLuint vao2{0};

    makeCurrent();
    glUseProgram(shaderProgram);

    glBindVertexArray(vaoSunMoon);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);


    makeCurrent();

    //Libera os VBOs atuais, caso já tenham sido criados. Importante para não consumir toda memória da GPU.
    destroyVBOs();

    //reconfigura o array de vértices, colors e índices.
    vertices2.resize(4);
    colors2.resize(4);
    indices2.resize(6); //2*3 -> dois triângulos.

    //Define a posição dos vértices, inserindo-as no array.
    vertices2[0] = QVector4D(0, 0 , 0, 1);
    vertices2[1] = QVector4D( 0.6, -0.6 , 0, 1);
    vertices2[2] = QVector4D( 0.6, 0.6 , 0, 1);
    vertices2[3] = QVector4D(-0.6, 0.6 , 0, 1);


    //Cria as cores para os vértices.
    colors2[0] = QVector4D(0, 0, 0, 1); // Red
    colors2[1] = QVector4D(0, 0, 0, 1); // Green
    colors2[2] = QVector4D(0, 0, 0, 1); // Blue
    colors2[3] = QVector4D(0, 0, 0, 1); // Yellow

    //Gera a topologia do retângulo.
    indices2[0] = 0; indices2[1] = 1; indices2[2] = 2;
    indices2[3] = 2; indices2[4] = 3; indices2[5] = 0;

    //Cria VAO
    glGenVertexArrays(1, &vao2);
    //Associa atributos vertex ao VAO atual
    glBindVertexArray(vao2);

    //Gera VBO de posições (vértices)
    glGenBuffers(1, &vboVertices2);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices2);
    glBufferData(GL_ARRAY_BUFFER, vertices2.size()*sizeof(QVector4D), vertices2.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Gera VBO de cores
    glGenBuffers (1, &vboColors2);
    glBindBuffer (GL_ARRAY_BUFFER, vboColors2);
    glBufferData (GL_ARRAY_BUFFER, colors2.size()*sizeof(QVector4D), colors2.data(), GL_STATIC_DRAW);

    glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndices2);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, eboIndices2);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices2.size()*sizeof(GLuint), indices2.data(), GL_STATIC_DRAW);
}
