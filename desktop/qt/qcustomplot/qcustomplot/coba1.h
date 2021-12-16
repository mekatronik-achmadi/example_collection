#ifndef COBA1_H
#define COBA1_H

#include <QMainWindow>
#include "qcustomplot/qcustomplot.h"

namespace Ui {
class coba1;
}

class coba1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit coba1(QWidget *parent = 0);
    ~coba1();

private:
    Ui::coba1 *ui;
};

#endif // COBA1_H
