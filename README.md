<!--
 * @Author: lyh458
 * @Date: 2021-08-09 16:52:34
 * @LastEditTime: 2021-08-09 21:35:58
 * @LastEditors: lyh458
 * @Description: TO DO
 * @FilePath: /iiwa_ur/README.md
-->

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

**Note**: I am used a UR5 with CB2, so I have to use this driver, but if you use a UR with >= CB3, you can't used these packages directly without some modifications for the new driver [ur_robot_driver](https://github.com/UniversalRobots/Universal_Robots_ROS_Driver) and [fmauch/universal_robot](https://github.com/fmauch/universal_robot).

## Usages

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

- Simulate in Gazebo:

```xml
roslaunch iiwa_ur_moveit_config moveit_planning_execution.launch sim:=true
```

**some other options may be used**:

- `-limited`: if true, use the joint_limited version (joint limits restricted to [-pi,pi]) of UR, default `false`.
- `-use_pedestal`： if true, use pedestal instead of simple robot, default `true`.
- `-ur_max_payload`: maximum payload for ur, `5.0` for ur5, `3.0` for ur3, `10.0` for ur10, default `5.0`. Note: musted be set if you used ur3 or ur10 instead of ur5.

More options info can be checked in launch files.

## References

- [dual_ur](https://github.com/Liuyvjin/shixi_dual_ur)