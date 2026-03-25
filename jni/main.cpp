#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include "hooks.h"

#define LOG_TAG "GTASA_UTF8"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// 获取模块基址的辅助函数
uintptr_t get_module_base(const char* module_name) {
    uintptr_t addr = 0;
    char line[1024];
    FILE* fp = fopen("/proc/self/maps", "rt");
    if (fp != nullptr) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                addr = strtoul(line, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("--- 汉化补丁注入中 ---");

    // 1. 获取游戏主库基址
    uintptr_t base = get_module_base("libGTASA.so");
    
    if (base == 0) {
        LOGI("错误: 未能找到 libGTASA.so 基址");
        return JNI_VERSION_1_6;
    }

    // 2. 执行 Hook 挂载
    InstallHooks(base);

    LOGI("--- 注入完成，等待游戏调用 ---");
    return JNI_VERSION_1_6;
}
