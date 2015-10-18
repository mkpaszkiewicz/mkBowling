#ifndef POINT_IMPL_HPP_
#define POINT_IMPL_HPP_

#include "common.hpp"

template<typename T> Point<T>::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template<typename T> Point<T>::Point(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template<typename T> Point<T>::Point(const Vector3df& vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
}

template<typename T> Point<T>::Point(const Point<T>& point)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
}

template<typename T> void Point<T>::rotateX(float angle)
{
	float cosinus = cos(angle * PI / 180);
	float sinus = sin(angle * PI / 180);

	float y_ = y;
	float z_ = z;

	y = y_ * cosinus - z_ * sinus;
	z = y_ * sinus + z_ * cosinus;
}

template<typename T> void Point<T>::rotateY(float angle)
{
	float cosinus = cos(angle * PI / 180);
	float sinus = sin(angle * PI / 180);

	float x_ = x;
	float z_ = z;

	x = x_ * cosinus + z_ * sinus;
	z = -x_ * sinus + z_ * cosinus;
}

template<typename T> void Point<T>::rotateZ(float angle)
{
	float cosinus = cos(angle * PI / 180);
	float sinus = sin(angle * PI / 180);

	float x_ = x;
	float y_ = y;

	x = x_ * cosinus - y_ * sinus;
	y = x_ * sinus + y_ * cosinus;
}

template<typename T> Point<T>& Point<T>::randomize()
{
	x = random<T>(-1, 1);
	y = random<T>(-1, 1);

	return *this;
}

template<typename T> Point<T>& Point<T>::operator+=(const Point<T>& point)
{
	*this = *this + point;
	return *this;
}


template<typename T> Point<T>& Point<T>::operator-=(const Point<T>& point)
{
	*this = *this - point;
	return *this;
}

template<typename T> T* Point<T>::toArray() const
{
	T* result = new T[3];
	result[0] = x;
	result[1] = y;
	result[2] = z;
	return result;
}

template<typename T> T* Point<T>::toMatrix() const
{
	T* result = new T[16];
	memset(result, 0, 16);
	result[0] = result[5] = result[10] = result[15] = 1;
	result[12] = x;
	result[13] = y;
	result[14] = z;
	return result;
}

template<typename T> T distance(const Point<T> &a, const Point<T> &b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

template<typename T> Point<T> operator+(const Point<T> &a, const Point<T> &b)
{
	Point<T> result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

template<typename T> Point<T> operator-(const Point<T> &a, const Point<T> &b)
{
	Point<T> result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

template<typename T> Point<T> operator*(const Point<T> &point, T r)
{
	Point<T> result;
	result.x = point.x * r;
	result.y = point.y * r;
	result.z = point.z * r;
	return result;
}

template<typename T> Point<T> operator*(T r, const Point<T> &point)
{
    return point * r;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const Point<T> &point)
{
	os << "[" << point.x << ", " << point.y << ", " << point.z << "]";
	return os;
}

#endif /* POINT_IMPL_HPP_ */
