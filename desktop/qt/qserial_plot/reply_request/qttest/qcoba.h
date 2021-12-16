#ifndef QCOBA_H
#define QCOBA_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#define DATA_SIZE 200

namespace Ui {
class qcoba;
}

class qcoba : public QMainWindow
{
    Q_OBJECT

public:
    explicit qcoba(QWidget *parent = 0);
    ~qcoba();

private slots:
    void on_btnOpen_clicked();

    void req_data();
    void read_data();
    void parse_int(QString strInput);
    void view_var();
    void plot_var();

    void on_btnStart_clicked();

private:
    Ui::qcoba *ui;
    QSerialPort* my_port;
    QTimer* tmrReq;

    QByteArray rawdata;
    QString strdata;

    uint8_t vnum,v1,v2,v3;

    double vdat1[DATA_SIZE];
    double vdat2[DATA_SIZE];
    double vdat3[DATA_SIZE];
    double xdat[DATA_SIZE];
    const int datsize=DATA_SIZE;

    QwtPlotCurve *crv1;
    QwtPlotCurve *crv2;
    QwtPlotCurve *crv3;

};

#endif // QCOBA_H
