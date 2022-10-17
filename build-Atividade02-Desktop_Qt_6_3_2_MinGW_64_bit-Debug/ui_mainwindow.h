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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QComboBox *comboBoxColor;
    QFrame *frame_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QStackedWidget *widgetSwitcher;
    QWidget *pageCirculo;
    QSpinBox *circuloRaio;
    QLabel *label_6;
    QSpinBox *circuloCentroY;
    QLabel *label_7;
    QSpinBox *circuloCentroX;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *pageRetangulo;
    QSpinBox *retanguloL1;
    QSpinBox *retanguloL2;
    QSpinBox *retanguloL3;
    QSpinBox *retanguloL4;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *pageReta;
    QSpinBox *retaL1;
    QLabel *label_14;
    QSpinBox *retaL2;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QSpinBox *retaL4;
    QSpinBox *retaL3;
    QLabel *label_18;
    QWidget *pageElipse;
    QSpinBox *elipseL1;
    QLabel *label_10;
    QSpinBox *elipseL2;
    QLabel *label_11;
    QSpinBox *elipseL3;
    QLabel *label_12;
    QSpinBox *elipseL4;
    QLabel *label_13;
    QWidget *pageRoundedRect;
    QSpinBox *roundedL4;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QSpinBox *roundedL2;
    QSpinBox *roundedL1;
    QLabel *label_22;
    QSpinBox *roundedL3;
    QLabel *label_23;
    QSpinBox *roundedX2;
    QLabel *label_24;
    QSpinBox *roundedX1;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(904, 602);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, -1, 491, 21));
        label->setAlignment(Qt::AlignCenter);
        comboBoxColor = new QComboBox(centralwidget);
        comboBoxColor->addItem(QString());
        comboBoxColor->addItem(QString());
        comboBoxColor->addItem(QString());
        comboBoxColor->addItem(QString());
        comboBoxColor->addItem(QString());
        comboBoxColor->setObjectName(QString::fromUtf8("comboBoxColor"));
        comboBoxColor->setGeometry(QRect(190, 530, 121, 24));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(540, 19, 351, 501));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(2);
        verticalLayoutWidget = new QWidget(frame_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 351, 271));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        widgetSwitcher = new QStackedWidget(verticalLayoutWidget);
        widgetSwitcher->setObjectName(QString::fromUtf8("widgetSwitcher"));
        pageCirculo = new QWidget();
        pageCirculo->setObjectName(QString::fromUtf8("pageCirculo"));
        circuloRaio = new QSpinBox(pageCirculo);
        circuloRaio->setObjectName(QString::fromUtf8("circuloRaio"));
        circuloRaio->setGeometry(QRect(20, 40, 71, 31));
        circuloRaio->setMinimum(10);
        circuloRaio->setMaximum(250);
        circuloRaio->setValue(250);
        label_6 = new QLabel(pageCirculo);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 20, 61, 20));
        circuloCentroY = new QSpinBox(pageCirculo);
        circuloCentroY->setObjectName(QString::fromUtf8("circuloCentroY"));
        circuloCentroY->setGeometry(QRect(130, 100, 71, 31));
        circuloCentroY->setMinimum(0);
        circuloCentroY->setMaximum(480);
        circuloCentroY->setValue(250);
        label_7 = new QLabel(pageCirculo);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 80, 61, 20));
        circuloCentroX = new QSpinBox(pageCirculo);
        circuloCentroX->setObjectName(QString::fromUtf8("circuloCentroX"));
        circuloCentroX->setGeometry(QRect(20, 100, 71, 31));
        circuloCentroX->setMinimum(0);
        circuloCentroX->setMaximum(480);
        circuloCentroX->setValue(250);
        label_8 = new QLabel(pageCirculo);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 100, 21, 31));
        label_9 = new QLabel(pageCirculo);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(210, 100, 61, 31));
        widgetSwitcher->addWidget(pageCirculo);
        pageRetangulo = new QWidget();
        pageRetangulo->setObjectName(QString::fromUtf8("pageRetangulo"));
        retanguloL1 = new QSpinBox(pageRetangulo);
        retanguloL1->setObjectName(QString::fromUtf8("retanguloL1"));
        retanguloL1->setGeometry(QRect(30, 40, 71, 31));
        retanguloL1->setMinimum(0);
        retanguloL1->setMaximum(480);
        retanguloL1->setValue(50);
        retanguloL2 = new QSpinBox(pageRetangulo);
        retanguloL2->setObjectName(QString::fromUtf8("retanguloL2"));
        retanguloL2->setGeometry(QRect(180, 40, 71, 31));
        retanguloL2->setMinimum(0);
        retanguloL2->setMaximum(480);
        retanguloL2->setValue(50);
        retanguloL3 = new QSpinBox(pageRetangulo);
        retanguloL3->setObjectName(QString::fromUtf8("retanguloL3"));
        retanguloL3->setGeometry(QRect(30, 100, 71, 31));
        retanguloL3->setMinimum(0);
        retanguloL3->setMaximum(480);
        retanguloL3->setValue(375);
        retanguloL4 = new QSpinBox(pageRetangulo);
        retanguloL4->setObjectName(QString::fromUtf8("retanguloL4"));
        retanguloL4->setGeometry(QRect(180, 100, 71, 31));
        retanguloL4->setMinimum(0);
        retanguloL4->setMaximum(480);
        retanguloL4->setValue(375);
        label_2 = new QLabel(pageRetangulo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 50, 49, 16));
        label_3 = new QLabel(pageRetangulo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(270, 50, 49, 16));
        label_4 = new QLabel(pageRetangulo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 110, 49, 16));
        label_5 = new QLabel(pageRetangulo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(270, 110, 49, 16));
        widgetSwitcher->addWidget(pageRetangulo);
        pageReta = new QWidget();
        pageReta->setObjectName(QString::fromUtf8("pageReta"));
        retaL1 = new QSpinBox(pageReta);
        retaL1->setObjectName(QString::fromUtf8("retaL1"));
        retaL1->setGeometry(QRect(30, 30, 71, 31));
        retaL1->setMinimum(0);
        retaL1->setMaximum(480);
        retaL1->setValue(50);
        label_14 = new QLabel(pageReta);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(270, 40, 49, 16));
        retaL2 = new QSpinBox(pageReta);
        retaL2->setObjectName(QString::fromUtf8("retaL2"));
        retaL2->setGeometry(QRect(180, 30, 71, 31));
        retaL2->setMinimum(0);
        retaL2->setMaximum(480);
        retaL2->setValue(50);
        label_15 = new QLabel(pageReta);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(110, 40, 49, 16));
        label_16 = new QLabel(pageReta);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(270, 110, 49, 16));
        label_17 = new QLabel(pageReta);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(110, 110, 49, 16));
        retaL4 = new QSpinBox(pageReta);
        retaL4->setObjectName(QString::fromUtf8("retaL4"));
        retaL4->setGeometry(QRect(180, 100, 71, 31));
        retaL4->setMinimum(0);
        retaL4->setMaximum(480);
        retaL4->setValue(450);
        retaL3 = new QSpinBox(pageReta);
        retaL3->setObjectName(QString::fromUtf8("retaL3"));
        retaL3->setGeometry(QRect(30, 100, 71, 31));
        retaL3->setMinimum(0);
        retaL3->setMaximum(480);
        retaL3->setValue(450);
        label_18 = new QLabel(pageReta);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(30, 150, 201, 31));
        widgetSwitcher->addWidget(pageReta);
        pageElipse = new QWidget();
        pageElipse->setObjectName(QString::fromUtf8("pageElipse"));
        elipseL1 = new QSpinBox(pageElipse);
        elipseL1->setObjectName(QString::fromUtf8("elipseL1"));
        elipseL1->setGeometry(QRect(30, 40, 71, 31));
        elipseL1->setMinimum(0);
        elipseL1->setMaximum(480);
        elipseL1->setValue(35);
        label_10 = new QLabel(pageElipse);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(110, 50, 49, 16));
        elipseL2 = new QSpinBox(pageElipse);
        elipseL2->setObjectName(QString::fromUtf8("elipseL2"));
        elipseL2->setGeometry(QRect(180, 40, 71, 31));
        elipseL2->setMinimum(0);
        elipseL2->setMaximum(480);
        elipseL2->setValue(175);
        label_11 = new QLabel(pageElipse);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(270, 50, 49, 16));
        elipseL3 = new QSpinBox(pageElipse);
        elipseL3->setObjectName(QString::fromUtf8("elipseL3"));
        elipseL3->setGeometry(QRect(30, 100, 71, 31));
        elipseL3->setMinimum(0);
        elipseL3->setMaximum(480);
        elipseL3->setValue(400);
        label_12 = new QLabel(pageElipse);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(270, 110, 49, 16));
        elipseL4 = new QSpinBox(pageElipse);
        elipseL4->setObjectName(QString::fromUtf8("elipseL4"));
        elipseL4->setGeometry(QRect(180, 100, 71, 31));
        elipseL4->setMinimum(0);
        elipseL4->setMaximum(480);
        elipseL4->setValue(100);
        label_13 = new QLabel(pageElipse);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(110, 110, 49, 16));
        widgetSwitcher->addWidget(pageElipse);
        pageRoundedRect = new QWidget();
        pageRoundedRect->setObjectName(QString::fromUtf8("pageRoundedRect"));
        roundedL4 = new QSpinBox(pageRoundedRect);
        roundedL4->setObjectName(QString::fromUtf8("roundedL4"));
        roundedL4->setGeometry(QRect(180, 80, 71, 31));
        roundedL4->setMinimum(0);
        roundedL4->setMaximum(480);
        roundedL4->setValue(375);
        label_19 = new QLabel(pageRoundedRect);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(110, 90, 49, 16));
        label_20 = new QLabel(pageRoundedRect);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(270, 30, 49, 16));
        label_21 = new QLabel(pageRoundedRect);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(110, 30, 49, 16));
        roundedL2 = new QSpinBox(pageRoundedRect);
        roundedL2->setObjectName(QString::fromUtf8("roundedL2"));
        roundedL2->setGeometry(QRect(180, 20, 71, 31));
        roundedL2->setMinimum(0);
        roundedL2->setMaximum(480);
        roundedL2->setValue(50);
        roundedL1 = new QSpinBox(pageRoundedRect);
        roundedL1->setObjectName(QString::fromUtf8("roundedL1"));
        roundedL1->setGeometry(QRect(30, 20, 71, 31));
        roundedL1->setMinimum(0);
        roundedL1->setMaximum(480);
        roundedL1->setValue(50);
        label_22 = new QLabel(pageRoundedRect);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(270, 90, 49, 16));
        roundedL3 = new QSpinBox(pageRoundedRect);
        roundedL3->setObjectName(QString::fromUtf8("roundedL3"));
        roundedL3->setGeometry(QRect(30, 80, 71, 31));
        roundedL3->setMinimum(0);
        roundedL3->setMaximum(480);
        roundedL3->setValue(375);
        label_23 = new QLabel(pageRoundedRect);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(270, 150, 49, 16));
        roundedX2 = new QSpinBox(pageRoundedRect);
        roundedX2->setObjectName(QString::fromUtf8("roundedX2"));
        roundedX2->setGeometry(QRect(180, 140, 71, 31));
        roundedX2->setMinimum(0);
        roundedX2->setMaximum(500);
        roundedX2->setValue(100);
        label_24 = new QLabel(pageRoundedRect);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(110, 150, 49, 16));
        roundedX1 = new QSpinBox(pageRoundedRect);
        roundedX1->setObjectName(QString::fromUtf8("roundedX1"));
        roundedX1->setGeometry(QRect(30, 140, 71, 31));
        roundedX1->setMinimum(0);
        roundedX1->setMaximum(500);
        roundedX1->setValue(100);
        widgetSwitcher->addWidget(pageRoundedRect);

        verticalLayout_2->addWidget(widgetSwitcher);

        frame = new QFrame(verticalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 904, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        widgetSwitcher->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Atividade 02", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">\303\201REA DE DESENHO</span></p></body></html>", nullptr));
        comboBoxColor->setItemText(0, QCoreApplication::translate("MainWindow", "White", nullptr));
        comboBoxColor->setItemText(1, QCoreApplication::translate("MainWindow", "Black", nullptr));
        comboBoxColor->setItemText(2, QCoreApplication::translate("MainWindow", "Red", nullptr));
        comboBoxColor->setItemText(3, QCoreApplication::translate("MainWindow", "Green", nullptr));
        comboBoxColor->setItemText(4, QCoreApplication::translate("MainWindow", "Blue", nullptr));

        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Clear", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "C\303\255rculo", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Ret\303\242ngulo", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Reta", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Elipse", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Ret\303\242ngulo com bordas arredondadas", nullptr));

#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QCoreApplication::translate("MainWindow", "Selecione uma figura geom\303\251trica e edite suas propriedades correspondentes.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("MainWindow", "Raio", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Centro", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "P1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "P2", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "P3", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "P4", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Y1", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "X1", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Y2", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "X2", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "*Voc\303\252 n\303\243o ver\303\241 a cor branca.", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "P1", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "P2", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "P4", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "P3", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "P3", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "P2", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "P1", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "P4", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "X2", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "X1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
