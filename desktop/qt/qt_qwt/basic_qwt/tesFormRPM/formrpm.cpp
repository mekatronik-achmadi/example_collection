#include "speedo_meter.h"
#include "rpm.h"
#include "formrpm.h"
#include "ui_formrpm.h"

extern int val_speed;

formrpm::formrpm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::formrpm)
{
    ui->setupUi(this);
    connect(ui->hsRPM,SIGNAL(valueChanged(int)),this,SLOT(rpm_changed(int)));
}

formrpm::~formrpm()
{
    delete ui;
}

void formrpm::on_actionQuit_triggered()
{
    QApplication::quit();
}

void formrpm::rpm_changed(int val){
    val_speed=10000*val/100;
}

