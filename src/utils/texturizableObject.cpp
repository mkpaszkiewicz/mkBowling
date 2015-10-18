#include "texturizableObject.hpp"

TexturizableObject::TexturizableObject()
{
	this->filenames = std::vector<std::string>();
	this->textureIds = new unsigned int[getTextureNumber()];
}

TexturizableObject::TexturizableObject(std::vector<std::string>& filenames)
{
	this->filenames = filenames;
	this->textureIds = new unsigned int[getTextureNumber()];
}

TexturizableObject::~TexturizableObject()
{
}

int TexturizableObject::getTextureNumber() const
{
	return filenames.size();
}

std::vector<std::string> TexturizableObject::getFilenames() const
{
	return filenames;
}

void TexturizableObject::setFilenames(std::vector<std::string> filenames)
{
	this->filenames = filenames;
	delete textureIds;
	this->textureIds = new unsigned int[getTextureNumber()];
}

unsigned int* TexturizableObject::getTextureIds()
{
	return textureIds;
}

