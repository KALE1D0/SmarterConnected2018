#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"



using namespace std;
using namespace cv;
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */


long temptime=0;
 char base_name[256];
 string str;

void callback(const sensor_msgs::ImageConstPtr& msg)
{
cv_bridge::CvImagePtr cv_ptr;
try
 {
 cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
 }
 catch (cv_bridge::Exception& e)
 {
   ROS_ERROR("cv_bridge exception: %s", e.what());
 return;
 }

    Mat oriImg = cv_ptr->image;
    Mat srcImg; cvtColor(oriImg, srcImg, CV_BGR2GRAY);

    imshow("source", srcImg);
    Mat dstImg = srcImg.clone();

    GaussianBlur(srcImg,srcImg,Size(3,3),0,0);
    Canny(srcImg,srcImg,40,60,3);  

    cvtColor(srcImg, dstImg, CV_GRAY2RGB);

    imshow("threshold", srcImg);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarcy;

    findContours(srcImg, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    cout<<"num="<<contours.size()<<endl;
    cout<<endl;
    vector<Rect> boundRect(contours.size());
    vector<RotatedRect> box(contours.size());
    Point2f rect[4];
    for(int i=0; i<contours.size(); i++)
    {
        box[i] = minAreaRect(Mat(contours[i]));
        boundRect[i] = boundingRect(Mat(contours[i]));
        cout<<box[i].angle<<endl;
        cout<<box[i].center<<endl;
        cout<<box[i].size.width<<endl;
        cout<<box[i].size.height<<endl;
        cout<<endl;

        char width[20], height[20];

        sprintf(width, "width=%0.2f", box[i].size.width);
        sprintf(height, "height=%0.2f", box[i].size.height);

        box[i].points(rect);

        for(int j=0; j<4; j++)
        {
            line(dstImg, rect[j], rect[(j+1)%4], Scalar(0,255,0), 1, 8);
            line(oriImg, rect[j], rect[(j+1)%4], Scalar(0,255,0), 1, 8);

        }
    
    }
    imshow("dst", dstImg);
    imshow("ori",oriImg);
 cv::waitKey(3);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "recv_pic");



  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/camera/image_raw", 1000, callback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();
  return 0;
}