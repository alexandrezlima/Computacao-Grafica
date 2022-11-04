#include "enemy.h"

#include <stdlib.h>
#include <QApplication>
#include <QVector4D>
#include <iostream>

using namespace std;

void Enemy::create(GLuint program)
{
    initializeOpenGLFunctions();
    makeCurrent();

    m_randomEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    m_movementCDTimer.start();
    lastRandom = m_randomTime(m_randomEngine);
    lastRandomShoot = 500;

    destroy();
    wasInitialized = true;

    m_program = program;

    //Resgata e guarda os ponteiros para as variáveis uniformes do shader.
    m_rotationLoc = glGetUniformLocation(m_program, "rotation");
    m_scaleLoc = glGetUniformLocation(m_program, "scale");
    m_translationLoc = glGetUniformLocation(m_program, "translation");

    m_rotation = 0.0f;
    m_velocity = 2.0f;
    m_scale = 0.085f;
    m_position[0] = 0.0f;
    m_position[1] = 0.8f;
    totalHits = 0;


    array vertices{
                    // Ship body
                      array{0.0f, -1.0f, 0.0f, 1.0f}
                    , array{1.0f, 1.0f, 0.0f, 1.0f}
                    , array{0.0f, 0.5f, 0.0f, 1.0f}
                    , array{-1.0f, 1.0f, 0.0f, 1.0f}
                   };

    array colors{
                         array{0.9f,0.5f,0.5f,1.0f}
                       , array{0.9f,0.5f,0.5f,1.0f}
                       , array{0.9f,0.5f,0.5f,1.0f}
                       , array{0.9f,0.5f,0.5f,1.0f}
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

void Enemy::destroy()
{
    if (wasInitialized)
    {
        makeCurrent();
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteBuffers(1, &m_VBOColors);
        glDeleteVertexArrays(1, &m_VAO);
        wasInitialized = false;

        m_bullets.destroy();
        totalHits = 0;
    }

}


Enemy::Enemy(QWidget *parent) : QOpenGLWidget(parent)
{
}

//Destrutor da classe OpenGLWidget.
Enemy::~Enemy()
{
}

void Enemy::paint(GameData const &gameData)
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

void Enemy::updateGame(GameData const &gameData, float deltaTime)
{
    float randomInRange = m_randomPosition(m_randomEngine);

    m_position[0] += m_velocity * deltaTime;

    if ((abs(randomInRange) > 0) and m_movementCDTimer.elapsed() > lastRandom)
    {
        m_movementCDTimer.restart();
        m_velocity *= -1;
        lastRandom = m_randomTime(m_randomEngine);
        m_velocity = (abs(m_velocity)/m_velocity) * m_randomVelocity(m_randomEngine);


    }

    if ((abs(randomInRange) > 0) and m_movementCDTimer.elapsed() < lastRandomShoot)
    {
        shoot();
        lastRandomShoot = m_randomTime(m_randomEngine);
    }


    if (abs(m_position[0] + m_velocity * deltaTime) > 0.9f)
    {
        m_velocity *= -1;
        m_position[0] = 0.9f * abs(m_position[0])/m_position[0];
    }


    if(isShooting)
    {
        m_bullets.updateGame(gameData, -deltaTime);

        if(getBulletPosition()[1] < -1.0f)
            isShooting = false;
    }

    update();
}

std::vector<float> Enemy::getPosition()
{
    return m_position;
}



void Enemy::shoot()
{
    if (!isShooting)
    {
        //can shoot.
        isShooting = true;

        bool rnd{m_randomVelocity(m_randomEngine) > 2.5};

        m_bullets.shoot(getPosition(), 0.05, rnd);
    }
}

void Enemy::stopShooting()
{
    isShooting = false;
}

bool Enemy::getIsShooting()
{
    return isShooting;
}

int Enemy::getTotalHits()
{
    return totalHits;
}

void Enemy::addHit()
{
    totalHits++;
}

std::vector<float> Enemy::getBulletPosition()
{
    return m_bullets.getBulletPosition();
}
