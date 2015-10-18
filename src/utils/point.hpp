#ifndef POINT_HPP_
#define POINT_HPP_

#include <ostream>
#include <cstdlib>
#include <cstring>

/**
 * Template class representing three dimensional point.
 */
template<typename T> class Point
{
public:

	/**
	 * X coordinate.
	 */
	T x;

	/**
	 * Y coordinate.
	 */
	T y;

	/**
	 * Y coordinate.
	 */
	T z;

	/**
	 * Constructs the zero [0, 0, 0] point.
	 */
	Point();

	/**
	 * Constructs the specified point from other point.
	 */
	Point(const Point<T>& point);

	/**
	 * Constructs the specified point.
	 */
	Point(T x, T y, T z);

	/**
	 * Constructs point from vector;
	 */
	Point(const Vector3df& vector);

	/*
	 * Rotates point around x axis.
	 */
	void rotateX(float angle);

	/*
	 * Rotates point around Y axis.
	 */
	void rotateY(float angle);

	/*
	 * Rotates point around Y axis.
	 */
	void rotateZ(float angle);

	/**
	 * Randomizes point.
	 */
	Point<T>& randomize();

	/**
	 * Adding point to itself by coordinates.
	 */
	Point<T>& operator+=(const Point<T>& point);

	/**
	 * Substracting point from itself by coordinates.
	 */
	Point<T>& operator-=(const Point<T>& point);

	/**
	 * Convert vector to an array.
	 */
	T* toArray() const;

	/**
	 * Converts vector to matrix.
	 */
	T* toMatrix() const;
};

/**
 * Return distance between two points.
 */
template<typename T> T distance(const Point<T> &a, const Point<T> &b);

/**
 * Adding points by coordinates.
 */
template<typename T> Point<T> operator+(const Point<T> &a, const Point<T> &b);

/**
 * Substracting points by coordinates.
 */
template<typename T> Point<T> operator-(const Point<T> &a, const Point<T> &b);

/**
 * Multiplying point and number.
 */
template<typename T> Point<T> operator*(const Point<T> &point, T r);
template<typename T> Point<T> operator*(T r, const Point<T> &point);

/**
 * Outputting to stream.
 */
template<typename T> std::ostream& operator<<(std::ostream& os, const Point<T> &point);

#include "point_impl.hpp"

#endif /* POINT_HPP_ */
