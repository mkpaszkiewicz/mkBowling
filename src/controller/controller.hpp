#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "../utils/common.hpp"
#include "../core/application.hpp"
#include "../model/model.hpp"

/**
 * Available context menu options.
 */
enum ContextMenuItem
{
	EXIT, NORMAL_CAMERA, SIDE_CAMERA, FOLLOWING_CAMERA
};

class Controller
{
	private:
		Application* application;

	public:
		Controller(Application* app);
		void contextMenuEvent(int value);
		void keyPressed(unsigned char key);
		void specialKeyPressed(int key);
};

#endif /* CONTROLLER_HPP_ */
