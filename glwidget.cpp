#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    timer = new QTimer(this);
    timer->setInterval(20);
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    timer->stop();
}

void GLWidget::loop()
{
    updateGL();
}

void GLWidget::initializeGL()
{
    // Init Stuff
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}
void GLWidget::paintGL()
{
    // Background and clearing
    qglClearColor(QColor(Qt::black));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Show Text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText( 10,  9 , 0, "Object Demo", QFont("Ubuntu", 30, 10, false));
    renderText( -9,  9 , 0, "File:" + fileName, QFont("Ubuntu", 30, 10, false));
    glPopMatrix();

    glPushMatrix();
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawObject(objectID, 0, 0, 0);
    glPopMatrix();
}
void GLWidget::resizeGL(int width, int height)
{
    // Safety Check! Wear your hard hat
    if(width == 0)
        width = 1;
    if(height == 0)
        height = 1;
    double ratio = (width>height?((double)width/(double)height):((double)height/(double)width));
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f,ratio,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -50.0);
}

void GLWidget::setupScene(QString fn)
{
   fileName = fn;
   objectID = loadFile(fn);
   timer->start();
}

GLuint GLWidget::loadFile(QString fn)
{
    //mod.load("mini_obj.obj");
    mod.load(fn.toUtf8().constData());
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    for(int i = 0; i < mod.faces.size(); i++)
    {
        switch(mod.faces[i].vtnPairs.size())
        {
            case 3:
                glBegin(GL_TRIANGLES);
                break;
            case 4:
                glBegin(GL_QUADS);
                break;
            case 5:
                glBegin(GL_POLYGON);
                break;
        }

        for(int j = 0; j < mod.faces[i].vtnPairs.size(); j++)
        {
            //the info for the normals and textures is in the same spot, im just not using it right now
            oGlVertex vert = mod.vertexes[mod.faces[i].vtnPairs[j].vert-1];
            glVertex3f(vert.x,vert.y, vert.z);
        }
        glEnd();
    }

    glEndList();
    return list;
}


void GLWidget::drawObject(GLuint obj, float dx, float dy, float dz)
{
    glPushMatrix();
    glTranslated(dx, dy, dz);
    glCallList(obj);
    glPopMatrix();
}
void GLWidget::setFileName(QString file)
{
    fileName = file;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    setCursor(Qt::ClosedHandCursor);
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}
void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}
void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}
void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
