/*
LISTA DE MODIFICAÇÕES.
    -Remodelagem da interface gráfica.
    -Alteração na forma como o open dialog é chamado: ao abrir da segunda vez em diante fará com que a última pasta aberta seja exibida.

*/





#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs(model);
    destroyShaders(model);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_DEPTH_TEST);

    connect(&timer, &QTimer::timeout, this, [&](){update();});
    timer.start(0);


    connect(&localTimer, &QTimer::timeout, this, &OpenGLWidget::animate);
    localTimer.start(0);
    fpsElapsedTimer.start();
    elapsedTimer.start();


    emit updateToonShadingBox(false);
    emit updatePlanetHidden(true);
}

void OpenGLWidget::animate()
{
    if(++frameCount==100)
    {
        QString str = QString("<html><head/><body><p>%1 FPS<br/></p></body></html>").arg(QString::number(frameCount/(fpsElapsedTimer.restart()/1000.0f), 'f', 0));
        emit updateFPS(str);
        frameCount=0;
    }

    GLfloat deltaTime = elapsedTimer.restart()/1000.0f;

    cloudAngle += deltaTime;

}

void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    camera.resizeViewPort(width, height);

    if (model)
        trackBall.resizeViewport(width, height);

}

void OpenGLWidget::paintGL()
{
    if (!model)  return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    paintModel();
    paintWireframe();
}

void OpenGLWidget::paintModel()
{
    if (!wireframeOnly)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        camera.resizeViewPort(this->width(),this->height(),orthographic);

        model->modelMatrix.setToIdentity();
        model->modelMatrix.translate(0, 0, zoom);
        //Futura implementação: movimentação do objeto no espaço pelas teclas W,A,S,D. model->modelMatrix.translate(leftRight, upDown, 0);
        model->modelMatrix.rotate(trackBall.getRotation());
        model->rescaleModelMatrix();

        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);


        glBindVertexArray(model->vao);
        auto shaderProgramID{model->shaderProgram[model->currentShader]};
        glUseProgram(shaderProgramID);

        auto locModel{glGetUniformLocation(shaderProgramID, "model")};
        auto locView{glGetUniformLocation(shaderProgramID, "view")};
        auto locProjection{glGetUniformLocation(shaderProgramID, "projection")};
        auto locNormalMatrix{glGetUniformLocation(shaderProgramID, "normalMatrix")};

        auto locLightPosition{glGetUniformLocation(shaderProgramID, "lightPosition")};
        auto locAmbientProduct{glGetUniformLocation(shaderProgramID, "ambientProduct")};
        auto locDiffuseProduct{glGetUniformLocation(shaderProgramID, "diffuseProduct")};
        auto locSpecularProduct{glGetUniformLocation(shaderProgramID, "specularProduct")};
        auto locShininess{glGetUniformLocation(shaderProgramID, "shininess")};
        auto ambientProduct{light.ambient*model->material.ambient};
        auto diffuseProduct{light.diffuse*model->material.diffuse};
        auto specularProduct{light.specular*model->material.specular};

        auto locToonLevel{glGetUniformLocation(shaderProgramID, "toonLevel")};
        auto locToonColor{glGetUniformLocation(shaderProgramID, "toonColor")};
        auto locCloudAngle{glGetUniformLocation(shaderProgramID, "angle")};
        auto locCutOff{glGetUniformLocation(shaderProgramID, "cutoff")};

        glUniform4fv(locToonColor, 1, &(toonColors[0]));
        glUniform1f(locToonLevel, toonLevel);
        glUniform1f(locCloudAngle, cloudAngle);
        glUniform1f(locCutOff, spotlightCutOff);


        glUniform4fv(locLightPosition, 1, &(light.position[0]));
        glUniform4fv(locAmbientProduct, 1, &(ambientProduct[0]));
        glUniform4fv(locDiffuseProduct, 1, &(diffuseProduct[0]));
        glUniform4fv(locSpecularProduct, 1, &(specularProduct[0]));
        glUniformMatrix4fv(locModel, 1, GL_FALSE, model->modelMatrix.data());
        glUniformMatrix3fv(locNormalMatrix, 1, GL_FALSE, model->modelMatrix.normalMatrix().data());
        glUniform1f(locShininess, static_cast<GLfloat>(model->material.shininess));
        glUniformMatrix4fv(locProjection, 1, GL_FALSE, camera.projectionMatrix.data());
        glUniformMatrix4fv(locView, 1, GL_FALSE, camera.viewMatrix.data());

        glDrawElements(GL_TRIANGLES, model->numFaces * 3, GL_UNSIGNED_INT, nullptr);


        switch(model->currentShader)
        {
            case 7: //texture
            {
                glUniform1i(glGetUniformLocation(shaderProgramID, "colorTexture"),0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, model->textureID);
                break;
            }
            case 8: //texture layer
            {
                glUniform1i(glGetUniformLocation(shaderProgramID, "layerLower"),1);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, model->textureIDLayerLower);

                glUniform1i(glGetUniformLocation(shaderProgramID, "layerUpper"),2);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, model->textureIDLayerUpper);
                break;
            }
            case 9: //normal mapping
            {
                glUniform1i(glGetUniformLocation(shaderProgramID, "textureColor"),3);
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, model->textureIDNormalMapColor);

                glUniform1i(glGetUniformLocation(shaderProgramID, "textureNormals"),4);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, model->textureIDNormalMapNormals);
                break;
            }
            case 10:
            {
                glBindTexture(GL_TEXTURE_CUBE_MAP, model->textureIDCubeMap);
                break;
            }//switch


            glDrawElements(GL_TRIANGLES, model->numFaces * 3, GL_UNSIGNED_INT, nullptr);
        }
    }
}

