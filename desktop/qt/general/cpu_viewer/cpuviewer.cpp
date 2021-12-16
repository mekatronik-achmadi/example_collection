#include "cpuviewer.h"
#include "ui_cpuviewer.h"

CpuViewer::CpuViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CpuViewer)
{
    ui->setupUi(this);

    m_axis = new QtCharts::QValueAxis();
    series = new QtCharts::QSplineSeries();
    chart = new QtCharts::QChart();
    chartview = new QtCharts::QChartView(chart,ui->wdgtChart);

    tmr = new QTimer(this);
    tmr->setInterval(500);
    QObject::connect(tmr, SIGNAL(timeout()), this, SLOT(tmr_timeout()));

    max_x = 10;
    max_y = 100;

    m_axis->setTickCount(2*max_x/3);
    m_x = m_axis->tickCount();
    series->append(m_x, m_y);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAxisX(m_axis, series);
    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);

    chart->axisX()->setRange(0, max_x);
    chart->axisX()->hide();
    chart->axisY()->setRange(0, max_y);

    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setGeometry(QRect(0, 0, ui->wdgtChart->width(), ui->wdgtChart->height()));

    tmr->start();
}

CpuViewer::~CpuViewer()
{
    delete ui;
}

void CpuViewer::tmr_timeout(){

    qreal x = chart->plotArea().width() / m_axis->tickCount();
    qreal dx = (m_axis->max() - m_axis->min()) / m_axis->tickCount();

    m_x += dx;
    m_y = cpu_percent();
    series->append(m_x, m_y);

    chart->scroll(x, 0);

}

double CpuViewer::cpu_percent(){

#if (defined (Q_OS_WIN) || defined (Q_OS_WIN32) || defined (Q_OS_WIN64))

    PDH_FMT_COUNTERVALUE counterVal;

    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);

    return counterVal.doubleValue;

#elif (defined (Q_OS_LINUX))

    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;

#endif
}
