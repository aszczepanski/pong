#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <iostream>
#include <common/IThread.h>
#include <common/Mutex.h>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace common
{

struct Selection
{
  bool selectObject;
  bool ready;
  cv::Rect field;
  cv::Point start;
};

class SharedMemory;

class Camera
{
public:
  Camera(common::SharedMemory&);
  ~Camera();

  void getPosition(int& position) const;
  void init();
  static void onMouse(int event, int x, int y, int flags, void* param);
  int configure();
  void setTracking();

private:
  int screen_width;
  cv::string main_window;
  common::SharedMemory& sharedMemory;
  CvCapture *camCapture;
  Selection area;
  bool backprojMode;
  int trackObject;
};

}

#endif // BALL_H
