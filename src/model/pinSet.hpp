#ifndef PINSET_HPP_
#define PINSET_HPP_

#include "../utils/common.hpp"
#include "../model/pin.hpp"

class PinSet: public MovingObject
{
	private:
		static const int PINS_NUMBER = 10;

		float space;
		Vector3df position;

	public:
		std::vector<Pin> pins;

		PinSet();
		PinSet(std::vector<std::string> filenames);
		void reset();
		void hideKnockedPins();
		void setPosition(const Vector3df position);
		void setSpace(float space);
};

#endif /* PINSET_HPP_ */
