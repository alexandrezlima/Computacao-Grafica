#include "player.h"

#include <stdlib.h>
#include <QApplication>
#include <QVector4D>
#include <iostream>

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
    m_velocity = 2.0f;
    m_scale = 0.100f;
    m_position[0] = 0.0f;
    m_position[1] = -0.8f;
    totalHits = 0;

    array vertices{
                    // Ship body
                      array{-1.0f, -1.0f, 0.0f, 1.0f}
                    , array{0.0f, -0.5f, 0.0f, 1.0f}
                    , array{1.0f, -1.0f, 0.0f, 1.0f}
                    , array{0.0f, 1.0f, 0.0f, 1.0f}
                   };

    array colors{
                         array{0.5f,0.5f,0.9f,1.0f}
                       , array{0.5f,0.5f,0.9f,1.0f}
                       , array{0.5f,0.5f,0.9f,1.0f}
                       , array{0.5f,0.5f,0.9f,1.0f}
                 };

    // Normalização para o intervalo [-1,1]
    for (auto &position : vertices) {
        position[0] /= 1.0f;
        position[1] /= 1.0f;
    }

    array const indices{0, 1, 3
                        ,1, 2, 3
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


    m_bullets.create(program);
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
        totalHits = 0;

        m_bullets.destroy();

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

    //Caso o player tenha atirado, a bala será renderizada.
    if (isShooting)
        m_bullets.paint(gameData);

    glUseProgram(m_program);

    glBindVertexArray(m_VAO);

    //Binding para as variáveis uniformes.
    glUniform4f(m_translationLoc,  m_position[0], m_position[1], 0, 1);
    glUniform1f(m_scaleLoc, m_scale);
    glUniform1f(m_rotationLoc, m_rotation);


    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);

    glUseProgram(0);

}

void Player::updateGame(GameData const &gameData, float deltaTime)
{
    int keyRight{1};
    int keyUp{1};

    if (gameData.m_input[static_cast<size_t>(Input::Right)])
    {
        m_position[0] += m_velocity * deltaTime;
        keyRight = 1;
    }

    if (gameData.m_input[static_cast<size_t>(Input::Left)])
    {
        m_position[0] -= m_velocity * deltaTime;
        keyRight = -1;
    }

    if (gameData.m_input[static_cast<size_t>(Input::Up)])
    {
        m_position[1] += m_velocity * deltaTime;
        keyUp = 1;
    }

    if (gameData.m_input[static_cast<size_t>(Input::Down)])
    {
        m_position[1] -= m_velocity * deltaTime;
        keyUp = -1;
    }

    if (gameData.m_input[static_cast<size_t>(Input::Fire)])
        shoot();

    if (abs(m_position[0]) > 0.9f )
        m_position[0] = 0.9f * keyRight;

    if (abs(m_position[1]) > 0.9f)
        m_position[1] = 0.9f * keyUp;
    else if(abs(m_position[1]) < 0.1f)
        m_position[1] = -0.1f * keyUp;


    isMovementPressed = gameData.m_input[static_cast<size_t>(Input::Right)] ||
            gameData.m_input[static_cast<size_t>(Input::Left)] ||
            gameData.m_input[static_cast<size_t>(Input::Up)] ||
            gameData.m_input[static_cast<size_t>(Input::Down)];

    if(isShooting)
    {
        m_bullets.updateGame(gameData, deltaTime);

        if(getBulletPosition()[1] > 1.0f)
            isShooting = false;
    }

    update();
}

void Player::shoot()
{
    if (!isShooting)
    {
        //can shoot.
        isShooting = true;

        m_bullets.shoot(getPosition(), 0.05, !isMovementPressed);
        //comando para paint de bullet
    }
}

void Player::stopShooting()
{
    isShooting = false;
}

bool Player::getIsShooting()
{
    return isShooting;
}

std::vector<float> Player::getPosition()
{
    return m_position;
}

int Player::getTotalHits()
{
    return totalHits;
}

void Player::addHit()
{
    totalHits++;
}

std::vector<float> Player::getBulletPosition()
{
    return m_bullets.getBulletPosition();
}
