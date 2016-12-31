#include "glwidget.h"
#include <QCoreApplication>
#include <QtCore>

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    xZoom = 1;
    yZoom = 1;
    zZoom = 1;
    rotating = false;
    zooming = false;
    //initialize class variables

    readCoordinates();
    readConnectivity();
    //initialize vectors
}

void GLWidget::readCoordinates(){

    QFile file("C:/Users/Ted Huang/Desktop/Git/qt_openGL_imaging/XYZ.txt");
    //finds file containing coordinates
    //***directory should be changed accordingly****

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString line;

        //iterating through each line
        do
        {
            line = stream.readLine();
            line = line.replace('\t', ' ');
            QStringList list = line.split(' ');
            //manipulates text file to create a list of numbers

            QVector3D *point = new QVector3D();
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i] != ""){
                    if (i==0){
                        float x = list[i].toFloat()/750;
                        point->setX(x);
                    }
                    if (i==1){
                        float y = list[i].toFloat()/750;
                        point->setY(y);
                    }
                    if (i==2){
                        float z = list[i].toFloat()/750;
                        point->setZ(z);
                    }
                    //collecting X, Y, and Z coordinates and scaling appropriately (dividing by 750)
                    //scaling should be changed depending on magnitude of coordinates
                }
            }
            coordinates.push_back(*point);
            //add point to coordinates

        }while(!line.isNull());
        //keep iterating until the last line is reached
    }
}

void GLWidget::readConnectivity(){
    QFile file("C:/Users/Ted Huang/Desktop/Git/qt_openGL_imaging/CONN.txt");
    //finds file containing connectivity instructions
    //***directory should be changed accordingly****

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        QString line;
        do
        {
            line = stream.readLine();
            line = line.replace('\t', ' ');
            QStringList list = line.split(' ');
            //creates list of numbers in each line

            QVector2D *connection = new QVector2D();
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i] != "")
                {
                    if (i==0)
                        connection->setX(list[i].toFloat());
                    if (i==1)
                        connection->setY(list[i].toFloat());
                }
            }
            connectivity.push_back(*connection);

        }while(!line.isNull());
        //keep iterating until the last line is reached

        file.close();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *ev)
{
    if(rotating){
        lastPos = ev -> pos();
    }
    //when in rotation mode: if mouse is pressed, then store
    //the current mouse position

    if(zooming){
        if (ev->buttons() & Qt::LeftButton)
        {
            xZoom = xZoom * 1.5;
            yZoom = yZoom * 1.5;
            zZoom = zZoom * 1.5;
            update();
        }
        if (ev->buttons() & Qt::RightButton)
        {
            xZoom = xZoom * 2/3;
            yZoom = yZoom * 2/3;
            zZoom = zZoom * 2/3;
            update();
        }
    }
    //when in zooming mode: if left mouse button is pressed, increase zoom factor
    //if right mouse button is pressed, decrease zoom factor
}

void GLWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(rotating){
        int dx = ev->x() - lastPos.x();
        int dy = ev->y() - lastPos.y();

        if (ev->buttons() & Qt::LeftButton) {
            setXRotation(xRot + 8 * dy);
            setYRotation(yRot + 8 * dx);
        }
        //sets xRot and yRot based on deviation of current position
        //with lastPos

        lastPos = ev->pos();
    }
}

void GLWidget::draw()
{

    initializeOpenGLFunctions();
    glEnable(GL_POINT_SMOOTH);

    glColor3f(0, 0, 1);
    //set color to blue

    glBegin(GL_LINES);
        for (unsigned int i = 0; i < connectivity.size(); i++)
        {
            int index1 = connectivity[i].x();
            int index2 = connectivity[i].y();
            //indices of the points in the coordinates vector

            glVertex3f(coordinates[index1].x(), coordinates[index1].y(), coordinates[index1].z());
            glVertex3f(coordinates[index2].x(), coordinates[index2].y(), coordinates[index2].z());
            //draw a connecting line between the first and second coordinate
        }
    glEnd();

    glColor3f(1, 0, 0);
    //set color to red

    glBegin(GL_POINTS);
        for (unsigned int i = 0; i < coordinates.size(); i++)
            glVertex3f(coordinates[i].x(), coordinates[i].y(), coordinates[i].z());
    glEnd();
    //draws the vertices in red

    glDisable(GL_POINT_SMOOTH);
}

void GLWidget::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(1, 1, 1, 1);
    //sets background color white
}

void GLWidget::paintGL(){

    initializeOpenGLFunctions();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glScalef(xZoom, yZoom, zZoom);
    //apply zooming factor

    glRotatef(xRot/16, 1, 0 ,0);
    glRotatef(yRot/16, 0, 1 ,0);
    glRotatef(zRot/16, 0, 0, 1);
    //rotate by an amount of xRot, yRot, and zRot, with appropriate scaling

    draw();
}

void GLWidget::resizeGL(int w, int h){

    initializeOpenGLFunctions();
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_3D);
    glEnable(GL_BLEND);

    update();
    //defines default resize function
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
    //makes it so that 0 <= angle <= 360
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
    //changes xRot and updates the image
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
    //changes yRot and updates the image
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }
    //changes yRot and updates the image
}
