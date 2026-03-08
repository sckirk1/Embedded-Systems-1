#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->parent = parent;
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_clicked()
{
    // Hide the about dialog
    hide();
    // Show the main window
    parent->show();
}
