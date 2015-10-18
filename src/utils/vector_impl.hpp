#ifndef VECTOR_IMPL_HPP_
#define VECTOR_IMPL_HPP_

#include <cmath>

template<typename T> Vector3d<T>::Vector3d()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

template<typename T> Vector3d<T>::Vector3d(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<typename T> Vector3d<T>::Vector3d(const Vector3d<T>& vector3d)
{
	this->x = vector3d.x;
	this->y = vector3d.y;
	this->z = vector3d.z;
}

template<typename T> T Vector3d<T>::magnitude() const
{
	return T(sqrt(x * x + y * y + z * z));
}

template<typename T> Vector3d<T>& Vector3d<T>::normalize()
{
	T length = magnitude();

	if (length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	return *this;
}

template<typename T> Vector3d<T>& Vector3d<T>::randomize()
{
	x = random<T>(-1, 1);
	y = random<T>(-1, 1);
	z = random<T>(-1, 1);

	return *this;
}

template<typename T> Vector3d<T> Vector3d<T>::operator-() const
{
	Vector3d<T> result;

	result.x = -x;
	result.y = -y;
	result.z = -z;

	return result;
}

template<typename T> Vector3d<T>& Vector3d<T>::operator+=(const Vector3d<T>& vector3d)
{
	*this = *this + vector3d;
	return *this;
}

template<typename T> Vector3d<T>& Vector3d<T>::operator-=(const Vector3d<T>& vector3d)
{
	*this = *this - vector3d;
	return *this;
}

template<typename T> T* Vector3d<T>::toArray() const
{
	T* result = new T[3];
	result[0] = x;
	result[1] = y;
	result[2] = z;
	return result;
}

template<typename T> T* Vector3d<T>::toMatrix() const
{
	T* result = new T[16];
	memset(result, 0, 16);
	result[0] = result[5] = result[10] = result[15] = 1;
	result[12] = x;
	result[13] = y;
	result[14] = z;
	return result;
}

template<typename T> Vector3d<T> operator+(const Vector3d<T> &a, const Vector3d<T> &b)
{
	Vector3d<T> result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

template<typename T> Vector3d<T> operator-(const Vector3d<T> &a, const Vector3d<T> &b)
{
	Vector3d<T> result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

template<typename T> Vector3d<T> operator*(const Vector3d<T> &a, T r)
{
	Vector3d<T> result;
	result.x = a.x * r;
	result.y = a.y * r;
	result.z = a.z * r;
	return result;
}

template<typename T> Vector3d<T> operator*(T r, const Vector3d<T> &a)
{
	return a * r;
}

template<typename T> Vector3d<T> crossProduct(const Vector3d<T> &a, const Vector3d<T> &b)
{
	Vector3d<T> result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

template<typename T> Vector3d<T> dotProduct(const Vector3d<T> &a, const Vector3d<T> &b)
{
	Vector3d<T> result;
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const Vector3d<T> &a)
{
	os << "[" << a.x << ", " << a.y << ", " << a.z << "]";
	return os;
}

template<typename T> T random(T rangeMin, T rangeMax)
{
	return ((rangeMax - rangeMin) * rand() / RAND_MAX) + rangeMin;
}

#endif // VECTOR_IMPL_HPP_
