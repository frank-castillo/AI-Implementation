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

	// TODO:
	//	while end node not reached && open list isn’t empty:
	//		select node N from open list <- depend on your strategy
	//		if node is end
	//			found = true
	//		else expand node N :
	//			if expanded node isn’t in open nor closed lists:
	//				add expanded node to open list, set parent
	//		Add node N to closed list

	return found;
}
