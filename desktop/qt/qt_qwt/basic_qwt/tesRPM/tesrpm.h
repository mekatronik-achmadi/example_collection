#ifndef TESRPM_H
#define TESRPM_H

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

class tesRPM : public QFrame
{
    Q_OBJECT

public:
    tesRPM(QWidget *parent = NULL);

private slots:
    void changeSpeed(void);
    
private:
    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial( void );
    
    SpeedoMeter *d_speedo;
};

#endif // TESRPM_H
