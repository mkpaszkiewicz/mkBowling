#include "view.hpp"

const std::string View::imagePath = "graphics/";
const std::string View::imageFormat = ".tga";

View::View()
{
}

void View::texturize(Model& model)
{
	texturize(model.getPlace());
	texturize(model.getBowl());
	texturize(model.getPlace().machine1);
	texturize(model.getPlace().machine2);
	texturize(model.getPlace().pinSet);
	texturize(model.getPlace().pinSet1);
	texturize(model.getPlace().pinSet2);
}

void View::render(Model& model) const
{
	render(model.getCamera());
	render(model.getPlace());
	render(model.getBowl());
	if (!model.isAnimating())
	{
		Vector3df position = model.getBowl().getPosition();
		Vector3df normal = Vector3df(0.0, 1.0, 0.0);
		drawArrow(position, normal, model.getPower(), model.getDirection(), model.getRotation());
	}
}

void View::texturize(TexturizableObject& object)
{
	std::vector<Image*> images;
	for (int i = 0; i < object.getTextureNumber(); ++i)
	{
		images.push_back(new Image(imagePath + object.getFilenames()[i] + imageFormat, TARGA));
	}
	glGenTextures(object.getTextureNumber(), object.getTextureIds());
	for (int i = 0; i < object.getTextureNumber(); ++i)
	{
		glBindTexture(GL_TEXTURE_2D, object.getTextureIds()[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[i]->getWidth(), images[i]->getHeight(), 0, images[i]->getFormat(),
				images[i]->getType(), images[i]->getPixels());
	}
}

void View::texturize(BowlingMachine& bowlingMachine)
{
	texturize((TexturizableObject&) bowlingMachine);
	texturize(bowlingMachine.bowl1);
	texturize(bowlingMachine.bowl2);
	texturize(bowlingMachine.bowl3);
}

void View::texturize(PinSet& pinSet)
{
	for (Pin& pin : pinSet.pins)
	{
		texturize(pin);
	}
}

void View::drawTexturedRectangle(const Vector3df& a, const Vector3df& b, const Vector3df& c, const Vector3df& d,
		const Vector3df& normal, GLuint textureId, float xRepeat, float yRepeat) const
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_QUADS);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(a.x, a.y, a.z);
	glTexCoord2f(0.0, yRepeat);
	glVertex3f(b.x, b.y, b.z);
	glTexCoord2f(xRepeat, yRepeat);
	glVertex3f(c.x, c.y, c.z);
	glTexCoord2f(xRepeat, 0.0);
	glVertex3f(d.x, d.y, d.z);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void View::drawArrow(const Vector3df& position, const Vector3df& normal, float power, float direction, float rotation) const
{
	float width = 2.0;
	float diffuseDefault[] = { 0.8, 0.8, 0.8, 1.0 };
	float diffuse[] = { 0.6, 0.0, 0.0, 1.0 };

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glRotatef(-direction / 2, 0, 1, 0);
	glTranslatef(position.x, position.y, position.z);

	glBegin(GL_QUADS);

	glNormal3f(normal.x, normal.y, normal.z);

	if (rotation == 0)
	{
		glVertex3f(-width / 2, 0.0, 0.0);
		glVertex3f(-width / 2, 0.0, -power);
		glVertex3f(width / 2, 0.0, -power);
		glVertex3f(width / 2, 0.0, 0.0);
	}
	else
	{
		drawArc(Point3df(-width / 2, 0.0, 0.0), Point3df(-width / 2, 0.0, -power), Point3df(1000 / rotation, 0.0, -power / 2), 16,
				width);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-direction / 2, 0, 1, 0);
	glTranslatef(position.x - rotation / 60, position.y, position.z - power + 1);
	glRotatef(-rotation / 2, 0, 1, 0);

	glBegin(GL_POLYGON);
	glVertex3f(-3 * width / 2, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -5);
	glVertex3f(3 * width / 2, 0.0, 0.0);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseDefault);
	glPopMatrix();
}

void View::drawArc(const Point3df& start, const Point3df& end, const Point3df& centre, int segments, float width) const
{
	float radius = distance(centre, start);
	float angle = asin(distance(start, end) / 2 / radius) * 360 / PI;
	int rotation = centre.x > start.x ? -1 : 1;
	Point3df point = start;
	Point3df previous = point;
	for (int i = 0; i < segments; i++)
	{
		glVertex3f(point.x, point.y, point.z);
		previous = point;
		point.x -= centre.x;
		point.y -= centre.y;
		point.z -= centre.z;
		point.rotateY(rotation * angle / segments);
		point.x += centre.x;
		point.y += centre.y;
		point.z += centre.z;
		glVertex3f(point.x, point.y, point.z);
		glVertex3f(point.x + width, point.y, point.z);
		glVertex3f(previous.x + width, previous.y, previous.z);
	}
}

