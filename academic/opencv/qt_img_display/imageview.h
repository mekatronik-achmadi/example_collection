#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QMainWindow>

namespace Ui {
class ImageView;
}

class ImageView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();
    
private:
    Ui::ImageView *ui;
    int i,j;
};

#endif // IMAGEVIEW_H