void OpenGLWidget::paintWireframe()
{
    if (wireframe or wireframeOnly)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        camera.resizeViewPort(this->width(),this->height(),orthographic);

        model->modelMatrix.setToIdentity();
        model->modelMatrix.translate(0, 0, zoom+0.01f); //Pequeno offset no wireframe.
        //Futura implementação: movimentação do objeto no espaço pelas teclas W,A,S,D.model->modelMatrix.translate(leftRight, upDown, 0)
        model->modelMatrix.rotate(trackBall.getRotation());
        model->rescaleModelMatrix();

        //    glEnable(GL_CULL_FACE);
        //    glCullFace(GL_BACK);


        float wireframeShader = 1; //Inicia wireframe com shader normal.
        (currentShaderIndex != 1 and currentShaderIndex != 5)? wireframeShader = 1 :  wireframeShader = 0; //Pega um shader diferente do desenho do modelo.

        glBindVertexArray(model->vao);
        auto shaderProgramID{model->shaderProgram[(wireframeOnly)? model->currentShader : wireframeShader]};
        glUseProgram(shaderProgramID);

        auto locModel{glGetUniformLocation(shaderProgramID, "model")};
        auto locView{glGetUniformLocation(shaderProgramID, "view")};
        auto locProjection{glGetUniformLocation(shaderProgramID, "projection")};
        auto locNormalMatrix{glGetUniformLocation(shaderProgramID, "normalMatrix")};

        auto locLightPosition{glGetUniformLocation(shaderProgramID, "lightPosition")};
        auto locAmbientProduct{glGetUniformLocation(shaderProgramID, "ambientProduct")};
        auto locDiffuseProduct{glGetUniformLocation(shaderProgramID, "diffuseProduct")};
        auto locSpecularProduct{glGetUniformLocation(shaderProgramID, "specularProduct")};
        auto locShininess{glGetUniformLocation(shaderProgramID, "shininess")};
        auto ambientProduct{light.ambient*model->material.ambient};
        auto diffuseProduct{light.diffuse*model->material.diffuse};
        auto specularProduct{light.specular*model->material.specular};

        auto locToonLevel{glGetUniformLocation(shaderProgramID, "toonLevel")};
        auto locToonColor{glGetUniformLocation(shaderProgramID, "toonColor")};
        auto locCloudAngle{glGetUniformLocation(shaderProgramID, "angle")};
        auto locCutOff{glGetUniformLocation(shaderProgramID, "cutoff")};

        glUniform4fv(locToonColor, 1, &(toonColors[0]));
        glUniform1f(locToonLevel, toonLevel);
        glUniform1f(locCloudAngle, cloudAngle);
        glUniform1f(locCutOff, spotlightCutOff);


        glUniform4fv(locLightPosition, 1, &(light.position[0]));
        glUniform4fv(locAmbientProduct, 1, &(ambientProduct[0]));
        glUniform4fv(locDiffuseProduct, 1, &(diffuseProduct[0]));
        glUniform4fv(locSpecularProduct, 1, &(specularProduct[0]));
        glUniformMatrix4fv(locModel, 1, GL_FALSE, model->modelMatrix.data());
        glUniformMatrix3fv(locNormalMatrix, 1, GL_FALSE, model->modelMatrix.normalMatrix().data());
        glUniform1f(locShininess, static_cast<GLfloat>(model->material.shininess));
        glUniformMatrix4fv(locProjection, 1, GL_FALSE, camera.projectionMatrix.data());
        glUniformMatrix4fv(locView, 1, GL_FALSE, camera.viewMatrix.data());

        glDrawElements(GL_TRIANGLES, model->numFaces * 3, GL_UNSIGNED_INT, nullptr);
    }
}


