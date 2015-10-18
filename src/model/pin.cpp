#include "pin.hpp"

const std::vector<Point3df> Pin::contour =
{
	Point3df(0.50775,	0.0, 		0.0),
	Point3df(0.707,		0.45,		0.0),
	Point3df(0.9765,	1.35,		0.0),
	Point3df(1.1275,	2.025,		0.0),
	Point3df(1.19,		2.7, 		0.0),
	Point3df(1.14075,	3.525,		0.0),
	Point3df(0.92575,	4.35,		0.0),
	Point3df(0.568,		5.175, 		0.0),
	Point3df(0.49125,	5.625,		0.0),
	Point3df(0.44925,	6.0, 		0.0),
	Point3df(0.4675,	6.525,		0.0),
	Point3df(0.5235,	7.05,		0.0),
	Point3df(0.6015,	7.575,		0.0),
	Point3df(0.63675,	8.1, 		0.0),
	Point3df(0.6,		8.4,		0.0),
	Point3df(0.5196,	8.7,		0.0),
	Point3df(0.3,		8.85,		0.0),
	Point3df(0.0,		9.0, 		0.0)
};

Pin::Pin()
{
	this->radius = 1.19;
	this->height = 9.0;
	reset();
}

Pin::Pin(std::vector<std::string> filenames): TexturizableObject(filenames)
{
	this->radius = 1.19;
	this->height = 9.0;
	reset();
}

void Pin::reset()
{
	position = Vector3df (0.0, 0.0, 0.0);
	lookDirection = Vector3df(0.0, 0.0, -1.0);
	rightVector = Vector3df (1.0, 0.0, 0.0);
	upVector = Vector3df (0.0, 1.0, 0.0);

	rotatedX = 0.0;
	rotatedY = 0.0;
	rotatedZ = 0.0;

	falling = false;
	fallen = false;
	visible = true;
}

void Pin::setRadius(float radius)
{
	this->radius = radius;
}

float Pin::getRadius() const
{
	return radius;
}

float Pin::getDiameter() const
{
	return 2 * radius;
}

const Vector3df& Pin::getUpVector() const
{
	return upVector;
}

void Pin::setHeight(float height)
{
	this->height = height;
}

float Pin::getHeight() const
{
	return height;
}

bool Pin::isFalling() const
{
	return falling;
}

void Pin::setFalling(bool falling)
{
	this->falling = falling;
}

bool Pin::hasFallen() const
{
	return fallen;
}

void Pin::setHasFallen(bool fallen)
{
	this->fallen = fallen;
}

bool Pin::isVisible() const
{
	return visible;
}

void Pin::setVisible(bool visible)
{
	this->visible = visible;
}

