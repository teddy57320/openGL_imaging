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


protected:
    void keyPressEvent(QKeyEvent *event);
    //enables closing with "Esc" key


private slots:

    void on_Rotate_clicked();
    //toggles between non-rotating and rotating mode

    void on_Zoom_pressed();

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
