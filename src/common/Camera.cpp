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

  namedWindow(this->main_window, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL);
  Mat input, original;

  CvCapture *camCapture = NULL;
  bool configuring = true;

  // camera init
  if (!(camCapture = cvCaptureFromCAM(CV_CAP_ANY))) {
    std::cout << "LOG: Failed to capture from camera\n";
    return -1;
  }

  std::cout << "LOG: Camera opened successfully << " << camCapture << "\n";

  IplImage *cameraFrame;

  // first step starts here
  while (configuring)
  {
    if ((cameraFrame = cvQueryFrame(camCapture)))
    {
      input = Mat(cameraFrame, false);
      imshow(main_window, input);
    }

    if (cvWaitKey(30) != -1)
    {
      configuring = false;
    }
  }
  cvReleaseCapture(&camCapture);

  cvDestroyAllWindows();

  this->setPosition(11);

  return 0;
}
