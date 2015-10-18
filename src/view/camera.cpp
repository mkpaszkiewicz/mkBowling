#include "camera.hpp"

Camera::Camera()
{
}

float* Camera::toMatrix()
{
	float* matrix = new float[16];
	float array[16] = { rightVector.x,	upVector.x,	lookDirection.x,	0,
						rightVector.y,	upVector.y, lookDirection.y,	0,
						rightVector.z,	upVector.z, lookDirection.z,	0,
						0,				0,			0,					1 };
	std::copy(array, array + 16, matrix);
	return matrix;
}

float* Camera::toMatrixTPP()
{
	float* matrix = new float[16];
	float array[16] = { rightVector.x,		rightVector.y,		rightVector.z,		0,
						upVector.x,			upVector.y, 	  	upVector.z,   		0,
						lookDirection.x,	lookDirection.y,	lookDirection.z,	0,
						0,					0,				   	0,				  	1 };
	std::copy(array, array + 16, matrix);
	return matrix;
}

void Camera::setLookDirection(const Vector3df& direction)
{
	lookDirection = direction;
}
