#include "ros/ros.h"
#include <iostream>
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
  string videoFile;
  double rateFactor = 1.0;
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <video_file> [rate]\n";
    return -1;
  } else {
    videoFile = argv[1];
    if (argc >= 3) {
      rateFactor = atof(argv[2]);
    }
  }
  //initialize node
  ros::init(argc, argv, "cv_example");

  // node handler
  ros::NodeHandle n;
  cv::VideoCapture cap(videoFile);

  // Check if camera opened successfully
  if(!cap.isOpened()){
   	cout << "Error opening video stream" << endl;
        return -2;
  }
  
  // Default resolutions of the frame are obtained.The default resolutions are system dependent.
  int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  double rate = cap.get(cv::CAP_PROP_FPS);
  if (rate < 1.0) {
    rate = 30;
  }
  int sleepInterval = 1000 / (rate * rateFactor);
  if (sleepInterval == 0)
    sleepInterval = 1;
  int count = 0;
  while(ros::ok()){
    Mat frame;
   
    // Capture frame-by-frame
    cap >> frame;
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;
    if (count == 0) {
      cout << "Channels " << frame.channels() << " Bitdepth (bytes) " << frame.elemSize1() << endl;
    }
    // Display the resulting frame    
    imshow( "Frame", frame );
 
    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(sleepInterval);
    if( c == 27 ) 
      break;
    ++count;
  }

  // When everything done, release the video capture and write object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
  return 0;
}
