#include "bowl.hpp"

Bowl::Bowl()
{
	this->radius = 2.25;
	reset();
}

Bowl::Bowl(std::vector<std::string> filenames) :
		TexturizableObject(filenames)
{
	this->radius = 2.25;
	reset();
}

void Bowl::reset()
{
	position = Vector3df(0.0, radius, -5.0);
	lookDirection = Vector3df(0.0, 0.0, -1.0);
	rightVector = Vector3df(1.0, 0.0, 0.0);
	upVector = Vector3df(0.0, 1.0, 0.0);

	rotatedX = -135.0;
	rotatedY = 0.0;
	rotatedZ = 0.0;
}

void Bowl::setRadius(float radius)
{
	this->radius = radius;
}

float Bowl::getRadius() const
{
	return radius;
}
