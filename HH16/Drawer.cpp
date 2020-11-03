#include "Drawer.h"

using namespace std;

Drawer::Drawer(size_t height, size_t width)
	:height(height), width(width)
{
	image.resize(4 * height*width);
	color_old.resize(height*width);
	color_new.resize(height*width);


}

Drawer::~Drawer(){
}

void Drawer::initial_drawer()
{
	/*for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y < (height / 16))
				color_old[y*width + x] = red;
			//set_point(image, x, y, red);
			else if (y < (height / 8))
				color_old[y*width + x] = white;
			//set_point(image, x, y, white);
			else if (y < (height * 3 / 16))
				color_old[y*width + x] = red;
			//set_point(image, x, y, red);
			else if (y < (height / 4))
				color_old[y*width + x] = white;
			//set_point(image, x, y, white);
			else if (y < (height * 5 / 16))
				color_old[y*width + x] = red;
			//set_point(image, x, y, red);
			else if (y < (height * 3 / 8))
				color_old[y*width + x] = white;
			//set_point(image, x, y, white);
			else if (y < (height * 7 / 16))
				color_old[y*width + x] = red;
			//set_point(image, x, y, red);
			else if (y < (height / 2))
				color_old[y*width + x] = white;
			else if (y < (height * 9 / 16))
				color_old[y*width + x] = red;
			else if (y < (height * 5 / 8))
				color_old[y*width + x] = white;
			else if (y < (height * 11 / 16))
				color_old[y*width + x] = red;
			else if (y < (height * 3 / 4))
				color_old[y*width + x] = white;
			else if (y < (height * 13 / 16))
				color_old[y*width + x] = red;
			else if (y < (height * 7 / 8))
				color_old[y*width + x] = white;
			else if (y < (height * 15 / 16))
				color_old[y*width + x] = red;
			else
				color_old[y*width + x] = white;
			//set_point(image, x, y, white);
		}
	}*/

	unsigned int nStripe = 8;

	unsigned int gap = height / nStripe;

	int n = 8;

	//»­ÌõÎÆ
	for (size_t y = 0; y < height; y++)
	{
		n = floor(y / gap);

		for (size_t x = 0; x < width; x++)
		{
			if (!(n % 2))
				color_old[y*width + x] = red;
			else
				color_old[y*width + x] = white;
		}
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			set_point(image, x, y, color_old[y*width + x]);
		}
	}

	output_png("0000.png", image);
}

void Drawer::output_png(const char* filename, vector<unsigned char>& image)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void Drawer::set_point(vector<unsigned char>& image, size_t x, size_t y, color color)
{
	//int x = x_i;
	//int y = height - y_i;
	image[4 * width * y + 4 * x + 0] = color.R;
	image[4 * width * y + 4 * x + 1] = color.G;
	image[4 * width * y + 4 * x + 2] = color.B;
	image[4 * width * y + 4 * x + 3] = color.A;
}

void Drawer::color_advect()
{
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{

		}
	}
}