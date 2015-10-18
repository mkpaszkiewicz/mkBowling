#ifndef PIN_HPP_
#define PIN_HPP_

#include "../utils/common.hpp"
#include "../utils/movingObject.hpp"
#include "../utils/texturizableObject.hpp"

class Pin: public MovingObject, public TexturizableObject
{
	private:
		float radius;
		float height;

		bool falling;
		bool fallen;
		bool visible;

	public:
		static const std::vector<Point3df> contour;

		Pin();
		Pin(std::vector<std::string> filenames);
		void reset();
		void setRadius(float radius);
		float getRadius() const;
		float getDiameter() const;
		const Vector3df& getUpVector() const;
		void setHeight(float height);
		float getHeight() const;
		bool isFalling() const;
		void setFalling(bool falling);
		bool hasFallen() const;
		void setHasFallen(bool fallen);
		bool isVisible() const;
		void setVisible(bool visible);
};

#endif /* PIN_HPP_ */
