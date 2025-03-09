#include "edge.h"

Edge::Edge() {}

Edge::Edge(
	double x1, double y1, double z1,
	double x2, double y2, double z2,
	double x3, double y3, double z3
)
{
	FirstVertex = Vector3D(x1, y1, z1);
	SecondVertex = Vector3D(x2, y2, z2);
	ThirdVertex = Vector3D(x3, y3, z3);
	_nullable = false;
}

Edge::Edge(Vector3D vertex1, Vector3D vertex2, Vector3D vertex3)
{
	FirstVertex = vertex1;
	SecondVertex = vertex2;
	ThirdVertex = vertex3;
	_nullable = false;
}

bool Edge::IsNullable()
{
	return _nullable;
}


