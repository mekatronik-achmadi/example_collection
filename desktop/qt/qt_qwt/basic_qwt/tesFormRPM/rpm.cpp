#include "rpm.h"
#include "formrpm.h"

int val_speed;

rpm::rpm(QWidget *parent) :
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

QwtDial *rpm::createDial(void){
    QwtDial *dial=NULL;

    d_speedo = new SpeedoMeter( this );
    d_speedo->setScaleStepSize( 1000.0 );
    d_speedo->setScale( 0.0, 10000.0 );
    d_speedo->scaleDraw()->setPenWidth( 2 );

    QTimer *timer = new QTimer( d_speedo );
    timer->connect( timer, SIGNAL( timeout() ),this, SLOT( changeSpeed() ) );
    timer->start( 50 );

    dial = d_speedo;
    return dial;
}

QPalette rpm::colorTheme(const QColor &base) const{
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

void rpm::changeSpeed(void){
    double value = val_speed;
    d_speedo->setValue(value);
}
