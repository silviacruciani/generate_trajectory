/*
 * trajectory_generator.cpp
 *
 *  Created on: May 17, 2019
 *      Author: Silvia Cruciani
*/

#include "generate_trajectory/trajectory_generator.hpp"

using namespace generate_trajectory;

JointTrajectoryGenerator::JointTrajectoryGenerator(double max_vel, double max_acc, uint size){
    waypoints_size_=size;
    max_vel_=max_vel;
    max_acc_=max_acc;
    traj_gen_=std::shared_ptr<trajectory::TrajectoryGenerator>(new trajectory::TrajectoryGenerator(max_vel, max_acc, size)); 
}

JointTrajectoryGenerator::~JointTrajectoryGenerator(){

}

void JointTrajectoryGenerator::setWaypointsNumber(uint size){
    waypoints_size_=size;
    traj_gen_=std::shared_ptr<trajectory::TrajectoryGenerator>(new trajectory::TrajectoryGenerator(max_vel_, max_acc_, waypoints_size_));
}

void JointTrajectoryGenerator::setLimits(double max_vel, double max_acc){
    max_acc_=max_acc;
    max_vel_=max_vel;
    traj_gen_=std::shared_ptr<trajectory::TrajectoryGenerator>(new trajectory::TrajectoryGenerator(max_vel_, max_acc_, waypoints_size_)); 

}

trajectory_msgs::JointTrajectory JointTrajectoryGenerator::generate(trajectory_msgs::JointTrajectory input_traj) const{
    trajectory_msgs::JointTrajectory output_traj;
    traj_gen_->generate(input_traj, output_traj);

    return output_traj;
}