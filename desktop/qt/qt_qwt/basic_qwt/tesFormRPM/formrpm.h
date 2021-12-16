#ifndef FORMRPM_H
#define FORMRPM_H

#include <QMainWindow>
#include <QPalette>
#include <QFrame>
#include <QLayout>
#include <QTimer>
#include <QTabWidget>
#include <QString>
#include <QPainter>
#include <qwt_dial.h>
#include "speedo_meter.h"

class QwtDial;
class SpeedoMeter;
class rpm;

namespace Ui {
class formrpm;
}

class formrpm : public QMainWindow
{
    Q_OBJECT

public:
    explicit formrpm(QWidget *parent = 0);
    ~formrpm();

private slots:
    void on_actionQuit_triggered();

private:
     Ui::formrpm *ui;

private slots:
     void rpm_changed(int val);
};

#endif // FORMRPM_H
