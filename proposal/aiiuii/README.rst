==============================
Interbotix Ros Xsarms Toolkits
==============================



Basic Information
=================

The GitHub repository: https://github.com/aiiuii/Interbotix_Ros_Xsarms_Toolkits

Problem to Solve
================

Recently, my supervising professor purchased a robotic arm for the lab. Unfortunately, no one in the lab had any experience with it, so learning how to use it ended up being one of my professor's assigned tasks.

For this project, I intended to create a GUI system that would allow users to control the robot arm. Although the vendor already had an example, it was too simple in its functionality.

In this project I will use the following tools:

* PyQt: 
      To create GUI interface.
* ROS: 
      The Robot Operating System (ROS) is a set of software libraries and tools that help you build robot applications.
* IRROS: 
      The SDK developed by the vendor.It provides API to interact with robotic arm.
* MoveIt: 
      MoveIt is ROS's most advanced and flexible library for motion planning and manipulation tasks. It integrates state-of-the-art inverse kinematics solvers, path planning algorithms, and collision detection into a single, unified ROS interface.



Prospective Users
=================

Anyone who needs to use robotic arm.

System Architecture
===================

1. 
The system will monitor ROS nodes created by IRROS, analyze data and show related information on the screen.

2.
The system will provides GUI to adjust target position and orientation.Then, users can perform moveit_planning command and robotic arm will follow it.

3. 
The system will allows users to record the state of robotic arm and replay it.

API Description
===============

Example
~~~~~~~~~~~

``getinfo(string node_name)``: Get information from ROS nodes.

``record(double* joint_state, string record_name="")``: Record the current state of robotic arm and store shortcuts to access it when needed. 

``replay(string record_name)``: Replay of previously stored states.

``move(double* joint_state)``: Call the API from MoveIt and pass the result into ROS nodes.

Engineering Infrastructure
==========================

build system: 
      catkin_make

testing framework: 
      pytest

version control:
      git

Schedule
========

* Week 1: Familiar with the IRROS structure.
* Week 2: Familiar with the MoveIt API.
* Week 3: Using catkin_make to build workspace and setting launch files.
* Week 4: Implement the set of functions to manipulate robotic arm. 
* Week 5: Implement the set of functions to record and replay.
* Week 6: Build GUI with PyQt
* Week 7: Prepare presentation
* Week 8: Buffer

References
==========

* ROS: https://www.ros.org/
* MoveIt: https://moveit.ros.org/
* IRROS: https://github.com/Interbotix
* PyQt: https://wiki.python.org/moin/PyQt
