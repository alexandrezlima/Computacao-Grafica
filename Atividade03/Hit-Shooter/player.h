#ifndef PLAYER_H
#define PLAYER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QVector2D>
#include <QTimer>
#include <QFile>
#include <vector>

#include "gamedata.h"

class Player : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();
    void create(GLuint program);
    void paint(GameData const &gameData);
    void updateGame(GameData const &gameData, float deltaTime);
    void destroy();
    std::vector<float> getPosition();


    float m_rotation{0};
    float m_scale{1.0f};
    float m_velocity{2};
    std::vector<float> m_position{0, -0.8f};

    QTimer m_bulletCDTimer;

private:
    GLuint m_program{};
    GLint m_translationLoc{};
    GLint m_scaleLoc{};
    GLint m_rotationLoc{};

    GLuint m_VAO{0};
    GLuint m_VBO{0};
    GLuint m_VBOColors{0};
    GLuint m_EBO{0};

    bool wasInitialized{false};
};

#endif // PLAYER_H
