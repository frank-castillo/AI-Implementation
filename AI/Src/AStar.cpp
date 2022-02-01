#include "Precompiled.h"
#include "AStar.h"

using namespace AI;

namespace
{
	bool List_Sorter(const GridBasedGraph::Node* nodeA, const GridBasedGraph::Node* nodeB)
	{
		return (nodeA->g + nodeA->h < nodeB->g + nodeB->h);
	}
}

bool ASTAR::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristic getHeuristic)
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
				if (neighbour == nullptr)
					continue;

				// I have not encountered this node
				if (!neighbour->inOpenList)
				{
					// Add expanded node to open list, set parent
					mOpenList.push_back(neighbour);
					neighbour->g = node->g + getCost(node, neighbour);
					neighbour->h = getHeuristic(neighbour, endX, endY);
					neighbour->inOpenList = true;
					neighbour->parent = node;
					//InsertSortedElement(neighbour);
					mOpenList.sort(List_Sorter);
				}

				else if (!neighbour->inClosedList)
				{
					if (node->g + getCost(node, neighbour) < neighbour->g)
					{
						neighbour->parent = node;
						neighbour->g = getCost(node, neighbour);
						mOpenList.sort(List_Sorter);
					}
				}

			}
		}

		// Add node N to closed list
		node->inClosedList = true;
		mClosedList.push_back(node);
	}

	return found;
}

void ASTAR::InsertSortedElement(AI::GridBasedGraph::Node* node)
{
	if (mOpenList.empty())
	{
		mOpenList.push_front(node);
		return;
	}

	for (std::list<AI::GridBasedGraph::Node*>::iterator it = mOpenList.begin(); it != mOpenList.end(); ++it)
	{
		auto currentNode = *it;

		if (node->g + node->h < currentNode->g + currentNode->h)
		{
			mOpenList.insert(it, node);
			return;
		}
	}
}