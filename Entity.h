#pragma once
#include "Vec2.h"
#include "color.h"
enum class EntityType{Monster,Potion};
struct Entity 
{
	Vec2 pos;
	char symbol;
	Color color;
	EntityType entitytype;
	int hp;
	bool active;
};