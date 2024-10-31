#pragma once
#include <compare>

struct Coord
{
    Coord(int x, int y)
        : x(x), y(y)
    {
    }
    int x;
    int y;
    auto operator<=>(const Coord& coord) const = default;
};