void View::render(BowlingMachine& machine) const
{
	Vector3df position = machine.getPosition();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, machine.getTextureIds()[0]);

	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 0);
	glVertex3f(position.x, position.y, position.z);
	glVertex3f(position.x, position.y + 10, position.z);
	glVertex3f(position.x, position.y + 16, position.z + 2);
	glVertex3f(position.x, position.y + 16, position.z + 7);
	glVertex3f(position.x, position.y + 10, position.z + 11);
	glVertex3f(position.x, position.y + 10, position.z + 26);
	glVertex3f(position.x, position.y + 7, position.z + 28);
	glVertex3f(position.x, position.y, position.z + 28);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 0);
	glVertex3f(position.x + 6, position.y, position.z);
	glVertex3f(position.x + 6, position.y + 10, position.z);
	glVertex3f(position.x + 6, position.y + 16, position.z + 2);
	glVertex3f(position.x + 6, position.y + 16, position.z + 7);
	glVertex3f(position.x + 6, position.y + 10, position.z + 11);
	glVertex3f(position.x + 6, position.y + 10, position.z + 26);
	glVertex3f(position.x + 6, position.y + 7, position.z + 28);
	glVertex3f(position.x + 6, position.y, position.z + 28);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3f(position.x + 6, position.y, position.z);
	glVertex3f(position.x + 6, position.y + 10, position.z);
	glVertex3f(position.x, position.y + 10, position.z);
	glVertex3f(position.x, position.y, position.z);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, -3);
	glVertex3f(position.x + 6, position.y + 10, position.z);
	glVertex3f(position.x + 6, position.y + 16, position.z + 2);
	glVertex3f(position.x, position.y + 16, position.z + 2);
	glVertex3f(position.x, position.y + 10, position.z);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(position.x + 6, position.y + 16, position.z + 2);
	glVertex3f(position.x + 6, position.y + 16, position.z + 7);
	glVertex3f(position.x, position.y + 16, position.z + 7);
	glVertex3f(position.x, position.y + 16, position.z + 2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 2, 3);
	glVertex3f(position.x + 6, position.y + 16, position.z + 7);
	glVertex3f(position.x + 6, position.y + 10, position.z + 11);
	glVertex3f(position.x, position.y + 10, position.z + 11);
	glVertex3f(position.x, position.y + 16, position.z + 7);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(position.x + 6, position.y + 10, position.z + 11);
	glVertex3f(position.x + 6, position.y + 10, position.z + 26);
	glVertex3f(position.x, position.y + 10, position.z + 26);
	glVertex3f(position.x, position.y + 10, position.z + 11);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 2, 3);
	glVertex3f(position.x + 6, position.y + 10, position.z + 26);
	glVertex3f(position.x + 6, position.y + 7, position.z + 28);
	glVertex3f(position.x, position.y + 7, position.z + 28);
	glVertex3f(position.x, position.y + 10, position.z + 26);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(position.x + 6, position.y + 7, position.z + 28);
	glVertex3f(position.x + 6, position.y, position.z + 28);
	glVertex3f(position.x, position.y, position.z + 28);
	glVertex3f(position.x, position.y + 7, position.z + 28);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	render(machine.bowl1);
	render(machine.bowl2);
	render(machine.bowl3);
}

void View::render(Camera& camera) const
{
	// the point at which the camera looks
	Vector3df lookPoint = camera.position + camera.lookDirection;

	gluLookAt(camera.position.x, camera.position.y, camera.position.z, lookPoint.x, lookPoint.y, lookPoint.z, camera.upVector.x,
			camera.upVector.y, camera.upVector.z);
}

