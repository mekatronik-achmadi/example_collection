#include "number.h"
#include "ui_number.h"

number::number(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::number)
{
    ui->setupUi(this);
    connect(ui->actionShow,SIGNAL(triggered()),this,SLOT(convert()));
}

number::~number()
{
    delete ui;
}

void number::convert(){

    //QString str = "CONVERT";

      /* int to QString */
//    int vint =  45;
//    QString str = QString::number(vint);

    /* QByteArray to QString */
//    QByteArray vbyte= "aaa";
//    QString str = vbyte;

    /* QByteArray to char than to string */
    QByteArray vbyte = "a";
    const char ch[]= {vbyte.at(0)};
    QByteArray vbyte2 = QByteArray::fromRawData(ch,1);
    QString str = vbyte2;

    /* QByteArray to QString in hex */
//    QByteArray vbyte= "a";
//    QString str = vbyte.toHex();

    /* int hexa to QByteArray than to string*/
//    const char ch[] = {0x61};
//    QByteArray vbyte = QByteArray::fromRawData(ch,1);
//    QString str = vbyte;

    ui->lblView->setText(str);

}
