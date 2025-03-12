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

std::string Edge::ToString()
{
	std::string result = "Vertex{\n";
	result += FirstVertex.ToString() + '\n';
	result += SecondVertex.ToString() + '\n';
	result += ThirdVertex.ToString() + '\n';
	result += '}';

	return result;
}

void Edge::MoveBy(Vector3D delta)
{
	FirstVertex += delta;
	SecondVertex += delta;
	ThirdVertex += delta;
}

void Edge::TransformBy(Matrix3D matrix)
{
	FirstVertex = matrix * FirstVertex;
	SecondVertex = matrix * SecondVertex;
	ThirdVertex = matrix * ThirdVertex;
}

Vector3D Edge::Center()
{
	double x = (FirstVertex.Coordinates.X + SecondVertex.Coordinates.X + ThirdVertex.Coordinates.X) / 3.0;
	double y = (FirstVertex.Coordinates.Y + SecondVertex.Coordinates.Y + ThirdVertex.Coordinates.Y) / 3.0;
	double z = (FirstVertex.Coordinates.Z + SecondVertex.Coordinates.Z + ThirdVertex.Coordinates.Z) / 3.0;

	return Vector3D(x, y, z);
}
