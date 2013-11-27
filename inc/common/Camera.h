#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdexcept>

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

  void getPosition(int& position);
  int configure();
  void setTracking();

private:
  static void onMouse(int event, int x, int y, int flags, void* param);

  common::SharedMemory& sharedMemory;

  cv::VideoCapture camCapture;
  cv::Rect trackWindow;
  cv::RotatedRect trackBox;
  int hsize;
  float hranges[2];
  const float* phranges;
  const cv::string main_window;

  Selection area;
  bool backprojMode;
  int trackObject;

  int vmin, vmax, smin;

  // IplImage *cameraFrame;

  cv::Mat image, frame, hsv, hue, mask, hist, histimg, backproj;

  class OpenCameraException : public std::exception {};
  class CaptureException : public std::exception {};

};

}

#endif // BALL_H
