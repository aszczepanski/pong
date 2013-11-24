#include <common/Camera.h>

using namespace common;
using namespace cv;

bool drag_drop = false;

Camera::Camera()
{
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

void Camera::measureHand(int event, int x, int y, int flags, void* param)
{
  Drawing* obj = (Drawing*) param;
  if (event == CV_EVENT_MOUSEMOVE)
  {
    if ((*obj).drag_drop == true)
    {
      (*obj).radius = sqrt(pow(abs((*obj).point.x - x), 2) + pow(abs((*obj).point.y - y), 2));
    }
  }
  else if (event == CV_EVENT_LBUTTONDOWN)
  {
    (*obj).drag_drop = true;
    (*obj).point.x = x;
    (*obj).point.y = y;
  }
  else if (event == CV_EVENT_LBUTTONUP)
  {
    (*obj).drag_drop = false;
  }
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

  // first step starts here (taking snapshot)
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

  // second step starts here (pointing to object)
  configuring = true;
  original = input.clone();

  Drawing obj;
  Drawing *obj_ptr = &obj;
  obj.radius = 0;
  obj.drag_drop = false;

  while (configuring)
  {
    imshow(main_window, input);
    cv::setMouseCallback(main_window, measureHand, obj_ptr);
    if (obj.radius > 0 && obj.drag_drop == true)
    {
      input = original.clone();
      circle(input, obj.point, obj.radius, Scalar(0, 0, 255), 5, 8, 0);
    }

    if (cvWaitKey(30) != -1) {
      configuring = false;
    }
  }
  cvReleaseCapture(&camCapture);

  cvDestroyAllWindows();

  setPosition(11);

  return 0;
}
