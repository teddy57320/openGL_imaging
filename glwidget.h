#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include <QMouseEvent>
#include <QOpenGLFunctions_3_2_Compatibility>


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_2_Compatibility
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void readCoordinates();
    void readConnectivity();


    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

    std::vector<QVector3D> coordinates;
    std::vector<QVector2D> connectivity;


    double x_displace, y_displace;

    double xRot, yRot;

    bool rotating;

private:

    void draw();

    QPoint lastPos;

protected:


    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

public slots:

    void setXRotation(int angle);
    void setYRotation(int angle);

signals:

    void xRotationChanged(double angle);
    void yRotationChanged(double angle);

};

#endif // GLWIDGET_H
