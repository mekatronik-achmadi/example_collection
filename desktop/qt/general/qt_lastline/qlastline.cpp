#include "qlastline.h"
#include "ui_qlastline.h"

int thedata;

qlastline::qlastline(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qlastline)
{
    ui->setupUi(this);

    tmrData = new QTimer(this);
    tmrSelect = new QTimer(this);

    QObject::connect(tmrData,SIGNAL(timeout()),this,SLOT(add_data()));
    QObject::connect(tmrSelect,SIGNAL(timeout()),this,SLOT(select_data()));

    tmrData->start(1000);
    tmrSelect->start(1000);

}

qlastline::~qlastline()
{
    delete ui;
}

void qlastline::add_data(){
    thedata++;
    QString strdata = "this is data on ";
    QString strnumb = QString::number(thedata);
    strdata += strnumb;
    strdata += "\n";
    ui->txtData->insertPlainText(strdata);
}

void qlastline::select_data(){
    ui->lblSelected->clear();

    QString setdata = ui->txtData->toPlainText();
    QStringList strlist = setdata.split("\n");
    uint cdata= strlist.count();

    if(cdata>2){
        ui->lblSelected->setText(strlist[cdata-2].toLatin1());
    }
}
