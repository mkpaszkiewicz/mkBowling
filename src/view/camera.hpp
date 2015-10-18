#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../utils/common.hpp"
#include "../utils/movingObject.hpp"
/**
 * Available camera modes.
 */
enum CameraMode
{
	NORMAL, FOLLOWING, SIDE
};

/*
 * Class representing camera, which can be rotated and moved around in the three dimensional space.
 */
class Camera: public MovingObject
{
		friend class View;

	public:

		/*
		 * Constructs camera located in (0, 0, 0) and looking at (0, 0, -1).
		 */
		Camera();

		/**
		 * Returns matrix representing upVector, rightVector, lookDirection.
		 */
		float* toMatrix();

		/**
		 * Returns matrix representing upVector, rightVector, lookDirection
		 * useful in third person perspective rendering (transposed matrix).
		 */
		float* toMatrixTPP();

		void setLookDirection(const Vector3df& direction);
};

#endif /* CAMERA_HPP_ */
