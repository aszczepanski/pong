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

void Camera::processInput(Mat &input) const
{
  // Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
  // Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));
  Mat hsv_mat;

  cv::cvtColor(input, hsv_mat, COLOR_BGR2HSV);

  inRange(hsv_mat, Scalar(hsv.h_min, hsv.s_min, hsv.s_min), Scalar(hsv.h_max, hsv.s_max, hsv.v_max), input);

  // erode(input, input, erodeElement);
  // erode(input, input, erodeElement);
  // dilate(input, input, dilateElement);
  // dilate(input, input, dilateElement);
}

void Camera::initTrackbars()
{
  char TrackbarName[50];
  sprintf(TrackbarName, "H (min) %d", hsv.h_min);
  sprintf(TrackbarName, "H (max) %d", hsv.h_max);
  sprintf(TrackbarName, "S (min) %d", hsv.s_min);
  sprintf(TrackbarName, "S (max) %d", hsv.s_max);
  sprintf(TrackbarName, "V (min) %d", hsv.v_min);
  sprintf(TrackbarName, "V (max) %d", hsv.v_max);

  createTrackbar("H (min)", main_window, &hsv.h_min, 255, NULL);
  createTrackbar("H (max)", main_window, &hsv.h_max, 255, NULL);
  createTrackbar("S (min)", main_window, &hsv.s_min, 255, NULL);
  createTrackbar("S (max)", main_window, &hsv.s_max, 255, NULL);
  createTrackbar("V (min)", main_window, &hsv.v_min, 255, NULL);
  createTrackbar("V (max)", main_window, &hsv.v_max, 255, NULL);
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

  // second step(2) starts here - init HSV values
  input = original.clone();
  cvtColor(input, original, COLOR_BGR2HSV);

  int h = 0, s = 0, v = 0, count = 0, offset = 30;
  Vec3d pixel;

  int pt_x = obj.point.x, pt_y = obj.point.y, pt_r = obj.radius;

  for(int x = pt_x - pt_r; x < pt_x + pt_r; x++)
  {
    for(int y = pt_y - pt_r; y < pt_y + pt_r; y++)
    {
      Vec3b bgrPixel = original.at<Vec3b>(y, x);
      h += (int)bgrPixel[0];
      s += (int)bgrPixel[1];
      v += (int)bgrPixel[2];
      count++;
    }
  }

  h /= count; s /= count; v /= count;

  hsv.h_min = max(0, h - offset); hsv.h_max = min(255, h + offset);
  hsv.s_min = max(0, s - offset); hsv.s_max = min(255, s + offset);
  hsv.v_min = max(0, v - offset); hsv.v_max = min(255, v + offset);


  // third step - show image
  configuring = true;
  initTrackbars();

  Mat backup;
  backup = input.clone();

  while (configuring) {
    processInput(input);
    imshow(main_window, input);
    input = backup.clone();

    if (cvWaitKey(30) != -1) {
      configuring = false;
    }
  }

  cvDestroyAllWindows();

  setPosition(11);

  return 0;
}
