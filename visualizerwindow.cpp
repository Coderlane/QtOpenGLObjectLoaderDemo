#include "visualizerwindow.h"
#include "ui_visualizerwindow.h"

VisualizerWindow::VisualizerWindow(QWidget *parent, QString newFile) : QMainWindow(parent), ui(new Ui::VisualizerWindow)
{
    ui->setupUi(this);
    showFullScreen();
    filename = newFile;
    ui->glWidget->setupScene(filename);
}

VisualizerWindow::~VisualizerWindow()
{
    delete ui;
}
