#include "pinSet.hpp"

PinSet::PinSet()
{
	space = 3.0;
	for(int i = 0; i < PINS_NUMBER; i++)
	{
		pins.push_back(Pin());
	}
}

PinSet::PinSet(std::vector<std::string> filenames)
{
	space = 3.0;
	for(int i = 0; i < PINS_NUMBER; i++)
	{
		pins.push_back(Pin(filenames));
	}
}

void PinSet::reset()
{
	Vector3df pinPosition = position;
	float spaceBetweenCentres = space + pins[0].getDiameter();
	Vector3df move = Vector3df(-spaceBetweenCentres / 2, 0.0, -spaceBetweenCentres * sqrt(3) / 2);

	for(Pin& pin : pins)
		pin.reset();

	pins[0].setPosition(pinPosition);

	pinPosition += move;
	pins[1].setPosition(pinPosition);
	pins[2].setPosition(pinPosition + Vector3df(spaceBetweenCentres, 0.0, 0.0));

	pinPosition += move;
	pins[3].setPosition(pinPosition);
	pins[4].setPosition(pinPosition + Vector3df(spaceBetweenCentres, 0.0, 0.0));
	pins[5].setPosition(pinPosition + Vector3df(spaceBetweenCentres * 2, 0.0, 0.0));

	pinPosition += move;
	pins[6].setPosition(pinPosition);
	pins[7].setPosition(pinPosition + Vector3df(spaceBetweenCentres, 0.0, 0.0));
	pins[8].setPosition(pinPosition + Vector3df(spaceBetweenCentres * 2, 0.0, 0.0));
	pins[9].setPosition(pinPosition + Vector3df(spaceBetweenCentres * 3, 0.0, 0.0));
}

void PinSet::hideKnockedPins()
{
	for(Pin& pin : pins)
	{
		if(!pin.isVisible())
		{
			pin.setPosition(pin.getPosition() + Vector3df(0.0, -10.0, 0.0));
		}
	}
}

void PinSet::setPosition(const Vector3df position)
{
	this->position = position;
	reset();
}

void PinSet::setSpace(float space)
{
	this->space = space;
	reset();
}
