#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <opencv2/opencv.hpp>

using namespace std;

int user_data;
const double u0 = 319.52883;
const double v0 = 271.61749;
const double fx = 528.57523;
const double fy = 527.57387;


void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
 viewer.setBackgroundColor(0.0, 0.0, 0.0);
}

int main()
{
 pcl::PointCloud<pcl::PointXYZRGB> cloud_a;
 pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

 cv::Mat color = cv::imread("rgb.jpg");
 cv::Mat depth1 = cv::imread("depth.png");

 cv::Size dsize = cv::Size(color.cols, color.rows);
 cv::Mat depth = cv::Mat(dsize, CV_8UC3);
 resize(depth1,depth,dsize);

 int rowNumber = color.rows;
 int colNumber = color.cols;

 cloud_a.height = rowNumber;
 cloud_a.width = colNumber;
 cloud_a.points.resize(cloud_a.width * cloud_a.height);

 for (unsigned int u = 0; u < rowNumber; ++u)
 {
  for (unsigned int v = 0; v < colNumber; ++v)
  {
   unsigned int num = u*colNumber + v;
   double Xw = 0, Yw = 0, Zw = 0;

   //Zw = ((double)depth.at<uchar>(u, v)) / 255.0 * 10001.0;
   //Xw = (u - u0) * Zw / fx;
   //Yw = (v - v0) * Zw / fy;
   Zw = ((double)depth.at<uchar>(u, v));
   Xw = u;
      Yw = v;

   cloud_a.points[num].b = color.at<cv::Vec3b>(u, v)[0];
   cloud_a.points[num].g = color.at<cv::Vec3b>(u, v)[1];
   cloud_a.points[num].r = color.at<cv::Vec3b>(u, v)[2];

   cloud_a.points[num].x = Xw;
   cloud_a.points[num].y = Yw;
   cloud_a.points[num].z = Zw;
  }
 }

 *cloud = cloud_a;

 pcl::visualization::CloudViewer viewer("Cloud Viewer");/*
 viewer.showCloud(cloud);

 viewer.runOnVisualizationThreadOnce(viewerOneOff);

 while (!viewer.wasStopped())
 {
  user_data = 9;
 }
*/
 return 0;
}

