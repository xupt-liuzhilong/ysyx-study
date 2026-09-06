# Ex19 简单对象系统学习总结

- 所属阶段：一生一芯 E3-Linux → Learn C The Hard Way
- 学习与整理日期：2026-09-06
- 本轮完成：游戏主体、代码审计练习、4 项附加题
- 验证结果：拆分后原游戏 5 项测试全部 PASS；第二个游戏 `ex19_alt` 编译、移动和攻击正常。
- 保留问题：完整地图销毁尚未实现，已有 Valgrind 泄漏报告。
- 后续章节：**Ex20 尚未开始。**

## 一、这一章的核心结构

Ex18 把函数指针当作参数传递。Ex19 把函数指针存入结构体，让一个对象同时带有数据和行为。

~~~text
Object
  ├── description
  ├── init
  ├── describe
  ├── destroy
  ├── move
  └── attack
~~~

这是一套用 C 手工组织的简单对象系统，行为分发由结构体中的函数指针完成；对象创建、资源所有权和销毁也要由程序显式处理。

| 对象 | 保存的状态 | 主要行为 |
| --- | --- | --- |
| `Object` | 描述字符串和函数指针 | 提供默认接口 |
| `Monster` | `Object proto`、`hit_points` | 初始化血量、接受攻击 |
| `Room` | `Object proto`、怪物、四向房间指针 | 寻找下一房间、向怪物转发攻击 |
| `Map` | `Object proto`、`start`、`location` | 创建地图、维护当前位置、转发操作 |

## 二、预处理、头文件和两个关键宏

学习过程中先用 `cpp ex18.c | less` 观察预处理输出：头文件被展开，宏和条件编译指令在正式编译前得到处理。进入 `less` 后可搜索 `/bubble_sort`，按 `q` 退出。

### 1. 头文件保护

本次教材式写法：

~~~c
#ifndef _object_h
#define _object_h

/* declarations */

#endif
~~~

同一个编译单元反复包含该头文件时，保护宏让其主体只展开一次。**这不能解决两个不同 .c 文件各自定义同一个外部函数或全局变量的问题。** 后面遇到的 `multiple definition` 属于链接层面的重复定义。

### 2. NEW：选择类型大小和原型

~~~c
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
~~~

`##` 拼接预处理记号，因此：

~~~c
NEW(Map, "The Hall of the Minotaur.")
~~~

展开为：

~~~c
Object_new(sizeof(Map), MapProto, "The Hall of the Minotaur.")
~~~

`NEW` 是本章定义的宏；它最终仍然调用普通 C 函数。

### 3. 下划线宏：访问行为字段

~~~c
#define _(N) proto.N
~~~

于是：

~~~c
game->_(move)(game, NORTH);
~~~

展开为：

~~~c
game->proto.move(game, NORTH);
~~~

前面的 `game->proto.move` 选择函数指针，括号中的 `game` 是显式传入的当前对象地址。

## 三、Object 与 void *self

核心接口结构：

