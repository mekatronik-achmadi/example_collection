#ifndef RPM_H
#define RPM_H

#include <QWidget>
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

class rpm : public QFrame
{
    Q_OBJECT

public:
    rpm(QWidget *parent = NULL);

private slots:
    void changeSpeed(void);

private:
    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial( void );

    SpeedoMeter *d_speedo;
};

#endif // RPM_H
