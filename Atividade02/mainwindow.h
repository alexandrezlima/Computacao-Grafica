#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void drawBackgroundArea();
    Qt::GlobalColor getQColor();
    void updateCirculo();
    void updateRetangulo();
    void updateReta();
    void updateElipse();
    void updateRounded();
    void limpaFigura();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_circuloRaio_valueChanged(int arg1);

    void on_circuloRaio_2_valueChanged(int arg1);

    void on_circuloCentroY_valueChanged(int arg1);

    void on_circuloCentroX_valueChanged(int arg1);

    void on_comboBoxColor_currentIndexChanged(int index);

    void on_retanguloL1_valueChanged(int arg1);

    void on_retanguloL2_valueChanged(int arg1);

    void on_retanguloL3_valueChanged(int arg1);

    void on_retanguloL4_valueChanged(int arg1);

    void on_elipseL1_valueChanged(int arg1);

    void on_elipseL2_valueChanged(int arg1);

    void on_elipseL3_valueChanged(int arg1);

    void on_elipseL4_valueChanged(int arg1);

    void on_retaL1_valueChanged(int arg1);

    void on_retaL2_valueChanged(int arg1);

    void on_retaL3_valueChanged(int arg1);

    void on_retaL4_valueChanged(int arg1);

    void on_roundedL1_valueChanged(int arg1);

    void on_roundedL2_valueChanged(int arg1);

    void on_roundedL3_valueChanged(int arg1);

    void on_roundedL4_valueChanged(int arg1);

    void on_roundedX1_valueChanged(int arg1);

    void on_roundedX2_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int currentDrawType{0};

};
#endif // MAINWINDOW_H
