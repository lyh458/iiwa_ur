#include <moveit/move_group_interface/move_group_interface.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "get_current_pose");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    static const std::string IIWA_UR_GROUP = "iiwa_ur";
    static const std::string IIWA_GROUP = "iiwa_manipulator";
    static const std::string UR_GROUP = "ur_manipulator";

    // The :move_group_interface:`MoveGroupInterface` class can be easily
    // setup using just the name of the planning group you would like to control and plan for.
    moveit::planning_interface::MoveGroupInterface move_group(IIWA_UR_GROUP);
    moveit::planning_interface::MoveGroupInterface move_group_iiwa(IIWA_GROUP);
    moveit::planning_interface::MoveGroupInterface move_group_ur(UR_GROUP);

    // Raw pointers are frequently used to refer to the planning group for improved performance.
    const robot_state::JointModelGroup *joint_model_group =
        move_group.getCurrentState()->getJointModelGroup(IIWA_UR_GROUP);
    const robot_state::JointModelGroup *joint_model_group_iiwa =
        move_group.getCurrentState()->getJointModelGroup(IIWA_GROUP);
    const robot_state::JointModelGroup *joint_model_group_ur =
        move_group.getCurrentState()->getJointModelGroup(UR_GROUP);

    const robot_state::JointModelGroup *joint_model_group_iiwa_1 =
        move_group_iiwa.getCurrentState()->getJointModelGroup(IIWA_GROUP);
    const robot_state::JointModelGroup *joint_model_group_ur_1 =
        move_group_ur.getCurrentState()->getJointModelGroup(UR_GROUP);

    while (ros::ok())
    {
        // Get Joint Values with copyJointGroupPositions
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // We can retreive the current set of joint values stored in the state for the Panda arm.
        ROS_INFO("\33[33m[API TEST]: copyJointGroupPositions:");
        moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
        std::vector<double> joint_group_positions;
        current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
        const std::vector<std::string> &joint_names = joint_model_group->getVariableNames();
        for (std::size_t i = 0; i < joint_names.size(); ++i)
        {
            ROS_INFO("Current position of Joint \33[1;33m%s\33[0m is: \33[32m%f\33[0m", joint_names[i].c_str(), joint_group_positions[i]);
        }


        // Get Active Joint names
        // ^^^^^^^^^^^^^^^^^^^^^^
        // ROS_INFO("\33[33m[API TEST]: getActiveJoints():");
        // const std::vector<std::string> &active_joint_names = move_group.getActiveJoints();
        // for (std::size_t i = 0; i < active_joint_names.size(); ++i)
        // {
        //     ROS_INFO("Active joint \33[1;33m%i\33[0m is \33[1;32m%s\33[0m:", active_joint_names.size(), active_joint_names[i].c_str());
        // }
        
        // Get Joint Values with getCurrentJointValues()
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        ROS_INFO("\33[33m[API TEST]: getCurrentJointValues():");
        const std::vector<std::string> &active_joint_names = move_group.getActiveJoints();
        std::vector<double> current_joint_values = move_group.getCurrentJointValues();
        for (std::size_t i = 0; i < current_joint_values.size(); ++i)
        {
            ROS_INFO("Current position of Joint \33[1;33m%s\33[0m is: \33[32m%f\33[0m", active_joint_names[i].c_str(), current_joint_values[i]);
        }

        // Get Pose of a Link
        // ^^^^^^^^^^^^^^^^^^
        // Get pose for a specified link
        std::string link_name("iiwa_link_ee");
        ROS_INFO("\33[33m[API TEST]: getCurrentPose() -->\33[0m current pose of \33[32m%s\33[0m is", link_name.c_str());
        ROS_INFO_STREAM(move_group.getCurrentPose(link_name));
        
        // ROS_INFO_STREAM("move_group.getCurrentPose()" << move_group.getCurrentPose(link_name));
        // ROS_INFO_STREAM("getCurrentJointValues:" << std::endl);
        // move_group.getCurrentJointValues();
        // ROS_INFO_STREAM("printDirtyInfo" << std::endl);
        // current_state->printDirtyInfo();
        // ROS_INFO_STREAM("printStateInfo" << std::endl);
        // current_state->printStateInfo();
        // // printStatePositions: print value of each joint
        // ROS_INFO_STREAM("printStatePositions" << std::endl);
        // current_state->printStatePositions();
        // ROS_INFO_STREAM("printStatePositionsWithJointLimits" << std::endl);
        // current_state->printStatePositionsWithJointLimits(joint_model_group);
        // ROS_INFO_STREAM("printTransforms" << std::endl);
        // current_state->printTransforms();

        // // vvvvvvvvvvvvvvv测试不同move_group获得的joint_model_group是否一直vvvvvvvvvvvvvvvv //
        // std::vector<double> joint_group_positions_iiwa;
        // current_state->copyJointGroupPositions(joint_model_group_iiwa, joint_group_positions_iiwa);
        // // We can retreive the current set of joint values stored in the state for the Panda arm.
        // const std::vector<std::string> &joint_names_iiwa = joint_model_group_iiwa->getVariableNames();
        // for (std::size_t i = 0; i < joint_names_iiwa.size(); ++i)
        // {
        //     ROS_INFO("[move_group] Current position of Joint \33[1;33m%s\33[0m is: \33[32m%f\33[0m", joint_names_iiwa[i].c_str(), joint_group_positions_iiwa[i]);
        // }

        // std::vector<double> joint_group_positions_iiwa_1;
        // current_state->copyJointGroupPositions(joint_model_group_iiwa_1, joint_group_positions_iiwa_1);
        // const std::vector<std::string> &joint_names_iiwa_1 = joint_model_group_iiwa_1->getVariableNames();
        // for (std::size_t i = 0; i < joint_names_iiwa_1.size(); ++i)
        // {
        //     ROS_INFO("[sub_move_group] Current position of Joint \33[1;33m%s\33[0m is: \33[32m%f\33[0m", joint_names_iiwa_1[i].c_str(), joint_group_positions_iiwa_1[i]);
        // }
        // // ^^^^^^^^^^^^^^测试不同move_group获得的joint_model_group是否一致，YES^^^^^^^^^^^^^ //
    }
    ros::shutdown();

    // END_TUTORIAL

    return 0;
}