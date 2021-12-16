#include "coba.h"
#include "ui_coba.h"

coba::coba(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::coba)
{
    ui->setupUi(this);
}

coba::~coba()
{
    delete ui;
}

void coba::on_actionAbout_triggered()
{
    QApplication::aboutQt();
}

void coba::on_actionQuit_triggered()
{
    QApplication::quit();
}
