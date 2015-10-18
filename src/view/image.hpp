#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "../utils/common.hpp"

/**
 * Available image formats.
 */
enum ImageType
{
	/**
	 * Uncompressed targa
	 */
	TARGA
};

/**
 * Class representing 2D image.
 */
class Image
{
	protected:

		/**
		 * Width of image in pixels.
		 */
		int width;

		/**
		 * Height of image in pixels.
		 */
		int height;

		/**
		 * Can be one of following: GL_BGR, GL_BGRA, GL_LUMINANCE.
		 */
		GLenum format;

		/**
		 * Default: GL_UNSIGNED_BYTE.
		 */
		GLenum type;

		/**
		 * Pixels data storage.
		 */
		char* pixels;

	public:

		/**
		 * Loads an image in a specified type from file.
		 */
		Image(const std::string& filename, enum ImageType type);

		/**
		 * Destructor.
		 */
		~Image();

		/**
		 * Loads an image from specified file.
		 */
		bool loadTarga(std::ifstream& file);

		/**
		 * Saves an image in TARGA format.
		 */
		bool saveTarga(const std::string& filename);

		/**
		 * Returns width of the image in pixels.
		 */
		int getWidth() const;

		/**
		 * Returns height of the image in pixels.
		 */
		int getHeight() const;

		/**
		 * Returns width of the image in pixels.
		 */
		GLenum getFormat() const;

		/**
		 * Returns the type of image.
		 */
		GLenum getType() const;

		/**
		 * Returns the storage of pixels.
		 */
		char* getPixels();

		/**
		 * Indicates whether the image contains any pixels.
		 */
		bool isValid() const;

};

#endif // IMAGE_HPP_
