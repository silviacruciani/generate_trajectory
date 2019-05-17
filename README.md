# generate_trajectory

This ros package contains a server to generate a joint trajectory from a set of waypoints in joint space. <br />
It requires the package joint_trajectory_generator from pr2_common_actions.
```bash
    sudo apt-get install ros-kinetic-pr2-common-actions 
```

### usage example


The file *trajectory_generator_server.cpp* contains the main server to transform the list of waypoints into a joint trajectory.
```bash
    rosrun generate_trajectory trajectory_generator_server
```

A client node should send a request using the definition of the srv file *GenerateTrajectory.srv*. <br />
Apart from the wayponts, also the maximum velocity and the maximum acceleration must be specified. <br />
<br />
The file *trajectory_generator_client.py* contains an example with three joints and three waypoints. Run:
```bash
   rosrun generate_trajectory trajectory_generator_client.py 
```
You should see the resulting joint trajectory that follows the given waypoints.