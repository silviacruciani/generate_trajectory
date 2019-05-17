/*
 * trajectory_generator_server.cpp
 *
 *  Created on: May 17, 2019
 *      Author: Silvia Cruciani
*/

#include "generate_trajectory/trajectory_generator.hpp"
#include "generate_trajectory/GenerateTrajectory.h"
#include <ros/ros.h>

#define EPSILON 0.0000001

class TrajectoryGeneratorServer{
public:
    TrajectoryGeneratorServer(){
        max_vel_=0.0; 
        max_acc_=0.0;
        size_=0;
        joint_traj_gen_=std::shared_ptr<generate_trajectory::JointTrajectoryGenerator>(new generate_trajectory::JointTrajectoryGenerator(max_vel_, max_acc_, size_));
    }

    ~TrajectoryGeneratorServer(){

    }

    bool generateTrajectory(generate_trajectory::GenerateTrajectoryRequest &req, generate_trajectory::GenerateTrajectoryResponse &res){
        //update the trajectory generator with the new values
        ROS_INFO_STREAM("Received waypoints of size: "<<req.waypoints.size());
        initializeTrajectoryGenerator(req.max_vel, req.max_acc, req.waypoints.size());
        //initialize the joint trajectory msgs
        trajectory_msgs::JointTrajectory input_traj;
        input_traj.points=req.waypoints;
        // double time=0.0;
        // for(int i=0; i<input_traj.points.size(); i++){
        //     input_traj.points[i].time_from_start=ros::Duration(time);
        //     time+=1.0;
        // }
        ROS_INFO("preparing to generate trajectory");
        //generate the trajectory
        trajectory_msgs::JointTrajectory ouptput_traj=joint_traj_gen_->generate(input_traj);
        ROS_INFO("Trajectory generated!");
        res.trajectory=ouptput_traj;
        return true;
    }

    /**
        resets the trajectory generator with the new values
    */
    void initializeTrajectoryGenerator(double max_vel, double max_acc, uint size){
        if(size!=size_){
            size_=size;
            joint_traj_gen_->setWaypointsNumber(size_);
        }
        if(fabs(max_vel-max_vel_)>EPSILON || fabs(max_acc-max_acc_)>EPSILON){
            max_vel_=max_vel;
            max_acc_=max_acc;
            joint_traj_gen_->setLimits(max_vel_, max_acc_);
        }
    }

private:
    std::shared_ptr<generate_trajectory::JointTrajectoryGenerator> joint_traj_gen_;
    double max_vel_, max_acc_;
    uint size_;

};


int main(int argc, char *argv[]){
    ros::init(argc, argv, "trajectory_generator_server");
    ros::NodeHandle n;
    TrajectoryGeneratorServer traj_gen;
    ros::ServiceServer service=n.advertiseService("generate_trajectory", &TrajectoryGeneratorServer::generateTrajectory, &traj_gen);
    ROS_INFO("Server ready to generate trajectories.");
    ros::spin();
    return 0;
}