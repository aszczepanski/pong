#include <common/Camera.h>

using namespace common;
using namespace cv;

Camera::Camera()
{
  this->drag_drop = false;
  this->screen_width = 1280;
  this->main_window = "Pong Configuration";
}

void Camera::getHSV(HSV& hsv) const
{
  hsv = this->hsv;
}

void Camera::setHSV(HSV hsv)
{
  this->hsv = hsv;
}

void Camera::getPosition(int& position) const
{
  position = this->position;
}

void Camera::setPosition(int position)
{
  this->position = position;
}

int Camera::configure()
{

  Mat input, original;

  CvCapture *camCapture = this->camera_handle;
  int ret = 0;
  bool configuring = true;

  // camera init
  if (!(camCapture = cvCaptureFromCAM(CV_CAP_ANY))) {
    std::cout << "LOG: Failed to capture from camera\n";
    return -1;
  }
  std::cout << "LOG: Everything is fine\n";

  this->setPosition(11);

  return 0;
}
