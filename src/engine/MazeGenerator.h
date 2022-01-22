#pragma once

#include "RenderList.h"

#include <vector>
#include <stack>

struct MazeCell
{
	bool topOpen = false;
	bool bottomOpen = false;
	bool leftOpen = false;
	bool rightOpen = false;
};

class MazeGenerator {
public:
	MazeGenerator(int cellColumns, int cellRows);

	// will fill one cell then return true. Returns false when the maze is fully generated
	bool itterateGeneration();
	void fullyGenerate();
	bool isFullyGenerated();

	void appendToRenderList(RenderList& renderList, float baseX, float baseY, float totalWidth, float totalHeight);

	std::vector<std::vector<MazeCell>> getCells();

private:
	std::vector<std::vector<MazeCell>> cells;
	bool cellWasVisited(MazeCell& cell);
	std::vector<std::array<int, 2>> getPossibleNextCells(int x, int y);
	bool isInBounds(int x, int y);
	void connectCells(std::array<int, 2> cell1, std::array<int, 2> cell2);

	int cellsFilled = 0;
	std::stack<std::array<int, 2>> visitStack;

};


