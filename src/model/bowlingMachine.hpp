#ifndef BOWLINGMACHINE_HPP_
#define BOWLINGMACHINE_HPP_

#include "../utils/common.hpp"
#include "../model/bowl.hpp"
#include "../utils/texturizableObject.hpp"

class BowlingMachine: public TexturizableObject
{
	private:
		Vector3df position;

	public:
		Bowl bowl1;
		Bowl bowl2;
		Bowl bowl3;

		BowlingMachine();
		BowlingMachine(std::vector<std::string> filenames);
		const Vector3df getPosition() const;
		void setPosition(const Vector3df position);
		void setFilenames(std::vector<std::string> filenames);
};

#endif /* BOWLINGMACHINE_HPP_ */
