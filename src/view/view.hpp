#ifndef VIEW_HPP_
#define VIEW_HPP_

#include "camera.hpp"
#include "image.hpp"
#include "../utils/common.hpp"
#include "../model/model.hpp"
#include "../model/place.hpp"
#include "../model/bowl.hpp"
#include "../model/bowlingMachine.hpp"
#include "../model/pin.hpp"

class View
{
	private:
		static const std::string imagePath;
		static const std::string imageFormat;

		void drawTexturedRectangle(const Vector3df& a, const Vector3df& b, const Vector3df& c, const Vector3df& d,
				const Vector3df& normal, GLuint textureId, float xRepeat, float yRepeat) const;
		void drawArrow(const Vector3df& position, const Vector3df& normal, float power, float direction, float rotation) const;
		void drawArc(const Point3df& start, const Point3df& end, const Point3df& centre, int segments, float width) const;
		void texturize(TexturizableObject& object);
		void texturize(BowlingMachine& bowlingMachine);
		void texturize(PinSet& pinSet);

		void render(Camera& camera) const;
		void render(Place& place) const;
		void render(BowlingMachine& machine) const;
		void render(Bowl& bowl) const;
		void render(PinSet& pinSet) const;
		void render(Pin& pin) const;

	public:
		View();
		void texturize(Model& model);
		void render(Model& model) const;
};

#endif /* VIEW_HPP_ */
