#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    zoom = 0;
    // Setup the timer (Main Loop)
    timer = new QTimer(this);
    timer->setInterval(60);
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    timer->stop();
}

void GLWidget::loop()
{
    // Nothing to do here, just redraw
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


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  LightAmbient);

}
void GLWidget::paintGL()
{
    // Background and clearing
    qglClearColor(QColor(Qt::black));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();
    //glTranslated(0.0,0.0,0.0);
    glTranslated(LightPosition[0],LightPosition[1], LightPosition[2]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glPopMatrix();

    // Show Text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    //renderText( 10,  9 , 0, "Object Demo", QFont("Ubuntu", 30, 10, false));
    renderText( -9,  9 , 0, "File:" + fileName, QFont("Ubuntu", 30, 10, false));
    glPopMatrix();

    // For Zooming
    glTranslated(0.0, 0.0, zoom);

    // Rotate the screen if necessary and then draw the object from the list
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
    // Setup the viewport for the new size
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f,ratio,0.1f,800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -50.0);
}

void GLWidget::setupScene(QString fn)
{
    // Set the filename and start the timer
    fileName = fn;
    objectID = loadFile(fn);
    timer->start();
}
GLuint GLWidget::loadFile(QString fn)
{
    // Load the file
    mod.load(fn.toUtf8().constData());

    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    int materialIndex = -1;



    for(int i = 0; i < mod.faces.size(); i++)
    {
        //check for proper material to use
        if(materialIndex < (int)mod.matIndexes.size() - 1) //typecasting unsigned to signed int
        {
            if(i >= mod.matIndexes[materialIndex+1].fIndex)
            {
                //apply materiel.
                materialIndex++;
                int tempI = mod.matIndexes[materialIndex].matIndex;
                if(tempI != -1)
                {
                glMaterialfv(GL_FRONT, GL_AMBIENT,OGVTF mod.materials[tempI].Ka);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, OGVTF mod.materials[tempI].Kd);
                glMaterialfv(GL_FRONT, GL_SPECULAR,OGVTF mod.materials[tempI].Ks);
                glMaterialf(GL_FRONT, GL_SHININESS, mod.materials[tempI].Ns);
                }
            }
        }
        //

        switch(mod.faces[i].vtnPairs.size())
        {
        case 3:
            glBegin(GL_TRIANGLES);
            break;
        case 4:
            glBegin(GL_QUADS);
            break;
        default:
            glBegin(GL_POLYGON);
            break;
        }

        if(mod.faces[i].vtnPairs[0].norm > 0)
        {
            oGlVertex norm = mod.normalVectors[mod.faces[i].vtnPairs[0].norm-1];
            glNormal3fv(OGVTF norm);
        }
        else
        {
            oGlVertex norm = mod.calcNormal(mod.vertexes[mod.faces[i].vtnPairs[0].vert-1], mod.vertexes[mod.faces[i].vtnPairs[1].vert-1],mod.vertexes[mod.faces[i].vtnPairs[2].vert-1]);
            glNormal3fv(OGVTF norm);
        }

        for(int j = 0; j < mod.faces[i].vtnPairs.size(); j++)
        {
            if(mod.faces[i].vtnPairs[j].tex > 0)
            {
                oGlVertex tex = mod.textureCoords[mod.faces[i].vtnPairs[j].tex-1];
                glTexCoord3fv(OGVTF tex);
            }
            oGlVertex vert = mod.vertexes[mod.faces[i].vtnPairs[j].vert-1];
            glVertex3fv(OGVTF vert);

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

void GLWidget::setZoom(float z)
{
    zoom = z;
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
