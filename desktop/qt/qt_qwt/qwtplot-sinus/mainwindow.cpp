#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer1=new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(tick1()));

    ui->qwtPlot->setAxisScale(0,-1,1,0.2);

    crv1 = new QwtPlotCurve("Curve 1");
    crv1->setPen(QPen(Qt::darkBlue));

    timer1->start(100);

    uint16_t i;
    for( i = 0; i < DATA_SIZE; i++ )
    {
        xval[i] = double( i ) * 100 / double( DATA_SIZE - 1 );
        xdat[i]=0;
        vdat1[i]=0;
    }

    index=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot1()
{
    for(uint16_t i=DATA_SIZE-1;i>0;i--){
        xdat[i] = xdat[i-1];
        vdat1[i] = vdat1[i-1];
    }

    xdat[0]=xval[index];
    vdat1[0]=yval;

    crv1->setRawSamples(xdat,vdat1,datsize);
    crv1->attach(ui->qwtPlot);

    ui->qwtPlot->replot();

}


void MainWindow::tick1()
{
    yval = qSin(xval[index]);
    plot1();
    next_val();
}

void MainWindow::next_val(){
    index++;
    if(index==DATA_SIZE){
        index=0;
        uint16_t i;
        for( i = 0; i < DATA_SIZE; i++ )
        {
            xdat[i]=0;
            vdat1[i]=0;
        }
    }
}
