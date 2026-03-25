#include "hooks.h"
#include "injector.hpp"
#include <android/log.h>

// 假设使用 Substrate 或类似的 Hook 接口
extern "C" void MSHookFunction(void *symbol, void *replace, void **result);

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "GTASA_32_UTF8", __VA_ARGS__)

// v2.00 ARMv7 (32位) 偏移
#define OFF_CFONT_PRINTSTRING 0x534064

void (*orig_CFont_PrintString)(float x, float y, const char* text) = nullptr;

void my_CFont_PrintString(float x, float y, const char* text) {
    if (text && (unsigned char)text[0] > 0x7F) {
        // 检测到 UTF8/多字节字符
        LOGI("捕获文本: %s", text);
        // 这里后续接入系统字体渲染逻辑
    }
    orig_CFont_PrintString(x, y, text);
}

void InstallHooks(uintptr_t baseAddr) {
    LOGI("检测到 ARMv7 环境，开始挂载 v2.00 补丁...");

    void* target = (void*)(baseAddr + OFF_CFONT_PRINTSTRING);
    
    // 注意：32位 Hook 需要处理 Thumb 模式地址 (地址 + 1)
    // 但 MSHook 通常会自动处理。如果是手动汇编 Hook 则需注意。
    MSHookFunction(target, (void*)my_CFont_PrintString, (void**)&orig_CFont_PrintString);
    
    LOGI("Hook 成功安装于: %p", target);
}
