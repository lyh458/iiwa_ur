# IIWA_UR Dual-Arm ROS Packages

![iiwa-ur-dual-arm](https://cdn.jsdelivr.net/gh/lyh458/ImageRepo@main/image/1628164009592-1628164009582.png)

- **iiwa_ur_description**: a URDF for a KUKA LBR IIWA robot and a universal robot (default: iiwa7 and ur5).
- **iiwa_ur_moveit_config**: a MoveIt! package to work with the robot description just defined.
- **iiwa_ur_bringup**: a package to bringup the iiwa and ur union.
- **iiwa_ur_gazebo**: a package simulate motion in gazebo for the union.

## Dependencies

- [iiwa_stack](https://github.com/IFL-CAMP/iiwa_stack): ROS integration for the KUKA LBR IIWA R800/R820 (7/14 Kg).
- [universal_robot](https://github.com/ros-industrial/universal_robot): ROS-Industrial Universal Robots support.
- [ur_modern_driver](https://github.com/ros-industrial/ur_modern_driver): ROS 1 driver for CB1 and CB2 controllers with UR5 or UR10 robots from Universal Robots.

**Note**: I am using a UR5 with CB2, so I have to use this driver, but if you use a UR with >= CB3, you can't use these packages directly without some modifications for the new driver [ur_robot_driver](https://github.com/UniversalRobots/Universal_Robots_ROS_Driver) and [fmauch/universal_robot](https://github.com/fmauch/universal_robot).


## Supported ROS Distribution

ROS Melodic.

## Usages

After installing all the dependencies, you can:

- Only visualize in RVIZ:

  ```xml
  roslaunch iiwa_ur_moveit_config demo.launch
  ```

- Real robot control:

  - please make sure that iiwa and ur are in the same subnet. eg. iiwa: `172.31.1.147`, ur: `172.31.1.12`.

  - roslaunch the integrated launch file

    ```xml
    roslaunch iiwa_ur_moveit_config moveit_planning_execution.launch sim:=false ur_ip:=<your_ur_ip>
    ```

The rqt_graph:

![rqt_graph_real](https://cdn.jsdelivr.net/gh/lyh458/ImageRepo@main/image/1628570846470-1628570846458-iiwa_ur_moveit_real_robot_seperated_namespace.png)

- Simulate in Gazebo:

  ```xml
  roslaunch iiwa_ur_moveit_config moveit_planning_execution.launch sim:=true
  ```

The rqt_graph:

![rqt_graph_sim](https://cdn.jsdelivr.net/gh/lyh458/ImageRepo@main/image/1628571178979-1628571178961-iiwa_ur_moveit_gazebo_seperated_namespace.png)

**some other options may be used**:

- `-limited`: if true, use the joint_limited version (joint limits restricted to [-pi,pi]) of UR, default `false`.
- `-use_pedestal`： if true, use pedestal instead of simple robot, default `true`.
- `-ur_max_payload`: maximum payload for ur, `5.0` for ur5, `3.0` for ur3, `10.0` for ur10, default `5.0`. Note: musted be set if you used ur3 or ur10 instead of ur5.

More options info can be checked in launch files.

## Other Branches

This branch `master` holds iiwa and ur in two different namespace, if you prefect a unified namespace version, you can try this branch [all-in-one-namespace](https://github.com/lyh458/iiwa_ur/tree/all-in-one-namespace), whose almost all nodes and topics are included in a same namespace, `dual_arm` by default.

## References

- [dual_ur](https://github.com/Liuyvjin/shixi_dual_ur)