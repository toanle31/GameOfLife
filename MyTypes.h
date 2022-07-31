#pragma once
#include <cstdint>

struct Point
{
    int64_t x;
    int64_t y;

    Point() { x = 0; y = 0; }
    Point(int64_t inX, int64_t inY) { x = inX, y = inY; }

    Point operator+(const Point& other) const
    {
        return Point(x + other.x, y + other.y);
    }

    Point& operator=(const Point& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
};

struct Cell
{
    Point Position;
    mutable bool IsAlive;
    mutable int8_t AliveNeighborCount;

    Cell() 
    { 
        Position.x = 0; 
        Position.y = 0; 
        IsAlive = false; 
        AliveNeighborCount = 0;
    }

    Cell(Point p)
    {
        Position.x = p.x;
        Position.y = p.y;
        IsAlive = false;
        AliveNeighborCount = 0;
    }
    // operator== used for unordered_set
    bool operator==(const Cell& other) const
    {
        return (Position.x == other.Position.x && 
            Position.y == other.Position.y);
    }
};

// Class for Hash function
class HashFunction 
{
public:
    size_t operator() (const Cell& c) const
    {
        return (c.Position.x + 10) * c.Position.y;
    }
};