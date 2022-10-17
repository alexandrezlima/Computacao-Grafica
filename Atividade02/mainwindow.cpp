#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widgetSwitcher->setHidden(true);
    ui->comboBoxColor->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    drawBackgroundArea();


    switch (currentDrawType)
    {
    case 0:
        //Faz o update para apagar o desenho. Oculta a página de configurações da figura.
        break;
    case 1:
        //Faz o update para desenhar o círculo
        updateCirculo();
        break;
    case 2:
        //Faz o update para desenhar o retângulo
        updateRetangulo();
        break;
    case 3:
        //Faz o update para desenhar o triângulo
        updateReta();
        break;
    case 4:
        //Faz o update para desenhar elipse
        updateElipse();
        break;
    case 5:
        //Faz o update para desenhar um polígono
        updateRounded();
        break;
    }
}

void MainWindow::drawBackgroundArea()
{
    //Desenha a área quadrada na qual o desenho será incluído. Apenas por motivos estéticos.

    //x1=20, y1=20; x2=500, y2=500 são os extremos da área onde o desenho será criado.
    QPainter painter(this);

    //FillRect colore o fundo com cor branca.
    painter.fillRect(20, 20, 500, 500, Qt::white);

    //drawRect desenha as margens da "área desenhável".
    painter.drawRect(20, 20, 500, 500);
}

//Retorna a cor equivalente ao index do combo box.
Qt::GlobalColor MainWindow::getQColor()
{
    switch (ui->comboBoxColor->currentIndex())
    {
    case 0:
        return Qt::white;
    case 1:
        return Qt::black;
    case 2:
        return Qt::red;
    case 3:
        return Qt::green;
    case 4:
        return Qt::blue;
    }
}

//Desenha o círculo utilizando as informações relacionadas ao círculo.
void MainWindow::updateCirculo()
{

    QPainter painter(this);

    int x = ui->circuloCentroX->value() + 40; //Adiciona o offset em x.
    int y = ui->circuloCentroY->value() + 40; //Adiciona o offset em y.

    int raio = ui->circuloRaio->value();

    painter.setBrush(getQColor());
    painter.drawEllipse((x-raio)/2, (y-raio)/2, raio*2, raio*2);
}

//Desenha o retângulo utilizando as informações relacionadas ao retângulo.
void MainWindow::updateRetangulo()
{
    QPainter painter(this);

    int l1 = ui->retanguloL1->value() + 20;
    int l2 = ui->retanguloL2->value() + 20;
    int l3 = ui->retanguloL3->value() + 20;
    int l4 = ui->retanguloL4->value() + 20;

    painter.setBrush(getQColor());
    painter.drawRect(l1, l2, l3, l4);

}

//Desenha a reta utilizando as informações relacionadas à reta. A reta na cor branca se mistura ao background, não podendo ser enxergada.
void MainWindow::updateReta()
{
    QPainter painter(this);

    int l1 = ui->retaL1->value() + 20;
    int l2 = ui->retaL2->value() + 20;
    int l3 = ui->retaL3->value() + 20;
    int l4 = ui->retaL4->value() + 20;

    painter.setPen(getQColor());
    painter.drawLine(l1, l2, l3, l4);
}

//Desenha a elipse utilizando as informações relacionadas à elipse.
void MainWindow::updateElipse()
{

    QPainter painter(this);

    int l1 = ui->elipseL1->value() + 20;
    int l2 = ui->elipseL2->value() + 20;
    int l3 = ui->elipseL3->value() + 20;
    int l4 = ui->elipseL4->value() + 20;

    painter.setBrush(getQColor());
    painter.drawEllipse(l1, l2, l3, l4);
}

//Desenha um retângulo de bordas arredondadas utilizando as informações relacionadas a este retângulo e os ângulos de suas bordas.
void MainWindow::updateRounded()
{

    QPainter painter(this);

    int l1 = ui->roundedL1->value() + 20;
    int l2 = ui->roundedL2->value() + 20;
    int l3 = ui->roundedL3->value() + 20;
    int l4 = ui->roundedL4->value() + 20;

    int x1 = ui->roundedX1->value();
    int x2 = ui->roundedX2->value();


    painter.setBrush(getQColor());
    painter.drawRoundedRect(l1, l2, l3, l4, x1, x2);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //Mostra ou oculta a tela de informações da figura.
    ui->widgetSwitcher->setHidden(!index);
    ui->comboBoxColor->setHidden(!index);

    //Altera o index do switcher para exibir os boxes correspondentes à figura
    ui->widgetSwitcher->setCurrentIndex(index-1);
    currentDrawType = index;
    update();
}

//FUNÇÕES PARA UPDATE DO DESENHO.
void MainWindow::on_circuloRaio_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_circuloCentroX_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_circuloCentroY_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_comboBoxColor_currentIndexChanged(int index)
{
    update();
}

void MainWindow::on_circuloRaio_2_valueChanged(int arg1)
{

}

void MainWindow::on_retanguloL1_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retanguloL2_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retanguloL3_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retanguloL4_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_elipseL1_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_elipseL2_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_elipseL3_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_elipseL4_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retaL1_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retaL2_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retaL3_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_retaL4_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_roundedL1_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_roundedL2_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_roundedL3_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_roundedL4_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_roundedX1_valueChanged(int arg1)
{
    update();
}

void MainWindow::on_roundedX2_valueChanged(int arg1)
{
    update();
}

