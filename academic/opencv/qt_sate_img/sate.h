#ifndef SATE_H
#define SATE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

#include "SerialPortLibs/qextserialport.h"
#include "SerialPortLibs/qextserialenumerator.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define USE_SERIAL 0

namespace Ui {
class sate;
}

class sate : public QMainWindow
{
    Q_OBJECT

public:
    explicit sate(QWidget *parent = 0);
    ~sate();

private slots:
    void on_btnFile_clicked();

    void on_btnAnalize_clicked();

    uint get_pixel_count( cv::Mat imgInput,int lH,int hH, int lS, int hS, int lV, int hV,std::string winname);

    uint get_pixel_max(uint v1,uint v2, uint v3);

    void on_btnCam_clicked();

    void routine_cam();
    
    void mydelay(int millisecondsToWait);

#if USE_SERIAL

    void open_serial();

    void close_serial();
#endif

private:
    Ui::sate *ui;

    QString imgFile;
    cv::Mat imgOri;

    QTimer *tmrCam;
    cv::VideoCapture devCam;

#if USE_SERIAL
    QextSerialPort* mySerial;
#endif

};

#endif // SATE_H
