#ifndef PLACE_HPP_
#define PLACE_HPP_

#include "../utils/common.hpp"
#include "../model/bowlingMachine.hpp"
#include "../model/pinSet.hpp"
#include "../utils/texturizableObject.hpp"

class Place: public TexturizableObject
{
	private:
		/*
		 * width, height, length
		 */
		Vector3df size;

		/*
		 * x, y, z of front bottom left vertex
		 */
		Vector3df position;

	public:
		BowlingMachine machine1;
		BowlingMachine machine2;
		PinSet pinSet;
		PinSet pinSet1;
		PinSet pinSet2;

		Place();
		Place(std::vector<std::string> filenames, std::vector<std::string> machineTextures, std::vector<std::string> pinTextures);
		const Vector3df getSize() const;
		const Vector3df getPosition() const;
		void setSize(const Vector3df size);
		void setPosition(const Vector3df position);
};

#endif /* PLACE_HPP_ */
