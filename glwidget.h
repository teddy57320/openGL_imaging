#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QtGui>
#include <Qvector>
#include <QMouseEvent>
#include <QOpenGLFunctions_3_2_Compatibility>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_2_Compatibility
{
    Q_OBJECT
public:

    explicit GLWidget(QWidget *parent = 0);

    void readCoordinates();
    //reads XYZ file to obtain XYZ coordinates of all the points (from "XYZ.txt")

    void readConnectivity();
    //reads instructions on how to connect the individual points (from "CONN.txt")

    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    //used to implement rotation with mouse

    std::vector<QVector3D> coordinates;
    std::vector<QVector2D> connectivity;
    //vectors holding the coordinates and connectivty relations

    double xRot, yRot, zRot;
    //angle of rotation of original image

    double xZoom, yZoom, zZoom;
    //factor of zooming

    bool rotating, zooming;
    //used to enter and exit rotation mode with mouse

private:

    void draw();
    //default openGL function

    QPoint lastPos;
    //stores last position of the mouse

protected:

    void initializeGL();
    //default openGL function

    void paintGL();
    //default openGL function

    void resizeGL(int w, int h);
    //default openGL function

public slots:

    void setXRotation(int angle);
    //modifies xRot

    void setYRotation(int angle);
    //modifies yRot

    void setZRotation(int angle);
    //modifies zRot
};

#endif // GLWIDGET_H
