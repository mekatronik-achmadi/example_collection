#ifndef TA_HMI_H
#define TA_HMI_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>

namespace Ui {
class TA_HMI;
}

class TA_HMI : public QMainWindow
{
    Q_OBJECT

public:
    explicit TA_HMI(QWidget *parent = 0);
    ~TA_HMI();

private slots:
    void on_btnOpen_clicked();
    void on_btnStart_clicked();

    void ta_req_data();
    void ta_read_data();
    void ta_parse_int(QString strInput);

private:
    Ui::TA_HMI *ui;

    QSerialPort* my_port;
    QTimer* tmrReq;

    QByteArray rawdata;
    int vnum;
};

#endif // TA_HMI_H
