#include "MazeGenerator.h"



MazeGenerator::MazeGenerator(int cellColumns, int cellRows)
{
	for (int i = 0; i < cellColumns; i++) {
		cells.push_back(std::vector<MazeCell>(cellRows));
	}
	visitStack.push({ cellColumns / 2, cellRows / 2 });
}

bool MazeGenerator::itterateGeneration()
{
	if (isFullyGenerated()) return false;

	std::array<int, 2> cursor = visitStack.top();
	std::vector<std::array<int, 2>> possibleCells = getPossibleNextCells(cursor[0], cursor[1]);

	if (possibleCells.size() == 0)
		visitStack.pop();

	else {
		std::array<int, 2> dest = possibleCells[rand() % possibleCells.size()];
		connectCells(cursor, dest);
		visitStack.push(dest);
		cellsFilled++;
	}

	return !isFullyGenerated();
}

void MazeGenerator::fullyGenerate()
{
	while (itterateGeneration());
}

bool MazeGenerator::isFullyGenerated()
{
	return cellsFilled >= cells.size() * cells[0].size() - 1;
}

void MazeGenerator::appendToRenderList(RenderList& renderlist, float baseX, float baseY, float totalWidth, float totalHeight)
{

	float cellDistX = totalWidth / cells.size();
	float cellDistY = totalHeight / cells[0].size();

	float bgColorR = 0.1f;
	float bgColorG = 0.1f;
	float bgColorB = 0.1f;
	float bgColorA = 1.0f;
	renderlist.addQuad(baseX, baseY, totalWidth, totalHeight, bgColorR, bgColorG, bgColorB, bgColorA);

	float wallThickness = 5.0f;
	float wallColorR = 1.0f;
	float wallColorG = 1.0f;
	float wallColorB = 1.0f;
	float wallColorA = 1.0f;

	for (int x = 0; x < cells.size(); x++) {
		for (int y = 0; y < cells[0].size(); y++) {
			MazeCell& cell = cells[x][y];

			if (!cell.topOpen) {
				float rx = baseX + cellDistX * x;
				float ry = baseY + cellDistY * y + cellDistY;
				renderlist.addLine(rx, ry, rx + cellDistX, ry, wallThickness, wallColorR, wallColorG, wallColorB, wallColorA);
			}

			if (!cell.bottomOpen) {
				float rx = baseX + cellDistX * x;
				float ry = baseY + cellDistY * y;
				renderlist.addLine(rx, ry, rx + cellDistX, ry, wallThickness, wallColorR, wallColorG, wallColorB, wallColorA);
			}

			if (!cell.leftOpen) {
				float rx = baseX + cellDistX * x;
				float ry = baseY + cellDistY * y;
				renderlist.addLine(rx, ry, rx, ry + cellDistY, wallThickness, wallColorR, wallColorG, wallColorB, wallColorA);
			}

			if (!cell.rightOpen) {
				float rx = baseX + cellDistX * x + cellDistX;
				float ry = baseY + cellDistY * y;
				renderlist.addLine(rx, ry, rx, ry + cellDistY, wallThickness, wallColorR, wallColorG, wallColorB, wallColorA);
			}

		}
	}
}

std::vector<std::vector<MazeCell>> MazeGenerator::getCells()
{
	return cells;
}

bool MazeGenerator::cellWasVisited(MazeCell& cell)
{
	return cell.bottomOpen || cell.topOpen || cell.leftOpen || cell.rightOpen;
}

std::vector<std::array<int, 2>> MazeGenerator::getPossibleNextCells(int x, int y)
{
	std::vector<std::array<int, 2>> possibleCells;

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (abs(dx) == abs(dy)) continue;
			if (!isInBounds(x + dx, y + dy)) continue;

			MazeCell& cell = cells[x + dx][y + dy];
			if (cellWasVisited(cell)) continue;

			possibleCells.push_back({ x + dx, y + dy });

		}
	}

	return possibleCells;
}

bool MazeGenerator::isInBounds(int x, int y)
{
	return !(x < 0 || y < 0 || x >= cells.size() || y >= cells[0].size());
}

void MazeGenerator::connectCells(std::array<int, 2> cell1, std::array<int, 2> cell2)
{
	MazeCell& cellRef1 = cells[cell1[0]][cell1[1]];
	MazeCell& cellRef2 = cells[cell2[0]][cell2[1]];

	// cell1 is above cell2
	if (cell1[1] > cell2[1]) {
		cellRef1.bottomOpen = true;
		cellRef2.topOpen = true;
	}

	// cell1 is below cell2
	if (cell1[1] < cell2[1]) {
		cellRef1.topOpen = true;
		cellRef2.bottomOpen = true;
	}

	// cell1 is left of cell2
	if (cell1[0] < cell2[0]) {
		cellRef1.rightOpen = true;
		cellRef2.leftOpen = true;
	}

	// cell1 is right of cell2
	if (cell1[0] > cell2[0]) {
		cellRef1.leftOpen = true;
		cellRef2.rightOpen = true;
	}

}
