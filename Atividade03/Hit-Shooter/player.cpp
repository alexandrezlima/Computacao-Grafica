#include "player.h"

#include <stdlib.h>
#include <QApplication>
#include <QVector4D>

using namespace std;

void Player::create(GLuint program)
{
    initializeOpenGLFunctions();
    makeCurrent();

    destroy();
    wasInitialized = true;

    m_program = program;

    //Resgata e guarda os ponteiros para as variáveis uniformes do shader.
    m_rotationLoc = glGetUniformLocation(m_program, "rotation");
    m_scaleLoc = glGetUniformLocation(m_program, "scale");
    m_translationLoc = glGetUniformLocation(m_program, "translation");

    m_rotation = 0.0f;
    m_velocity = 0.0f;
    m_scale = 0.125f;
    m_PosYOffset = 0;
    m_PosY = 0;

    array vertices{
                    // Ship body
                      array{0.0f, -00.9f, 0.0f, 1.0f}
                    , array{-0.9f, -0.9f, 0.0f, 1.0f}
                    , array{-0.9f, 0.0f, 0.0f, 1.0f}
                    , array{-0.0f, 0.0f, 0.0f, 1.0f}
                   };

    array colors{
                         array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}
                       , array{0.5f,0.5f,0.5f,1.0f}
                 };

    // Normalização para o intervalo [-1,1]
    for (auto &position : vertices) {
        position[0] /= 1.0f;
        position[1] /= 1.0f;
    }

    array const indices{0, 1, 2
                        ,2, 3, 0
                       };
    // clang-format on


    // Gera VAO
    glGenVertexArrays(1, &m_VAO);

    // Bind vertex attributes to current VAO
    glBindVertexArray(m_VAO);

    // Gera VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Gera VBO de cores
    glGenBuffers(1, &m_VBOColors);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    // Gera EBO
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}

void Player::destroy()
{
    if (wasInitialized)
    {
        makeCurrent();
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteBuffers(1, &m_VBOColors);
        glDeleteVertexArrays(1, &m_VAO);
        wasInitialized = false;
    }

}


Player::Player(QWidget *parent) : QOpenGLWidget(parent)
{
}

//Destrutor da classe OpenGLWidget.
Player::~Player()
{
}

void Player::paint(GameData const &gameData)
{
    if (gameData.m_state != State::Playing) return;

    glUseProgram(m_program);

    glBindVertexArray(m_VAO);

    //Binding para as variáveis uniformes.
    glUniform4f(m_translationLoc, 0, 0, 0, 1);
    glUniform1f(m_scaleLoc, 10.0f);
    glUniform1f(m_rotationLoc, 0.0f);


    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);

    glUseProgram(0);


}

void Player::update(GameData const &gameData, float deltaTime)
{

}
