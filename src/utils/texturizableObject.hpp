#ifndef TEXTURIZABLE_OBJECT_HPP_
#define TEXTURIZABLE_OBJECT_HPP_

#include "../utils/common.hpp"

class TexturizableObject
{
	protected:
		std::vector<std::string> filenames;

		unsigned int* textureIds;

	public:
		TexturizableObject();

		TexturizableObject(std::vector<std::string>& filenames);

		~TexturizableObject();

		/**
		 * Sets filenames
		 */
		void setFilenames(std::vector<std::string> filenames);

		/**
		 * Returns number of textures - filenames size
		 */
		int getTextureNumber() const;

		/**
		 * Returns filenames
		 */
		std::vector<std::string> getFilenames() const;

		/**
		 * Returns textureIds
		 */
		unsigned int* getTextureIds();
};

#endif /* TEXTURIZABLEOBJECT_HPP_ */

