#include "visualizerwindow.h"
#include "ui_visualizerwindow.h"

VisualizerWindow::VisualizerWindow(QWidget *parent, QString newFile) : QMainWindow(parent), ui(new Ui::VisualizerWindow)
{
    ui->setupUi(this);
    showFullScreen();
    filename = newFile;
    ui->glWidget->setupScene(filename);
    connect(ui->glWidget, SIGNAL(emitClose()), this, SLOT(close()));
}

VisualizerWindow::~VisualizerWindow()
{
    delete ui;
}


void VisualizerWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(QMessageBox::question(this, "Exit", "Would you like to exit", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            close();
        }
        // Back to the action!
    }
    else if(event->key() == Qt::Key_Up)
    {
        ui->glWidget->setZoom(MAX_ZOOM);
    }
    else if(event->key() == Qt::Key_Down)
    {
        ui->glWidget->setZoom(-MAX_ZOOM);
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void VisualizerWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down )
    {
        ui->glWidget->setZoom(0);
    }
    else
    {
        QWidget::keyReleaseEvent(event);
    }
}
