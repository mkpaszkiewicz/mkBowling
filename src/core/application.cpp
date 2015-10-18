#include "application.hpp"

Application::Application(int* argc, char * argv[])
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	this->windowID = initWindow("mkBowling", 0, 0, 650, 650);

	this->model = new Model();
	this->view = new View();
	this->controller = new Controller(this);

	initLights();
	initCallbacks();
	initContextMenu();
}

/**
 * Run the application.
 */
void Application::start()
{
	glutMainLoop();
}

/**
 * Stop the application.
 */
void Application::exit()
{
	glutDestroyWindow(this->windowID);
	std::exit(0);
}

Controller& Application::getController()
{
	return *controller;
}

View& Application::getView()
{
	return *view;
}

Model& Application::getModel()
{
	return *model;
}

/**
 * Initializes application window.
 */
int Application::initWindow(const std::string& title, int x, int y, int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	int windowId = glutCreateWindow(title.c_str());

	glClearColor(0, 0, 0, 0);

	glEnable(GL_NORMALIZE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	return windowId;
}

/*
 * Initializes positions and direction of lights;
 */
void Application::initLights()
{
	glEnable(GL_LIGHTING);

	//glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, 0 );
	glLightModelf( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	float ambient[4] = { 0.6, 0.6, 0.6, 1 };
	float diffuse[4] = { 0.8, 0.8, 0.8, 1 };
	float specular[4] = { 0.7, 0.7, 0.7, 1 };
	float direction[3] = { 0, -1, 0 };
	float spot = 75;
	float position0[4] = { 0, 85, 20, 1 };
	float position1[4] = { 0, 85, -200, 1 };
	float position2[4] = { 0, 85, -110, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
}

/**
 * Context menu initialization.
 */
void Application::initContextMenu()
{
	glutCreateMenu(contextMenuEvent);
	glutAddMenuEntry("Exit", EXIT);
	glutAddMenuEntry("Normal camera", NORMAL_CAMERA);
	glutAddMenuEntry("Side camera", SIDE_CAMERA);
	glutAddMenuEntry("Following camera", FOLLOWING_CAMERA);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * Registers callbacks.
 */
void Application::initCallbacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutIdleFunc(display);
	glutTimerFunc(model->FRAME_TIME, timer, 1);
}
