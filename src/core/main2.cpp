#include "application.h"
#include "../players/threadpool.h"
#include "../client/threadedclient.h"
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * Main function.
 */

#include <iostream>
#include <map>
#include <string>


int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("Usage: %s hotname port\n", argv[0]);
		return 0;
	}
	if (Application::client_->start(argv[1], argv[2])) {
		Application::client_->interact();
		Application::client_->sendthis("Hi");
		std::cout << "Receiving the number of players: " << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::map< std::string, std::string> players = Application::client_->deserizalize();
		
		stringstream strValue;
		strValue << players.size();
		strValue >> Application::playerNumber;

		std::cout << "Number of Player: " << Application::playerNumber << std::endl;
	}
	static std::shared_ptr<Application> application = std::make_shared< Application>(&argc, argv);
	std::shared_ptr<View> view = application->getView();
	std::shared_ptr<Model> model = application->getModel();
	model->initScreen(Application::playerNumber);
	view->texturize(model, Application::playerNumber);
	application->start();

	Application::client_->terminate();
	WSACleanup();

	return 0;
}
