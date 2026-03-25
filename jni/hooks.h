#ifndef HOOKS_H
#define HOOKS_H

#include <cstdint>

// 模拟游戏内部的字体渲染参数结构（如果需要更精准的控制）
struct CFont {
    static void PrintString(float x, float y, const char* text);
    // 可以在这里添加更多游戏内函数定义
};

// 初始化 Hook 的入口
void InstallHooks(uintptr_t baseAddr);

#endif
