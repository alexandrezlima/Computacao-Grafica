#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>
#include <QVector4D>
#include <vector>
#include <QFile>


class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT

protected:
   void initializeGL();
   void resizeGL(int w, int h);
   void paintGL();

private:
    QTimer timer;    
    bool blinkFlag{false};
    std::array<float, 4> m_clearColor{0.906f, 0.910f, 0.918f, 1.0f};

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    bool isDay{true};

    //Declaração dos VBOs e VAOs
    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};

    //Declaração dos VBOs e VAOs
    GLuint vboVertices2{0};
    GLuint vboColors2{0};
    GLuint eboIndices2{0};
    GLuint vao2{0};

    //House base.
    GLuint vaoHB{0}, vboHB{0}, vboColorHB{0}, eboHB{0};

    //House roof.
    GLuint vaoHF{0}, vboHF{0}, vboColorHF{0}, eboHF{0};

    //House window.
    GLuint vaoHW{0}, vboHW{0}, vboColorHW{0}, eboHW{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;


    //Declaração do shader program.
    GLuint shaderProgram{0};

    //Cabeçalho das funções.
    void createVBOs(GLuint &theVAO, GLuint &theVBO, GLuint &theColors, GLuint &theEBO);
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void keyPressEvent(QKeyEvent *event);

    //VBOs para desenhos
    GLuint vaoSunMoon{0};
    GLuint vboVerticesSunMoon{0};
    const unsigned int steps{800};

    //Funções para desenhos
    void setupModels();
    void drawHouseBase();
    void drawHouseRoof();
    void drawSunMoon();     //A cor é alterada dependendo do horário do dia (usando a variávei isDay).
    void drawHouseWindow(); //A janela tem um gradiente de cor diferente dependendo do horário do dia.

public slots:
    void toggleDarkMode(bool);
};


#endif // OPENGLWIDGET_H
