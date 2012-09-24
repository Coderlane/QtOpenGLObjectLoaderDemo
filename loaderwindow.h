#ifndef LOADERWINDOW_H
#define LOADERWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "visualizerwindow.h"

namespace Ui {
class LoaderWindow;
}

class LoaderWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LoaderWindow(QWidget *parent = 0);
    ~LoaderWindow();

private:
    Ui::LoaderWindow *ui;
    VisualizerWindow *visualizer;
    QString filename;

public slots:
    void visualizerClosed();
    
private slots:
    void on_launchButton_clicked();
    void on_objectButton_clicked();
};

#endif // LOADERWINDOW_H
