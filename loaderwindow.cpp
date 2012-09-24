#include "loaderwindow.h"
#include "ui_loaderwindow.h"

LoaderWindow::LoaderWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoaderWindow)
{
    ui->setupUi(this);
    ui->launchButton->setEnabled(false);
    filename = "";
    visualizer = NULL;
}
LoaderWindow::~LoaderWindow()
{
    delete ui;
}
void LoaderWindow::on_launchButton_clicked()
{
    ui->launchButton->setEnabled(false);
    visualizer =  new VisualizerWindow(this, filename);
    connect(visualizer, SIGNAL(destroyed()), this, SLOT(visualizerClosed()));
}
void LoaderWindow::on_objectButton_clicked()
{

    filename = QFileDialog::getOpenFileName(this, tr("Load Object"), "", tr("Object File (*.obj)"));
    if(filename != NULL){
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            ui->launchButton->setEnabled(false);
        else
             ui->launchButton->setEnabled(true);
    }
    else
        ui->launchButton->setEnabled(false);
}
void LoaderWindow::visualizerClosed()
{
    ui->launchButton->setEnabled(true);
    disconnect(visualizer, SIGNAL(destroyed()), this, SLOT(visualizerClosed()));
    visualizer = NULL;
}
