#ifndef COMMON_HPP_
#define COMMON_HPP_

/*
 * GLUT library
 */
#include <GL/glut.h>
#include <GL/glu.h>

/*
 * C/C++ library
 */
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

/*
 * Macros
 */
#define PI M_PI

/*
 * Consts
 */
const int LEFT = -1;
const int RIGHT = 1;
const int DECREASE = -1;
const int INCREASE = 1;

/*
 * Utilities
 */
#include "vector.hpp"
typedef Vector3d<float> Vector3df;

#include "point.hpp"
typedef Point<float> Point3df;

/*
 * Forward declarations.
 */
class Application;
class Model;
class View;
class Controller;
class MovingObject;
class BowlingMachine;
class Bowl;
class Camera;
class Place;

/*
 * Prototypes.
 */
void resize(int width, int height);
void display();
void keyPressed(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y);
void contextMenuEvent(int value);
void timer(int value);

#endif /* COMMON_HPP_ */
