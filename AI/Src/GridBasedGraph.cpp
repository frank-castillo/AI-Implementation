#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	//TODO
	// Resize mNodes to the matching dimension
	// For each node, set it's attributes (row/column)
	// However, the connection is up to the user
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	return nullptr;
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	return nullptr;
}

int GridBasedGraph::GetIndex(int x, int y) const
{
	return x + (y * mColumns);
}
