#include "opencv2/opencv.hpp"    
using namespace cv;  
#include <iostream>    
using namespace std;  
int main()  
{     
    Mat srcImg = imread("/home/jetuz/photo/test12", CV_LOAD_IMAGE_COLOR);  
     
    imshow("srcImg", srcImg); 

    Mat copyImg = srcImg.clone();  
    cvtColor(srcImg, srcImg, CV_BGR2GRAY);  
    threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY);  
    imshow("threshold", srcImg);  
    vector <vector<Point> > contours;  
    vector<Vec4i> hierarcy;   
     
    findContours(srcImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);    
       
    drawContours(copyImg, contours, -1, Scalar(0, 255, 0), 1, 8);  
       
    vector<Rect> boundRect(contours.size());  
   
    vector<RotatedRect> roRect(contours.size());  
  
    for (int i = 0; i < contours.size(); i++)  
    {  
        
        boundRect[i] = boundingRect(Mat(contours[i]));  
          
        int width = boundRect[i].width;  
        int height = boundRect[i].height;  
        int x = boundRect[i].x;  
        int y = boundRect[i].y;  
         
        rectangle(copyImg, Rect(x, y, width, height), Scalar(255, 0, 0), 2, 8);  
        
        roRect[i] = minAreaRect(Mat(contours[i]));  
         
        Point2f pts[4];  
        roRect[i].points(pts);  
         
        line(copyImg, pts[0], pts[1], Scalar(0, 0, 255), 2, 8);  
        line(copyImg, pts[0], pts[3], Scalar(0, 0, 255), 2, 8);  
        line(copyImg, pts[2], pts[1], Scalar(0, 0, 255), 2, 8);  
        line(copyImg, pts[2], pts[3], Scalar(0, 0, 255), 2, 8);  
    }  
    
    

    imshow("ÂÖÀªºÍÕýÍâ½Ó¾ØÐÎºÍ×îÐ¡Íâ½Ó¾ØÐÎ", copyImg); 

    waitKey(0);  
    return 0;  
}  
