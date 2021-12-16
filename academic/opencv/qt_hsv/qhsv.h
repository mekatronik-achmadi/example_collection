#ifndef QHSV_H
#define QHSV_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class qhsv;
}

class qhsv : public QMainWindow
{
    Q_OBJECT

public:
    explicit qhsv(QWidget *parent = 0);
    ~qhsv();

private slots:
    void color_conv();

private:
    Ui::qhsv *ui;

    cv::Mat imgHSV;
    cv::Mat imgBGR;

    uchar vHue;
    uchar vSat;
    uchar vVal;

    QTimer* tmr;
};

#endif // QHSV_H
