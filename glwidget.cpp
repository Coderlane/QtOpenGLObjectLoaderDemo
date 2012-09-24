#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    fileName = ":/resources/monkey.obj";
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

    setupScene();
}
void GLWidget::paintGL()
{
    // Background and clearing
    qglClearColor(QColor(Qt::black));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Show Text
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText( 10,  9 , 0, "Object Demo", QFont("Ubuntu", 30, 10, false));

    glColor3f(0.0f, 1.0f, 0.0f);
    drawObject(objectID, 0, 0, 0);
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
    glTranslated(0.0, 0.0, -50);
}

void GLWidget::setupScene()
{
    objectID = loadFile(fileName);
}


GLuint GLWidget::loadFile(QString fn)
{
    bool loaded = false;
    QString line;
    QTextStream lineStream;
    QFile file(fn);
    QVector<Vertex> verti;
    QVector<Triangle> triangleFaces;
    QVector<Vertex> normals;
    if(file.isOpen())
    {

        while (!file.atEnd())											// Start reading file data
        {

            line = file.readLine(99999999);
            lineStream.setString(&line);
            if(line.at(0) == 'v')
            {
                float x = 0, y = 0, z = 0;
                line[0] = ' ';
                lineStream >> x >> y >> z;
                verti.append((struct Vertex) {x, y, z});
            }
            else if(line.at(0) == 'f')
            {
                line[0] = ' ';
                int vertexNumber[4] = { 0, 0, 0 };
                lineStream >> vertexNumber[0] >> vertexNumber[1] >> vertexNumber[2];
                vertexNumber[0] -= 1;
                vertexNumber[1] -= 1;
                vertexNumber[2] -= 1;
                triangleFaces.append((struct Triangle) {verti.at(vertexNumber[0]), verti.at(vertexNumber[1]), verti.at(vertexNumber[2])});
                normals.append(calculateNormal(triangleFaces.last().a, triangleFaces.last().b, triangleFaces.last().c));
            }
            else
            {
                  // Do nothing
            }
        }
        loaded = true;
    }
    else
    {

    }
    if(loaded)
    {
        GLuint list = glGenLists(1);
        glNewList(list, GL_COMPILE);


        glEndList();
        return list;
    }
    else
    {
        GLuint list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        glColor3f(1.0f, 0.0f, 0.0f);
        renderText( 0,  0 , 0, "ERROR LOADING FILE", QFont("Ubuntu", 30, 10, false));
        glEndList();
        return list;
    }
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
Vertex GLWidget::calculateNormal(Vertex a, Vertex b, Vertex c)
{
    /* calculate Vector1 and Vector2 */
    float va[3], vb[3], vr[3], val;

    va[0] = a.x - b.x;
    va[1] = a.y - b.y;
    va[2] = a.z - b.z;

    vb[0] = a.x - c.x;
    vb[1] = a.y - c.y;
    vb[2] = a.z - c.z;

    /* cross product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    /* normalization factor */
    val = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );

    return ((struct Vertex) {vr[0]/val, vr[1]/val, vr[2]/val});
}
