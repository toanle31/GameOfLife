#include "Game.h"

const Point Game::NeighborCoords[] = {	Point(-1, -1), Point(0, -1), Point(1, -1), 
										Point(-1, 0),				 Point(1, 0),
										Point(-1, 1),  Point(0, 1),  Point(1, 1)};

void Game::UpdateAliveNeighborCount(const Cell& c)
{
	// Update each of c's neighbor's AliveNeighborCount,
	// If the neighbor's not already being tracked, add it to set for tracking.
	for (int i = 0; i < 8; i++)
	{
		// check if neighbor cell is out of bounds
		if ((c.Position.x == INT64_MAX && NeighborCoords[i].x > 0) || 
			(c.Position.x == INT64_MIN && NeighborCoords[i].x < 0)) continue;
		if ((c.Position.y == INT64_MAX && NeighborCoords[i].y > 0) ||
			(c.Position.y == INT64_MIN && NeighborCoords[i].y < 0)) continue;

		Point p = c.Position + NeighborCoords[i];
		Cell NeighborCell(p);
		std::unordered_set<Cell>::iterator it = NewGen.find(NeighborCell);
		int tmp = 0;
		if (it != NewGen.end())					 // neighbor cell already being tracked
		{
			(*it).AliveNeighborCount++;
		}
		else                                    // neighbor cell not being tracked
		{
			NeighborCell.AliveNeighborCount = 1;
			NewGen.insert(NeighborCell);
		}
	}
}

void Game::Simulate()
{
	OldGen.clear();
	OldGen = NewGen;
	NewGen.clear();

	// Iteratate through all relevant cells in previous generation and apply rules
	// A cell will be added to NewGen if it was dead and becomes alive or stays alive
	for (auto& CurrentCell : OldGen)
	{
		std::unordered_set<Cell>::iterator it = NewGen.find(CurrentCell);

		// if cell is alive and has 2-3 living neighbors, it lives to next gen
		// if cell is dead and has 3 living neighbors, it becomes alive in the next gen
		bool cond1 = CurrentCell.IsAlive && CurrentCell.AliveNeighborCount < 4 && CurrentCell.AliveNeighborCount > 1;
		bool cond2 = !CurrentCell.IsAlive && CurrentCell.AliveNeighborCount == 3;

		// In both cases:
		// If cell is already being tracked, set IsAlive to true and call UpdateAliveNeighborCount
		// If not then add it and call UpdateAliveNeighborCount.
		if (cond1 || cond2)
		{
			if (it != NewGen.end())
			{
				(*it).IsAlive = true;
				UpdateAliveNeighborCount((*it));
			}
			else
			{
				Cell NewCell(CurrentCell.Position);
				NewCell.IsAlive = true;
				NewGen.insert(NewCell);
				UpdateAliveNeighborCount(NewCell);
			}
		}
	}
}