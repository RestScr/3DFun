#pragma once

#include "constants.h"
#include "edge.h"
//#include "vector3d.h"

class EdgedObject
{
private:
	Edge _edges[MAX_POLYGONS_PER_OBJECT];
	unsigned int _edgesAmount = 0;

public:
	Vector3D Center;
	EdgedObject();
	EdgedObject(Edge[MAX_POLYGONS_PER_OBJECT]);
	void AddEdge(Edge);
	void MoveBy(Vector3D);
	Edge *Edges();
	unsigned int EdgesAmount();
};
