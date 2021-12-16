#include "qhsv.h"
#include "ui_qhsv.h"

qhsv::qhsv(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qhsv)
{
    ui->setupUi(this);

    tmr = new QTimer(this);
    QObject::connect(tmr,SIGNAL(timeout()),this,SLOT(color_conv()));
    tmr->start(100);
}

qhsv::~qhsv()
{
    delete ui;
}

void qhsv::color_conv()
{
    vHue = ui->sldHue->value();
    vSat = ui->sldSat->value();
    vVal = ui->sldVal->value();

    ui->txtHue->setText(QString::number(vHue));
    ui->txtSat->setText(QString::number(vSat));
    ui->txtVal->setText(QString::number(vVal));

    imgHSV= cv::Mat(100,100,CV_8UC3,cv::Scalar(vHue,vSat,vVal));
    imgBGR = cv::Mat::zeros(100,100,CV_8UC3);
    cv::cvtColor(imgHSV,imgBGR,CV_HSV2BGR);
    cv::imshow("BRG",imgBGR);
}
