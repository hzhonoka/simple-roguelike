# Simple Roguelike

大一五一假期 C++ 练手项目，终端 Roguelike 地牢生成器。

## 技术栈

- C++17
- 标准库：`std::vector`、`std::stack`、`std::mt19937`、`&lt;chrono&gt;`、`&lt;fstream&gt;`
- 终端渲染：ANSI 转义码（颜色 + 清屏），Windows API 兼容性处理
- 构建工具：Visual Studio 2022 / MSBuild

## 已实现

- [x] **DFS 回溯随机迷宫生成**：奇数网格 + 栈实现非递归 DFS，保证全图连通
- [x] **随机拆墙**：生成后遍历内部墙，15% 概率拆毁，制造环路和隐藏通道
- [x] **多层楼层系统**：`std::vector&lt;Map&gt;` 惰性生成，玩家可无限下楼，旧楼层持久化保留
- [x] **玩家状态封装**：`Player` 类管理坐标 / HP / 当前楼层，支持 `heal()` / `takeDamage()` / `move()`
- [x] **地图类封装**：`Map` 职责单一，仅管理 `tiles` 地形数组，提供 `isWalkable()` / `getRandomFloorPos()` 等服务接口
- [x] **ANSI 颜色渲染**：`Color` 模块封装转义码，`Tile` 绑定颜色，行缓冲输出优化（`std::string` 预分配）
- [x] **楼梯系统**：`Tile::StairsDown` 内置到地图，随机远离玩家出生点放置

## TODO

- [ ] 物品系统：红药水 `!`、金币等可拾取实体
- [ ] 怪物系统：史莱姆 `s` + 简单 AI（视野内追击玩家）
- [ ] 战斗系统：碰撞扣血 / 玩家攻击 / 死亡判定
- [ ] 存档读档：二进制序列化 `floors` + `player` 状态，启动时自动加载
- [ ] 战争迷雾 / 视口系统：仅渲染玩家周围区域
- [ ] 上楼通道 `Tile::StairsUp`

| 按键        | 功能            |
| :-------- | :------------ |
| `W/A/S/D` | 移动            |
| `E`       | 下楼（站在 `>` 上时） |
| `Q`       | 退出            |


## 编译运行

```bash
# Visual Studio
打开 gamedesign.sln → F5 运行

# 或命令行（需 MSVC 环境）
cl /std:c++17 /EHsc MainGame.cpp Map.cpp Player.cpp CreateLog.cpp
```

.
├── MainGame.cpp      # 游戏主循环
├── Map.h / Map.cpp   # 地图生成与查询
├── Player.h / Player.cpp  # 玩家状态
├── Vec2.h            # 坐标结构体
├── Tile.h            # 地形枚举 + 颜色绑定
├── Color.h           # ANSI 颜色工具
└── CreateLog.h/cpp   # 日志（预留存档接口）
