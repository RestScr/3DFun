#include "cube.h"

Cube::Cube(Vector3D center, double width)
{
	_width = width;
	Center = center;

	_generateCubeEdges();
}

void Cube::_generateCubeEdges()
{
	int halfWidth = _width / 2;
	// top vertices
	Vector3D vertex1(
		Center.Coordinates.X + halfWidth,
		Center.Coordinates.Y + halfWidth,
		Center.Coordinates.Z + halfWidth
	);
	Vector3D vertex2(
		Center.Coordinates.X - halfWidth,
		Center.Coordinates.Y + halfWidth,
		Center.Coordinates.Z + halfWidth
	);
	Vector3D vertex3(
		Center.Coordinates.X - halfWidth,
		Center.Coordinates.Y + halfWidth,
		Center.Coordinates.Z - halfWidth
	);
	Vector3D vertex4(
		Center.Coordinates.X + halfWidth,
		Center.Coordinates.Y + halfWidth,
		Center.Coordinates.Z - halfWidth
	);


	// bottom
	Vector3D vertex5(
		Center.Coordinates.X + halfWidth,
		Center.Coordinates.Y - halfWidth,
		Center.Coordinates.Z - halfWidth
	);
	Vector3D vertex6(
		Center.Coordinates.X + halfWidth,
		Center.Coordinates.Y - halfWidth,
		Center.Coordinates.Z + halfWidth
	);
	Vector3D vertex7(
		Center.Coordinates.X - halfWidth,
		Center.Coordinates.Y - halfWidth,
		Center.Coordinates.Z + halfWidth
	);
	Vector3D vertex8(
		Center.Coordinates.X - halfWidth,
		Center.Coordinates.Y - halfWidth,
		Center.Coordinates.Z - halfWidth
	);

	Edge edges[MAX_POLYGONS_PER_OBJECT];
	edges[0] = Edge(vertex1, vertex2, vertex3);
	edges[1] = Edge(vertex3, vertex4, vertex1);
	edges[2] = Edge(vertex1, vertex2, vertex7);
	edges[3] = Edge(vertex7, vertex6, vertex1);
	edges[4] = Edge(vertex4, vertex1, vertex6);
	edges[5] = Edge(vertex6, vertex5, vertex4);
	edges[6] = Edge(vertex5, vertex8, vertex3);
	edges[7] = Edge(vertex3, vertex4, vertex5);
	edges[8] = Edge(vertex8, vertex3, vertex2);
	edges[9] = Edge(vertex2, vertex7, vertex8);
	edges[10] = Edge(vertex6, vertex7, vertex8);
	edges[11] = Edge(vertex8, vertex5, vertex6);

	for (int i = 0; i < 12; i++)
	{
		AddEdge(edges[i]);
	}
}
