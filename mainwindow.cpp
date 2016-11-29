#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QVector3D>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->xSlider->setRange(0, 360*16);
    ui->ySlider->setRange(0, 360*16);
    ui->zSlider->setRange(0, 360*16);
    //sets the ranges of the sliders

    connect(ui->xSlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setXRotation(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setYRotation(int)));
    connect(ui->zSlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setZRotation(int)));
    //when value of xSlider is changed, call setXRotation();
    //same with ySlider and zSlider

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
            close();
    //closes window upon pressing "Esc"
}


void MainWindow::on_Rotate_clicked()
{
    QCursor cursor;
    if(!(ui->widget->rotating)){

      cursor.setShape(Qt::ClosedHandCursor);
      ui->widget->rotating = true;
      ui->widget->zooming = false;
      //switch to rotating mode

      }
    else
      {

      cursor.setShape(Qt::ArrowCursor);
      ui->widget->rotating = false;
      //switch to non-rotating mode

      }
    this->setCursor(cursor);
    //switch cursor appearance
}

void MainWindow::on_Zoom_pressed()
{
    QCursor cursor;
    if(!(ui->widget->zooming)){

      cursor.setShape(Qt::SizeAllCursor);
      ui->widget->zooming = true;
      ui->widget->rotating = false;
      //switch to zooming mode

      }
    else
      {

      cursor.setShape(Qt::ArrowCursor);
      ui->widget->zooming = false;
      //switch to non-zooming mode

      }
    this->setCursor(cursor);
    //switch cursor appearance

}
