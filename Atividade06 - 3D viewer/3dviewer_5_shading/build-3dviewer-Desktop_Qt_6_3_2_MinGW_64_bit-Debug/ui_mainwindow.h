/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page_9;
    QFrame *infoBox;
    QStackedWidget *stackedWidget_2;
    QWidget *page_13;
    QCheckBox *checkBoxDarkMode;
    QCheckBox *checkBoxWireframe;
    QCheckBox *checkOrthographic;
    QComboBox *shaderComboBox;
    QLabel *lblFPS;
    QPushButton *btnLoadToggleTexture;
    QFrame *frame_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QCheckBox *checkboxDisableHighlight;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QSlider *slider_Highlight;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    QCheckBox *checkSpotlight;
    QCheckBox *checkBoxWireframeOnly;
    QWidget *page_14;
    QLabel *lblVertices;
    QFrame *toonShadingBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *toonShadingVertical;
    QLabel *shadinglevels;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QSlider *slider_Levels;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lblLevels;
    QLabel *shadingColor;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSlider *slider_red;
    QSpacerItem *horizontalSpacer;
    QLabel *lblRedValue;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QSlider *slider_green;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblGreenValue;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_12;
    QSlider *slider_blue;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lblBlueValue;
    QGridLayout *gridLayout;
    OpenGLWidget *openGLWidget;
    QWidget *page_10;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 768);
        MainWindow->setMinimumSize(QSize(450, 450));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setDockOptions(QMainWindow::AnimatedDocks);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        infoBox = new QFrame(page_9);
        infoBox->setObjectName(QString::fromUtf8("infoBox"));
        infoBox->setGeometry(QRect(5, 5, 200, 201));
        sizePolicy.setHeightForWidth(infoBox->sizePolicy().hasHeightForWidth());
        infoBox->setSizePolicy(sizePolicy);
        infoBox->setAutoFillBackground(false);
        infoBox->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 47, 48);\n"
"border-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        infoBox->setFrameShape(QFrame::StyledPanel);
        infoBox->setFrameShadow(QFrame::Plain);
        infoBox->setLineWidth(1);
        stackedWidget_2 = new QStackedWidget(infoBox);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(10, 10, 181, 181));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy1);
        page_13 = new QWidget();
        page_13->setObjectName(QString::fromUtf8("page_13"));
        checkBoxDarkMode = new QCheckBox(page_13);
        checkBoxDarkMode->setObjectName(QString::fromUtf8("checkBoxDarkMode"));
        checkBoxDarkMode->setGeometry(QRect(0, 30, 83, 22));
        checkBoxDarkMode->setChecked(true);
        checkBoxDarkMode->setTristate(false);
        checkBoxWireframe = new QCheckBox(page_13);
        checkBoxWireframe->setObjectName(QString::fromUtf8("checkBoxWireframe"));
        checkBoxWireframe->setGeometry(QRect(100, 50, 80, 22));
        checkOrthographic = new QCheckBox(page_13);
        checkOrthographic->setObjectName(QString::fromUtf8("checkOrthographic"));
        checkOrthographic->setGeometry(QRect(0, 50, 96, 22));
        shaderComboBox = new QComboBox(page_13);
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->addItem(QString());
        shaderComboBox->setObjectName(QString::fromUtf8("shaderComboBox"));
        shaderComboBox->setEnabled(false);
        shaderComboBox->setGeometry(QRect(0, 100, 181, 24));
        shaderComboBox->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(61, 125, 230);"));
        lblFPS = new QLabel(page_13);
        lblFPS->setObjectName(QString::fromUtf8("lblFPS"));
        lblFPS->setGeometry(QRect(-2, 0, 71, 21));
        lblFPS->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblFPS->setMargin(1);
        btnLoadToggleTexture = new QPushButton(page_13);
        btnLoadToggleTexture->setObjectName(QString::fromUtf8("btnLoadToggleTexture"));
        btnLoadToggleTexture->setGeometry(QRect(80, -7, 101, 31));
        btnLoadToggleTexture->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 116, 98);\n"
