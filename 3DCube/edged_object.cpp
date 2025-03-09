#include "edged_object.h"

EdgedObject::EdgedObject() {}

EdgedObject::EdgedObject(Edge edges[MAX_POLYGONS_PER_OBJECT]) {
	for (int i = 0; !edges[i].IsNullable(); i++)
	{
		_edges[i] = edges[i];
		_edgesAmount = i + 1;
	}
}

void EdgedObject::AddEdge(Edge edge)
{
	_edges[_edgesAmount++] = edge;
}

Edge* EdgedObject::Edges()
{
	return _edges;
}

unsigned int EdgedObject::EdgesAmount()
{
	return _edgesAmount;
}

