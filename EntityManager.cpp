#include "EntityManager.h"
#include <algorithm>
#include "player.h"

EntityManager::EntityManager() : rng(std::random_device{}()) {}

Entity* EntityManager::GetEntityAt(Vec2 targetpos)
{
	for (Entity& single : entities)
	{
		if (single.pos.x == targetpos.x && single.pos.y == targetpos.y && single.active == true)
		{
			return &single;
		}
	}
	return nullptr;
}

const Entity* EntityManager::GetEntityAt(Vec2 targetpos) const
{
	for (const Entity& single : entities)
	{
		if (single.pos.x == targetpos.x && single.pos.y == targetpos.y && single.active==true)
		{
			return &single;
		}
	}
	return nullptr;
}

bool EntityManager::HasEntityAt(Vec2 targetpos) const
{
	return GetEntityAt(targetpos) != nullptr;
}

int EntityManager::GetMonsterCount() const
{
	int count = 0;
	for (const auto& single : entities)
	{
		if (single.entitytype==EntityType::Monster&&single.active==true)
		{
			count += 1;
		}
	}
	return count;
}
Vec2 EntityManager::FindValidPos(const Map& map, Vec2 ExcludeStair,Player& player) const
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		Vec2 PossibleChoice = map.getRandomFloorPosExcluding(player.getpos(),6);
		if (!((PossibleChoice.x == player.getpos().x && PossibleChoice.y == player.getpos().y) ||
			(PossibleChoice.x == ExcludeStair.x && PossibleChoice.y == ExcludeStair.y))
			&&!HasEntityAt(PossibleChoice))
		{
			return PossibleChoice;
		}
	}
	return { 1,1 };//
}

void EntityManager::SpawnPotion(const Map& map, Vec2 stairpos,Player& player)
{
	Vec2 TempPos = FindValidPos(map,stairpos,player);
	entities.push_back({ TempPos,'!',Color::Red,EntityType::Potion,0,true });
}

void EntityManager::SpawnMonster(const Map& map, Vec2 stairpos, Player& player)
{
	int count = SetMonsterCount(player.getcurrentfloor());
	while (count != 0)
	{
		count--;
		Vec2 playerpos = player.getpos();
		Vec2 TempPos = FindValidPos(map, stairpos,player);
		entities.push_back({ TempPos,'S',Color::Green,EntityType::Monster,SetMonsterHP(player.getcurrentfloor()),true});
	}
}

void EntityManager::UpdateMonster(const Map& map, Vec2 playerpos, Player& player)
{
	for (auto& single : entities)
	{
		if (single.entitytype != EntityType::Monster) continue;
		

		int dx = playerpos.x - single.pos.x;
		int dy = playerpos.y - single.pos.y;
		int dist = std::abs(dx) + std::abs(dy);

		if (dist > 10 || dist <= 1) continue; 

		int stepX = 0, stepY = 0;
		if (dx != 0) stepX = (dx > 0) ? 1 : -1;      
		else if (dy != 0) stepY = (dy > 0) ? 1 : -1;

		Vec2 next = { single.pos.x + stepX, single.pos.y + stepY };

		bool blocked = !map.isWalkable(next);
		if ((next.x == playerpos.x && next.y == playerpos.y)||HasEntityAt(next)) blocked = true;

		if (!blocked) {
			single.pos = next;
		}
		else
		{
			Vec2 fourdir[4] = { {1,0},{0,-1},{-1,0},{0,1} };
			std::shuffle(std::begin(fourdir), std::end(fourdir), rng);
			for (int j = 0; j < 4; j++)
			{
				next = { single.pos.x + fourdir[j].x, single.pos.y + fourdir[j].y };
				if ((!(next.x == playerpos.x && next.y == playerpos.y)) && !HasEntityAt(next) && map.isWalkable(next))
				{
					single.pos = next;
					break;
				}
			}
		}
	}
}

void EntityManager::ProcessPlayerAction(Player& player, Vec2 nextPos, const Map& map) {
	auto e = GetEntityAt(nextPos);

	if (e && e->entitytype == EntityType::Monster) {
		player.takeDamage(SetMonsterDamage(player.getcurrentfloor()));
		e->hp -= 20;
		if (e->hp <= 0) e->active = false;
	}
	else if (e && e->entitytype == EntityType::Potion) {
		player.heal(20);
		e->active = false;
		player.setpos(nextPos);
	}
	else if (map.isWalkable(nextPos)) {
		player.setpos(nextPos);
	}
}

void EntityManager::RemoveInactive() {
	for (int i = entities.size() - 1; i >= 0; i--) {
		if (!entities[i].active) {
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityManager::clear() {
	entities.clear();
}