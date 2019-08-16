#pragma once

#include <EOUL\File.hpp>

#include <string>

namespace EOUL::dependencies {

	#define STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_STATIC
	#include <EOUL\dependencies\stb_image.h>
	#undef STB_IMAGE_STATIC
	#undef STB_IMAGE_IMPLEMENTATION

}

namespace EOUL::IO {

	class Image final : public FileBase {

		private:

			unsigned char* pixels = nullptr;
			unsigned int width = 0, height = 0, numComponents = 0;

		public:

			Image() = default;
			Image(std::filesystem::path path) : FileBase(std::move(path)) {

				this->load();

			}

			Image(Image&& other) noexcept {

				this->swap(other);

			}

			~Image() {

				if (this->pixels != nullptr) {

					dependencies::stbi_image_free(this->pixels);

				}

			}

		public:

			/* swaps 2 images */
			inline void swap(Image& other) {

				std::swap(this->width, other.width);
				std::swap(this->pixels, other.pixels);
				std::swap(this->height, other.height);
				std::swap(this->numComponents, other.numComponents);

			}
			
			/* loads/reloads image and deletes current pixel data */
			inline void load() {

				if (this->pixels != nullptr) {

					dependencies::stbi_image_free(this->pixels);

				}

				if (this->exists() && this->isFile() && !this->isDirectory()) {

					int width, height, numComponents;

					this->pixels = dependencies::stbi_load(path.u8string().c_str(), &width, &height, &numComponents, 0);

					this->width = width;
					this->height = height;
					this->numComponents = numComponents;

				}

			}

			/* returns the red channel with a scale from 0 - 255, of the specified pixel */
			inline unsigned char getRed(unsigned int x, unsigned int y) const {

				unsigned char bytePerPixel = (unsigned char)this->numComponents;
				unsigned char* pixelOffset = this->pixels + (y * this->width + x) * bytePerPixel;

				return pixelOffset[0];

			}
			/* returns the green channel with a scale from 0 - 255, of the specified pixel */
			inline unsigned char getGreen(unsigned int x, unsigned int y) const {

				unsigned char bytePerPixel = (unsigned char)this->numComponents;
				unsigned char* pixelOffset = this->pixels + (y * this->width + x) * bytePerPixel;

				return pixelOffset[1];

			}
			/* returns the blue channel with a scale from 0 - 255, of the specified pixel */
			inline unsigned char getBlue(unsigned int x, unsigned int y) const {

				unsigned char bytePerPixel = (unsigned char)this->numComponents;
				unsigned char* pixelOffset = this->pixels + (y * this->width + x) * bytePerPixel;

				return pixelOffset[2];

			}
			/* returns the alpha channel with a scale from 0 - 255, of the specified pixel */
			inline unsigned char getAlpha(unsigned int x, unsigned int y) const {

				unsigned char bytePerPixel = (unsigned char)this->numComponents;
				unsigned char* pixelOffset = this->pixels + (y * this->width + x) * bytePerPixel;

				return this->numComponents >= 4 ? pixelOffset[3] : 0xff;


			}
			/* returns an unsigned integer representation of the rgba values, of the specified pixel */
			inline unsigned int getRGBA(unsigned int x, unsigned int y) const {

				unsigned char bytePerPixel = (unsigned char)this->numComponents;
				unsigned char* pixelOffset = this->pixels + (y * this->width + x) * bytePerPixel;
				unsigned char r = pixelOffset[0];
				unsigned char g = pixelOffset[1];
				unsigned char b = pixelOffset[2];
				unsigned char a = this->numComponents >= 4 ? pixelOffset[3] : 0xff;

				return (a << 24) | (r << 16) | (g << 8) | (b << 0);

			}

			/* returns width of the image */
			inline unsigned int getWidth() const {

				return this->width;

			}
			/* returns height of the image */
			inline unsigned int getHeight() const {

				return this->height;

			}

			/* returns a pointer to the pixel array */
			inline const unsigned char* getPixels() const {

				return this->pixels;

			}

	};

}