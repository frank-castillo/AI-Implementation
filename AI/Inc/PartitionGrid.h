#pragma once

namespace AI
{
	template <class T>
	class PartitionGrid
	{
	public:
		using Cell = std::vector<T*>;

		void Resize(size_t columns, size_t rows)
		{
			mCells.clear();
			mCells.resize(columns * rows);
			mColumns = columns;
			mRows = rows;
		}

		void ClearCells()
		{
			for (auto& cell : mCells)
				cell.clear();
		}

		Cell& GetCell(size_t column, size_t row)
		{
			XASSERT(column < mColumns&& row < mRows, "[PartitionGrid] Invalid indices.");
			return mCells[column + (row * mColumns)];
		}

		const Cell& GetCell(size_t column, size_t row) const
		{
			XASSERT(column < mColumns&& row < mRows, "[PartitionGrid] Invalid indices.");
			return mCells[column + (row * mColumns)];
		}

		size_t GetColumns() const { return mColumns; }
		size_t GetRows() const { return mRows; }

	private:
		std::vector<Cell> mCells;
		size_t mColumns;
		size_t mRows;
	};
}