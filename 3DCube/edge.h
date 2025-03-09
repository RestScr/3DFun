#pragma once

#include "vector3d.h"

class Edge
{
public:
	Vector3D FirstVertex;
	Vector3D SecondVertex;
	Vector3D ThirdVertex;

	Edge();
	Edge(double, double, double,
		double, double, double,
		double, double, double);
	Edge(Vector3D, Vector3D, Vector3D);
};
