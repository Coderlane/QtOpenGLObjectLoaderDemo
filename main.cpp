#include <QtGui/QApplication>
#include "loaderwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoaderWindow w;
    w.show();
    
    return a.exec();
}
