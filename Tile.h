#pragma once
#include "color.h"
enum class Tile : char {Wall = '#', Floor = '.', Stair = '>',Potion = '!' };

inline Color getTileColor(Tile t) {
    switch (t) {
    case Tile::Wall:       return Color::White;
    case Tile::Floor:      return Color::Gray;
    case Tile::Stair:      return Color::Blue;
    case Tile::Potion:     return Color::Red;
    default:               return Color::Reset;
    }
}