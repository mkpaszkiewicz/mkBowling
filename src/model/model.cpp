#include "model.hpp"
#include <algorithm>
Model::Model()
{
	std::vector<std::string> textures = std::vector<std::string>();
	std::vector<std::string> pinTextures = std::vector<std::string>();
	std::vector<std::string> machineTextures = std::vector<std::string>();

	textures.push_back("floor1");
	textures.push_back("floor2");
	textures.push_back("ceiling");
	textures.push_back("logo");
	textures.push_back("glass");
	textures.push_back("wall");
	pinTextures.push_back("pin");
	machineTextures.push_back("machine");
	machineTextures.push_back("bowl_blue");
	machineTextures.push_back("bowl_maroon");
	machineTextures.push_back("bowl_green");
	this->place = Place(textures, machineTextures, pinTextures);

	textures.clear();
	textures.push_back("bowl_red");
	this->bowl = Bowl(textures);
	this->normalCamera = Camera();
	this->sideCamera = Camera();
	this->followingCamera = Camera();
	this->cameraMode = NORMAL;

	place.setSize(Vector3df(100.0, 50.0, 270.0));
	place.setPosition(Vector3df(-50.0, 0.0, 25.0));

	normalCamera.setPosition(Vector3df(0.0, 20.0, 25.0));
	normalCamera.rotateX(-12.0);

	sideCamera.setPosition(Vector3df(-40.0, 35.0, -150.0));

	followingCamera.setPosition(Vector3df(0.0, 0.0, 0.0));
	followingCamera.rotateX(-5.0);

	firstThrow = true;
	reset();
}

Place& Model::getPlace()
{
	return place;
}

Bowl& Model::getBowl()
{
	return bowl;
}

Camera& Model::getCamera()
{
	switch (cameraMode)
	{
		default:
		case NORMAL:
			return normalCamera;

		case SIDE:
			return sideCamera;

		case FOLLOWING:
			return followingCamera;
	}
}

void Model::update()
{
	Vector3df placePosition = place.getPosition();
	Vector3df placeSize = place.getSize();
	Vector3df bowlPosition = bowl.getPosition();
	float bowlRadius = bowl.getRadius();

	Vector3df followingCameraPosition = bowlPosition + Vector3df(0, 2 * bowlRadius, 8 * bowlRadius);
	followingCamera.setPosition(followingCameraPosition);

	Vector3df sideCameraPosition = sideCamera.getPosition();
	sideCamera.setLookDirection(
			Vector3df(bowlPosition.x - sideCameraPosition.x, bowlPosition.y - sideCameraPosition.y,
					bowlPosition.z - sideCameraPosition.z));

	if (isAnimating())
	{
		bowl.rotateY(-rotation / 300);
		bowl.moveForward(0.05 * power);
		bowl.rotX(360 * 0.05 * power / (2 * PI * bowl.getRadius()));
	}

	if (bowlPosition.z <= placePosition.z - 7 * placeSize.z / 8)
	{
		elapsed = true;
	}

	checkCollision();
}

void Model::checkCollision()
{
	collisionBackWall();
	collisionGutter();
	collisionBowlPin();
	collisionPinPin();
	collisionPinWall();
}

void Model::collisionBowlPin()
{
	Vector3df bowlPosition = bowl.getPosition();

	for (Pin& pin : place.pinSet.pins)
	{
		Vector3df pinPosition = pin.getPosition();
		float dist = distance(Point3df(pinPosition.x, 0.0, pinPosition.z), Point3df(bowlPosition.x, 0.0, bowlPosition.z));

		if (dist < pin.getRadius() + bowl.getRadius())
		{
			Vector3df moveVector = Vector3df(pinPosition.x - bowlPosition.x, 0.0, pinPosition.z - bowlPosition.z);
			moveVector.normalize();
			moveVector = moveVector * (pin.getRadius() + bowl.getRadius() - dist);

			pin.move(moveVector);
			power *= 0.994;
			pin.rotateZ(-moveVector.x * 8);
			pin.rotateX(-moveVector.z * 8);
			pin.setFalling(true);

			bowl.rotateY(moveVector.x * 80 / power);
		}

		pinFall(pin);
		pinPosition = pin.getPosition();
		if (std::max(abs(pin.getRotatedX()), abs(pin.getRotatedZ())) > 0)
		{
			float y = std::max(abs(pin.getRotatedX()), abs(pin.getRotatedZ())) / 90 * pin.getRadius();
			pin.setPosition(Vector3df(pinPosition.x, y, pinPosition.z));
		}
	}
}

void Model::pinFall(Pin& pin) const
{
	if (!pin.isFalling())
	{
		return;
	}

	pin.rotateX(-pin.getRotatedX() * 0.2);
	pin.rotateZ(-pin.getRotatedZ() * 0.2);

	if (pin.getRotatedX() < -90 || pin.getRotatedX() > 90)
	{
		int sign = pin.getRotatedX() > 0 ? 1 : -1;
		pin.rotateX(pin.getRotatedX() - sign * 90);
		pin.setFalling(false);
		pin.setHasFallen(true);
	}

	if (pin.getRotatedZ() < -90 || pin.getRotatedZ() > 90)
	{
		int sign = pin.getRotatedZ() > 0 ? 1 : -1;
		pin.rotateZ(pin.getRotatedZ() - sign * 90);
		pin.setFalling(false);
		pin.setHasFallen(true);
	}
}

void Model::collisionPinWall()
{
	for (Pin& pin : place.pinSet.pins)
	{
		Vector3df pinPosition = pin.getPosition();
		Vector3df upVector = -pin.getUpVector();
		Vector3df top = pinPosition + upVector.normalize() * pin.getHeight();

		if (top.z < place.getPosition().z - place.getSize().z)
		{
			pin.move(Vector3df(0.0, 0.0, place.getPosition().z - place.getSize().z - top.z));
		}
	}
}

