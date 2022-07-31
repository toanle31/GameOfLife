// Conway's Game Of Life implementation.

#include <iostream>
#include <string>

#include <sstream>
#include <unordered_set>
#include "Game.h"
#include "MyTypes.h"

#define NUM_SIM_CYCLES 10

Point ParseLine(const std::string& Line);

int main()
{
    // Reading from stdin, EOF character needs to be generated with CTRL+Z to break the while loop
    std::string Line;
    std::cout << "Paste in input then press Enter." << std::endl 
              << "To run simulation press CTRL+Z then Enter: " << std::endl;
    Game Game;

    // Gets location of seed cells from stdin, and add it to cells we're tracking
    // If it's already being tracked (i.e having living neighbors) set IsAlive to true
    // and update its neighbors count of living cells
    while (std::getline(std::cin, Line))
    {
        Point p = ParseLine(Line);

        Cell NewCell(p);
        NewCell.IsAlive = true;

        std::unordered_set<Cell>::iterator it = Game.NewGen.find(NewCell);
        if (it != Game.NewGen.end())
        {
            (*it).IsAlive = true;
            Game.UpdateAliveNeighborCount((*it));
        }
        else
        {
            Game.NewGen.insert(NewCell);
            Game.UpdateAliveNeighborCount(NewCell);
        }
    }

    // Simulate
    for (int i = 0; i < NUM_SIM_CYCLES; i++)
    {
        Game.Simulate();
    }

    // Output to stdout
    std::cout << "Location of living cells after  " << 
             NUM_SIM_CYCLES << " generation: " << std::endl;
    std::cout << "#Life 1.06" << std::endl;
    for (auto& CurrentCell : Game.NewGen)
    {
        if (CurrentCell.IsAlive)
        {
            std::cout << CurrentCell.Position.x << " " << CurrentCell.Position.y << std::endl;
        }
    }
    return 0;
}

/**
 * Parse input to get position of initial alive cells.
 * Assumes input to always be (x,y).
 */
Point ParseLine(const std::string& Line)
{
    // TODO: error checking for invalid input
    Point p;
    std::istringstream iss(Line);
    char Delim;

    iss >> Delim >> p.x >> Delim >> p.y >> Delim;

    return p;
}