#pragma once

#if defined(_WIN32)      // Windows 32 or 64
    #if defined(_WIN64)  // Windows 64
        #define NEO_PLATFORM_WINDOWS
    #else  // Windows 32
        #error "Windows x86 is not supported yet !"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)  // Apple
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR == 1
        #error "Iphone Simulator is not supported yet !"
    #elif TARGET_OS_IPHONE == 1  // IOS
        #define NEO_PLATFORM_IOS
        #error "IOS is not supported yet !"
    #elif TARGET_OS_MAC == 1  // MacOS
        #define NEO_PLATFORM_MACOS
        #error "MACOS is not supported yet !"
    #else
        #error "Unknown Apple platform !"
    #endif
#elif defined(__ANDROID__)  // Android
    #define NEO_PLATFORM_ANDROID
    #error "Android is not supported yet !"
#elif defined(__linux__)  // Linux
    #define NEO_PLATFORM_LINUX
    #error "Linux is not supported yet !"
#else  // Unknown platform
    #error "Unknown platform !"
#endif
