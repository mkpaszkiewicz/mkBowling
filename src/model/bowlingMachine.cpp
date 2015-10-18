#include "bowlingMachine.hpp"
#include "../view/view.hpp"

BowlingMachine::BowlingMachine()
{
	this->position = Vector3df(0, 0, 0);
}

BowlingMachine::BowlingMachine(std::vector<std::string> filenames) :
		TexturizableObject(filenames)
{
	std::vector<std::string> bowlTexture = std::vector<std::string>();

	bowlTexture.push_back(filenames[1]);
	bowl1.setFilenames(bowlTexture);

	bowlTexture.clear();
	bowlTexture.push_back(filenames[2]);
	bowl2.setFilenames(bowlTexture);

	bowlTexture.clear();
	bowlTexture.push_back(filenames[3]);
	bowl3.setFilenames(bowlTexture);
}

const Vector3df BowlingMachine::getPosition() const
{
	return position;
}

void BowlingMachine::setPosition(const Vector3df position)
{
	this->position = position;
	this->bowl1.setPosition(position + Vector3df(3, 12.25, 13.25));
	this->bowl2.setPosition(position + Vector3df(3, 12.25, 17.75));
	this->bowl3.setPosition(position + Vector3df(3, 12.25, 22.25));
}
