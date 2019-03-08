================Prerequisite=================
1. Tiago workspace

2. Make sure to include ros package "dock_charge_sm_msgs" into the workspace. Package can be found at: https://github.com/pal-robotics/iros_mmh_msgs, please clone the whole repository into workspace and compile.

================Action Server Interface======
1. Make sure to first navigate the robot to the specified areas(Please check manual).


2. For docking, please run the following command,
$ rosrun actionlib axclient.py /go_and_dock

A window will pop up, change the parameter "use_current_pose" to be true, and click "send goal".


3. For undocking, please run the following command,
$ rosrun actionlib axclient.py /undocker_server

After the window pops up, click "send goal".


===============Rviz Plugin Interface Not found====

