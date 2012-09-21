#include "visualizerwindow.h"
#include "ui_visualizerwindow.h"

VisualizerWindow::VisualizerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualizerWindow)
{
    ui->setupUi(this);
}

VisualizerWindow::~VisualizerWindow()
{
    delete ui;
}
