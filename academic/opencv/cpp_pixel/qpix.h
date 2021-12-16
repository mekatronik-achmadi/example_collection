#ifndef QPIX_H
#define QPIX_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace Ui {
class qpix;
}

class qpix : public QMainWindow
{
    Q_OBJECT

public:
    explicit qpix(QWidget *parent = 0);
    ~qpix();

private:
    Ui::qpix *ui;
    uint i,j;
    cv::Mat cobaori;
    cv::Mat cobapix;
    cv::Mat cobapos;

    cv::Mat xval;
    cv::Mat mxSum;
    float xSum;
    uint xcen;

    cv::Mat mArea;
    uint Area;

    cv::Mat yval;
    cv::Mat mySum;
    float ySum;
    uint ycen;

    cv::Mat cobaline;
};

#endif // QPIX_H
