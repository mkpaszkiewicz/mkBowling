#ifndef MOVING_OBJECT_HPP_
#define MOVING_OBJECT_HPP_

#include "../utils/common.hpp"

class MovingObject
{
	protected:
		/*
		 * Object look direction (local Z axis).
		 */
		Vector3df lookDirection;

		/*
		 * Object right direction (local X axis).
		 */
		Vector3df rightVector;

		/*
		 * Object up direction (local Y axis).
		 */
		Vector3df upVector;

		/*
		 * Vector pointing position_ from zero point (0, 0, 0).
		 */
		Vector3df position;

		/*
		 * Object rotation angle around local X axis.
		 */
		float rotatedX;

		/*
		 * Object rotation angle around local Y axis.
		 */
		float rotatedY;

		/*
		 * Object rotation angle around local Z axis.
		 */
		float rotatedZ;
	public:

		/*
		 * Constructs camera located in (0, 0, 0) and directed to (0, 0, -1).
		 */
		MovingObject();

		/*
		 * Destructor
		 */
		virtual ~MovingObject();

		/*
		 * Sets attributes to default.
		 */
		virtual void reset();

		/**
		 * Returns Object position.
		 */
		const Vector3df getPosition() const;

		/**
		 * Sets Object position.
		 */
		void setPosition(const Vector3df position);

		/**
		 * Moves Object with a specified vector.
		 */
		void move(const Vector3df& direction);

		/**
		 * Rotates Object around local X axis with a specified angle.
		 */
		void rotateX(float angle);

		/**
		 * Rotates Object around local Y axis with a specified angle.
		 */
		void rotateY(float angle);

		/**
		 * Rotates Object around local Z axis with a specified angle.
		 */
		void rotateZ(float angle);

		/**
		 * Rotates Object around local X axis with a specified angle, changes only rotatedX.
		 */
		void rotX(float angle);

		/**
		 * Rotates Object around local Y axis with a specified angle, changes only rotatedY.
		 */
		void rotY(float angle);

		/**
		 * Rotates Object around local Z axis with a specified angle, changes only rotatedZ.
		 */
		void rotZ(float angle);

		/**
		 * Moves Object along look direction with a specified distance.
		 */
		void moveForward(float distance);

		/**
		 * Moves Object upwards with a specified distance.
		 */
		void moveUpward(float distance);

		/**
		 * Moves Object along right direction with a specified distance.
		 */
		void moveRight(float distance);

		/**
		 * Returns lookDirection.
		 */
		const Vector3df& getDirectionVector() const;
		/**
		 * Returns rightVector.
		 */
		const Vector3df& getRightVector() const;
		/**
		 * Returns upVector.
		 */
		const Vector3df& getUpVector() const;

		/**
		 * Returns rotatedX.
		 */
		float getRotatedX() const;

		/**
		 * Returns rotatedY.
		 */
		float getRotatedY() const;

		/**
		 * Returns rotatedZ.
		 */
		float getRotatedZ() const;
};

#endif /* MOVING_OBJECT_HPP_ */
