#include <ros/ros.h>
#include <apriltags_ros/AprilTagDetection.h>
#include <apriltags_ros/AprilTagDetectionArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <vector>
#include <cmath>
#include <boost/bind.hpp>
#include<std_msgs/Int32.h>

void atCallback (const AprilTagDetectionArray& atArray, ros::Publisher &id_pub) {
    std::vector<AprilTagDetection>::iterator it;
    int first = 1;
    int id;
    geometry_msgs::PoseStamped tag_pose;
    double maxdist;
    double dist;
    for(it = atArray.detections.begin(); it != atArray.detections.end(); ++it) {
        tag_pose = it->pose;
        dist = sqrt(std::pow(tag_pose.pose.position.x,2) + std::pow(tag_pose.pose.position.y,2) + std::pow(tag_pose.pose.position.z,2));
        if(first) {
            first = 0;
            id = it->id;
            maxdist = dist;
        } else if(dist > maxdist){
            id = it->id;
        }
    }
    std_msgs::Int32 msg;
    msg.data = id;
    id_pub.publish(msg);
}

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "id_publisher");
    ros::NodeHandle nh;
    ros::Publisher id_pub = nh.advertise<std_msgs::Int32>("id",1000);
    ros::Subscriber at_sub = nh.subscribe<AprilTagDetectionArray>("tag_detections", 100, bind(atCallback, _1, boost::ref(id_pub)));
    ros::spin();
    return 0;
}
