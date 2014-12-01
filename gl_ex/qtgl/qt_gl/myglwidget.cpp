#include <QtOpenGL>
#include <QMouseEvent>
#include <QWheelEvent>
#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(),parent)
{
    alpha = 25;
    beta = -25;
    distance = 2.5;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(640, 480);
}

void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    qglClearColor(QColor(Qt::black));
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    static GLfloat lightPosition[4] = { 5, 5, 5, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();

    vertices << QVector3D(1,0,-2) << QVector3D(0,1,-2) << QVector3D(-1,0,-2);
}

void MyGLWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

void MyGLWidget::paintGL()
{
    QMatrix4x4 mMatrix, vMatrix;

    QMatrix4x4 camTrans;
    camTrans.rotate(alpha,0,1,0);
    camTrans.rotate(beta,1,0,0);

    QVector3D camPos = camTrans * QVector3D(0,0,distance);
    QVector3D camUpDir = camTrans * QVector3D(0,1,0);

    vMatrix.lookAt(camPos, QVector3D(0,0,0), camUpDir);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    shaderProgram.bind();
    shaderProgram.setUniformValue("mvpMatrix",pMatrix*vMatrix*mMatrix);
    shaderProgram.setUniformValue("color",QColor(Qt::red));

    shaderProgram.setAttributeArray("vertex", vertices.constData());
    shaderProgram.enableAttributeArray("vertex");

    glDrawArrays(GL_TRIANGLES,0,vertices.size());

    shaderProgram.disableAttributeArray("vertex");
    shaderProgram.release();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    event->accept();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dX = event->x() - lastPos.x();
    int dY = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        alpha += dX;
        while (alpha<0)
        {
            alpha += 360;
        }

        while (alpha>=360)
        {
            alpha -= 360;
        }

        beta += dY;

        if (beta<-90)
        {
            beta = -90;
        }

        if (beta>90)
        {
            beta = 90;
        }
    }

    updateGL();
    lastPos = event->pos();
    event->accept();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical)
    {
        if (delta<0)
        {
            distance *= 1.1;
        } else if (delta>0)
        {
            distance *= 0.9;
        }
        updateGL();
    }

    event->accept();
}
