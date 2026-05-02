#pragma once
#include "Vec2.h"
class Player
{
	private:
		Vec2 pos;
		int curhp,maxhp;
		int currentfloor;
	public:
		Player(Vec2 outpos, int outcurhp, int outmaxhp);
		Vec2 getpos() const;
		int getcurhp() const;
		int getcurrentfloor() const;
		int getmaxhp() const;
		void heal(int amount);    // 加血，不超过maxHp
		void takeDamage(int dmg);
		void setmaxhp(int change);
		void setpos(Vec2 setting);
		void move(Vec2 delta);
		void godown();
};