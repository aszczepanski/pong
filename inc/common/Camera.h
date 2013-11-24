#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace common
{

struct HSV
{
  int h_min, h_max, s_min, s_max, v_min, v_max;
};

class Camera
{
public:
  Camera();

  void getHSV(HSV& hsv) const;
  void setHSV(HSV hsv);

  void getPosition(int& position) const;
  void setPosition(int position);

  int configure();

private:
  int position;
  HSV hsv;
  int screen_width;
  bool drag_drop;
  cv::string main_window;
  CvCapture *camera_handle;
};

}

#endif // BALL_H
