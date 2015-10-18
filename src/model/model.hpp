#ifndef MODEL_HPP_
#define MODEL_HPP_
#include "../utils/common.hpp"
#include "../view/camera.hpp"
#include "../model/place.hpp"
#include "../model/bowl.hpp"

class Model
{
	private:
		static const int MAX_POSITION = 14;
		static const int MIN_POSITION = -14;
		static const int MAX_POWER = 40;
		static const int MIN_POWER = 10;
		static const int MAX_DIRECTION = 25;
		static const int MIN_DIRECTION = -25;
		static const int MAX_ROTATION = 60;
		static const int MIN_ROTATION = -60;

		Place place;
		Bowl bowl;
		Camera normalCamera;
		Camera sideCamera;
		Camera followingCamera;
		CameraMode cameraMode;

		float position;
		float power;
		float direction;
		float rotation;

		bool animating;
		bool elapsed;
		bool inGutter;
		bool firstThrow;

		void checkCollision();
		void collisionBackWall();
		void collisionGutter();
		void collisionBowlPin();
		void collisionPinPin();
		void collisionPinWall();
		void pinCollision(Pin& a, const Point3df& aPoint, Pin& b, const Point3df& bPoint);
		void pinFall(Pin& pin) const;

	public:
		static const int FRAME_TIME = 40;
		static const int WAITING_TIME = 60;

		Model();
		Place& getPlace();
		Bowl& getBowl();
		Camera& getCamera();
		void update();
		void setCameraMode(CameraMode cameraMode);
		void setPosition(float position);
		void setPower(float power);
		void setDirection(float direction);
		void setRotation(float rotation);
		float getPosition() const;
		float getPower() const;
		float getDirection() const;
		float getRotation() const;
		void startAnimation();
		bool isAnimating() const;
		bool hasAnimationElapsed() const;
		void reset();
};

#endif /* MODEL_HPP_ */
