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
    //set the range of the slider
    //"xSlider" and "ySlider" are the custom set names of the sliders

    connect(ui->xSlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setXRotation(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setYRotation(int)));
    //when slider value is changed --> call setXRotation or setYRotation
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
