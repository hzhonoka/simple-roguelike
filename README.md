# Simple Roguelike

大一五一假期 C++ 练手项目，终端 Roguelike 地牢生成器。QAQ

## 技术栈

- C++17
- 标准库：`std::vector`、`std::stack`、`std::mt19937`、`&lt;chrono&gt;`、`&lt;fstream&gt;`
- 终端渲染：ANSI 转义码（颜色 + 清屏），Windows API 兼容性处理
- 构建工具：Visual Studio 2022 / MSBuild

## 已实现

- [x] **DFS 回溯随机迷宫生成**：奇数网格 + 栈实现非递归 DFS，保证全图连通
- [x] **随机拆墙**：生成后遍历内部墙，动态概率拆毁，制造环路和隐藏通道
- [x] **难度曲线**：`Difficulty.h` 控制地图尺寸 / 拆墙率 / 怪物数量 / 怪物属性随楼层递增
- [x] **多层楼层系统**：`std::vector&lt;Map&gt;` 惰性生成，玩家可无限下楼，旧楼层持久化保留
- [x] **玩家状态封装**：`Player` 类管理坐标 / HP / 当前楼层，支持 `heal()` / `takeDamage()`
- [x] **实体系统**：`EntityManager` 统一管理怪物 / 药水，支持生成 / 查询 / 尸体清理
- [x] **怪物 AI**：视野内追击玩家，贴脸咬人，被阻挡时随机方向绕路
- [x] **战斗系统**：碰撞互殴（玩家扣血 + 怪物扣血），原地对砍不移动
- [x] **物品系统**：红药水 `!`，踩上回血 +20 并消失
- [x] **死亡重开**：HP ≤ 0 显示 `YOU DIED`，按 `R` 重置世界，按 `Q` 退出
- [x] **ANSI 颜色渲染**：`Color` 模块封装转义码，`Tile` / `Entity` 绑定颜色，行缓冲输出优化

## TODO

- [ ] 装备 / 武器系统：攻击力成长，暴击率
- [ ] 原地攻击键 `J`：不移动直接砍周围怪物
- [ ] 存档读档：二进制序列化 `floors` + `player` 状态，启动时自动加载
- [ ] 战争迷雾 / 视口系统：仅渲染玩家周围区域
- [ ] 上楼通道 `Tile::StairsUp`：可以回上层
- [ ] 更多怪物种类：骷髅、Boss 等

## 操作说明

| 按键 | 功能 |
|:---|:---|
| `W/A/S/D` | 移动 / 撞向怪物对砍 |
| `E` | 下楼（站在 `&gt;` 上时） |
| `R` | 死亡后重新开始 |
| `Q` | 退出游戏 |

## 编译运行

```bash
# Visual Studio
打开 gamedesign.sln → F5 运行

# 或命令行（需 MSVC 环境）
cl /std:c++17 /EHsc MainGame.cpp Map.cpp Player.cpp EntityManager.cpp CreateLog.cpp
```

## 项目结构

```
.
├── MainGame.cpp              # 游戏主循环（输入 → 战斗 → 怪物回合 → 渲染）
├── Map.h / Map.cpp           # 地图生成（DFS + 拆墙）与地形查询
├── Player.h / Player.cpp     # 玩家状态（HP / 坐标 / 楼层）
├── Entity.h                  # 实体原子（怪物 / 药水）
├── EntityManager.h / .cpp    # 实体管家（生成 / AI / 碰撞 / 尸体清理）
├── Difficulty.h              # 难度曲线（楼层 → 地图尺寸 / 怪物强度）
├── Vec2.h                    # 坐标结构体
├── Tile.h                    # 地形枚举 + 颜色绑定
├── Color.h                   # ANSI 颜色工具
└── CreateLog.h / .cpp        # 日志（预留存档接口）
```