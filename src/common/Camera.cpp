#include <common/Camera.h>
#include <common/SharedMemory.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdio>

using namespace common;
using namespace cv;
using namespace std;

bool drag_drop = false;

Camera::Camera(SharedMemory& sharedMemory)
  : sharedMemory(sharedMemory)
{
  this->main_window = "Pong Configuration";
  this->screen_width = 1280;
  this->backprojMode = false;
  this->area.selectObject = false;
  this->area.ready = false;
  this->trackObject = 0;
}

Camera::~Camera()
{
  cvDestroyAllWindows();
  cvReleaseCapture(&camCapture);
}

void Camera::getPosition(int& position) const
{
  Mat input;
  IplImage *cameraFrame;

  int new_position = -1;

  if ((cameraFrame = cvQueryFrame(camCapture))) {
    input = Mat(cameraFrame, false);
  }
}

void Camera::onMouse(int event, int x, int y, int flags, void* param)
{
  Selection* obj = (Selection*) param;
  if(obj->selectObject)
  {
    obj->field.x = MIN(x, obj->start.x);
    obj->field.y = MIN(y, obj->start.y);
    obj->field.width = std::abs(x - obj->start.x);
    obj->field.height = std::abs(y - obj->start.y);
  }

  switch( event )
  {
  case CV_EVENT_LBUTTONDOWN:
    obj->start = Point(x,y);
    obj->field = Rect(x,y,0,0);
    obj->selectObject = true;
    break;
  case CV_EVENT_LBUTTONUP:
    obj->selectObject = false;
    obj->ready = true;
    std::cout << "ready to work\n";
    break;
  }
}

void Camera::init()
{
  namedWindow(this->main_window, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL);
  if (!(this->camCapture = cvCaptureFromCAM(CV_CAP_ANY))) {
    std::cout << "LOG: Failed to capture from camera\n";
  }
  std::cout << "LOG: Success!\n";
}

int Camera::configure()
{

  Mat input, original;
  IplImage *cameraFrame;

  bool configuring = true;


  Selection tmp_area;
  Selection *tmp_area_ptr = &tmp_area;
  setMouseCallback(main_window, onMouse, tmp_area_ptr);

  // first step starts here (taking snapshot)
  while (configuring)
  {
    if ((cameraFrame = cvQueryFrame(this->camCapture)))
    {
      input = Mat(cameraFrame, false);

      if(tmp_area.selectObject && tmp_area.field.width > 0 && tmp_area.field.height > 0)
      {
        Mat roi(input, this->area.field);
        bitwise_not(roi, roi);
        this->area.field = tmp_area.field;
      }
      if(tmp_area.ready) {
        configuring = false;
        this->trackObject = -1;
      }
      imshow(main_window, input);
    }

    if (cvWaitKey(30) != -1)
    {
      configuring = false;
    }
  }
  return 0;
}
