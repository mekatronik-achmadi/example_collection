#include "dialtest.h"
#include "ui_dialtest.h"

dialtest::dialtest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dialtest)
{
    ui->setupUi(this);

    connect(ui->dialNumber,SIGNAL(valueChanged(int)),this,SLOT(lcdNumberSet()));
    connect(ui->btnNumber,SIGNAL(clicked()),this,SLOT(dialNumberSet()));
    connect(ui->hsliNumber,SIGNAL(valueChanged(int)),SLOT(dialNumberSet2()));

    ui->lcdNumber->display(ui->dialNumber->value());
    ui->lneNumber->setText(QString::number(ui->dialNumber->value()));
}

dialtest::~dialtest()
{
    delete ui;
}

void dialtest::dialNumberSet(){
     ui->dialNumber->setValue(ui->lneNumber->text().toInt());
     ui->lcdNumber->display(ui->dialNumber->value());
     ui->hsliNumber->setValue(ui->lcdNumber->value());
}

void dialtest::lcdNumberSet(){
    ui->hsliNumber->setValue(ui->dialNumber->value());
    ui->lcdNumber->display(ui->dialNumber->value());
    ui->lneNumber->setText(QString::number(ui->dialNumber->value()));
}

void dialtest::dialNumberSet2(){
    ui->dialNumber->setValue(ui->hsliNumber->value());
    ui->lcdNumber->display(ui->hsliNumber->value());
    ui->lneNumber->setText(QString::number(ui->hsliNumber->value()));
}