void OpenGLWidget::toggleDarkMode(bool changeToDarkMode)
{
    makeCurrent();
    if(changeToDarkMode)
        glClearColor(0,0,0,1);
    else
        glClearColor(1,1,1,1);
    update();
}

void OpenGLWidget::destroyVBOs(std::shared_ptr<Model> m)
{
    makeCurrent();
    if(!m) return;
    glDeleteBuffers(1,&m->vboVertices);
    glDeleteBuffers(1,&m->vboNormals);
    glDeleteBuffers(1,&m->eboIndices);
    glDeleteVertexArrays(1,&m->vao);
    m->vboVertices=0;
    m->eboIndices=0;
    m->vboVertices=0;
    m->vao=0;
}

void OpenGLWidget::destroyShaders(std::shared_ptr<Model> m)
{
    makeCurrent();
    if(!m) return;
    for(GLuint shaderProgramID : m->shaderProgram)
        glDeleteProgram(shaderProgramID);
}


void OpenGLWidget::createVBOs(std::shared_ptr<Model> m)
{
    makeCurrent();
    if(!m) return;

    destroyVBOs(m);

    glGenVertexArrays(1,&m->vao);
    glBindVertexArray(m->vao);

    glGenBuffers(1,&m->vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER,m->vboVertices);
    glBufferData(GL_ARRAY_BUFFER,m->numVertices*sizeof(QVector4D),m->vertices.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m->vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, m->vboNormals);
    glBufferData(GL_ARRAY_BUFFER, m->numVertices * sizeof(QVector3D), m->normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m->vboTextCoords);
    glBindBuffer(GL_ARRAY_BUFFER, m->vboTextCoords);
    glBufferData(GL_ARRAY_BUFFER, m->numVertices * sizeof(QVector2D), m->textureCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &m->vboTangents);
    glBindBuffer(GL_ARRAY_BUFFER, m->vboTangents);
    glBufferData(GL_ARRAY_BUFFER, m->numVertices * sizeof(QVector4D), m->tangents.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(3);


    glGenBuffers(1,&m->eboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m->eboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m->numFaces*3*sizeof(GLuint),m->indices.data(),GL_STATIC_DRAW);
}

void OpenGLWidget::createShaders(std::shared_ptr<Model> m)
{
    makeCurrent();
    if(!m) return;//testar sem esta linha
    destroyShaders(m);

    for(size_t i{0}; i < m->shaderProgram.size(); i++)
    {
        QFile vs(m->vertexShaderFileName[i]);
        QFile fs(m->fragmentShaderFileName[i]);

        if(!vs.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << m->vertexShaderFileName[i] + " not found";
            return;
        }
        if(!fs.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << m->fragmentShaderFileName[i] + " not found";
            return;
        }

        auto byteArrayVs{vs.readAll()};
        auto byteArrayFs{fs.readAll()};

        const char *c_strVs{byteArrayVs};
        const char *c_strFs{byteArrayFs};

        vs.close();
        fs.close();

        GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
        glShaderSource(vertexShader,1,&c_strVs,0);
        glCompileShader(vertexShader);

        GLint isCompiled{0};
        glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&isCompiled);
        if(!isCompiled)
        {
            GLint maxLength{0};
            glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader,maxLength,&maxLength,&infoLog[0]);
            qDebug("%s",&infoLog[0]);
            glDeleteShader(vertexShader);
            return;
        }

        GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
        glShaderSource(fragmentShader,1,&c_strFs,0);
        glCompileShader(fragmentShader);

        isCompiled = 0;
        glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&isCompiled);
        if(!isCompiled)
        {
            GLint maxLength{0};
            glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader,maxLength,&maxLength,&infoLog[0]);
            qDebug("%s",&infoLog[0]);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return;
        }

        m->shaderProgram[i] = glCreateProgram();
        glAttachShader(m->shaderProgram[i],vertexShader);
        glAttachShader(m->shaderProgram[i],fragmentShader);
        glLinkProgram(m->shaderProgram[i]);

        GLint isLinked{0};
        glGetProgramiv(m->shaderProgram[i],GL_LINK_STATUS,&isLinked);
        if(!isLinked)
        {
            GLint maxLength{0};
            glGetProgramiv(m->shaderProgram[i],GL_INFO_LOG_LENGTH,&maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m->shaderProgram[i],maxLength,&maxLength,&infoLog[0]);
            qDebug("%s",&infoLog[0]);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(m->shaderProgram[i]);
            return;
        }

        glDetachShader(m->shaderProgram[i],vertexShader);
        glDetachShader(m->shaderProgram[i],fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


}


