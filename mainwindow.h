#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();   

    void on_Reset_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);


private slots:

    void on_Rotate_clicked();

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
