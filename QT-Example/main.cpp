#include "mainwindow.h"

#include <QApplication>

// This is the main entry point for the QT Application.
// This will create an application instance, and create and open the MainWindow.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
