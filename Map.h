#pragma once
#include <vector>
#include "Vec2.h"
#include "Tile.h"
#include "Difficulty.h"
class Map
{
	private:
		int height, width;
		std::vector<Tile> tiles;
		Vec2 stairsDownPos;
		int index(Vec2 pos) const;//返回数组下标
	public:
		Map(int h, int w);
		void fillmap();
		Vec2 getstair() const;
		int getheight() const;
		int getwidth() const;
		void setstairs(Vec2 setpos);
		Tile get(Vec2 pos) const;//得到某点属性
		void set(Vec2 pos, Tile t);//改变某点属性
		bool inBounds(Vec2 pos) const;//是否边界
		bool isWalkable(Vec2 pos) const;//是否可走
		void generate(int floor);
		Vec2 getRandomFloorPos() const;//获取一个随机的 Floor 坐标（用于玩家出生）
		Vec2 getRandomFloorPosExcluding(Vec2 center, int minDist) const;
		//获取一个随机的 Floor 坐标，但排除掉某个坐标周围 N 格（用于放楼梯，别刷在脸上）
};