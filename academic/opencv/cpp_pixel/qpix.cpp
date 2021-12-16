#include "qpix.h"
#include "ui_qpix.h"

qpix::qpix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qpix)
{
    ui->setupUi(this);

    // ============================ IMAGE LOADING ===============================
    cobaori=cv::imread("./img.png");

    uint rows = cobaori.rows;
    uint cols = cobaori.cols;

    cv::cvtColor(cobaori,cobapix,CV_BGR2GRAY);

    std::cout << "rows= " << rows << "=" << "cols=" << cols << std::endl;
    std::cout<< std::endl;

    // ============================ IMAGE 1 and 0 ===============================

    cobapos= cv::Mat(rows,cols,CV_8U,cv::Scalar(0));
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            if(cobapix.at<uchar>(i,j)==255){cobapos.at<uchar>(i,j)=1;}
            else{cobapos.at<uchar>(i,j)=0;}
        }
    }

    std::cout<< "Image 1 and 0" << std::endl;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            uint val=cobapos.at<uchar>(i,j);
            std::cout << val;
        }
        std::cout<< std::endl;
    }
    std::cout<< std::endl;

    // PERHATIKAN UKURAN BIT !!!!!!!!!!!!!!!!!!
    // Mat operated by Mat, C++ operated by C++

    // ============================ X-SUMMING EACH ===============================

    xval=cv::Mat(1,cols,CV_16U,cv::Scalar(0));
    for(i=0;i<cols;i++){
        xval.at<ushort>(0,i)=0;
        for(j=0;j<rows;j++){
            xval.at<ushort>(0,i)=xval.at<ushort>(0,i)+cobapos.at<uchar>(j,i);
        }
    }

    std::cout<< "X-sum-each" << std::endl;
    for(i=0;i<cols;i++){
        uint val=xval.at<ushort>(0,i);
        std::cout << val << std::endl;
    }
    std::cout << std::endl;

    // ============================ Area ===============================

    mArea=cv::Mat(1,1,CV_16U,cv::Scalar(0));

    for(i=0;i<cols;i++){
        mArea.at<ushort>(0,0)=mArea.at<ushort>(0,0)+xval.at<ushort>(0,i);
    }

    Area=mArea.at<ushort>(0,0);

    std::cout<< "Area" << std::endl;
    std::cout << Area << std::endl;
    std::cout << std::endl;

    // ============================ X-SUMMING ===============================

    mxSum=cv::Mat(1,1,CV_32F,cv::Scalar(0));

    for(i=0;i<cols;i++){
        mxSum.at<float>(0,0)=mxSum.at<float>(0,0)+(i*xval.at<ushort>(0,i));
    }

    std::cout<< "X-sum" << std::endl;
    xSum=mxSum.at<float>(0,0);
    std::cout << xSum << std::endl;
    std::cout << std::endl;

    // ============================ X-CENTROID ===============================

    xcen=xSum/Area;

    std::cout<< "X-centroid" << std::endl;
    std::cout << xcen << std::endl;
    std::cout << std::endl;

    // ============================ Y-SUMMING EACH ===============================

    yval=cv::Mat(1,rows,CV_16U,cv::Scalar(0));
    for(i=0;i<rows;i++){
        yval.at<ushort>(0,i)=0;
        for(j=0;j<cols;j++){
            yval.at<ushort>(0,i)=yval.at<ushort>(0,i)+cobapos.at<uchar>(i,j);
        }
    }

    std::cout<< "Y-sum-each" << std::endl;
    for(i=0;i<rows;i++){
        uint val = yval.at<ushort>(0,i);
        std::cout << val << std::endl;
    }
    std::cout << std::endl;

    // ============================ Y-SUMMING ===============================

    mySum=cv::Mat(1,1,CV_32F,cv::Scalar(0));

    for(i=0;i<rows;i++){
        mySum.at<float>(0,0)=mySum.at<float>(0,0)+(i*yval.at<ushort>(0,i));
    }

    std::cout<< "Y-sum" << std::endl;
    ySum=mySum.at<float>(0,0);
    std::cout << ySum << std::endl;
    std::cout << std::endl;

    // ============================ Y-CENTROID ===============================

    ycen=ySum/Area;

    std::cout<< "Y-centroid" << std::endl;
    std::cout << ycen << std::endl;
    std::cout << std::endl;

    // ============================ Create Line to centroid  ================

    cobaline=cv::Mat::zeros(cobapix.size(),CV_8UC3);
    cv::line(cobaline,cv::Point(xcen,ycen),cv::Point(0,0),cv::Scalar(0,255,0),5);

    cobaori=cobaori+cobaline;
    cv::imshow("Result",cobaori);

}

qpix::~qpix()
{
    delete ui;
}

