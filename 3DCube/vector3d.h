#pragma once

#include <cmath>
#include <string>
#include "position3d.h"

class Vector3D
{
public:
	Position3D Coordinates;

	Vector3D();
	Vector3D(double x, double y, double z);
	Vector3D(Position3D);

	Vector3D operator+(Vector3D&);
	Vector3D operator-(Vector3D&);
	Vector3D operator*(double);
	double operator*(Vector3D&);
	void operator+=(Vector3D&);
	void operator-=(Vector3D&);
	void operator*=(double);

	Vector3D VectorMultiply(Vector3D&);

	std::string ToString();

	double Absolute();

	double ProjectionOn(Vector3D&);
};