~~~c
typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
    char *description;

    int (*init)(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;
~~~

`void *self` 让这些接口能够接收不同的对象地址。进入具体函数后，再按实际对象类型使用：

~~~c
void Object_describe(void *self)
{
    Object *obj = self;
    printf("%s.\n", obj->description);
}
~~~

`void *` 不能直接访问 `description`，需要先转为知道成员布局的对象指针。这个转换不会检查运行时类型；调用者必须传入符合该实现预期的对象。

本章把 `Object proto` 放在具体结构体的第一个成员：

~~~c
struct Monster {
    Object proto;
    int hit_points;
};
~~~

这让对象起始处包含通用的 Object 部分。结构体起始地址与其首成员的关系是此布局的基础，并不意味着任意两个结构体指针都能互换使用。相关语言规则见 [C11 委员会草案 N1570 `6.7.2.1](https://open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)。

## 四、Object_new：创建对象的过程

原型示例：

~~~c
Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};
~~~

这里只指定怪物需要的行为；其余成员按初始化规则得到零值，`Object_new` 为缺少的行为补上默认函数。

创建过程：

~~~text
接收 size、proto、description
    ↓
为缺失的 init/describe/destroy/move/attack 补默认函数
    ↓
calloc(1, size) 分配具体对象需要的空间
    ↓
*el = proto 复制 Object 部分
    ↓
strdup(description) 复制描述字符串
    ↓
调用 el->init(el)
    ↓
成功返回对象；初始化失败则调用 destroy 并返回 NULL
~~~

需要记住三个细节：

1. `size` 来自 `sizeof(Map/Room/Monster)`，申请的是具体对象的大小。
2. `Object *el` 决定 `*el = proto` 只复制 Object 部分；后续成员由清零的存储和具体初始化函数建立。这不是深拷贝整张地图。
3. `strdup` 另行申请字符串存储，必须与对象本体分别释放。

默认 `Object_destroy` 的责任是：

~~~text
释放 obj->description
释放 obj 本体
~~~

它不会自动遍历 Map 中的 Room，也不会沿 Room 指针找到并销毁 Monster。`Object_new` 虽然在初始化失败时调用 `destroy`，能否清理部分构造的对象图，仍取决于具体销毁实现。

## 五、地图、移动和攻击

### 1. 原地图与扩展

原版创建 Hall、Throne、Arena、Kitchen，在 Arena 放置 Minotaur。附加题在 Kitchen 北侧增加 Cellar 和 Cave troll：

~~~text
                                      Cellar
                                        ↕
                                        │
Arena          ↔       Throne     ↔    Kitchen
                          ↕
                          │
                         Hall
~~~

图中竖直向上表示 north，向下表示 south。对应连接为：

~~~c
hall->north = throne;

throne->west = arena;
throne->east = kitchen;
throne->south = hall;

arena->east = throne;

kitchen->west = throne;
kitchen->north = cellar;

cellar->south = kitchen;
~~~

房间通过指针形成图；返回方向需要显式连接，不能认为设置 `a->north = b` 后就自动有 `b->south = a`。

Map 中：

~~~c
Room *start;
Room *location;
~~~

`start` 指向起点，`location` 指向当前位置。初始化时两者都指向 Hall；移动后只改变 `location`。它们可能指向同一个房间，不是两份独立分配的房间。

### 2. 移动链

~~~text
process_input
    → game->proto.move
    → Map_move
    → 当前 location->proto.move
    → Room_move
    → 返回 next
    → 成功时更新 map->location
~~~

`Room_move` 根据方向及出口是否存在返回目标房间；`Map_move` 根据返回值更新玩家位置。

### 3. WEST 分支漏赋值：本次实际修复的逻辑错误

当时输入 `w` 后出现“往西走”的提示，却没有房间描述，查看出口仍像停在 Throne。

排查依据：

~~~text
WEST 分支能够打印
    → direction == WEST && room->west 已成立
    → 西侧出口指针存在
    → 应继续检查 next 和 location
~~~

用户确认漏写：

~~~c
next = room->west;
~~~

修复后的分支：

~~~c
} else if (direction == WEST && room->west) {
    printf("You go west, into:\n");
    next = room->west;
}
~~~

漏写时，`next` 仍为 NULL，后续描述不会执行，Map 也不会更新位置。补齐后成功进入 Arena，并攻击 Minotaur。

经验：**分支条件成立、提示语打印、状态更新、返回值有效，是需要逐项检查的不同环节。**

### 4. 攻击链和返回值

~~~text
a
  → process_input
  → Map_attack
  → Room_attack
  → Monster_attack
  → hit_points -= damage
~~~

怪物初始 `hit_points = 10`，每次伤害 `rand() % 4` 为 0～3。前几次仍存活并不说明攻击失败；本次实际多次攻击后出现死亡提示。

当前版本中：

- `Monster_attack` 根据怪物是否死亡返回状态。
- `Room_attack` 有怪物时调用它，但没有用其返回值销毁怪物；该分支随后返回 1。
- `Map_attack` 再返回 Room 层结果。

因此不能把 Map 或 Room 层的 1 简单理解为“怪物已经死了”。当时没有改动死亡后的保留行为，`room->bad_guy` 仍指向怪物，尚未实现销毁并清空指针。

## 六、输入和审计

### 1. 命令与输入修正

| 输入 | 行为 |
| --- | --- |
| `n/s/e/w` | 四向移动 |
| `l` | 显示当前房间存在的出口 |
| `a` | 发起攻击 |
| 未识别字符，如 `x` | 进入 `default`，打印提示 |
| EOF | 结束输入循环 |

审计把原来的 `char ch = getchar();` 改为：

~~~c
int ch = getchar();

if (ch == EOF) {
    printf("Giving up? You suck.\n");
    return 0;
} else {
    getchar(); /* eat ENTER */
}
~~~

`getchar` 返回 `int`，需要同时表示正常字节和 EOF；应与 `EOF` 比较，不把 `-1` 硬编码成所有平台的 EOF 值。见 [N1570 `7.21.7.6 及输入函数约定](https://open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)。

终端空行按 Ctrl+D 通常会使下一次读取遇到 EOF；有未提交字符时，不应把 Ctrl+D 理解为必定立即退出。管道输入耗尽也会遇到 EOF。

当前第二个 `getchar()` 只吃掉一个字符，适合本次“单字符命令加换行”的用法；没有实现完整的任意长度输入行处理。

### 2. 本次审计覆盖的重点

| 位置 | 检查内容 |
| --- | --- |
| `Object_new` | `description`、`size`；`calloc` 和 `strdup` 结果；初始化返回值 |
| `Object_describe` | 对象和描述字符串 |
| `Object_init/move/attack` | 对象参数的有效性 |
| `Object_destroy` | 保留对 NULL 的容忍行为 |
| `Room_move` | 对象、方向、返回房间及其 describe 指针 |
| `Room_attack` | 对象、非负伤害、有怪物时的 attack 指针 |
| `Map_move/attack` | 当前位置、函数指针、方向或伤害参数 |
| `Map_init` | 每次 `NEW` 的结果，建立连接前先确认对象存在 |
| `process_input/main` | 游戏对象、当前位置、行为指针、EOF 与 default 路径 |

本次按照练习要求检查 `if/else` 和 `switch/default`，部分分支通过注释说明“维持原状态”。要学的是检查未处理路径，不是把“必须在所有工程中添加空 else”当作通用风格。

`assert` 检查成立条件，失败时暴露问题；它不会替代释放资源和返回错误。定义 `NDEBUG` 后断言可能不再执行，因此完整的分配失败处理不能只靠断言。相关规则见 [N1570 `7.2](https://open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)。

## 七、Valgrind：已定位但未修复的泄漏

这份报告来自**新增 Cellar 之前的四房间、一怪物版本**：

~~~text
HEAP SUMMARY:
    in use at exit: 608 bytes in 12 blocks
    total heap usage: 14 allocs, 2 frees, 2,656 bytes allocated

608 (64 direct, 544 indirect) bytes in 1 blocks are definitely lost

LEAK SUMMARY:
    definitely lost: 64 bytes in 1 blocks
    indirectly lost: 544 bytes in 11 blocks
    possibly lost: 0 bytes in 0 blocks
    still reachable: 0 bytes in 0 blocks
    suppressed: 0 bytes in 0 blocks

ERROR SUMMARY: 1 errors from 1 contexts
~~~

报告调用栈指向 `Object_new` 中的 `calloc`，由 `main` 创建 Map 的调用触发。

### 1. 为什么会直接和间接丢失

~~~text
Map
 ├── 描述字符串
 └── start/location
       ↓
      Room 图
       ├── 房间描述字符串
       └── Monster
             └── 怪物描述字符串
~~~

Map 未在退出前销毁，顶层引用消失后，其他对象也随之失去可达路径。`definitely lost` 是已经找不到有效指针链的块；`indirectly lost` 是只能通过其他已丢失块到达的块，见 [Valgrind Memcheck 泄漏分类](https://valgrind.org/docs/manual/mc-manual.html#mc-manual.leaks)。

### 2. 608 字节的核算

按当时对话中的 64 位布局与字符串，可以得到：

| 内容 | 大小 |
| --- | ---: |
| Map | 64 字节 |
| 4 个 Room | 4 × 88 = 352 字节 |
| 1 个 Monster | 56 字节 |
| 6 个描述字符串，含末尾零字节 | 26 + 15 + 16 + 29 + 32 + 18 = 136 字节 |
| 合计 | **608 字节** |

这解释了 Map 的 64 字节直接泄漏，以及其余 544 字节间接泄漏；大小依赖当时平台与具体字符串。报告中的 14 次分配、2 次释放是整次运行的总统计，不应把所有分配都说成来自自己的 `NEW`。

### 3. 目前的准确状态

- 完成了 Valgrind 运行、报告阅读与对象关系分析。
- **没有实现完整 `Map_destroy()`；没有最终版零泄漏证明。**
- 单独调用默认 `Object_destroy(game)` 只会清理 Map 的描述和本体，无法清掉整张地图。
- 房间连接是有回路的图，不能不加控制地沿四个方向递归释放；`start` 和 `location` 也可能是同一对象的别名。
- 扩展地图和 `ex19_alt` 的对象数与字符串不同，不能沿用 608 字节作为它们的检测结果。

后续可通过明确拥有的对象列表或带访问记录的遍历设计销毁流程，每个对象只释放一次；这只是后续方向，**不计入今天完成的实现**。

## 八、Makefile：从单个程序到两个程序

### 1. 初始版本使用隐式规则

~~~makefile
CFLAGS=-Wall -g

all: ex19

ex19: object.o

clean:
	rm -f ex19
~~~

`make object.o` 可以只构建对象系统的目标文件。Make 的隐式规则能从 `object.c` 编译 `object.o`；构建 `ex19` 时再链接对象系统。

~~~text
object.c → object.o
ex19.c + object.o → ex19
~~~

头文件提供类型和接口声明，`.c` 包含实现，`.o` 是编译产物，最终可执行文件由链接得到。

### 2. clean 与 test 的扩展

第一个附加题把清理范围增加到 `object.o`；后续再增加 `game.o` 和两个程序。第二个附加题加入：

~~~makefile
test: ex19
	./test.sh
~~~

本次这种 Makefile 的命令行以真实 Tab 开头。`test: ex19` 表示测试前先更新程序，`test.sh` 执行功能测试。

### 3. 当天双程序版本

~~~makefile
CFLAGS=-Wall -g

all: ex19 ex19_alt

ex19: ex19.o object.o game.o
	$(CC) $(CFLAGS) ex19.o object.o game.o -o ex19

ex19_alt: ex19_alt.o object.o game.o
	$(CC) $(CFLAGS) ex19_alt.o object.o game.o -o ex19_alt

test: ex19
	./test.sh

clean:
	rm -f ex19 ex19_alt *.o
~~~

截图确认 `make clean` 后重新 `make`，生成了 `ex19.o`、`ex19_alt.o`、`object.o`、`game.o`，并分别链接两个程序。

**整理补充，未计作已经修改：** 这版 Makefile 仍可补充 `.PHONY: all test clean` 和头文件依赖。否则仅修改 `.h` 时，Make 可能无法判断相关目标文件需要重编译；因此不能声称已具备完整依赖跟踪。原理见 [GNU Make 手册](https://www.gnu.org/software/make/manual/make.html) 和 [Phony Targets](https://www.gnu.org/s/make/manual/html_node/Phony-Targets.html)。

## 九、自动测试：五项 PASS 的含义

`test.sh` 使用的主要工具：

~~~sh
#!/bin/sh
set -e

output=$(printf "n\nw\na\n" | ./ex19)
echo "$output" | grep -q "The arena"
echo "$output" | grep -q "You attack The evil minotaur"
~~~

这是测试脚本中的一个片段。`printf` 通过标准输入模拟按键，`grep -q` 通过退出状态判断输出是否包含预期文字。本脚本用 `set -e` 让未处理的失败停止执行；它并不是所有 Shell 语境下的通用异常机制。

先为脚本增加执行权限，再运行：

~~~bash
chmod +x test.sh
make test
~~~

| 测试 | 输入序列 | 核心检查 |
| --- | --- | --- |
| TEST 1: movement | `n e w s`，每个命令一行 | Throne、Kitchen、Hall 描述 |
| TEST 2: list exits | `l n l` | NORTH、SOUTH、EAST、WEST 出口文字 |
| TEST 3: attack | `n w a` | 进入 Arena，触发 Minotaur 攻击 |
| TEST 4: invalid input | `x` | 出现 `What?:` |
| TEST 5: extra room and monster | `n e n a` | 进入 Cellar，触发 Cave troll 攻击 |

前四项通过后，新增房间时加入第五项。多文件拆分修复后再次运行，截图确认 5 项均 PASS，末尾为 `All tests passed.`。

验证范围需要保留：

- 这是基于输出文字的功能回归测试，覆盖了本次重要路径。
- 攻击测试没有断言一次攻击就死亡，避免依赖随机伤害。
- 输出中找到关键字，并不等于严格验证了每一步位置和所有边界情况。
- `make test` 当前只测试 `ex19`；`ex19_alt` 是通过交互截图验证。
- 这些测试没有替代 Valgrind，也没有覆盖完整内存销毁。

## 十、多文件拆分与链接错误

### 1. 最终职责划分

| 文件 | 职责 |
| --- | --- |
| `object.h` | Object、Direction、通用接口与宏 |
| `object.c` | 默认对象行为、创建和基础销毁 |
| `game.h` | Monster、Room 的结构与函数声明，原型变量的 extern 声明 |
| `game.c` | Monster、Room 行为及原型变量的唯一定义 |
| `ex19.h` | 城堡游戏自己的 Map 声明 |
| `ex19.c` | 城堡 Map、初始化、输入和 main |
| `ex19_alt.c` | 森林游戏自己的 Map、MapProto、初始化、输入和 main |
| `test.sh` | 原游戏的 5 项回归测试 |
| `Makefile` | 构建、测试和清理 |

`game.h` 中：

~~~c
extern Object MonsterProto;
extern Object RoomProto;
~~~

这两行声明变量由别处定义；`game.c` 中才放真正带初始化的定义：

~~~c
Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};
~~~

### 2. 本次实际遇到 multiple definition

链接器报告重复的符号包括：

~~~text
Monster_attack
Monster_init
MonsterProto
Room_move
Room_attack
RoomProto
~~~

原因：这些实现已经复制到 `game.c`，却仍保留在 `ex19.c`。两个编译单元一起链接时，同一外部符号有两份定义。

修复方式是移除 `ex19.c` 中的 6 份重复定义，让它只保留自己的 Map 和主程序相关内容，再重新构建并运行 `make test`。截图确认构建成功、5 项测试全部通过。

这一问题不能通过“再加一层头文件保护”解决，也不是修改函数调用的参数能解决的。编译每个 `.c` 与链接多个 `.o` 是不同阶段。

### 3. 两个游戏怎样共享同一模块

~~~text
object.c   → object.o ─┬→ ex19
                      └→ ex19_alt

game.c     → game.o   ─┬→ ex19
                      └→ ex19_alt

ex19.c     → ex19.o     → 仅参与 ex19 链接
ex19_alt.c → ex19_alt.o → 仅参与 ex19_alt 链接
~~~

`object.o` 和 `game.o` 同时用于两个链接命令。两个程序各有自己的 `MapProto` 和 `main`，因为它们被链接成不同可执行文件，所以不构成重复定义。

不能把 `ex19.o` 与 `ex19_alt.o` 一起链接进同一个程序，否则它们的 `main` 和其他同名实现会冲突。

## 十一、第二个游戏：森林、洞穴和塔

`ex19_alt.c` 包含 `game.h`，重新建立自己的 Map：

~~~text
Forest --north--> Cave --east--> Tower
       <--south--      <--west--
                  │              │
                Goblin         Dragon
~~~

对象使用已有 `NEW(Room, ...)` 和 `NEW(Monster, ...)`，没有重新实现 Room 和 Monster。

截图中的交互为：

~~~text
l → NORTH
n → A dark cave.
a → You attack The ugly goblin!
e → An abandoned tower.
a → You attack The ancient dragon!
~~~

因此最后一个附加题的核心已经实现：**不同地图和入口，共用已编译的对象系统与游戏逻辑。** 截图中的 Goblin、Dragon 攻击后仍存活，这符合随机伤害设计；不把该截图描述为已经打死两只怪物。

## 十二、四项附加题与后续边界

| 附加题 | 本次完成结果 |
| --- | --- |
| clean 清理 object.o | 完成，后续扩展为清理两个程序及本目录目标文件 |
| 编写测试脚本并支持 make test | 完成，先 4 项，再扩展为 5 项 |
| 增加房间和怪物 | 完成，Cellar 与 Cave troll 已加入并测试 |
| 拆出 .o 并复用到另一游戏 | 完成，拆分后回归通过，森林游戏运行正常 |

仍待后续完善的项目：

- Map/Room/Monster 的完整所有权与销毁流程，以及最终 Valgrind 复测。
- 部分创建失败后的清理；`Object_new` 的大小约束不能只停留在 `size > 0`。
- 怪物死亡后的销毁与 `bad_guy` 清空。
- 更完整的输入行处理。
- Makefile 的头文件依赖与伪目标声明。
- 对第二个游戏补充自动测试。

这些是保留问题，不影响如实记录本轮练习已经完成，也不应被写成已经修好。**Ex20 尚未开始**：原对话虽给出过引入内容和 `dbg.h` 建议，但随后决定先整理今天的日志与两章总结，没有已执行 Ex20 实验的记录。

## 复习自检

- 能否把 `NEW(Map, ...)` 和 `game->_(move)(game, NORTH)` 手工展开？
- 能否解释 `Object proto` 为什么放在首成员，以及 `void *self` 的使用前提？
- 能否说明 `Room_move` 和 `Map_move` 分别改变什么？
- 能否沿调用链解释“打印往西却没移动”的原因？
- 能否区分函数声明、外部变量声明、真正定义以及链接阶段？
- 能否解释为什么两个程序可以分别有自己的 MapProto 和 main？
- 能否说明 5 项功能测试 PASS 与 608 字节泄漏为何可以同时存在？
- 能否指出默认 `Object_destroy` 为什么不能销毁整张地图？

