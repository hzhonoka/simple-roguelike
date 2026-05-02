#pragma once
#include <vector>
#include "Entity.h"
#include "Map.h"
#include "player.h"
#include <random>

class EntityManager
{
	private:
		std::vector<Entity> entities;
		Vec2 FindValidPos(const Map& map, Vec2 ExcludePlayer, Vec2 ExcludeStair) const;
		std::mt19937 rng;

	public:
		EntityManager();
		void SpawnPotion(const Map& map, Vec2 playerpos, Vec2 stairpos);
		void SpawnMonster(const Map& map, Vec2 playerpos, Vec2 stairpos);
		Entity* GetEntityAt(Vec2 targetpos);
		const Entity* GetEntityAt(Vec2 targetpos) const;//
		bool HasEntityAt(Vec2 targetpos) const;

		void UpdateMonster(const Map& map, Vec2 playerpos, Player& player);
		void ProcessPlayerAction(Player& player, Vec2 nextPos, const Map& map);
		void RemoveInactive();

		void clear();
};