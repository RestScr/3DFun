#pragma once

#include "vector3d.h"

class Edge
{
private:
	bool _nullable = true;
public:
	Vector3D FirstVertex;
	Vector3D SecondVertex;
	Vector3D ThirdVertex;

	bool IsNullable();
	Edge();
	Edge(double, double, double,
		double, double, double,
		double, double, double);
	Edge(Vector3D, Vector3D, Vector3D);
};
