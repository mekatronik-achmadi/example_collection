#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_math.h>

#define DATA_SIZE 1000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void plot1();
    void tick1();
    void next_val();


private:
    Ui::MainWindow *ui;

    const int datsize=DATA_SIZE;

    QTimer *timer1;
    QwtPlotCurve *crv1;

    double vdat1[DATA_SIZE];
    double xdat[DATA_SIZE];

    double xval[DATA_SIZE];
    double yval;

    int index;
};

#endif // MAINWINDOW_H
