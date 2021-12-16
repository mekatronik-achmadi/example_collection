#include "mycam.h"
#include "ui_mycam.h"

myCam::myCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myCam)
{
    ui->setupUi(this);

    cv::VideoCapture Cam(-1);
    cv::namedWindow("CameraCapture");
     while(cv::waitKey(33) != 27 )
     {
          Cam >> frameImage;
          cv::flip(frameImage,inversigambar,1);
          cv::imshow("CameraCapture",inversigambar);
     }
}

myCam::~myCam()
{
    delete ui;
}
