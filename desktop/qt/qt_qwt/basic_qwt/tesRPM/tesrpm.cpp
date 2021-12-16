#include "tesrpm.h"

tesRPM::tesRPM(QWidget *parent) :
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

QwtDial *tesRPM::createDial(void){
    QwtDial *dial=NULL;

    d_speedo = new SpeedoMeter( this );
    d_speedo->setScaleStepSize( 20.0 );
    d_speedo->setScale( 0.0, 240.0 );
    d_speedo->scaleDraw()->setPenWidth( 2 );

    QTimer *timer = new QTimer( d_speedo );
    timer->connect( timer, SIGNAL( timeout() ),this, SLOT( changeSpeed() ) );
    timer->start( 50 );

    dial = d_speedo;
    return dial;
}

QPalette tesRPM::colorTheme(const QColor &base) const{
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

void tesRPM::changeSpeed(){
    static double offset = 0.8;

    double speed = d_speedo->value();

    if ( ( speed < 7.0 && offset < 0.0 ) ||
        ( speed > 203.0 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    static int counter = 0;
    switch( counter++ % 12 )
    {
        case 0:
        case 2:
        case 7:
        case 8:
            break;
        default:
        d_speedo->setValue( speed + offset );
    }
}
