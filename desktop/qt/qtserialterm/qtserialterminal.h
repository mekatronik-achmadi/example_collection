#ifndef QTSERIALTERMINAL_H
#define QTSERIALTERMINAL_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMessageBox>
#include <QTimer>
#include <QTime>

namespace Ui {
class qtserialterminal;
}

class qtserialterminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit qtserialterminal(QWidget *parent = 0);
    ~qtserialterminal();

private slots:
    void on_actionQuit_triggered();

    void on_actionAboutQt_triggered();

    void on_chkUseDelay_clicked(bool checked);

    void on_btnOpen_clicked();

    void req_data();

    void read_data();

    void on_btnStart_clicked();

    void on_actionClear_triggered();

    void mydelay(int millisecondsToWait);

    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::qtserialterminal *ui;
    QSerialPort* my_port;
    QTimer* tmrReq;

};

#endif // QTSERIALTERMINAL_H
