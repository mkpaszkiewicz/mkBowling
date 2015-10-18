#include "image.hpp"

#define TARGA_HEADER_SIZE 0x12
#define TARGA_UNCOMP_RGB_IMG 0x02
#define TARGA_UNCOMP_BW_IMG 0x03

using namespace std;

Image::Image(const string& filename, enum ImageType type) :
		width(0), height(0), pixels(NULL)
{
	ifstream file(filename.c_str(), ios::binary);

	// no file on disk
	if (!file.is_open())
	{
		return;
	}

	switch (type)
	{
		case TARGA:
			loadTarga(file);
			break;
	}

	file.close();
}

Image::~Image()
{
	if (pixels != NULL)
	{
		delete[] (unsigned char*) pixels;
	}
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

GLenum Image::getFormat() const
{
	return format;
}

GLenum Image::getType() const
{
	return type;
}

char* Image::getPixels()
{
	return pixels;
}

bool Image::isValid() const
{
	return pixels != NULL;
}

bool Image::loadTarga(ifstream& file)
{
	char header[TARGA_HEADER_SIZE];

	// reading header
	file.read(header, TARGA_HEADER_SIZE);

	// skipping ImageID field
	file.seekg(header[0], ios_base::cur);

	width = (int) (header[12] & 255) + (header[13] << 8);
	height = (int) (header[14] & 255) + (header[15] << 8);
	type = GL_UNSIGNED_BYTE;
	int size = width * height;
	if (header[2] == TARGA_UNCOMP_RGB_IMG && header[16] == 24)
	{
		// image in BGR format - 24 bits
		size *= 3;
		format = GL_BGR;
	}
	else if (header[2] == TARGA_UNCOMP_RGB_IMG && header[16] == 32)
	{
		// image in BGRA format - 32 bits
		size *= 4;
		format = GL_BGRA;
	}
	else if (header[2] == TARGA_UNCOMP_BW_IMG && header[16] == 8)
	{
		// image in grayscale - 8 bits
		size *= 1;
		format = GL_LUMINANCE;
	}
	else
	{
		return false;
	}

	pixels = new char[size];
	file.read(pixels, size);

	return true;
}

bool Image::saveTarga(const string& filename)
{

	// image format
	if (format != GL_BGR && format != GL_BGRA && format != GL_LUMINANCE)
	{
		return false;
	}

	// pixel format
	if (type != GL_UNSIGNED_BYTE)
	{
		return false;
	}

	ofstream file(filename.c_str(), ios::binary);

	// cannot create file
	if (!file.is_open())
	{
		return false;
	}

	char header[TARGA_HEADER_SIZE];
	memset(header, 0, TARGA_HEADER_SIZE);

	// ImageType field
	if (format == GL_BGR || format == GL_BGRA)
	{
		header[2] = TARGA_UNCOMP_RGB_IMG;
	}
	else if (format == GL_LUMINANCE)
	{
		header[2] = TARGA_UNCOMP_BW_IMG;
	}

	// Width field
	header[12] = (unsigned char) width;
	header[13] = (unsigned char) (width >> 8);

	// Height field
	header[14] = (unsigned char) height;
	header[15] = (unsigned char) (height >> 8);

	// PixelDepth field
	if (format == GL_BGRA)
	{
		header[16] = 32;
	}
	else if (format == GL_BGR)
	{
		header[16] = 24;
	}
	else if (format == GL_LUMINANCE)
	{
		header[16] = 8;
	}

	// saving header
	file.write(header, TARGA_HEADER_SIZE);

	// saving image
	int size = width * height;
	if (format == GL_BGRA)
	{
		size *= 4;
	}
	else if (format == GL_BGR)
	{
		size *= 3;
	}
	else if (format == GL_LUMINANCE)
	{
		size *= 1;
	}
	file.write(pixels, size);

	return true;
}