void View::render(Place& place) const
{
	Vector3df position = place.getPosition();
	Vector3df size = place.getSize();

	//floor
	float specularDefault[] = { 0.0, 0.0, 0.0, 1.0 };
	float specular[] = { 0.9, 0.9, 0.9, 1.0 };
	float diffuseDefault[] = { 0.8, 0.8, 0.8, 1.0 };
	float diffuse[] = { 3.0, 3.0, 3.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);
	Vector3df normal = Vector3df(0, 1, 0);
	Vector3df a = Vector3df(position.x, position.y, position.z - size.z / 6);
	Vector3df b = Vector3df(position.x + size.x, position.y, position.z - size.z / 6);
	Vector3df c = Vector3df(position.x + size.x, position.y, position.z - size.z);
	Vector3df d = Vector3df(position.x, position.y, position.z - size.z);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[0], 3.0, 3.0);

	normal = Vector3df(0, 1, 0);
	a = Vector3df(position.x, position.y, position.z);
	b = Vector3df(position.x + size.x, position.y, position.z);
	c = Vector3df(position.x + size.x, position.y, position.z - size.z / 6);
	d = Vector3df(position.x, position.y, position.z - size.z / 6);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[1], 1.0, 3.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularDefault);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseDefault);

	//top
	normal = Vector3df(0, 1, 0);
	a = Vector3df(position.x, position.y + size.y, position.z);
	b = Vector3df(position.x, position.y + size.y, position.z - size.z);
	c = Vector3df(position.x + size.x, position.y + size.y, position.z - size.z);
	d = Vector3df(position.x + size.x, position.y + size.y, position.z);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[2], 8.0, 22.0);

	//back
	normal = Vector3df(0, 1, 1);
	a = Vector3df(position.x, position.y, position.z - size.z);
	b = Vector3df(position.x, position.y + size.y, position.z - size.z);
	c = Vector3df(position.x + size.x, position.y + size.y, position.z - size.z);
	d = Vector3df(position.x + size.x, position.y, position.z - size.z);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[3], 3.0, 1.0);

	//front
	normal = Vector3df(0, 1, -1);
	a = Vector3df(position.x + size.x, position.y, position.z);
	b = Vector3df(position.x + size.x, position.y + size.y, position.z);
	c = Vector3df(position.x, position.y + size.y, position.z);
	d = Vector3df(position.x, position.y, position.z);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[4], 1.0, 1.0);

	//left
	normal = Vector3df(1, 1, 0);
	a = Vector3df(position.x, position.y, position.z);
	b = Vector3df(position.x, position.y + size.y, position.z);
	c = Vector3df(position.x, position.y + size.y, position.z - size.z);
	d = Vector3df(position.x, position.y, position.z - size.z);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[5], 1.0, 1.0);

	//right
	normal = Vector3df(-1, 1, 0);
	a = Vector3df(position.x + size.x, position.y, position.z);
	b = Vector3df(position.x + size.x, position.y + size.y, position.z);
	c = Vector3df(position.x + size.x, position.y + size.y, position.z - size.z);
	d = Vector3df(position.x + size.x, position.y, position.z - size.z);
	drawTexturedRectangle(a, b, c, d, normal, place.getTextureIds()[5], 1.0, 1.0);

	render(place.machine1);
	render(place.machine2);
	render(place.pinSet);
	render(place.pinSet1);
	render(place.pinSet2);
}

void View::render(Bowl& bowl) const
{
	GLUquadric* ptr = gluNewQuadric();
	gluQuadricTexture(ptr, GL_TRUE);

	glPushMatrix();
	float specularDefault[] = { 0.0, 0.0, 0.0, 1.0 };
	float specular[] = { 0.8, 0.8, 0.8, 1.0 };
	float diffuseDefault[] = { 0.8, 0.8, 0.8, 1.0 };
	float diffuse[] = { 6.0, 6.0, 6.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, bowl.getTextureIds()[0]);
	Vector3df position = bowl.getPosition();
	glTranslatef(position.x, position.y, position.z);

	Vector3df rightVector = bowl.getRightVector();
	Vector3df upVector = bowl.getUpVector();
	Vector3df lookDirection = bowl.getDirectionVector();
	glRotatef(bowl.getRotatedX(), rightVector.x, rightVector.y, rightVector.z);
	glRotatef(bowl.getRotatedY(), upVector.x, upVector.y, upVector.z);
	glRotatef(bowl.getRotatedZ(), lookDirection.x, lookDirection.y, lookDirection.z);
	gluSphere(ptr, bowl.getRadius(), 32, 16);

	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularDefault);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseDefault);
	glPopMatrix();

	gluDeleteQuadric(ptr);
}

void View::render(PinSet& pinSet) const
{
	for (Pin& pin : pinSet.pins)
	{
		if (pin.isVisible())
		{
			render(pin);
		}
	}
}

void View::render(Pin& pin) const
{
	GLUquadric* ptr = gluNewQuadric();
	gluQuadricTexture(ptr, GL_TRUE);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pin.getTextureIds()[0]);
	Vector3df position = pin.getPosition();
	glTranslatef(position.x, position.y, position.z);

	if (abs(pin.getRotatedZ()) >= abs(pin.getRotatedX()))
	{
		int sign = pin.getRotatedZ() >= 0 ? -1 : 1;
		glRotatef(pin.getRotatedX() / 2, 0, sign, 0);
		glRotatef(pin.getRotatedZ(), 0, 0, -1);
	}
	else
	{
		int sign = pin.getRotatedX() >= 0 ? -1 : 1;
		glRotatef(pin.getRotatedZ() / 2, 0, sign, 0);
		glRotatef(pin.getRotatedX(), 1, 0, 0);
	}

	for (unsigned int i = 0; i < pin.contour.size() - 1; i++)
	{
		glBegin(GL_QUAD_STRIP);

		for (float angle = 0.0; angle <= 360; angle += 22.5)
		{
			Point3df point = pin.contour[i];
			point.rotateY(angle);
			glNormal3f(point.x, point.z, point.z);
			glTexCoord2f(angle / 360, point.y / pin.getHeight());
			glVertex3f(point.x, point.y, point.z);

			point = pin.contour[i + 1];
			point.rotateY(angle);
			glVertex3f(point.x, point.y, point.z);
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	gluDeleteQuadric(ptr);
}

