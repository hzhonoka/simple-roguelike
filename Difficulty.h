#pragma once
#include <algorithm>

inline int AddMapSize(int floor) 
{
    int add = floor/5;
    return std::min(add, 15);
}

inline int ReduceBreakChance(int floor) 
{
    int chance = 2 * ((floor+1) / 5);
    return std::min(chance, 40);
}

inline int SetMonsterCount(int floor) 
{
    return std::min(10, 1 + (floor+1) / 5);
}

inline int SetMonsterHP(int floor) 
{
    return 30 + floor * 3;
}

inline int SetMonsterDamage(int floor) 
{
    return 3 + floor / 2;
}