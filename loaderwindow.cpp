#include "loaderwindow.h"
#include "ui_loaderwindow.h"

LoaderWindow::LoaderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoaderWindow)
{
    ui->setupUi(this);
}

LoaderWindow::~LoaderWindow()
{
    delete ui;
}
