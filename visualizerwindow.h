#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QMainWindow>


const float MAX_ZOOM = 5;

namespace Ui {
class VisualizerWindow;
}

class VisualizerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VisualizerWindow(QWidget *parent = 0, QString filename = "");
    ~VisualizerWindow();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QString filename;
    Ui::VisualizerWindow *ui;
};

#endif // VISUALIZERWINDOW_H
