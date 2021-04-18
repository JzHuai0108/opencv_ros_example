# opencv_ros_example
ROS opencv example

Installation: 
- install OpenCV dependencies:

  sudo apt-get install ros-kinetic-cv-bridge
  
  sudo apt-get install ros-kinetic-cv-camera
  
- clone repository:

  cd ~/catkin_ws/src
  
  git clone https://github.com/JzHuai0108/opencv_ros_example
  
- compile example:

  cd ~/catkin_ws
  
  catkin build
  
To run:
- set camera (0 - first camera):

  rosparam set cv_camera/device_id 0 
  
- run:  

  cd ~/catkin_ws
  
  rosrun opencv_ros_example opencv_ros_example_node