void Model::collisionPinPin()
{
	static int pointsNumber = 10;

	std::vector<Pin>& pins = place.pinSet.pins;
	for (unsigned int i = 0; i < pins.size(); i++)
	{
		for (unsigned int j = i + 1; j < pins.size(); j++)
		{
			Pin& a = pins[i];
			Vector3df aUpVector = -a.getUpVector();
			Vector3df aBottom = a.getPosition();
			Point3df aPoints[pointsNumber];
			aPoints[0] = aBottom;
			for (int k = 1; k < pointsNumber; k++)
			{
				aPoints[k] = aBottom + aUpVector.normalize() * float(a.getHeight() * k / pointsNumber);
			}

			Pin& b = pins[j];
			Vector3df bUpVector = -b.getUpVector();
			Vector3df bBottom = b.getPosition();
			Point3df bPoints[pointsNumber];
			bPoints[0] = bBottom;
			for (int k = 1; k < pointsNumber; k++)
			{
				bPoints[k] = bBottom + bUpVector.normalize() * float(b.getHeight() * k / pointsNumber);
			}

			for (int k = 0; k < pointsNumber; k++)
			{
				for (int l = 0; l < pointsNumber; l++)
				{
					pinCollision(a, aPoints[k], b, bPoints[l]);
				}
			}
		}
	}
}

void Model::pinCollision(Pin& a, const Point3df& aPoint, Pin& b, const Point3df& bPoint)
{
	if (distance(aPoint, bPoint) < 1.9 * a.getRadius())
	{
		Vector3df aMoveVector = Vector3df(aPoint.x - bPoint.x, aPoint.y - bPoint.y, aPoint.z - bPoint.z);
		aMoveVector.normalize();
		aMoveVector = aMoveVector * float(0.2 * a.getRadius());
		Vector3df bMoveVector = -aMoveVector;
		a.move(aMoveVector);
		b.move(bMoveVector);
		a.rotateZ(-aMoveVector.x * 2);
		a.rotateX(-aMoveVector.z * 2);
		b.rotateZ(-bMoveVector.x * 2);
		b.rotateX(-bMoveVector.z * 2);
		a.setFalling(true);
		b.setFalling(true);
	}
}

void Model::collisionBackWall()
{
	Vector3df bowlPosition = bowl.getPosition();
	Vector3df placePosition = place.getPosition();
	Vector3df placeSize = place.getSize();
	Vector3df lookDirection = bowl.getDirectionVector();

	float edge = placePosition.z - placeSize.z;
	if (bowlPosition.z - bowl.getRadius() < edge)
	{
		power /= 25.0;
		rotation = 0;
		bowl.setPosition(Vector3df(bowlPosition.x, bowlPosition.y, edge + bowl.getRadius()));
		bowl.rotateY(180 - 2 * atan(lookDirection.x / lookDirection.z) * 180 / PI);
	}
}

void Model::collisionGutter()
{
	Vector3df bowlPosition = bowl.getPosition();
	Vector3df placePosition = place.getPosition();
	Vector3df placeSize = place.getSize();
	Vector3df lookDirection = bowl.getDirectionVector();

	if (!inGutter
			&& (bowlPosition.x < placePosition.x + placeSize.x / 3 + 6 || bowlPosition.x > placePosition.x + 2 * placeSize.x / 3 - 6))
	{
		power /= 1.5;
		rotation = 0;
		inGutter = true;
	}

	if (inGutter
			&& (bowlPosition.x < placePosition.x + placeSize.x / 3 + 3.75
					|| bowlPosition.x > placePosition.x + 2 * placeSize.x / 3 - 3.75))
	{
		bowl.rotateY(-atan(lookDirection.x / lookDirection.z) * 180 / PI);
	}
}

void Model::setCameraMode(CameraMode cameraMode)
{
	this->cameraMode = cameraMode;
}

void Model::setPosition(float position)
{
	if (this->position + position >= MIN_POSITION && this->position + position <= MAX_POSITION)
	{
		this->position += position;
		bowl.setPosition(bowl.getPosition() + Vector3df(float(position) / 2, 0.0, 0.0));
	}
}

void Model::setPower(float power)
{
	if (this->power + power >= MIN_POWER && this->power + power <= MAX_POWER)
		this->power += power;
}

void Model::setDirection(float direction)
{
	if (this->direction + direction >= MIN_DIRECTION && this->direction + direction <= MAX_DIRECTION)
	{
		this->direction += direction;
		bowl.rotateY(-direction / 2);
	}
}

void Model::setRotation(float rotation)
{
	if (this->rotation + rotation >= MIN_ROTATION && this->rotation + rotation <= MAX_ROTATION)
	{
		this->rotation += rotation;
	}
}

float Model::getPosition() const
{
	return position;
}

float Model::getPower() const
{
	return power;
}

float Model::getDirection() const
{
	return direction;
}

float Model::getRotation() const
{
	return rotation;
}

bool Model::isAnimating() const
{
	return animating;
}

void Model::startAnimation()
{
	animating = true;
}

bool Model::hasAnimationElapsed() const
{
	return elapsed;
}

void Model::reset()
{
	position = 0;
	power = 20;
	direction = 0;
	rotation = 0;

	animating = false;
	elapsed = false;
	inGutter = false;
	bowl.reset();
	if (firstThrow)
	{
		place.pinSet.reset();
		firstThrow = false;
	}
	else
	{
		for (Pin& pin : place.pinSet.pins)
		{
			pin.setVisible(!pin.hasFallen());
		}
		place.pinSet.hideKnockedPins();
		firstThrow = true;
	}
}
