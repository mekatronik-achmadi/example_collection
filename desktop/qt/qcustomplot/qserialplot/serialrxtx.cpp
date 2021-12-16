#include "serialrxtx.h"
#include "ui_serialrxtx.h"

QVector<double> datax(1000),datay1(1000),datay2(1000),datay3(1000);

serialrxtx::serialrxtx(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serialrxtx)
{
    ui->setupUi(this);
    seno= new QSerialPort(this);
    seno->setPortName("/dev/ttyUSB0");
    seno->open(QIODevice::ReadWrite);
    seno->setBaudRate(QSerialPort::Baud38400);
    seno->setDataBits(QSerialPort::Data8);
    seno->setStopBits(QSerialPort::OneStop);
    seno->setFlowControl(QSerialPort::NoFlowControl);
    seno->setParity(QSerialPort::NoParity);
    QObject::connect(seno,SIGNAL(readyRead()),this,SLOT(terima_data()));

    tmr_seno = new QTimer(this);
    QObject::connect(tmr_seno,SIGNAL(timeout()),this,SLOT(kirim_data()));
//    tmr_seno->start(100);
    ui->txtTx->installEventFilter(this);
    vcount=0;
}

serialrxtx::~serialrxtx()
{
    delete ui;
}

void serialrxtx::kirim_data(){
    seno->write("jancok\n");
    }

bool serialrxtx::eventFilter(QObject *obj, QEvent *event){
    if(event->type()== QEvent::KeyPress){
        QKeyEvent* tombol = static_cast <QKeyEvent* >(event);
        if (seno->isOpen()){
            QString str= tombol->text();
            if(str.length()){
                char chr= str.at(0).toLatin1();
                QByteArray qba = QByteArray::fromRawData(&chr,1);
                seno->write(qba);
                ui->txtTx->insertPlainText(qba);
               }
        }
        return true;
    }
    else{
        return QObject::eventFilter(obj,event);
    }
}

void serialrxtx::terima_data(){
    QByteArray rawdata= seno->readAll();

    ui->txtRx->insertPlainText(rawdata);

    QString indata=ui->txtRx->toPlainText();
    QStringList lsindata= indata.split("\n");
    uint cdata= lsindata.count();

    if(cdata<=2){return;}

    QStringList lsdata = lsindata[cdata-2].split(",");

    uint vdata1=lsdata[0].toInt();
    uint vdata2=lsdata[1].toInt();
    uint vdata3=lsdata[2].toInt();

    datax[vcount]=vcount;
    datay1[vcount]=vdata1;
    datay2[vcount]=vdata2;
    datay3[vcount]=vdata3;
    vcount++;

    if(vcount==1000){
        if(seno->isOpen()){seno->close();}
    }

    ui->myPlot->addGraph();
    ui->myPlot->graph(0)->setData(datax,datay1);
    ui->myPlot->graph(0)->setPen(QPen(Qt::blue));

    ui->myPlot->addGraph();
    ui->myPlot->graph(1)->setData(datax,datay2);
    ui->myPlot->graph(0)->setPen(QPen(Qt::black));

    ui->myPlot->addGraph();
    ui->myPlot->graph(2)->setData(datax,datay3);
    ui->myPlot->graph(0)->setPen(QPen(Qt::red));

    ui->myPlot->yAxis->setRange(0,4100);
    ui->myPlot->xAxis->setRange(0,1500);
    ui->myPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->myPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->myPlot->replot();
}

void serialrxtx::on_actionClear_triggered()
{
    ui->txtRx->clear();
}
