#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <GL/glu.h>
#include <cmath>

struct Vertex
{
    float x;
    float y;
    float z;
};
struct Triangle
{
    Vertex a;
    Vertex b;
    Vertex c;
};

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void setupScene();
    Vertex calculateNormal(Vertex a, Vertex b, Vertex c);

    GLuint loadFile(QString file);
    void drawObject(GLuint obj, float dx, float dy, float dz);

    GLuint objectID;
    QString fileName;

    /*
    vector<glm::vec4> suzanne_vertices;
    vector<glm::vec3> suzanne_normals;
    vector<GLushort> suzanne_elements;
    */

private:
    
signals:
    
public slots:
    void setFileName(QString file);
    
};

#endif // GLWIDGET_H
