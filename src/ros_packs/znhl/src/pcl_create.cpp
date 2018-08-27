#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <bits/stdc++.h>

pcl::PointCloud<pcl::PointXYZ> gen_pipe(int round, int layer, int length) {

    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.width = round * layer;
    cloud.height = 1;
    cloud.points.resize(cloud.width * cloud.height);

    for (size_t i = 0; i < cloud.points.size (); ++i)
    {
        double theta = (double)(i % round) / round * 2 * acos(-1.0);
        cloud.points[i].x = (double)(i / round + 1) / layer * length;
        cloud.points[i].y = cos(theta) * (1 + rand () / (RAND_MAX + 1.0f) / 7);
        cloud.points[i].z = sin(theta) * (1 + rand () / (RAND_MAX + 1.0f) / 7);
    }
    return cloud;
}

main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_create");

    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 1);
    //pcl::PointCloud<pcl::PointXYZ> cloud = gen_circle();
    sensor_msgs::PointCloud2 output;

    //Convert the cloud to ROS message


    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pcl::toROSMsg(gen_pipe(200, 100, 5), output);
        output.header.frame_id = "world";
        pcl_pub.publish(output);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}