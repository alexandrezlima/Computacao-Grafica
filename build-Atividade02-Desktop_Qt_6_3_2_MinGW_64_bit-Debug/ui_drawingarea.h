/********************************************************************************
** Form generated from reading UI file 'drawingarea.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWINGAREA_H
#define UI_DRAWINGAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_drawingArea
{
public:
    QLabel *label;

    void setupUi(QWidget *drawingArea)
    {
        if (drawingArea->objectName().isEmpty())
            drawingArea->setObjectName(QString::fromUtf8("drawingArea"));
        drawingArea->resize(400, 300);
        label = new QLabel(drawingArea);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 130, 49, 16));

        retranslateUi(drawingArea);

        QMetaObject::connectSlotsByName(drawingArea);
    } // setupUi

    void retranslateUi(QWidget *drawingArea)
    {
        drawingArea->setWindowTitle(QCoreApplication::translate("drawingArea", "Form", nullptr));
        label->setText(QCoreApplication::translate("drawingArea", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class drawingArea: public Ui_drawingArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWINGAREA_H
