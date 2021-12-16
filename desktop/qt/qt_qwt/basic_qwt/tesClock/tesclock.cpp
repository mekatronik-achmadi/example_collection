#include "tesclock.h"

tesClock::tesClock(QWidget *parent) :
    QFrame(parent)
{
    setAutoFillBackground( true );

    setPalette( colorTheme( QColor( Qt::darkGray ).dark( 150 ) ) );

    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setMargin( 0 );


    QwtDial *dial = createDial();
    layout->addWidget( dial, 0, 0 );

}

QwtDial *tesClock::createDial(void){
    QwtDial *dial=NULL;
    QwtAnalogClock *clock = new QwtAnalogClock(this);
    clock->scaleDraw()->setTickLength( QwtScaleDiv::MinorTick, 0 );
    clock->setLineWidth(6);
    clock->setFrameShadow(QwtDial::Sunken);
    clock->setTime();
    // update the clock every second
    QTimer *timer = new QTimer(clock);
    timer->connect(timer, SIGNAL(timeout()), clock, SLOT(setCurrentTime()));
    timer->start(1000);
    dial=clock;
    return dial;
}

QPalette tesClock::colorTheme(const QColor &base) const{
    QPalette palette;
    palette.setColor( QPalette::Base, base );
    palette.setColor( QPalette::Window, base.dark( 150 ) );
    palette.setColor( QPalette::Mid, base.dark( 110 ) );
    palette.setColor( QPalette::Light, base.light( 170 ) );
    palette.setColor( QPalette::Dark, base.dark( 170 ) );
    palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
    palette.setColor( QPalette::WindowText, base.dark( 200 ) );

    return palette;
}
