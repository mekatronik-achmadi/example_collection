#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(){
  VideoCapture cap(1); //capture the video from web cam

  // if not success, exit program
  if ( !cap.isOpened()){
      cout << "Cannot open the web cam" << endl;
      return -1;
  }
  
  //namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  
  int iLowH = 0;
  int iHighH = 179;

  int iLowS = 171;
  int iHighS = 255;

  int iLowV = 120;
  int iHighV = 255;
  
      //Create trackbars in "Control" window
//   cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
//   cvCreateTrackbar("HighH", "Control", &iHighH, 179);
// 
//   cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
//   cvCreateTrackbar("HighS", "Control", &iHighS, 255);
// 
//   cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
//   cvCreateTrackbar("HighV", "Control", &iHighV, 255);
  
  int iLastX = -1; 
  int iLastY = -1;
  
  //Capture a temporary image from the camera
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
  
  Mat imgTmp;
  cap.read(imgTmp);
  
//   resize(imgTmp, imgTmp, Size(320, 240), 0, 0, INTER_CUBIC);
  
  //Create a black image with the size as the camera output
  Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );
  
  while(true){
    
    Mat imgOriginal;
    
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    bool bSuccess = cap.read(imgOriginal); // read a new frame from video

    //if not success, break loop
    if (!bSuccess) {
	  cout << "Cannot read a frame from video stream" << endl;
	  break;
    }
    
//     resize(imgOriginal, imgOriginal, Size(320, 240), 0, 0, INTER_CUBIC);
    
    Mat imgHSV;

    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    Mat imgThresholded;
    
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    
    //morphological opening (removes small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

    //morphological closing (removes small holes from the foreground)
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    
    //Calculate the moments of the thresholded image
    Moments oMoments = moments(imgThresholded);
    
    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;
    
    // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
    if(dArea > 10000){
      //calculate the position of the ball
      int posX = dM10 / dArea;
      int posY = dM01 / dArea;
      
      cout << "posX = " << posX << " posY = " << posY << endl;
      
      if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0){
        line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
      }
      
      iLastX = posX;
      iLastY = posY;
      
    }
    
    imshow("Thresholded Image", imgThresholded); //show the thresholded image

    //imgOriginal = imgOriginal + imgLines;
//     imshow("Lines", imgLines); //show the original image
    imshow("Original", imgOriginal); //show the original image
    
      //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
    if(waitKey(30)==27){
	cout << "esc key is pressed by user" << endl;
	break; 
    }
  }
  return 0;
}
