#include "glwidget.h"
#include <QCoreApplication>
#include <QtCore>

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    //initialize class variables
    xRot = 0;
    yRot = 0;
    rotating = false;
}

void GLWidget::readCoordinates(){

    QFile file("C:/Users/Ted Huang/Desktop/Qt/openGL_imaging/XYZ.txt");
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
                if (list[i] != "")
                {
                    if (i==0){
                        point->setX((list[i].toFloat()/750));
                    }
                    if (i==1){
                        point->setY((list[i].toFloat()/750));
                    }
                    if (i==2){
                        point->setZ(list[i].toFloat()/750);
                    }
                    //collecting X, Y, and Z coordinates and scaling appropriately
                }
            }
            coordinates.push_back(*point);
            //add point to coordinates

        }while(!line.isNull());
        //while the line isn't blank, keep iterating

        file.close();
    }
}

void GLWidget::readConnectivity(){
    QFile file("C:/Users/Ted Huang/Desktop/CONN.txt");
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
                    if (i==0){
                        connection->setX(list[i].toFloat());
                    }
                    if (i==1){
                        connection->setY(list[i].toFloat());
                    }
                }
            }
            connectivity.push_back(*connection);

        }while(!line.isNull());
        //keep iterating until no more lines exist

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

    readCoordinates();
    readConnectivity();
    //initializing vectors

    glEnable(GL_POINT_SMOOTH);
    glColor3f(0, 0, 1);
    //set color to blue

    glBegin(GL_LINES);
        for (int i = 0; i < connectivity.size(); i++)
        {
            glVertex3f(coordinates[connectivity[i].x()-1].x(), coordinates[connectivity[i].x()-1].y(), coordinates[connectivity[i].x()-1].z());
            glVertex3f(coordinates[connectivity[i].y()-1].x(), coordinates[connectivity[i].y()-1].y(), coordinates[connectivity[i].y()-1].z());
        }
    glEnd();
    //draws connecting lines between vertices in blue

    glColor3f(1, 0, 0);
    //set color to blue

    glBegin(GL_POINTS);
        for (int i = 0; i < coordinates.size(); i++)
        {
            glVertex3f(coordinates[i].x(), coordinates[i].y(), coordinates[i].z());
        }
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


    glRotatef(xRot/16, 1, 0 ,0);
    glRotatef(yRot/16, 0, 1 ,0);
    //rotate by an amount of xRot and yRot, with appropriate scaling

    draw();
    //calls draw function
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


