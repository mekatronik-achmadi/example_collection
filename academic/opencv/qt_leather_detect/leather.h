#ifndef LEATHER_H
#define LEATHER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class leather;
}

class leather : public QMainWindow
{
    Q_OBJECT

public:
    explicit leather(QWidget *parent = 0);
    ~leather();

private slots:

    void on_btnOpen_clicked();

    void img_proc();

private:
    Ui::leather *ui;
    QString imgFile;
    cv::Mat imgGray;
    QTimer* tmrProc;

    cv::Mat imgSelect;
    cv::Mat imgCirc;

    uint vCol,vRow;
};

#endif // LEATHER_H
