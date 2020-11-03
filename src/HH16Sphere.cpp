# include "../include/HH16Sphere.h"
# include "../include/KaminoTimer.h"
# include "lodepng.h"

using namespace std;

const size_t width = 1024;
const size_t height = 512;

struct color {
	size_t R;
	size_t G;
	size_t B;
	size_t A;
};

color red = {255, 0, 0, 255};
color white = {255, 255, 255, 255};

void output_png(const char* filename, vector<unsigned char>& image)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void set_point(vector<unsigned char>& image, size_t x, size_t y, color color)
{
	//int x = x_i;
	//int y = height - y_i;
	image[4 * width * y + 4 * x + 0] = color.R;
	image[4 * width * y + 4 * x + 1] = color.G;
	image[4 * width * y + 4 * x + 2] = color.B;
	image[4 * width * y + 4 * x + 3] = color.A;
}

void initial_drawer()
{
	vector<unsigned char> image;
	image.resize(height*width * 4);
	vector<color> color_old;
	vector<color> color_new;
	color_old.resize(height*width);
	color_new.resize(height*width);

	for (int y = 0; y < height; y++)
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

HH16Sphere::HH16Sphere(fReal radius, size_t nTheta,
        float dt, float DT, int frames,
        std::string gridPath) :
        radius(radius), nTheta(nTheta + 1), nPhi(2 * nTheta), gridLen(M_PI / nTheta),
        dt(dt), DT(DT), frames(frames),
        gridPath(gridPath)
{
}

HH16Sphere::~HH16Sphere()
{
}

void HH16Sphere::run()
{
    HH16Solver solver(nPhi, nTheta, radius, gridLen, dt);

    HH16Quantity* u = solver.getAttributeNamed("u");
    HH16Quantity* v = solver.getAttributeNamed("v");

    //solver.write_data_bgeo(gridPath, 0);

    float T = 0.0;              // simulation time
    //KaminoTimer timer;
    //timer.startTimer();

	initial_drawer();

    for(int i = 1; i <= frames; i++){
        while(T < i*DT){
            solver.stepForward(dt);
            T += dt;
        }
        solver.stepForward(dt + i*DT - T);
        T = i*DT;

        //solver.write_data_bgeo(gridPath, i);
    }
    //float cpu_time = timer.stopTimer();
    //std::cout << "Time spent: " << cpu_time << " seconds" << std::endl;
    //std::cout << "Performance: " << frames / cpu_time << " frames per second" << std::endl;

    std::cout << "check" << std::endl;
}