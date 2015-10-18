#ifndef BOWLING_HPP_
#define BOWLING_HPP_

#include "../utils/common.hpp"
#include "../model/model.hpp"
#include "../view/view.hpp"
#include "../controller/controller.hpp"

class Application
{
	private:
		Model * model;
		View * view;
		Controller * controller;
		int windowID;

		int initWindow(const std::string & title, int x, int y, int width, int height);
		void initContextMenu();
		void initCallbacks();
		void initLights();

	public:
		Application(int * argc, char * argv[]);
		void start();
		void exit();
		Controller & getController();
		View & getView();
		Model & getModel();
};

#endif /* BOWLING_HPP_ */
