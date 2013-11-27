#include <common/Camera.h>
#include <common/SharedMemory.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace common;
using namespace cv;
using namespace std;

bool drag_drop = false;

Camera::Camera(SharedMemory& sharedMemory)
	: sharedMemory(sharedMemory), hsize(16), hranges{0,180}, 
		phranges(hranges), main_window("Pong Configuration"),
		trackObject(-1), histimg(Mat::zeros(200, 320, CV_8UC3))
{
  this->backprojMode = false;
  this->area.selectObject = false;
  this->area.ready = false;
  this->trackObject = 0;

//  namedWindow(main_window, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_NORMAL);
  namedWindow(main_window, CV_WINDOW_AUTOSIZE);

  camCapture.open(0);
  if (!camCapture.isOpened())
  {
	  std::cout << "LOG: Failed to capture from camera\n";
	  throw OpenCameraException();
  }
  else
  {
	  std::cout << "LOG: Success!\n";
  }
}

Camera::~Camera()
{
}

void Camera::setTracking()
{
	this->trackObject = 1;
}

void Camera::getPosition(int& position)
{
	camCapture >> frame;	

	if (!frame.empty())
	{
		flip(frame, image, 1);
//		frame.copyTo(image);
		cvtColor(image, hsv, CV_BGR2HSV);

		int _vmin = 10, _vmax = 256;

		inRange(hsv, Scalar(0, 30, min(_vmin,_vmax)),
				Scalar(180, 256, max(_vmin, _vmax)), mask);
		int ch[] = {0, 0};
		hue.create(hsv.size(), hsv.depth());
		mixChannels(&hsv, 1, &hue, 1, ch, 1);

		if(trackObject < 0)
		{
			Mat roi(hue, this->area.field), maskroi(mask, this->area.field);
			calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
			normalize(hist, hist, 0, 255, CV_MINMAX);

			trackWindow = this->area.field;
			trackObject = 1;

			histimg = Scalar::all(0);
			int binW = histimg.cols / hsize;
			Mat buf(1, hsize, CV_8UC3);
			for( int i = 0; i < hsize; i++ )
				buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
			cvtColor(buf, buf, CV_HSV2BGR);

			for( int i = 0; i < hsize; i++ )
			{
				int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
				rectangle( histimg, Point(i*binW,histimg.rows), Point((i+1)*binW,histimg.rows - val), Scalar(buf.at<Vec3b>(i)), -1, 8 );
			}
		}

		calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
		backproj &= mask;
		RotatedRect trackBox = CamShift(backproj, trackWindow, TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
		trackBox.angle = 90-trackBox.angle;

		ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );

		std::cout << "centered at: " << trackBox.center.x << "\n";
		position = trackBox.center.x;

		imshow(main_window, image);

		cv::waitKey(30);
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

int Camera::configure()
{

	Mat image, original;

	bool configuring = true;

	Selection tmp_area;
	tmp_area.ready = false;
	setMouseCallback(main_window, onMouse, &tmp_area);

	// first step starts here (taking snapshot)
	while (configuring)
	{
		camCapture >> original;
		if (original.empty())
		{
			throw CaptureException();
		}

		flip(original, image, 1);

		if(tmp_area.selectObject && tmp_area.field.width > 0 && tmp_area.field.height > 0)
		{
			Mat roi(image, this->area.field);
			bitwise_not(roi, roi);
			this->area.field = tmp_area.field;
		}
		if(tmp_area.ready) {
			configuring = false;
			this->trackObject = -1;
		}
		imshow(main_window, image);

		if (cvWaitKey(30) != -1)
		{
			configuring = false;
		}
	}
	return 0;
}
