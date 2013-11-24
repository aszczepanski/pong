#include <common/Camera.h>

using namespace common;

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

void Camera::configure()
{
  this->setPosition(11);
}
