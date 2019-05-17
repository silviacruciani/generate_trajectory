/*
 * trajectory_generator.hpp
 *
 *  Created on: May 17, 2019
 *      Author: Silvia Cruciani
*/

#ifndef GENERATE_TRAJECTORY_TRAJECTORY_GENERATOR
#define GENERATE_TRAJECTORY_TRAJECTORY_GENERATOR

#include <ros/ros.h>
#include <joint_trajectory_generator/trajectory_generation.h>

namespace generate_trajectory{
    class JointTrajectoryGenerator{
    public:
        /**
            @param max_vel the maximum allowed velocity
            @param mac_acc the maximum allowed acceleration
            @param size the number of waypoints
        */
        JointTrajectoryGenerator(double max_vel, double max_acc, uint size);
        ~JointTrajectoryGenerator();

        /**
            generates a trajectory with velocity and acceleration profile
            @param input_traj a joint trajectory message filled only with position values
            @return the trajectory message with timing law
        */
        trajectory_msgs::JointTrajectory generate(trajectory_msgs::JointTrajectory input_traj) const;

        /**
            sets a new number of waypoints in the trajectory generator
            @param size the number of waypoints
        */
        void setWaypointsNumber(uint size);

        /**
            sets the velocity and acceleration limits in the trajectory generator
            @param max_vel the maximum allowed velocity
            @param max_acc the maximum allowed acceleration
        */
        void setLimits(double max_vel, double max_acc);
    private:
        std::shared_ptr<trajectory::TrajectoryGenerator> traj_gen_;
        double max_acc_, max_vel_;
        uint waypoints_size_;
        
    };
}

#endif