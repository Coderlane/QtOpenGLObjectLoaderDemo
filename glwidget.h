#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QFile>
#include <QTimer>
#include <GL/glu.h>
#include "Model.h"
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void setZoom(float zoom);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    GLuint loadFile(QString file);
    void drawObject(GLuint obj, float dx, float dy, float dz);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);


    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void normalizeAngle(int *angle);

private:
    QPoint lastPos;
    GLuint objectID;
    QString fileName;
    oGlModel mod;
    QTimer *timer;

    int xRot;
    int yRot;
    int zRot;

    float zoom;
    
signals:
    void emitClose();

public slots:
    void loop();
    void setupScene(QString fileName);
    
};

#endif // GLWIDGET_H
