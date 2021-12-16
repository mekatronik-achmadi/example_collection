#include "qcoba.h"
#include "ui_qcoba.h"

qcoba::qcoba(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qcoba)
{
    ui->setupUi(this);

    my_port= new QSerialPort(this);
    QObject::connect(my_port,SIGNAL(readyRead()),SLOT(read_data()));

    tmrReq= new QTimer(this);
    connect(tmrReq,SIGNAL(timeout()),SLOT(req_data()));

    ui->pltData->setAxisScale(0,0,256);
    ui->pltData->setAxisScale(2,0,DATA_SIZE);

    crv1 = new QwtPlotCurve("Curve 1");
    crv1->setPen(QPen(Qt::darkBlue));

    crv2 = new QwtPlotCurve("Curve 2");
    crv2->setPen(QPen(Qt::darkGreen));

    crv3 = new QwtPlotCurve("Curve 3");
    crv3->setPen(QPen(Qt::darkRed));

    uint8_t i;
    for(i=0;i<DATA_SIZE;i++) {
        vdat1[i]=0;
        vdat2[i]=0;
        vdat3[i]=0;
        xdat[i]=i;
    }

}

qcoba::~qcoba()
{
    delete ui;
}

void qcoba::req_data(){
    ui->txtCommData->clear();

    if(!my_port->isOpen()){return;}

    QByteArray dataReq="data\n";

    my_port->write(dataReq);
}

void qcoba::read_data(){
    rawdata=my_port->readAll();

    ui->txtCommData->insertPlainText(rawdata);

    if(ui->txtCommData->toPlainText().isEmpty()){return;}

    parse_int(ui->txtCommData->toPlainText());
}

void qcoba::parse_int(QString strInput){
    QStringList strVal= strInput.split(",");

    vnum=strVal.count();
    ui->txtVnumb->setText(QString::number(vnum));

    if(vnum<3){return;}

    v1=strVal[0].toInt();
    v2=strVal[1].toInt();
    v3=strVal[2].toInt();

    view_var();
}

void qcoba::view_var(){

    uint8_t i;

    for(i=DATA_SIZE-1;i>0;i--){
        vdat1[i] = vdat1[i-1];
        vdat2[i] = vdat2[i-1];
        vdat3[i] = vdat3[i-1];
    }

    vdat1[0]=v1;
    vdat2[0]=v2;
    vdat3[0]=v3;

    ui->txtV1->setText(QString::number(v1));
    ui->txtV2->setText(QString::number(v2));
    ui->txtV3->setText(QString::number(v3));

    plot_var();
}

void qcoba::on_btnOpen_clicked()
{
    //Port Name
    QString dev_name="/dev/";
    dev_name += ui->cmbPort->currentText();

    //Baudrate
    QSerialPort::BaudRate dev_baud=QSerialPort::Baud9600;
    int baud_index=ui->cmbBaud->currentIndex();

    switch(baud_index){
        case 0: dev_baud=QSerialPort::Baud9600;break;
        case 1: dev_baud=QSerialPort::Baud19200;break;
        case 2: dev_baud=QSerialPort::Baud38400;break;
        case 3: dev_baud=QSerialPort::Baud57600;break;
        case 4: dev_baud=QSerialPort::Baud115200;break;
    }

    //Open Serial Port
    if(ui->btnOpen->text()=="Open"){
        my_port->setPortName(dev_name);
        if(my_port->open(QIODevice::ReadWrite)){
            my_port->setBaudRate(dev_baud,QSerialPort::AllDirections);
            my_port->setDataBits(QSerialPort::Data8);
            my_port->setStopBits(QSerialPort::OneStop);
            my_port->setFlowControl(QSerialPort::NoFlowControl);
            my_port->setParity(QSerialPort::NoParity);
            QMessageBox::information(this,"success","port success on "+dev_name );
            ui->btnOpen->setText("Close");
        }
        else{
            QMessageBox::critical(this,"Failed","port failed on "+dev_name);
            ui->btnOpen->setText("Open");
        }
    }
    else{
        if(my_port->isOpen()){
            my_port->close();
        }
        ui->btnOpen->setText("Open");
    }
}

void qcoba::plot_var(){

    crv1->setRawSamples(xdat,vdat1,datsize);
    crv2->setRawSamples(xdat,vdat2,datsize);
    crv3->setRawSamples(xdat,vdat3,datsize);

    crv1->attach(ui->pltData);
    crv2->attach(ui->pltData);
    crv3->attach(ui->pltData);

    ui->pltData->replot();
}

void qcoba::on_btnStart_clicked()
{
    if(!my_port->isOpen()){return;}

    if(ui->btnStart->text()=="Start"){
        tmrReq->start(500);
        ui->btnStart->setText("Stop");
    }
    else{
        tmrReq->stop();
        ui->btnStart->setText("Start");
    }
}
