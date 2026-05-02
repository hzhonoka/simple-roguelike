#include "CreateLog.h"
#include "Vec2.h"
#include "Map.h"
#include "player.h"
#include "color.h"
#include "EntityManager.h"
#include<iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <string>
void static printmap(const Map& themap,Player& player, const EntityManager& entityMgr)
{
    std::cout << "\033[2J\033[H";
    std::cout << "==========floor:" << player.getcurrentfloor() + 1 << "==========\n\n";
    for (int i = 0; i < themap.getheight(); i++) {
        std::string line;
        line.reserve(themap.getwidth() * 12);  // 预分配，避免频繁扩容

        for (int j = 0; j < themap.getwidth(); j++) {
            if (player.getpos().y == i && player.getpos().x == j) 
            {
                line += "\033[93m@\033[0m";
            }
            else if (auto e = entityMgr.GetEntityAt({ j, i }))
            {
                line += "\033[";
                line += std::to_string(static_cast<int>(e->color));
                line += "m";
                line += e->symbol;
                line += "\033[0m";
            }
            else 
            {
                Tile t = themap.get({ j, i });
                line += "\033[";
                line += std::to_string(static_cast<int>(getTileColor(t)));
                line += "m";
                line += static_cast<char>(t);
                line += "\033[0m";
            }
        }
        std::cout << line << '\n';
    }
    std::cout << "\nHP:" << player.getcurhp() << "/" << player.getmaxhp() << '\n';
}
int main()
{
    std::vector<Map> floors;
    EntityManager entityMgr;
    system("chcp 65001");
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif

    Log();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> mapsizeDist(7, 12);
    
    Player player({ 1,1 }, 100, 100);
    int h = mapsizeDist(gen) * 2 + 1;
    int w = mapsizeDist(gen) * 2 + 1;
    floors.emplace_back(h, w);
    floors[0].generate();
    player.setpos(floors[0].getRandomFloorPos());
    floors[0].setstairs(floors[0].getRandomFloorPosExcluding(player.getpos(), 8));
    entityMgr.SpawnPotion(floors[0], player.getpos(), floors[0].getstair());
    entityMgr.SpawnMonster(floors[0], player.getpos(), floors[0].getstair());
    printmap(floors[0], player, entityMgr);

    while (true) {
        if (_kbhit()) {           // 如果有按键按下
            char key = _getch();  // 读进来

            Vec2 next = player.getpos();   // 先复制当前位置
            if (key == 'w' || key == 'W') next.y -= 1;
            if (key == 's' || key == 'S') next.y += 1;
            if (key == 'a' || key == 'A') next.x -= 1;
            if (key == 'd' || key == 'D') next.x += 1;
            if (key == 'q' || key == 'Q') break;  // 退出
            entityMgr.ProcessPlayerAction(player, next, floors[player.getcurrentfloor()]);
            if (player.getpos().x == floors[player.getcurrentfloor()].getstair().x && player.getpos().y == floors[player.getcurrentfloor()].getstair().y)
            {
                if (key == 'e' || key == 'E')
                {
                    h = mapsizeDist(gen) * 2 + 1;
                    w = mapsizeDist(gen) * 2 + 1;
                    player.godown();
                    floors.emplace_back(h, w);
                    floors[player.getcurrentfloor()].generate();
                    player.setpos(floors[player.getcurrentfloor()].getRandomFloorPos());
                    floors[player.getcurrentfloor()].setstairs(floors[player.getcurrentfloor()].getRandomFloorPosExcluding(player.getpos(), 8));
                    entityMgr.clear();
                    entityMgr.SpawnPotion(floors[player.getcurrentfloor()], player.getpos(), floors[player.getcurrentfloor()].getstair());
                    entityMgr.SpawnMonster(floors[player.getcurrentfloor()], player.getpos(), floors[player.getcurrentfloor()].getstair());
                }
            }
            entityMgr.RemoveInactive();
            entityMgr.UpdateMonster(floors[player.getcurrentfloor()], player.getpos(), player);
            entityMgr.RemoveInactive();
            printmap(floors[player.getcurrentfloor()], player, entityMgr);
        }
    }
}