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

struct HSV
{
  int h_min, h_max, s_min, s_max, v_min, v_max;
};

struct Drawing
{
  CvPoint point;
  int radius;
  bool drag_drop;
};

class SharedMemory;

class Camera
{
public:
  Camera(common::SharedMemory&);
  ~Camera();

  void getHSV(HSV& hsv) const;
  void setHSV(HSV hsv);

  void getPosition(int& position) const;

  void initTrackbars();
  void processInput(cv::Mat &input) const;

  int getCenter(cv::Mat &input) const;

  void init();

  static void measureHand(int event, int x, int y, int flags, void* param);

  int configure();

private:
  int position;
  HSV hsv;
  int screen_width;
  cv::string main_window;
  common::SharedMemory& sharedMemory;
  CvCapture *camCapture;
};

}

#endif // BALL_H