"border-color: rgb(0, 0, 0);"));
        frame_2 = new QFrame(page_13);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 130, 181, 51));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frame_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 181, 51));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        checkboxDisableHighlight = new QCheckBox(verticalLayoutWidget);
        checkboxDisableHighlight->setObjectName(QString::fromUtf8("checkboxDisableHighlight"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkboxDisableHighlight->sizePolicy().hasHeightForWidth());
        checkboxDisableHighlight->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(checkboxDisableHighlight);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_5 = new QSpacerItem(10, 1, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        slider_Highlight = new QSlider(verticalLayoutWidget);
        slider_Highlight->setObjectName(QString::fromUtf8("slider_Highlight"));
        slider_Highlight->setEnabled(false);
        slider_Highlight->setMinimum(1);
        slider_Highlight->setMaximum(500);
        slider_Highlight->setSingleStep(10);
        slider_Highlight->setPageStep(100);
        slider_Highlight->setSliderPosition(20);
        slider_Highlight->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider_Highlight);

        horizontalSpacer_6 = new QSpacerItem(10, 1, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        checkSpotlight = new QCheckBox(page_13);
        checkSpotlight->setObjectName(QString::fromUtf8("checkSpotlight"));
        checkSpotlight->setEnabled(false);
        checkSpotlight->setGeometry(QRect(100, 30, 96, 22));
        checkBoxWireframeOnly = new QCheckBox(page_13);
        checkBoxWireframeOnly->setObjectName(QString::fromUtf8("checkBoxWireframeOnly"));
        checkBoxWireframeOnly->setGeometry(QRect(0, 70, 101, 22));
        stackedWidget_2->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName(QString::fromUtf8("page_14"));
        stackedWidget_2->addWidget(page_14);
        lblVertices = new QLabel(page_9);
        lblVertices->setObjectName(QString::fromUtf8("lblVertices"));
        lblVertices->setGeometry(QRect(210, 4, 621, 21));
        lblVertices->setStyleSheet(QString::fromUtf8("color: rgb(125, 125, 125);"));
        toonShadingBox = new QFrame(page_9);
        toonShadingBox->setObjectName(QString::fromUtf8("toonShadingBox"));
        toonShadingBox->setGeometry(QRect(5, 220, 200, 151));
        toonShadingBox->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 47, 48);\n"
"border-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        toonShadingBox->setFrameShape(QFrame::StyledPanel);
        toonShadingBox->setFrameShadow(QFrame::Plain);
        verticalLayoutWidget_2 = new QWidget(toonShadingBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 191, 131));
        toonShadingVertical = new QVBoxLayout(verticalLayoutWidget_2);
        toonShadingVertical->setSpacing(0);
        toonShadingVertical->setObjectName(QString::fromUtf8("toonShadingVertical"));
        toonShadingVertical->setSizeConstraint(QLayout::SetFixedSize);
        toonShadingVertical->setContentsMargins(0, 0, 5, 0);
        shadinglevels = new QLabel(verticalLayoutWidget_2);
        shadinglevels->setObjectName(QString::fromUtf8("shadinglevels"));
        QFont font;
        font.setPointSize(10);
        shadinglevels->setFont(font);

        toonShadingVertical->addWidget(shadinglevels);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        slider_Levels = new QSlider(verticalLayoutWidget_2);
        slider_Levels->setObjectName(QString::fromUtf8("slider_Levels"));
        slider_Levels->setMinimum(2);
        slider_Levels->setMaximum(10);
        slider_Levels->setPageStep(1);
        slider_Levels->setValue(5);
        slider_Levels->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(slider_Levels);

        horizontalSpacer_4 = new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        lblLevels = new QLabel(verticalLayoutWidget_2);
        lblLevels->setObjectName(QString::fromUtf8("lblLevels"));
        lblLevels->setMinimumSize(QSize(0, 0));
        lblLevels->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblLevels->setMargin(0);

        horizontalLayout_6->addWidget(lblLevels);


        verticalLayout_12->addLayout(horizontalLayout_6);


        toonShadingVertical->addLayout(verticalLayout_12);

        shadingColor = new QLabel(verticalLayoutWidget_2);
        shadingColor->setObjectName(QString::fromUtf8("shadingColor"));
        shadingColor->setFont(font);
        shadingColor->setScaledContents(true);
        shadingColor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        toonShadingVertical->addWidget(shadingColor);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(40, 0));

        horizontalLayout_4->addWidget(label_4);

        slider_red = new QSlider(verticalLayoutWidget_2);
        slider_red->setObjectName(QString::fromUtf8("slider_red"));
        sizePolicy1.setHeightForWidth(slider_red->sizePolicy().hasHeightForWidth());
        slider_red->setSizePolicy(sizePolicy1);
        slider_red->setStyleSheet(QString::fromUtf8(""));
        slider_red->setMaximum(1000);
        slider_red->setSingleStep(10);
        slider_red->setPageStep(10);
        slider_red->setValue(1000);
        slider_red->setOrientation(Qt::Horizontal);
        slider_red->setInvertedAppearance(false);

        horizontalLayout_4->addWidget(slider_red);

        horizontalSpacer = new QSpacerItem(10, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        lblRedValue = new QLabel(verticalLayoutWidget_2);
        lblRedValue->setObjectName(QString::fromUtf8("lblRedValue"));
        lblRedValue->setMinimumSize(QSize(0, 0));
        lblRedValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblRedValue->setMargin(0);

        horizontalLayout_4->addWidget(lblRedValue);


        verticalLayout_9->addLayout(horizontalLayout_4);


        verticalLayout_8->addLayout(verticalLayout_9);


        toonShadingVertical->addLayout(verticalLayout_8);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(verticalLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(40, 0));

        horizontalLayout_5->addWidget(label_10);

        slider_green = new QSlider(verticalLayoutWidget_2);
        slider_green->setObjectName(QString::fromUtf8("slider_green"));
        slider_green->setMaximum(1000);
        slider_green->setSingleStep(10);
        slider_green->setPageStep(10);
        slider_green->setValue(750);
        slider_green->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider_green);

        horizontalSpacer_2 = new QSpacerItem(10, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        lblGreenValue = new QLabel(verticalLayoutWidget_2);
        lblGreenValue->setObjectName(QString::fromUtf8("lblGreenValue"));
        lblGreenValue->setMinimumSize(QSize(0, 0));
        lblGreenValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblGreenValue->setMargin(0);

        horizontalLayout_5->addWidget(lblGreenValue);


        verticalLayout_11->addLayout(horizontalLayout_5);


        verticalLayout_10->addLayout(verticalLayout_11);


        toonShadingVertical->addLayout(verticalLayout_10);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_12 = new QLabel(verticalLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(label_12);

        slider_blue = new QSlider(verticalLayoutWidget_2);
        slider_blue->setObjectName(QString::fromUtf8("slider_blue"));
        slider_blue->setMaximum(1000);
        slider_blue->setSingleStep(10);
        slider_blue->setPageStep(10);
        slider_blue->setValue(1);
        slider_blue->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider_blue);

        horizontalSpacer_3 = new QSpacerItem(10, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        lblBlueValue = new QLabel(verticalLayoutWidget_2);
        lblBlueValue->setObjectName(QString::fromUtf8("lblBlueValue"));
        lblBlueValue->setMinimumSize(QSize(0, 0));
        lblBlueValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblBlueValue->setMargin(0);

        horizontalLayout->addWidget(lblBlueValue);


        verticalLayout->addLayout(horizontalLayout);


        toonShadingVertical->addLayout(verticalLayout);

        toonShadingVertical->setStretch(1, 1);
        toonShadingVertical->setStretch(3, 1);
        toonShadingVertical->setStretch(4, 1);
        toonShadingVertical->setStretch(5, 1);
        gridLayout = new QGridLayout(page_9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        openGLWidget = new OpenGLWidget(page_9);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(page_9);
        openGLWidget->raise();
        infoBox->raise();
        toonShadingBox->raise();
        lblVertices->raise();
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        stackedWidget->addWidget(page_10);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(MainWindow);
        QObject::connect(checkBoxDarkMode, SIGNAL(clicked(bool)), openGLWidget, SLOT(toggleDarkMode(bool)));
        QObject::connect(actionOpen, &QAction::triggered, openGLWidget, qOverload<>(&OpenGLWidget::showFileOpenDialog));
        QObject::connect(checkBoxWireframe, SIGNAL(clicked(bool)), openGLWidget, SLOT(toggleWireframe(bool)));
        QObject::connect(checkOrthographic, SIGNAL(clicked(bool)), openGLWidget, SLOT(toggleOrthographic(bool)));
        QObject::connect(shaderComboBox, SIGNAL(currentIndexChanged(int)), openGLWidget, SLOT(changeShader(int)));
        QObject::connect(openGLWidget, SIGNAL(enableSliderHighlight(bool)), slider_Highlight, SLOT(setEnabled(bool)));
        QObject::connect(openGLWidget, SIGNAL(enableComboShaders(bool)), shaderComboBox, SLOT(setEnabled(bool)));
        QObject::connect(slider_Highlight, SIGNAL(valueChanged(int)), openGLWidget, SLOT(changeHighlightModel(int)));
        QObject::connect(openGLWidget, SIGNAL(updateFPS(QString)), lblFPS, SLOT(setText(QString)));
        QObject::connect(btnLoadToggleTexture, &QPushButton::clicked, openGLWidget, qOverload<>(&OpenGLWidget::alternateTexture));
        QObject::connect(openGLWidget, SIGNAL(statusBarMessage(QString)), lblVertices, SLOT(setText(QString)));
        QObject::connect(openGLWidget, SIGNAL(updateRed(QString)), lblRedValue, SLOT(setText(QString)));
        QObject::connect(slider_red, SIGNAL(valueChanged(int)), openGLWidget, SLOT(onRedSliderChanged(int)));
        QObject::connect(slider_green, SIGNAL(valueChanged(int)), openGLWidget, SLOT(onGreenSliderChanged(int)));
        QObject::connect(slider_blue, SIGNAL(valueChanged(int)), openGLWidget, SLOT(onBlueSliderChanged(int)));
        QObject::connect(slider_Levels, SIGNAL(valueChanged(int)), openGLWidget, SLOT(onLevelSliderChanged(int)));
        QObject::connect(openGLWidget, SIGNAL(updateGreen(QString)), lblGreenValue, SLOT(setText(QString)));
        QObject::connect(openGLWidget, SIGNAL(updateBlue(QString)), lblBlueValue, SLOT(setText(QString)));
        QObject::connect(openGLWidget, SIGNAL(updateLevel(QString)), lblLevels, SLOT(setText(QString)));
        QObject::connect(openGLWidget, SIGNAL(updateToonShadingBox(bool)), toonShadingBox, SLOT(setVisible(bool)));
        QObject::connect(checkBoxWireframeOnly, SIGNAL(clicked(bool)), openGLWidget, SLOT(toggleWireframeOnly(bool)));
        QObject::connect(checkboxDisableHighlight, SIGNAL(clicked(bool)), openGLWidget, SLOT(toggleDisableHighlight(bool)));
        QObject::connect(openGLWidget, SIGNAL(updatePlanetHidden(bool)), btnLoadToggleTexture, SLOT(setHidden(bool)));
        QObject::connect(checkSpotlight, SIGNAL(clicked(bool)), openGLWidget, SLOT(onSpotlightChanged(bool)));
        QObject::connect(openGLWidget, SIGNAL(updateSpotlightCheckbox(bool)), checkSpotlight, SLOT(setEnabled(bool)));

        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Atividade 06 - 3D viewer", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        checkBoxDarkMode->setText(QCoreApplication::translate("MainWindow", "Dark Mode", nullptr));
        checkBoxWireframe->setText(QCoreApplication::translate("MainWindow", "Wireframe", nullptr));
        checkOrthographic->setText(QCoreApplication::translate("MainWindow", "Orthographic", nullptr));
        shaderComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Z-Depth", nullptr));
        shaderComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Normal Colors", nullptr));
        shaderComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Flat Shading", nullptr));
        shaderComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Gouraud Shading", nullptr));
        shaderComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Phong Shading", nullptr));
        shaderComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Normal + Phong", nullptr));
        shaderComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Toon Shading", nullptr));
        shaderComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Texture", nullptr));
        shaderComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "A Terra \303\251 redonda!", nullptr));
        shaderComboBox->setItemText(9, QCoreApplication::translate("MainWindow", "Normal Map", nullptr));
        shaderComboBox->setItemText(10, QCoreApplication::translate("MainWindow", "Cube Map", nullptr));

        lblFPS->setText(QCoreApplication::translate("MainWindow", "FPS", nullptr));
        btnLoadToggleTexture->setText(QCoreApplication::translate("MainWindow", "Alternate Texture!", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Highlight (alpha)</span></p></body></html>", nullptr));
        checkboxDisableHighlight->setText(QCoreApplication::translate("MainWindow", "Disable", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "500", nullptr));
#if QT_CONFIG(tooltip)
        checkSpotlight->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#aa0000;\">Spotlight est\303\241 dispon\303\255vel apenas para os shaders &quot;Phong Shading&quot;, &quot;Normal + Phong&quot; e &quot;Toon Shading&quot;.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSpotlight->setText(QCoreApplication::translate("MainWindow", "Spotlight", nullptr));
        checkBoxWireframeOnly->setText(QCoreApplication::translate("MainWindow", "Wireframe only", nullptr));
        lblVertices->setText(QString());
        shadinglevels->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Toon Shading Levels</span></p></body></html>", nullptr));
        lblLevels->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        shadingColor->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Toon Shading Color</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Red  ", nullptr));
        lblRedValue->setText(QCoreApplication::translate("MainWindow", "1.000", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        lblGreenValue->setText(QCoreApplication::translate("MainWindow", "0.750", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        lblBlueValue->setText(QCoreApplication::translate("MainWindow", "0.000", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
