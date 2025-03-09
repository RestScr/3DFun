#pragma once

#include "matrix3d.h"
#include "vector3d.h"
#include "edged_object.h"

class Cube : public EdgedObject
{
private:
	double _width;
	void _generateCubeEdges();

public:
	Cube(Vector3D, double);
};
