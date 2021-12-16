#include "coba1.h"
#include "ui_coba1.h"

//uchar vcobadata[]={10,25,40,35,65};
//uchar vcobax[]={1,2,3,4,5};

coba1::coba1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::coba1)
{
    ui->setupUi(this);

    QVector<double> cobax(255),cobadata(255),cobadata1(255);
//    QVector<double> cobax(255),cobadata(255);

    uchar i;
    for(i=0;i<255;i++){
        cobax[i]=i;
        cobadata[i]=10*i;
        cobadata1[i]=20*i;
    }

    ui->senoPlot->addGraph();
    ui->senoPlot->graph(0)->setData(cobax,cobadata);
    ui->senoPlot->graph(0)->setPen(QPen(QColor(255,0,0,100)));
    ui->senoPlot->graph(0)->setBrush(QBrush(QColor(255,0,0,50)));

    ui->senoPlot->addGraph();
    ui->senoPlot->graph(1)->setData(cobax,cobadata1);
    ui->senoPlot->graph(1)->setPen(QPen(QColor(0,255,0,100)));
    ui->senoPlot->graph(1)->setBrush(QBrush(QColor(0,255,0,50)));

    ui->senoPlot->yAxis->setRange(0,3000);
    ui->senoPlot->xAxis->setRange(0,300);

//    ui->senoPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->senoPlot->setInteractions(QCP::iRangeDrag);
//    ui->senoPlot->axisRect()->setRangeDrag(Qt::Horizontal);

    ui->senoPlot->replot();

}

coba1::~coba1()
{
    delete ui;
}
