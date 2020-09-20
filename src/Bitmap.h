#pragma once

#include <string>
#include <cstdint>
#include <memory>

namespace Fractal
{
	class Bitmap
	{
	public:
		Bitmap() = default;
		Bitmap(int width, int height);
		virtual ~Bitmap();

		void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
		bool Write(std::string filename);

	private:
		int m_Width{ 0 };
		int m_Height{ 0 };
		std::unique_ptr<uint8_t[]> m_pPixels{ nullptr };
	};
}