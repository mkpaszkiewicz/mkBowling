#include "place.hpp"

Place::Place()
{
}

Place::Place(std::vector<std::string> filenames, std::vector<std::string> machineTextures, std::vector<std::string> pinTextures) :
		TexturizableObject(filenames)
{
	machine1 = BowlingMachine(machineTextures);
	machine2 = BowlingMachine(machineTextures);
	pinSet = PinSet(pinTextures);
	pinSet1 = PinSet(pinTextures);
	pinSet2 = PinSet(pinTextures);
}

const Vector3df Place::getSize() const
{
	return size;
}

const Vector3df Place::getPosition() const
{
	return position;
}

void Place::setSize(const Vector3df size)
{
	this->size = size;
}

void Place::setPosition(const Vector3df position)
{
	this->position = position;

	machine1.setPosition(position + Vector3df(size.x / 3 - 3, 0, -size.z / 6));
	machine2.setPosition(position + Vector3df(2 * size.x / 3 - 3, 0, -size.z / 6));

	pinSet1.setPosition(position + Vector3df(size.x / 6, 0, -size.z * 7 / 8));
	pinSet.setPosition(position + Vector3df(size.x / 2, 0, -size.z * 7 / 8));
	pinSet2.setPosition(position + Vector3df(5 * size.x / 6, 0, -size.z * 7 / 8));
}

