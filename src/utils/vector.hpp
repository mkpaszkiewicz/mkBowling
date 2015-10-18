#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <ostream>
#include <cstdlib>
#include <cstring>

/**
 * Template class representing three dimensional vector.
 */
template<typename T> class Vector3d
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
		 * Z coordinate.
		 */
		T z;

		/**
		 * Constructs the zero [0, 0, 0] vector.
		 */
		Vector3d();

		/**
		 * Constructs the specified vector from other vector.
		 */
		Vector3d(const Vector3d<T>& vector3d);

		/**
		 * Constructs the specified vector.
		 */
		Vector3d(T x, T y, T z);

		/**
		 * Returns the magnitude.
		 */
		T magnitude() const;

		/**
		 * Normalizes vector.
		 */
		Vector3d<T>& normalize();

		/**
		 * Randomizes and normalizes vector.
		 */
		Vector3d<T>& randomize();

		/**
		 * Returns the opposite vector.
		 */
		Vector3d<T> operator-() const;

		/**
		 * Adding vector to itself.
		 */
		Vector3d<T>& operator+=(const Vector3d<T>& vector3d);

		/**
		 * Substracting vector from itself.
		 */
		Vector3d<T>& operator-=(const Vector3d<T>& vector3d);

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
 * Adding vectors.
 */
template<typename T> Vector3d<T> operator+(const Vector3d<T> &a, const Vector3d<T> &b);

/**
 * Substracting vectors.
 */
template<typename T> Vector3d<T> operator-(const Vector3d<T> &a, const Vector3d<T> &b);

/**
 * Multiplying vector and number.
 */
template<typename T> Vector3d<T> operator*(const Vector3d<T> &a, T r);
template<typename T> Vector3d<T> operator*(T r, const Vector3d<T> &a);

/**
 * Calculating the cross product of vectors.
 */
template<typename T> Vector3d<T> crossProduct(const Vector3d<T> &a, const Vector3d<T> &b);

/**
 * Calculating the scalar product of vectors.
 */
template<typename T> Vector3d<T> dotProduct(const Vector3d<T> &a, const Vector3d<T> &b);

/**
 * Outputting to stream.
 */
template<typename T> std::ostream& operator<<(std::ostream& os, const Vector3d<T> &a);

/**
 * Randomizes number from specified range.
 */
template<typename T> T random(T rangeMin, T rangeMax);

#include "vector_impl.hpp"

#endif // VECTOR_HPP_
