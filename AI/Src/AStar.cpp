#include "Precompiled.h"
#include "AStar.h"

using namespace AI;

namespace
{
	bool List_Sorter(const GridBasedGraph::Node* nodeA, const GridBasedGraph::Node* nodeB)
	{
		return (nodeA->h < nodeB->h);
	}
}

bool AI::ASTAR::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost)
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
					neighbour->parent = node;
					neighbour->inOpenList = true;
					neighbour->g = node->g + getCost(node, neighbour);
					neighbour->h = HeuristicCalculation(neighbour, endX, endY) + neighbour->g;
					//InsertSortedElement(neighbour);
					mOpenList.push_back(neighbour);
					mOpenList.sort(List_Sorter);
				}

				else if (!neighbour->inClosedList)
				{
					if (node->g + getCost(node, neighbour) < neighbour->g)
					{
						neighbour->parent = node;
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

void AI::ASTAR::InsertSortedElement(AI::GridBasedGraph::Node* node)
{
	if (mOpenList.empty())
	{
		mOpenList.push_back(node);
		return;
	}

	for (std::list<GridBasedGraph::Node*>::iterator it = mOpenList.begin(); it != mOpenList.end(); ++it)
	{
		if ((*it)->g <= node->g)
		{
			mOpenList.insert(it, node);
			break;
		}
	}
}

float AI::ASTAR::HeuristicCalculation(GridBasedGraph::Node* node, int endX, int endY)
{
	auto dx = abs(node->row - endX);
	auto dy = abs(node->column - endY);
	return 1 * (dx + dy) + (5 - 2 * 1) * std::min(dx, dy);
}
