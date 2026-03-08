#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <circuitbutton.h>
#include "about.h"
#include "brightnesscontrol.h"
#include "interiorlights.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void carHorn();

private slots:
    void on_about_clicked();

    void on_headlights_clicked();

    void on_Horn_pressed();

    void on_Horn_released();

private:
    Ui::MainWindow *ui;
    About *about;
    InteriorLights *interiorLights;
    BrightnessControl *brightnessControl;
    QTimer *hornTimer;

};
#endif // MAINWINDOW_H
