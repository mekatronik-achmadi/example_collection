#include "leather.h"
#include "ui_leather.h"

leather::leather(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leather)
{
    ui->setupUi(this);
    tmrProc=new QTimer(this);
    QObject::connect(tmrProc,SIGNAL(timeout()),this,SLOT(img_proc()));
}

leather::~leather()
{
    delete ui;
}

void leather::on_btnOpen_clicked()
{
    if(tmrProc->isActive()){
        tmrProc->stop();
    }

    imgFile = QFileDialog::getOpenFileName(this,"Select Picture","Portable Network Graphic (*.png)");

    if(imgFile.isEmpty()){
        return;
    }

    ui->txtFile->setText(imgFile);

    imgGray=cv::imread(imgFile.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);

    vRow= imgGray.rows;
    vCol= imgGray.cols;

    ui->xVal->setMaximum(vCol);
    ui->yVal->setMaximum(vRow);

    tmrProc->start(100);

//    cv::imshow("GrayOri",imgGray);

//    img_proc();

}

void leather::img_proc(){

    imgSelect=cv::Mat::zeros(imgGray.size(),CV_8UC1);
    imgCirc=cv::Mat::zeros(imgGray.size(),CV_8UC1);

    int xdis=30;
    int ydis=30;
    int i;

//    ========================================================================

    int PxA[10],PyA[10];

    PxA[0]=ui->xVal->value();  PxA[1]=PxA[0]+(1*xdis); PxA[2]=PxA[0]+(2*xdis); PxA[3]=PxA[0]+(3*xdis); PxA[4]=PxA[0]+(4*xdis);
    PyA[0]=ui->yVal->value();  PyA[1]=PyA[0]; PyA[2]=PyA[0]; PyA[3]=PyA[0]; PyA[4]=PyA[0];

    PxA[5]=PxA[0]; PxA[6]=PxA[1]; PxA[7]=PxA[2]; PxA[8]=PxA[3]; PxA[9]=PxA[4];
    PyA[5]=PyA[0]+(1*ydis); PyA[6]=PyA[5]; PyA[7]=PyA[5]; PyA[8]=PyA[5]; PyA[9]=PyA[5];

    for(i=0;i<10;i++){
        cv::circle(imgCirc,cv::Point(PxA[i],PyA[i]),5,255,2);
    };

    uchar vPA[10];

    for(i=0;i<10;i++){
        vPA[i] = imgGray.at<uchar>(PyA[i],PxA[i]);
    };

    uint sumPA=0;

    for(i=0;i<10;i++){
        sumPA=sumPA+vPA[i];
    };

    uchar PA=sumPA/10;

//    ========================================================================

    int PxB[10],PyB[10];

    PxB[0]=ui->xVal->value();  PxB[1]=PxB[0]+(1*xdis); PxB[2]=PxB[0]+(2*xdis); PxB[3]=PxB[0]+(3*xdis); PxB[4]=PxB[0]+(4*xdis);
    PyB[0]=ui->yVal->value()+(3*ydis);  PyB[1]=PyB[0]; PyB[2]=PyB[0]; PyB[3]=PyB[0]; PyB[4]=PyB[0];

    PxB[5]=PxB[0]; PxB[6]=PxB[1]; PxB[7]=PxB[2]; PxB[8]=PxB[3]; PxB[9]=PxB[4];
    PyB[5]=PyB[0]+(1*ydis); PyB[6]=PyB[5]; PyB[7]=PyB[5]; PyB[8]=PyB[5]; PyB[9]=PyB[5];

    for(i=0;i<10;i++){
        cv::circle(imgCirc,cv::Point(PxB[i],PyB[i]),5,255,2);
    };

    uchar vPB[10];

    for(i=0;i<10;i++){
        vPB[i] = imgGray.at<uchar>(PyB[i],PxB[i]);
    };

    uint sumPB=0;

    for(i=0;i<10;i++){
        sumPB=sumPB+vPB[i];
    };

    uchar PB=sumPB/10;

//    ========================================================================

    uchar PDiff;

    if(PA==PB){PDiff=0;}
    else if(PA>PB){PDiff=PA-PB;}
    else if(PA<PB){PDiff=PB-PA;}

//    ========================================================================

    imgSelect=imgCirc+imgGray;

    ui->txtGrayA->setText(QString::number(PA));
    ui->txtGrayB->setText(QString::number(PB));
    ui->txtGrayDiff->setText(QString::number(PDiff));

    cv::imshow("selected",imgSelect);

}
