#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	using NodeList = std::list<GridBasedGraph::Node*>;
	using GetCost = std::function<float(const GridBasedGraph::Node*, const GridBasedGraph::Node*)>;

	class ASTAR
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost);

		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		void InsertSortedElement(GridBasedGraph::Node* node);
		float HeuristicCalculation(GridBasedGraph::Node* node, int endX, int endY );

		NodeList mOpenList;
		NodeList mClosedList;
	};
}