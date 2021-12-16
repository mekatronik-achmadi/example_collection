#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(){
  VideoCapture cap(1);
  
  if ( !cap.isOpened()){
      cout << "Cannot open the web cam" << endl;
      return -1;
  }
  
  int iLowH = 0;
  int iHighH = 179;

  int iLowS = 171;
  int iHighS = 255;

  int iLowV = 120;
  int iHighV = 255;

  namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
  
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
  
  while(true){
    
    Mat imgOriginal;
    
    bool bSuccess = cap.read(imgOriginal);
    Mat imgsqr= Mat::zeros( imgOriginal.size(), CV_8UC3 );

    if (!bSuccess) {
	  cout << "Cannot read a frame from video stream" << endl;
	  break;
    }
    
    Mat imgHSV;

    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

    Mat imgThresholded;
    Mat imgThresholded2;
    
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
    imshow("Thresholded Image", imgThresholded);
    imgThresholded2=imgThresholded;
    
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    Moments oMoments = moments(imgThresholded);
    
    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    if(dArea > 10000){
      
      int posX = dM10 / dArea;
      int posY = dM01 / dArea;
      
      vector<vector<Point> > contours;
      vector<Vec4i> hierarchy;
      
      findContours( imgThresholded2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
      
      int Area = contourArea(contours[0]);

      int s = sqrt(Area);

      int posX1=(posX-(s/2))-5;
      int posY1=(posY-(s/2))-5;
      
      cout << "posX =" << posX << " posY=" << posY <<endl;
      cout << "dArea =" << dArea << " s =" << s << " posX1 =" << posX1 << " posY1=" << posY1 << endl;
      cout << "Area=" << Area << endl;
      
      Rect imgrect(posX1,posY1,s+10,s+10);
      rectangle(imgsqr,imgrect,Scalar(0,0,255),2);
      
    }
    
    Mat imgFinal;
    
    imshow("Thresholded Image 2", imgThresholded2);
    imgFinal = imgOriginal + imgsqr;
//     imgFinal = imgOriginal;
    imshow("Final", imgFinal);
    
    if(waitKey(30)==27){
	cout << "esc key is pressed by user" << endl;
	break; 
    }
  }
  return 0;
}
