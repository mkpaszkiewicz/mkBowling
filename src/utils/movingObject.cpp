#include "movingObject.hpp"

MovingObject::MovingObject()
{
	reset();
}

MovingObject::~MovingObject()
{
}

void MovingObject::reset()
{
	// initialize with default OpenGL values
	position = Vector3df(0.0, 0.0, 0.0);
	lookDirection = Vector3df(0.0, 0.0, -1.0);
	rightVector = Vector3df(1.0, 0.0, 0.0);
	upVector = Vector3df(0.0, 1.0, 0.0);

	rotatedX = 0.0;
	rotatedY = 0.0;
	rotatedZ = 0.0;
}

void MovingObject::move(const Vector3df& direction)
{
	position = position + direction;
}

void MovingObject::rotateX(float angle)
{
	rotatedX -= angle;

	float cosinus = cos(angle * PI / 180);
	float sinus = sin(angle * PI / 180);

	// rotate lookDirection around the rightVector
	lookDirection = lookDirection * cosinus + upVector * sinus;
	lookDirection.normalize();

	upVector = crossProduct(rightVector, lookDirection);
}

void MovingObject::rotateY(float angle)
{
	rotatedY -= angle;

	float cosinus = cos(angle * PI / 180);
	float sinus = sin(angle * PI / 180);

	// rotate lookDirection around the upVector
	lookDirection = lookDirection * cosinus - rightVector * sinus;
	lookDirection.normalize();

	rightVector = crossProduct(lookDirection, upVector);
}

void MovingObject::rotateZ(float angle)
{
	rotatedZ -= angle;

	float cosinus = cos(angle * PI / 180);
	float sinus = sin(angle * PI / 180);

	// rotate rightVector around lookDirection
	rightVector = rightVector * cosinus + upVector * sinus;
	rightVector.normalize();

	upVector = crossProduct(rightVector, lookDirection);
}

void MovingObject::rotX(float angle)
{
	rotatedX -= angle;
}

void MovingObject::rotY(float angle)
{
	rotatedY -= angle;
}

void MovingObject::rotZ(float angle)
{
	rotatedZ -= angle;
}

void MovingObject::moveForward(float distance)
{
	position = position + (lookDirection * distance);
}

void MovingObject::moveRight(float distance)
{
	position = position + (rightVector * distance);
}

void MovingObject::moveUpward(float distance)
{
	position = position + (upVector * distance);
}

float MovingObject::getRotatedX() const
{
	return rotatedX;
}

float MovingObject::getRotatedY() const
{
	return rotatedY;
}

float MovingObject::getRotatedZ() const
{
	return rotatedZ;
}

const Vector3df MovingObject::getPosition() const
{
	return position;
}

void MovingObject::setPosition(const Vector3df position)
{
	this->position = position;
}

const Vector3df& MovingObject::getDirectionVector() const
{
	return lookDirection;
}

const Vector3df& MovingObject::getRightVector() const
{
	return rightVector;
}

const Vector3df& MovingObject::getUpVector() const
{
	return upVector;
}

