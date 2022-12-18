#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>

#ifdef Q_OS_MAC
    #include <QOpenGLFunctions_4_1_Core>
#else
    #include <QOpenGLFunctions_4_0_Core>
#endif

#include <QTimer>
#include <QVector4D>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <QFileDialog>
#include <memory>
#include <model.h>
#include <camera.h>
#include <trackball.h>
#include <light.h>
#include <QElapsedTimer>


class OpenGLWidget : public QOpenGLWidget, protected
        #ifdef Q_OS_MAC
          QOpenGLFunctions_4_1_Core
        #else
          QOpenGLFunctions_4_0_Core
        #endif
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    void initializeGL() override;
    void resizeGL(int, int) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;

    std::shared_ptr<Model> model;

    void createVBOs(std::shared_ptr<Model>);
    void destroyVBOs(std::shared_ptr<Model>);
    void createShaders(std::shared_ptr<Model>);
    void destroyShaders(std::shared_ptr<Model>);
    bool wireframe{false};
    bool wireframeOnly{false};
    bool orthographic{false};
    int currentShaderIndex{0};

    float leftRight{0};
    float upDown{0};

    Camera camera;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    QTimer timer;
    float zoom{0};
    TrackBall trackBall;

    Light light;

    void loadTexture(std::shared_ptr<Model>);
    void loadTextureLayer(std::shared_ptr<Model>);
    void loadCubeMapTexture(std::shared_ptr<Model>);
    void loadNormalMapTexture(std::shared_ptr<Model>);

    QString lastDir{};

    QVector4D toonColors{QVector4D(1.0f, 0.75f, 0.0f, 1.0f)};
    GLfloat toonLevel{5.0f};
    GLfloat cloudAngle{0.0f};
    GLfloat spotlightCutOff{180.0f};
    GLfloat currentSpotlightCutOff{15.0f};

    void paintModel();
    void paintWireframe();

private:
    void animate();

    QTimer localTimer;
    QElapsedTimer fpsElapsedTimer;
    QElapsedTimer elapsedTimer;


    int frameCount{0};
    float currentShininess{20};
    bool isHightLightDisabled{false};
    int lastTexture{0};


signals:
    void statusBarMessage(QString);
    void enableComboShaders(bool);
    void enableSliderHighlight(bool);
    void updateFPS(QString);
    void updateRed(QString);
    void updateGreen(QString);
    void updateBlue(QString);
    void updateLevel(QString);
    void updateToonShadingBox(bool);
    void updatePlanetHidden(bool);
    void updateSpotlightCheckbox(bool);



public slots:
    void toggleDarkMode(bool);
    void toggleWireframe(bool);
    void toggleWireframeOnly(bool);
    void toggleOrthographic(bool);
    void showFileOpenDialog();
    void changeShader(int);
    void changeHighlightModel(int);
    void onRedSliderChanged(int);
    void onGreenSliderChanged(int);
    void onBlueSliderChanged(int);
    void onLevelSliderChanged(int);
    void toggleDisableHighlight(bool);
    void alternateTexture();
    void onSpotlightChanged(bool);
};

#endif // OPENGLWIDGET_H
