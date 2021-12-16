#ifndef TESCLOCK_H
#define TESCLOCK_H

#include <QMainWindow>
#include <QPalette>
#include <QFrame>
#include <QLayout>
#include <QTimer>
#include <QTabWidget>
#include <qwt/qwt_dial.h>
#include <qwt/qwt_analog_clock.h>

class QwtDial;
class QwtAnalogClock;

class tesClock : public QFrame
{
    Q_OBJECT

public:
    tesClock(QWidget *parent = NULL);


private:
    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial( void );
};

#endif // TESCLOCK_H
