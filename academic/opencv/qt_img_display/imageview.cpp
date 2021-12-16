#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);

    //from a image file

    QString filename="image.jpg";

    QImage img(filename);

    //====================================

    //image from a data array
    /*
    QImage img(640,380,QImage::Format_RGB32);

    QRgb val;

    QString s1="fc";
    QString s2="ce";

    bool ok;

    int v1=s1.toUInt(&ok,16);
    int v2=s2.toUInt(&ok,16);

    for(i=0;i<320;i++){
        for(j=0;j<380;j++){
            val=qRgb(v1,v1,v1);
            img.setPixel(i,j,val);
        };
    };

    for(i=0;i<320;i++){
        for(j=0;j<380;j++){
            val=qRgb(v2,v2,v2);
            img.setPixel(i+320,j,val);
        };
    };
    */
    //============================================

    //display the image

    ui->lblDisplay->setPixmap(QPixmap::fromImage(img));
}

ImageView::~ImageView()
{
    delete ui;
}
