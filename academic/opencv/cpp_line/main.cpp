#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(){
  Mat cobapix= imread("./img.png");
  uint rows = cobapix.rows;
  uint cols = cobapix.cols;
  Mat imgLines = Mat::zeros( rows,cols,CV_8UC3);

  while(1){
	line(imgLines,cv::Point(185,227-163),cv::Point(0,0),cv::Scalar(0,0,255),5);

	imshow("Ori", cobapix);
	imshow("Lines", imgLines);
	if(waitKey(30)==27){
	  break;
	}
  }
  
}
