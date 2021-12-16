#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cv::VideoCapture Cam(0);
    cv::namedWindow("CameraCapture");
    while(cv::waitKey(33) == 27 )
    {
      Cam >> frameImage;
      cv::imshow("CameraCapture",frameImage);
    }

}


