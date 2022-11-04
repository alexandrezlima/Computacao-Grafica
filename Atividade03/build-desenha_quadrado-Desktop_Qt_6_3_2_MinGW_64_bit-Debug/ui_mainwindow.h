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
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QStackedWidget *stackedWidget;
    QWidget *page;
    OpenGLWidget *openGLWidget;
    QLabel *lblEndGame;
    QLabel *lblHitsAndFrames;
    QPushButton *btnRestart;
    QLabel *label;
    QWidget *page_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(962, 860);
#if QT_CONFIG(statustip)
        MainWindow->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        MainWindow->setWhatsThis(QString::fromUtf8(""));
#endif // QT_CONFIG(whatsthis)
        MainWindow->setAutoFillBackground(false);
        MainWindow->setDockOptions(QMainWindow::AnimatedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 961, 861));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        openGLWidget = new OpenGLWidget(page);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setEnabled(true);
        openGLWidget->setGeometry(QRect(0, 0, 961, 861));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setFocusPolicy(Qt::StrongFocus);
        openGLWidget->setAutoFillBackground(true);
        lblEndGame = new QLabel(page);
        lblEndGame->setObjectName(QString::fromUtf8("lblEndGame"));
        lblEndGame->setGeometry(QRect(180, 140, 601, 151));
        QFont font;
        font.setPointSize(50);
        lblEndGame->setFont(font);
        lblEndGame->setAcceptDrops(false);
        lblEndGame->setAutoFillBackground(false);
        lblEndGame->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 47, 48);\n"
"border-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        lblEndGame->setFrameShape(QFrame::StyledPanel);
        lblEndGame->setAlignment(Qt::AlignCenter);
        lblEndGame->setWordWrap(false);
        lblEndGame->setIndent(0);
        lblHitsAndFrames = new QLabel(page);
        lblHitsAndFrames->setObjectName(QString::fromUtf8("lblHitsAndFrames"));
        lblHitsAndFrames->setGeometry(QRect(830, 760, 121, 91));
        QFont font1;
        font1.setPointSize(12);
        lblHitsAndFrames->setFont(font1);
        lblHitsAndFrames->setAcceptDrops(false);
        lblHitsAndFrames->setAutoFillBackground(false);
        lblHitsAndFrames->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 47, 48);\n"
"border-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        lblHitsAndFrames->setFrameShape(QFrame::Panel);
        lblHitsAndFrames->setFrameShadow(QFrame::Plain);
        lblHitsAndFrames->setScaledContents(false);
        lblHitsAndFrames->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lblHitsAndFrames->setWordWrap(false);
        lblHitsAndFrames->setMargin(10);
        lblHitsAndFrames->setIndent(0);
        btnRestart = new QPushButton(page);
        btnRestart->setObjectName(QString::fromUtf8("btnRestart"));
        btnRestart->setGeometry(QRect(410, 320, 121, 61));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 830, 561, 20));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(openGLWidget, SIGNAL(updateEndGameLabel(QString)), lblEndGame, SLOT(setText(QString)));
        QObject::connect(openGLWidget, SIGNAL(updateEndGameVisibility(bool)), lblEndGame, SLOT(setVisible(bool)));
        QObject::connect(openGLWidget, SIGNAL(updateFPSHit(QString)), lblHitsAndFrames, SLOT(setText(QString)));
        QObject::connect(openGLWidget, SIGNAL(updateRestartButton(bool)), btnRestart, SLOT(setVisible(bool)));
        QObject::connect(btnRestart, &QPushButton::clicked, openGLWidget, qOverload<>(&OpenGLWidget::restartButton));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Hit Shooter - Computa\303\247\303\243o Gr\303\241fica - Atividade 04", nullptr));
        lblEndGame->setText(QCoreApplication::translate("MainWindow", "YOU DIED!", nullptr));
        lblHitsAndFrames->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>FPS: x ms<br/>Hits Player: y<br/>Hits Enemy: x</p></body></html>", nullptr));
        btnRestart->setText(QCoreApplication::translate("MainWindow", "RESTART", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "W, A, S, D to move (or arrow keys). Space to shoot. Shooting while moving will result in a slower projectile.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
