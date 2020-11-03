#pragma once
#include "lodepng.h" 
#include "GlobalIncludes.h"

using namespace std;

struct color {
	size_t R;
	size_t G;
	size_t B;
	size_t A;
};

class Drawer
{
private:
	vector<unsigned char> image;
	vector<color> color_old;
	vector<color> color_new;
	color red = { 255, 0, 0, 255 };
	color white = { 255, 255, 255, 255 };
	size_t height;
	size_t width;

public:
	Drawer(size_t height, size_t width);
	~Drawer();

	void initial_drawer();
	void set_point(vector<unsigned char>& image, size_t, size_t, color);
	void color_advect();

	void output_png(const char*, vector<unsigned char>&);
};