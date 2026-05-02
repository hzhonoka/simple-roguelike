#include "Map.h"
#include <iostream>
#include <random>
#include <queue>
#include <tuple>
#include <stack>
#include <algorithm>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> breakDist(0, 100);
Map::Map(int h, int w)
{
	height = h, width = w;
	tiles.resize(height * width);
	stairsDownPos = { 0,0 };
	for (int i = 0 ;i < height * width ;i++)
	{
		tiles[i] = Tile::Wall;
	}
}
void Map::fillmap()
{
	for (int i = 0;i < height * width;i++)
	{
		tiles[i] = Tile::Wall;
	}
}
int Map::index(Vec2 pos) const
{
	return width * pos.y + pos.x;
}

Vec2 Map::getstair() const
{
	return stairsDownPos;
}
int Map::getheight() const 
{
	return height;
}

int Map::getwidth() const
{
	return width;
}

Tile Map::get(Vec2 pos) const
{
	return tiles[index(pos)];
}

void Map::set(Vec2 pos, Tile t)
{
	tiles[index(pos)] = t;
}

void Map::setstairs(Vec2 setpos)
{
	set(setpos, Tile::Stair);
	stairsDownPos = setpos;
}

bool Map::inBounds(Vec2 pos) const
{
	return (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height);
}

bool Map::isWalkable(Vec2 pos) const
{
	return inBounds(pos) && get(pos) != Tile::Wall;
}

Vec2 Map::getRandomFloorPos() const
{
	std::vector<Vec2> candidates;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (get({j,i})==Tile::Floor)
			{
				candidates.push_back({ j,i });
			}
		}
	}
	
	if (candidates.empty()) return { 1, 1 };

	std::uniform_int_distribution<int> dist(0, candidates.size() - 1);
	return candidates[dist(gen)];
}

Vec2 Map::getRandomFloorPosExcluding(Vec2 center, int minDist) const
{
	std::vector<Vec2> candidates;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (get({ j,i }) == Tile::Floor)
			{
				int manhattan = std::abs(j - center.x) + std::abs(i - center.y);
				if (manhattan<=minDist)
				{
					continue;
				}
				candidates.push_back({ j,i });
			}
		}
	}
	if (candidates.empty()) {
		return getRandomFloorPos();
	}
	std::uniform_int_distribution<int> dist(0, candidates.size() - 1);
	return candidates[dist(gen)];
}

void Map::generate()
{
	fillmap();
	struct Dir 
	{
		int dx, dy;
	};
	Dir dirs[4] = { {1,0},{-1,0},{0,-1},{0,1} };
	std::stack<Vec2> stk;
	stk.push({ 1,1 });
	while (!stk.empty())
	{
		Vec2 cur = stk.top();
		std::shuffle(std::begin(dirs), std::end(dirs), gen);
		bool found = false;
		for (Dir dir : dirs)
		{
			int nx = cur.x + 2 * dir.dx;
			int ny = cur.y + 2 * dir.dy;
			if (inBounds({ nx,ny }) && get({nx,ny}) == Tile::Wall)
			{
				set({ nx,ny }, Tile::Floor);
				set({ cur.x + dir.dx,cur.y + dir.dy }, Tile::Floor);
				found = true;
				stk.push({ nx,ny });
				break;
			}
		}
		if (!found)
		{
			stk.pop();
		}
	}
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (get({j,i})==Tile::Wall&& get({ j-1,i }) == Tile::Floor&& get({ j+1,i }) == Tile::Floor)
			{
				int num = breakDist(gen);
				if (num<=16)
				{
					set({ j,i }, Tile::Floor);
				}
			}
			else if (get({ j,i }) == Tile::Wall && get({ j,i + 1 }) == Tile::Floor && get({ j ,i - 1 }) == Tile::Floor)
			{
				int num = breakDist(gen);
				if (num <= 16)
				{
					set({ j,i }, Tile::Floor);
				}
			}
		}
	}
}