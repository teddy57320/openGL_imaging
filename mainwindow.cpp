#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QVector3D>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widget, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->widget, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));


    ui->xSlider->setRange(0, 360*16);
    ui->ySlider->setRange(0, 360*16);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Reset_clicked()
{

    /*ui->widget->xRot = -(ui->widget->x_displace);
    ui->widget->yRot = -(ui->widget->y_displace);
    update();*/

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
            close();
        else
        QWidget::keyPressEvent(event);
}



void MainWindow::on_Rotate_clicked()
{


    QCursor cursor;
    if(!(ui->widget->rotating))
      {
      cursor.setShape(Qt::ClosedHandCursor);
      ui->widget->rotating = true;
      }
    else
      {
      cursor.setShape(Qt::ArrowCursor);
      ui->widget->rotating = false;
      }
    this->setCursor(cursor);

}
