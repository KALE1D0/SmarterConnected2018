#include <pcl/point_cloud.h>
#include <opencv2/opencv.hpp>
#include <iostream>  
#include <pcl/io/pcd_io.h>
#include <pcl/io/png_io.h>  
#include <pcl/io/image_depth.h>
#include <pcl/point_types.h>  
#include <bits/stdc++.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/range_image/range_image_planar.h>
#include <pcl/visualization/common/float_image_utils.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

int main (int argc, char **argv)
{

    cv::Mat depth_image;
    depth_image.create(480, 640, CV_32F);
    double r = 480 / 1.732, s = sqrt(r * r - 240 * 240);
    for (int u = 0; u < depth_image.rows; ++u)
    {
        //double dep = cos(atan((double)abs(240 - u) / s)) * r;
        double dep = sqrt(r * r - (240 - u) * (240 - u)) * 0.8;
        for (int v = 0; v < depth_image.cols; ++v)
        {
            //double theta = (double)u / depth_image.rows * acos(-1.0) / 3;
            //cos(theta) * (1 + rand () / (RAND_MAX + 1.0f) / 30)
            depth_image.at<float>(u, v) = (float)(r - dep) * (1 + rand () / (RAND_MAX + 1.0f) / 6);
        }
        std::cout << dep << std::endl;
    }
    depth_image.convertTo(depth_image, CV_8U);
    cv::imwrite("depth.png", depth_image);
    return 0;
}