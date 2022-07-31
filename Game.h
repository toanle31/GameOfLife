#pragma once
#include <unordered_set>
#include "MyTypes.h"

/*
 * Game of life class to store generation information.
 * Instead of a 2D array that can get way too large, this only stores relevant cells.
 * Cells that are considered relevant are those that either are alive or have living neighbors.
 * Cells that becomes both dead and has no living neighbors will be removed from next generation.
 */
class Game
{
public:
	const static Point NeighborCoords[8];
	std::unordered_set<Cell, HashFunction> OldGen;
	std::unordered_set<Cell, HashFunction> NewGen;

	/*
	 * Update count of living neighbors for each of c's neighbors.
	 * This should be called when a cell becomes alive
	 */
	void UpdateAliveNeighborCount(const Cell& c);

	/*
	 * Move the simulation one generation forward, applying rules to relevant cells.
	 */
	void Simulate();
};

