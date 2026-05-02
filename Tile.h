#pragma once
#include "color.h"
enum class Tile : char {Wall = '#', Floor = '.', stair = '>',potion = '!' };

inline Color getTileColor(Tile t) {
    switch (t) {
    case Tile::Wall:       return Color::White;
    case Tile::Floor:      return Color::Gray;
    case Tile::stair:      return Color::Blue;
    case Tile::potion:     return Color::Red;
    default:               return Color::Reset;
    }
}