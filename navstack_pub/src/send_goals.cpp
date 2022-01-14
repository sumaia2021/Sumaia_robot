/*
 * 1 = First_Location_(START THE MAZE)
 * 2 = Second_Location
 * 3 = Third_Location
 * 4 = Forth_Location 
 * 5 = Fifth_Location
 * 6 = Sixth_Location
 * 7 = (EXIT FROM MAZE)_Location
(EXIT FROM MAZE)
 */
 
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
 
using namespace std;
 
// Action specification for move_base
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
int main(int argc, char** argv){
   
  // Connect to ROS
  ros::init(argc, argv, "simple_navigation_goals");
 
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
 
  // Wait for the action server to come up so that we can begin processing goals.
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
 
  int user_choice = 7;
  char choice_to_continue = 'Y';
  bool run = true;
     
  while(run) {
 
    // Ask the user where he wants the robot to go?
    cout << "\nWhere do you want the robot to go?" << endl;
    cout << "\n1 = First_Location" << endl;
    cout << "2 = Second_Location" << endl;
    cout << "3 = Third_Location" << endl;
    cout << "4 = Forth_Location" << endl;
    cout << "5 = Fifth_Location" << endl;
    cout << "6 = Sixth_Location" << endl;
    cout << "7 = (EXIT FROM MAZE)" << endl;
    cout << "\nEnter a number: ";
    cin >> user_choice;
 
    // Create a new goal to send to move_base 
    move_base_msgs::MoveBaseGoal goal;
 
    // Send a goal to the robot
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
         
    bool valid_selection = true;
 
    // Use map_server to load the map of the environment on the /map topic. 
    // Launch RViz and click the Publish Point button in RViz to 
    // display the coordinates to the /clicked_point topic.
    switch (user_choice) {
      case 1:
        cout << "\nGoal Location: Firsi_Location(STRAT THE MAZE)\n" << endl;
        goal.target_pose.pose.position.x = -4.0;
    goal.target_pose.pose.position.y = 1.47;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 2:
        cout << "\nGoal Location: Second_Location\n" << endl;
        goal.target_pose.pose.position.x = -4.8;
    goal.target_pose.pose.position.y = 3.5;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 3:
        cout << "\nGoal Location: Third_Location\n" << endl;
        goal.target_pose.pose.position.x = -4.1;
    goal.target_pose.pose.position.y = 5.5;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 4:
        cout << "\nGoal Location: Forth_Location\n" << endl;
        goal.target_pose.pose.position.x = 2.5;
    goal.target_pose.pose.position.y = 5.4;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 5:
        cout << "\nGoal Location: Fifth_Location\n" << endl;
        goal.target_pose.pose.position.x = 2.5;
    goal.target_pose.pose.position.y = 1.5;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 6:
        cout << "\nGoal Location: Sixth_Location\n" << endl;
        goal.target_pose.pose.position.x = 4.2;
    goal.target_pose.pose.position.y = 1.4;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 7:
        cout << "\nGoal Location:(EXIT FROM MAZE)\n" << endl;
        goal.target_pose.pose.position.x = 4.2;
    goal.target_pose.pose.position.y = -3.5;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      default:
        cout << "\nInvalid selection. Please try again.\n" << endl;
        valid_selection = false;
    }       
         
    // Go back to beginning if the selection is invalid.
    if(!valid_selection) {
      continue;
    }
 
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
 
    // Wait until the robot reaches the goal
    ac.waitForResult();
 
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("The robot has arrived at the goal location");
    else
      ROS_INFO("The robot failed to reach the goal location for some reason");
         
    // Ask the user if he wants to continue giving goals
    do {
      cout << "\nWould you like to go to another destination? (Y/N)" << endl;
      cin >> choice_to_continue;
      choice_to_continue = tolower(choice_to_continue); // Put your letter to its lower case
    } while (choice_to_continue != 'n' && choice_to_continue != 'y'); 
 
    if(choice_to_continue =='n') {
        run = false;
    }  
  }
   
  return 0;
}