void OpenGLWidget::showFileOpenDialog()
{
    //Ajuste para que o file dialog abra na pasta anterior, caso alguma pasta já tenha sido aberta.
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",(lastDir == ""? QDir::homePath() : lastDir),QString("OFF File (*.off)"),
                                                    nullptr
                                                   #ifdef Q_OS_LINUX
                                                   , QFileDialog::DontUseNativeDialog
                                                   #endif
                                                   );
    lastDir = fileName;

    if(!fileName.isEmpty())
    {
        model = std::make_shared<Model>();
        model->readOFFFile(fileName);

        createShaders(model);
        createVBOs(model);

        loadTexture(model);
        loadTextureLayer(model);
        loadCubeMapTexture(model);
        loadNormalMapTexture(model);

        trackBall.resizeViewport(width(), height());

        //inserimos este comando dentro do if
        emit statusBarMessage(QString("%1 Vertices and %2 Faces (%3)").arg(model->numVertices).arg(model->numFaces).arg(fileName));
        emit enableComboShaders(true);

        changeShader(currentShaderIndex);
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

void OpenGLWidget::toggleWireframe(bool w)
{
    makeCurrent();
    wireframe=w;
    update();
}

void OpenGLWidget::toggleWireframeOnly(bool w)
{
    makeCurrent();
    wireframeOnly = w;
    update();
}

void OpenGLWidget::toggleOrthographic(bool ortho)
{
    makeCurrent();
    orthographic = ortho;
    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
   makeCurrent();
   if(!model) return;
   zoom += 0.001f * event->angleDelta().y();
   update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    makeCurrent();
    if (!model) return;
    trackBall.mouseMove(event->position());
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    if (!model) return;
    if (event->button() & Qt::LeftButton)
        trackBall.mousePress(event->position());
    update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    makeCurrent();
    if (!model)  return;
    if (event->button() & Qt::LeftButton)
        trackBall.mouseRelease(event->position());
    update();
}

void OpenGLWidget::changeShader(int shaderIndex)
{
    makeCurrent();
    if (!model)  return;

    //Carrega o modelo de esfera automaticamente, afinal, a Terra é redonda!
    if (shaderIndex == 8)
    {
        QString file = ":/models/sphere.off";
        model = std::make_shared<Model>();
        model->readOFFFile(file);

        createShaders(model);
        createVBOs(model);

        loadTexture(model);
        loadTextureLayer(model);
        loadCubeMapTexture(model);
        loadNormalMapTexture(model);

        trackBall.resizeViewport(width(), height());
        //inserimos este comando dentro do if
        emit statusBarMessage(QString("%1 Vertices and %2 Faces (%3)").arg(model->numVertices).arg(model->numFaces).arg(file));
        emit enableComboShaders(true);
    }

    emit updatePlanetHidden(!(shaderIndex == 7));



    model->currentShader = shaderIndex;
    currentShaderIndex = shaderIndex;

    if ((shaderIndex > 1 && shaderIndex < 7) or shaderIndex > 8 )
        emit enableSliderHighlight(true);
    else
        emit enableSliderHighlight(false);

    if (shaderIndex == 6)
        emit updateToonShadingBox(true);
    else
        emit updateToonShadingBox(false);

    if (shaderIndex >= 4 && shaderIndex <= 6)
        emit updateSpotlightCheckbox(true);
    else
        emit updateSpotlightCheckbox(false);

    lastTexture = 0;

    update();
}

void OpenGLWidget::changeHighlightModel(int h)
{
    makeCurrent();
    if (!isHightLightDisabled)
        model->material.shininess = static_cast<float>(h);
    currentShininess = h;
    update();
}


void OpenGLWidget::onRedSliderChanged(int value)
{
    QString str = QString("%1").arg(QString::number(value/1000.0f, 'f', 3));
    emit updateRed(str);

    toonColors[0] = value/1000.0f;
}

void OpenGLWidget::onGreenSliderChanged(int value)
{
    QString str = QString("%1").arg(QString::number(value/1000.0f, 'f', 3));
    emit updateGreen(str);

    toonColors[1] = value/1000.0f;
}

void OpenGLWidget::onBlueSliderChanged(int value)
{
    QString str = QString("%1").arg(QString::number(value/1000.0f, 'f', 3));
    emit updateBlue(str);

    toonColors[2] = value/1000.0f;
}


void OpenGLWidget::onLevelSliderChanged(int value)
{
    QString str = QString("%1").arg(QString::number(value, 'f', 0));
    emit updateLevel(str);

    toonLevel = value;
}


//http://www.texturise.club/
//https://3dtextures.me/2018/10/04/sapphire-001/
void OpenGLWidget::loadTexture(std::shared_ptr<Model> m)
{
    auto image{QImage(":/textures/2k_jupiter.jpg").convertToFormat(QImage::Format_RGBA8888)};
    //auto image{QImage(":/textures/images/sapphire_color.jpg" ).convertToFormat(QImage::Format_RGBA8888)};
    //auto image{QImage(":/textures/images/Seamless_Pebbles_Texture.jpg" ).convertToFormat(QImage::Format_RGBA8888)};

    makeCurrent();

    if (m->textureID) glDeleteTextures(1, &m->textureID);

    glGenTextures(1, &m->textureID);
    glBindTexture(GL_TEXTURE_2D, m->textureID);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    update();
}

//https://www.solarsystemscope.com/textures/download/2k_earth_daymap.jpg //terra
void OpenGLWidget::loadTextureLayer(std::shared_ptr<Model> m)
{

    auto terra{QImage(":/textures/2k_earth_daymap.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto nuvem{QImage(":/textures/2k_earth_clouds.jpg").convertToFormat(QImage::Format_RGBA8888)};

    makeCurrent();

    if (m->textureIDLayerLower)  glDeleteTextures(1, &m->textureIDLayerLower);

    glGenTextures(1, &m->textureIDLayerLower);
    glBindTexture(GL_TEXTURE_2D, m->textureIDLayerLower);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,terra.width(),terra.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,terra.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (m->textureIDLayerUpper) glDeleteTextures(1, &m->textureIDLayerUpper);

    glGenTextures(1, &m->textureIDLayerUpper);
    glBindTexture(GL_TEXTURE_2D, m->textureIDLayerUpper);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,nuvem.width(),nuvem.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,nuvem.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    update();

}

void OpenGLWidget::loadNormalMapTexture(std::shared_ptr<Model> m)
{
    auto pedra{QImage(":/textures/2k_earth_daymap.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto normais{QImage(":/textures/2k_earth_normal_map.jpg").convertToFormat(QImage::Format_RGBA8888)};
//    auto pedra{QImage(":/textures/images/sapphire_color.jpg").convertToFormat(QImage::Format_RGBA8888)};
//    auto normais{QImage(":/textures/images/sapphire_normal.jpg").convertToFormat(QImage::Format_RGBA8888)};

//    auto pedra{QImage(":/textures/images/Seamless_Pebbles_Texture.jpg").convertToFormat(QImage::Format_RGBA8888)};
//    auto normais{QImage(":/textures/images/Seamless_Pebbles_Texture_NORMAL.jpg").convertToFormat(QImage::Format_RGBA8888)};

    makeCurrent();

    if (m->textureIDNormalMapColor)  glDeleteTextures(1, &m->textureIDNormalMapColor);

    glGenTextures(1, &m->textureIDNormalMapColor);
    glBindTexture(GL_TEXTURE_2D, m->textureIDNormalMapColor);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pedra.width(),pedra.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,pedra.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (m->textureIDNormalMapNormals) glDeleteTextures(1, &m->textureIDNormalMapNormals);

    glGenTextures(1, &m->textureIDNormalMapNormals);
    glBindTexture(GL_TEXTURE_2D, m->textureIDNormalMapNormals);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,normais.width(),normais.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,normais.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    update();
}


void OpenGLWidget::loadCubeMapTexture(std::shared_ptr<Model> m)
{
    auto negx{QImage(":/textures/cubemap/negx.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto negy{QImage(":/textures/cubemap/negy.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto negz{QImage(":/textures/cubemap/negz.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto posx{QImage(":/textures/cubemap/posx.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto posy{QImage(":/textures/cubemap/posy.jpg").convertToFormat(QImage::Format_RGBA8888)};
    auto posz{QImage(":/textures/cubemap/posz.jpg").convertToFormat(QImage::Format_RGBA8888)};


    if (m->textureIDCubeMap) glDeleteTextures(1, &m->textureIDCubeMap);

    glGenTextures(1, &m->textureIDCubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m->textureIDCubeMap);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, negx.width(), negx.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, negx.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, negy.width(), negy.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, negy.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, negz.width(), negz.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, negz.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, posx.width(), posx.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, posx.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, posy.width(), posy.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, posy.bits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, posz.width(), posz.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, posz.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void OpenGLWidget::toggleDisableHighlight(bool disable)
{
    makeCurrent();
    isHightLightDisabled = disable;

    if (!disable)
        model->material.shininess = currentShininess;
    else
       model->material.shininess = 99999999.9f;

    update();
}

void OpenGLWidget::alternateTexture()
{
    QString str = "";

    lastTexture++;

    if (lastTexture > 7)
        lastTexture = 0;

    switch(lastTexture)
    {
    case 0:
        str = ":/textures/2k_jupiter.jpg";
        qDebug("Júpiter!");
        break;
    case 1:
        str = ":/textures/2k_earth_daymap.jpg";
        qDebug("Terra!");
        break;
    case 2:
        str = ":/textures/2k_mars.jpg";
        qDebug("Marte!");
        break;
    case 3:
        str = ":/textures/2k_mercury.jpg";
        qDebug("Mercúrio!");
        break;
    case 4:
        str = ":/textures/2k_saturn.jpg";
        qDebug("Saturno!");
        break;
    case 5:
        str = ":/textures/2k_neptune.jpg";
        qDebug("Netuno!");
        break;
    case 6:
        str = ":/textures/2k_uranus.jpg";
        qDebug("Urano!");
        break;
    case 7:
        str = ":/textures/2k_venus_surface.jpg";
        qDebug("Vênus!");
        break;
    }


    auto image{QImage(str).convertToFormat(QImage::Format_RGBA8888)};
    //auto image{QImage(":/textures/images/sapphire_color.jpg" ).convertToFormat(QImage::Format_RGBA8888)};
    //auto image{QImage(":/textures/images/Seamless_Pebbles_Texture.jpg" ).convertToFormat(QImage::Format_RGBA8888)};

    makeCurrent();

    if (model->textureID) glDeleteTextures(1, &model->textureID);

    glGenTextures(1, &model->textureID);
    glBindTexture(GL_TEXTURE_2D, model->textureID);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    update();
}


void OpenGLWidget::onSpotlightChanged(bool visible)
{
    makeCurrent();

    visible ? spotlightCutOff = currentSpotlightCutOff : spotlightCutOff = 180.0f;

    update();
}
