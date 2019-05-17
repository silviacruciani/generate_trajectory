#! /usr/bin/env python

"""
    This file contains a test for the trajectory generator server

    @author: Silvia Cruciani (cruciani@kth.se)
"""

import rospy
from generate_trajectory.srv import *
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

def main():
    #make three joint trajectory points
    p1 = JointTrajectoryPoint()
    p1.positions = [0.0, 0.0, 0.0]
    p2 = JointTrajectoryPoint()
    p2.positions = [1.0, 0.5, 0.7]
    p3 = JointTrajectoryPoint()
    p3.positions = [2.0, 1.0, 1.5]

    waypoints = [p1, p2, p3]

    req = GenerateTrajectoryRequest()
    req.waypoints = waypoints
    req.max_vel = 1.0
    req.max_acc = 0.1

    rospy.wait_for_service('/generate_trajectory')

    try:
        trajectory_generator = rospy.ServiceProxy('/generate_trajectory', GenerateTrajectory)
        resp = trajectory_generator(req)
        print (resp)
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

if __name__ == '__main__':
    main()