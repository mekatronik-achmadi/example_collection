#ifndef SERIALRXTX_H
#define SERIALRXTX_H

#include <QMainWindow> // untuk membuat window
#include <QSerialPort>
#include <QTimer>
#include "qcustomplot/qcustomplot.h"

namespace Ui { //C++ program berbasis class, class dikumoulkan menjadi namespace
class serialrxtx;
}

class serialrxtx : public QMainWindow // public itu nanti sifatnya pulik bisa diakses kelas lain, rx tx merupakan turunan dari main window
{
    Q_OBJECT

public:
    explicit serialrxtx(QWidget *parent = 0);
    ~serialrxtx();

private:
    Ui::serialrxtx *ui;
    QSerialPort *seno;
    QTimer *tmr_seno;
    uint vcount;

private slots:
    void kirim_data();
    void terima_data();
    void on_actionClear_triggered();
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SERIALRXTX_H
