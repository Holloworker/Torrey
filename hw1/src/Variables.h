#pragma once
#include "vector.h"


class Variables
{
public:
	Variables(){};
public:
	static const int maxlights = 10;
	int numlights = 0;

	static const int maxobjects = 100000;

	static const int maxverts = 100;
	int numvertexs = 0;

	int numobjects;

	Real attenuation_const = 0;
	Real attenuation_linear = 0;
	Real attenuation_quadratic = 1.;

	int max_depth = 1;
	bool isPrimary_ray = true;

	int tile_size = 128;

	CameraType cameraType = PERSPECTIVE_CAM;
};