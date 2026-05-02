#include "player.h"
#include<algorithm>
#include<math.h>
Player::Player(Vec2 outpos, int outcurhp, int outmaxhp)
{
	pos = outpos, curhp = outcurhp, maxhp = outmaxhp;
	currentfloor = 0;
}

int Player::getcurhp() const 
{
	return curhp;
}

int Player::getmaxhp() const 
{
	return maxhp;
}

int Player::getcurrentfloor() const
{
	return currentfloor;
}

Vec2 Player::getpos() const
{
	return pos;
}

void Player::heal(int amount) 
{
	curhp = std::min(maxhp, curhp+amount);
}

void Player::takeDamage(int dmg)
{
	curhp = std::max(0, curhp - dmg);
}

void Player::setmaxhp(int change)
{
	//不会写了
}

void Player::setpos(Vec2 setting)
{
	pos.x = setting.x,pos.y = setting.y;
}

void Player::move(Vec2 delta)
{
	pos.x += delta.x, pos.y += delta.y;
}

void Player::godown()
{
	currentfloor += 1;
}


