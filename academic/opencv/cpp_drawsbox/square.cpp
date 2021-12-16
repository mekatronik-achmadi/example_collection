#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(){
  
  Mat imgsqr(200,200,CV_8UC3,Scalar(0,0,0));
  Rect imgrect(100,100,20,20);
  
  rectangle(imgsqr,imgrect,Scalar(255,255,255),-1);
  Mat imgsqr1;
  cvtColor(imgsqr, imgsqr1, COLOR_BGR2GRAY);
  
  Moments oMoments = moments(imgsqr1);
  
  double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;
  
  int posX = dM10 / dArea;
  int posY = dM01 / dArea;
  
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  
  findContours( imgsqr1, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  
  int Area = contourArea(contours[0]);
  
  int s = sqrt(Area);
  
  int posX1=(posX-(s/2))-5;
  int posY1=(posY-(s/2))-5;
  
  cout << "posX =" << posX << " posY=" << posY <<endl;
  cout << "dArea =" << dArea << " s =" << s << " posX1 =" << posX1 << " posY1=" << posY1 << endl;
  cout << "Area=" << Area << endl;
  
  Mat imgsqr2= Mat::zeros( imgsqr.size(), CV_8UC3 );
  Rect imgrect2(posX1,posY1,s+10,s+10);
  rectangle(imgsqr2,imgrect2,Scalar(0,0,255),2);

  imgsqr=imgsqr+imgsqr2;
  
  imshow("square",imgsqr);
  
  if(waitKey()==27){
    cout << "esc key is pressed by user" << endl; 
  }
}
