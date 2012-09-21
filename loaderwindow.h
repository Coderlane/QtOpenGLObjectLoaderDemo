#ifndef LOADERWINDOW_H
#define LOADERWINDOW_H

#include <QMainWindow>

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
};

#endif // LOADERWINDOW_H
