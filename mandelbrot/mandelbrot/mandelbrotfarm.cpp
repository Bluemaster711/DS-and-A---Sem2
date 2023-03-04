#include "mandelbrot.h"
#include "mandelbrotask.h"
#include "mandelbrotfarm.h"
#include <iostream>



void mandelbrotask::run() {

	const int WIDTH = 3840;
	const int HEIGHT = 2160;

	const int MAX_ITERATIONS = 1000;

	uint32_t image[HEIGHT][WIDTH]{};

	for (unsigned x = 0; x < WIDTH; x++)
	{

		std::complex<float> c(left_ + (x * (right_ - left_) / WIDTH),
			top_ + (line_ * (bottom_ - top_) / HEIGHT));

		std::complex<float> z(0.0, 0.0);

		int iterations = 0;
		while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
		{
			z = (z * z) + c;
			++iterations;
		}
		if (iterations == MAX_ITERATIONS)
		{

			image[line_][x] = 0x000000; // black
		}
		else
		{


			if (iterations <= 25)
			{
				image[line_][x] = 0xFF0000;
			}
			else if (iterations <= 50)
			{
				image[line_][x] = 0xFE6904;
			}
			else if (iterations <= 75)
			{
				image[line_][x] = 0xFEE104;
			}
			else if (iterations <= 100)
			{
				image[line_][x] = 0xB6FE04;
			}
			else if (iterations <= 125)
			{
				image[line_][x] = 0x13FE04;
			}
			else if (iterations <= 150)
			{
				image[line_][x] = 0x04FEA8;
			}
			else if (iterations <= 175)
			{
				image[line_][x] = 0x04E1FE;
			}
			else if (iterations <= 200)
			{
				image[line_][x] = 0x045BFE;
			}
			else if (iterations <= 250)
			{
				image[line_][x] = 0x0904FE;
			}
			else if (iterations <= 300)
			{
				image[line_][x] = 0x9404FE;
			}
			else if (iterations <= 400)
			{
				image[line_][x] = 0xFE04E1;
			}
			else if (iterations <= 450)
			{
				image[line_][x] = 0xFE047C;
			}
			else
			{
				image[line_][x] = 0xFE0404;
			}
		}
	}
	return;
}

