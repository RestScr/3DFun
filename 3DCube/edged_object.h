#pragma once

#include "constants.h"
#include "edge.h"

class EdgedObject
{
private:
	Edge _edges[MAX_POLYGONS_PER_OBJECT];
	unsigned int _edgesAmount = 0;

public:
	EdgedObject();
	EdgedObject(Edge[MAX_POLYGONS_PER_OBJECT]);
	void AddEdge(Edge);
	Edge *Edges();
	unsigned int EdgesAmount();
};
