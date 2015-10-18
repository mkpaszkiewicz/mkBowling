#ifndef TEXTURIZABLEOBJECT_HPP_
#define TEXTURIZABLEOBJECT_HPP_

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

	void setFilenames(std::vector<std::string> filenames);
	int getTextureNumber() const;
	std::vector<std::string> getFilenames() const;
	unsigned int* getTextureIds();
};

#endif /* TEXTURIZABLEOBJECT_HPP_ */





