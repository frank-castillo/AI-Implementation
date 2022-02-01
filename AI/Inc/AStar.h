#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	using NodeList = std::list<GridBasedGraph::Node*>;
	using GetCost = std::function<float(const GridBasedGraph::Node*, const GridBasedGraph::Node*)>;
	using GetHeuristic = std::function<float(const GridBasedGraph::Node*, const int, const int)>;

	class ASTAR
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristic getHeuristic);

		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		void InsertSortedElement(GridBasedGraph::Node* node);

		NodeList mOpenList;
		NodeList mClosedList;
	};
}