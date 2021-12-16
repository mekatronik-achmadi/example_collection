#include "gea.h"
#include "ui_gea.h"

gea::gea(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gea)
{
    ui->setupUi(this);
    connect(ui->btnCheck,SIGNAL(clicked()),this,SLOT(checkview()));
}

gea::~gea()
{
    delete ui;
}

void gea::checkview(){

    int x,y,z;

    arrtps=ui->inTPS->text();
    arrrpm=ui->inRPM->text();

    tps=arrtps.toInt();
    rpm=arrrpm.toInt();

    for(z=0;z<tabtps-1;z++){
            if((tps>=tab_tps[z])&&(tps<tab_tps[z+1])){x=z;}
            else if(tps>tab_tps[tabtps-1]){x=tabtps-1;}
   }

    for(z=0;z<tabrpm-1;z++){
            if((rpm>=tab_rpm[z])&&(rpm<tab_rpm[z+1])){y=z;}
            else if(rpm>tab_rpm[tabrpm-1]){y=tabrpm-1;}
   }

    inj_start=tab_inj_start[x][y];
    inj_stop=tab_inj_stop[x][y];
    ign_start=tab_ign_start[x][y];
    ign_stop=tab_ign_stop[x][y];

    ui->outINJStart->display(inj_start);
    ui->outINJStop->display(inj_stop);
    ui->outIGNStart->display(ign_start);
    ui->outIGNStop->display(ign_stop);
}
