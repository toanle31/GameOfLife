// Conway's Game Of Life implementation.

#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>

#define NUM_SIM_CYCLES 10

struct Cell
{
    int64_t x;
    int64_t y;
    bool IsAlive;
    int8_t AliveNeighborCount;

    Cell() { x = 0; y = 0; IsAlive = false; AliveNeighborCount = 0; }
};

void ParseLine(const std::string& Line, Cell* Cell);

int main()
{
    // Reading from stdin EOF character needs to be generated with CTRL+Z to break the while loop
    std::string Line;
    std::cout << "Paste in input then press Enter."
        << std::endl << "To run simulation press CTRL+Z then Enter: " << std::endl;
    while (std::getline(std::cin, Line))
    {
        Cell* ptr = new Cell();
        ptr->IsAlive = true;
        ParseLine(Line, ptr);
        // update neighbor's alive counts
    }

    // Simulate
    for (int i = 0; i < NUM_SIM_CYCLES; i++)
    {

    }

    // Output to stdout
    return 0;
}

/**
 * Parse input to get position of initial alive cells
 */
void ParseLine(const std::string& Line, Cell* InCell)
{
    std::istringstream iss(Line);
    char Delim;

    iss >> Delim >> InCell->x >> Delim >> InCell->y >> Delim;
}