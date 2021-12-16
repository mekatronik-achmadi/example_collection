#ifndef CPUVIEWER_H
#define CPUVIEWER_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QPointF>
#include <QTimer>

#if (defined (Q_OS_WIN) || defined (Q_OS_WIN32) || defined (Q_OS_WIN64))
#include "TCHAR.h"
#include "pdh.h"
#elif (defined (Q_OS_LINUX))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#define MAXPOINT 20

namespace Ui {
class CpuViewer;
}

class CpuViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit CpuViewer(QWidget *parent = 0);
    ~CpuViewer();

private:
    Ui::CpuViewer *ui;

    QtCharts::QSplineSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartview;

    QTimer *tmr;

    QtCharts::QValueAxis *m_axis;
    qreal m_step;
    qreal m_x;
    qreal m_y;
    int max_x,max_y;

#if (defined (Q_OS_WIN) || defined (Q_OS_WIN32) || defined (Q_OS_WIN64))
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;
#elif (defined (Q_OS_LINUX))
    unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
#endif

public slots:
    void tmr_timeout(void);
    double cpu_percent(void);

};

#endif // CPUVIEWER_H
