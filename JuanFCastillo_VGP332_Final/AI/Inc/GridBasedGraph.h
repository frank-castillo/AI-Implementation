#pragma once

namespace AI
{
	class GridBasedGraph
	{
	public:
		enum Direction // enums are basically numbers with names
		{
			North,
			South,
			East,
			West,
			NorthEast,
			NorthWest,
			SouthEast,
			SouthWest
		};

		struct Node
		{
			std::array<Node*, 8> neighbours = {};
			int column{ 0 };
			int row{ 0 };

			// Search params
			Node* parent = nullptr;
			bool inOpenList = false;
			bool inClosedList = false;
			float g = 0.0f;
			float h = 0.0f;
		};

		void Initialize(int columns, int rows);
		void ResetSearchParams();

		Node* GetNode(int x, int y); // This allows to modify a node
		const Node* GetNode(int x, int y) const; // This won't allow to modify a node

		int GetColumns() const { return mColumns; }
		int GetRows() const { return mRows; }

	private:
		int GetIndex(int x, int y) const;

		std::vector<Node> mNodes;
		int mColumns{ 0 };
		int mRows{ 0 };
	};
}