#include "Precompiled.h"
#include "BFS.h"

using namespace AI;

bool BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	// Reset everything
	graph.ResetSearchParams();
	mOpenList.clear();
	mClosedList.clear();

	// Add start node to open list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->inOpenList = true;

	bool found = false;
	node->parent = nullptr;
	// TODO:
	//	While end node not reached && open list isn't empty:
	while (!found && !mOpenList.empty())
	{
		// Select node N from open list <- depend on your strategy
		auto node = mOpenList.front();
		mOpenList.pop_front();

		// If node N is end
		if (node->column == endX && node->row == endY)
		{
			found = true;
		}
		else
		{
			// Else expand node N
			for (auto neighbour : node->neighbours)
			{
				// If expanded node isn't in open nor closed lists
				if(neighbour == nullptr || neighbour->inOpenList || neighbour->inClosedList)
					continue;

				// Add expanded node to open list, set parent
				neighbour->parent = node;
				neighbour->inOpenList = true;
				mOpenList.push_back(neighbour);
			}
		}

		// Add node N to closed list
		node->inClosedList = true;
		mClosedList.push_back(node);
	}

	return found;
}
