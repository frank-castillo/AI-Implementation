#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	//TODO
	// Resize mNodes to the matching dimension
	// For each node, set it's attributes (row/column)
	// However, the connection is up to the user

	mNodes.clear();
	mNodes.reserve(columns * rows);
	mColumns = columns;
	mRows = rows;

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			auto& node = mNodes.emplace_back();
			node.column = c;
			node.row = r;
		}
	}

	// Remember, memory is just one giant row of data
}

void GridBasedGraph::ResetSearchParams()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.inOpenList = false;
		node.inClosedList = false;
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
		return nullptr;

	const int index = GetIndex(x, y);
	return &mNodes[index];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
		return nullptr;

	const int index = GetIndex(x, y);
	return &mNodes[index];
}

int GridBasedGraph::GetIndex(int x, int y) const
{
	return x + (y * mColumns);
}
