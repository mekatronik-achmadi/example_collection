#include "ta_hmi.h"
#include "ui_ta_hmi.h"

TA_HMI::TA_HMI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TA_HMI)
{
    ui->setupUi(this);

    my_port = new QSerialPort(this);
    QObject::connect(my_port,SIGNAL(readyRead()),SLOT(ta_read_data()));

    tmrReq = new QTimer(this);
    QObject::connect(tmrReq,SIGNAL(timeout()),SLOT(ta_req_data()));

    ui->txtCommData->hide();
    ui->btnStart->setEnabled(false);
}


TA_HMI::~TA_HMI()
{
    delete ui;
}

void TA_HMI::ta_req_data(){
    ui->txtCommData->clear();

    if(!my_port->isOpen()){return;}

    QByteArray datareq="adc\n";

    my_port->write(datareq);
}

void TA_HMI::ta_read_data(){
    rawdata = my_port->readAll();

    ui->txtCommData->insertPlainText(rawdata);

    if(ui->txtCommData->toPlainText().isEmpty()){return;}

    ta_parse_int(ui->txtCommData->toPlainText());
}

void TA_HMI::ta_parse_int(QString strInput){
    QStringList strVal = strInput.split(",");

    vnum = strVal.count();
    if(vnum<1){return;}

    ui->barDataView->setValue(strVal[0].toInt());
}

void TA_HMI::on_btnOpen_clicked()
{
    QString dev_name = ui->cmbPort->currentText();

    QSerialPort::BaudRate dev_baud = QSerialPort::Baud9600;

    if(ui->btnOpen->text()=="Open"){
        my_port->setPortName(dev_name);

        if(my_port->open(QIODevice::ReadWrite)){
            my_port->setBaudRate(dev_baud,QSerialPort::AllDirections);
            my_port->setDataBits(QSerialPort::Data8);
            my_port->setStopBits(QSerialPort::OneStop);
            my_port->setFlowControl(QSerialPort::NoFlowControl);
            my_port->setParity(QSerialPort::NoParity);
            ui->btnOpen->setText("Close");
            ui->btnStart->setEnabled(true);
        }
        else{
            QMessageBox::critical(this,"Gagal","Port gagal dibuka " + dev_name);
            ui->btnOpen->setText("Open");
            ui->btnStart->setEnabled(false);
        }
    }
    else{
        if(my_port->isOpen()){
            my_port->close();
        }
        ui->btnOpen->setText("Open");
        ui->btnStart->setEnabled(false);
    }
}

void TA_HMI::on_btnStart_clicked()
{
    if(!my_port->isOpen()){return;}

    if(ui->btnStart->text()=="Start"){
        tmrReq->start(100);
        ui->btnStart->setText("Stop");
    }
    else{
        tmrReq->stop();
        ui->btnStart->setText("Start");
    }
}
