#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QMainWindow>

namespace Ui {
class VisualizerWindow;
}

class VisualizerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VisualizerWindow(QWidget *parent = 0);
    ~VisualizerWindow();
    
private:
    Ui::VisualizerWindow *ui;
};

#endif // VISUALIZERWINDOW_H
