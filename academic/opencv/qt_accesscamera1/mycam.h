#ifndef MYCAM_H
#define MYCAM_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class myCam;
}

class myCam : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit myCam(QWidget *parent = 0);
    ~myCam();
    
private:
    Ui::myCam *ui;
    cv::Mat frameImage;
    cv::Mat inversigambar;
    bool StateOnCamera;
};

#endif // MYCAM_H
