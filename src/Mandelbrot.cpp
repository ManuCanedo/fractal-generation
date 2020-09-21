#include <math.h>
#include "Mandelbrot.h"
#include "complex"
#include "Timer.cpp"

namespace Fractal
{
	int Mandelbrot::GetIterations(double x, double y)
	{
		std::complex<double> z{ 0 };
		std::complex<double> c(x, y);
		int iterations{ 0 };

		while (iterations < MAX_ITERATIONS)
		{
			z = z * z + c;
			if (abs(z) > 2) break;
			++iterations;
		}

		return iterations;
	}

	void Mandelbrot::GenerateFractalNaive(const int WIDTH, const int HEIGHT, std::unique_ptr<int[]>& pHistogram, std::unique_ptr<int[]>& pFractal)
	{
		Timer timer;

		for (int j = 0; j < HEIGHT; ++j)
			for (int i = 0; i < WIDTH; ++i)
			{
				double xFractal{ (static_cast<int64_t>(i) - WIDTH / 2 - 200) * 2.0 / HEIGHT };
				double yFractal{ (static_cast<int64_t>(j) - HEIGHT / 2) * 2.0 / HEIGHT };

				int iterations{ Mandelbrot::GetIterations(xFractal, yFractal) };
				pFractal[static_cast<int64_t>(j) * WIDTH + i] = iterations;
				if (iterations < Mandelbrot::MAX_ITERATIONS)
					++pHistogram[iterations];
			}
	}

	void Mandelbrot::ColorFractal(const int WIDTH, const int HEIGHT, Bitmap& image, std::unique_ptr<int[]>& pHistogram, std::unique_ptr<int[]>& pFractal)
	{
		Timer timer;

		int total{ 0 };
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
			total += pHistogram[i];

		for (int j = 0; j < HEIGHT; ++j)
			for (int i = 0; i < WIDTH; ++i)
			{
				uint8_t red{ 0 }, green{ 0 }, blue{ 0 };

				int iterations = pFractal[static_cast<int64_t>(j) * WIDTH + i];
				if (iterations != Mandelbrot::MAX_ITERATIONS)
				{
					uint8_t color{ (uint8_t)(256 * static_cast<double>(iterations) / Mandelbrot::MAX_ITERATIONS) };

					double hue{ 0.0 };
					for (int i = 0; i <= iterations; ++i)
						hue += static_cast<double>(pHistogram[i]) / total;

					red = 255 * hue;
					green = std::pow(255, hue);
					blue = hue * red;
				}

				image.SetPixel(i, j, red, green, blue);
			}
	}
}
