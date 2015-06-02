#ifndef __PLATFORMSCONFIG_H__
#define __PLATFORMSCONFIG_H__

#define CC_PLATFORM_UNKNOWN			   0
#define CA_PLATFORM_IOS                1
#define CA_PLATFORM_ANDROID            2
#define CA_PLATFORM_WIN32              3
#define CA_PLATFORM_MARMALADE          4
#define CA_PLATFORM_LINUX              5
#define CA_PLATFORM_BADA               6
#define CA_PLATFORM_BLACKBERRY         7
#define CA_PLATFORM_MAC                8
#define CA_PLATFORM_NACL               9
#define CA_PLATFORM_EMSCRIPTEN        10
#define CA_PLATFORM_TIZEN             11
#define CA_PLATFORM_QT5               12
#define CA_PLATFORM_WP8               13
#define CA_PLATFORM_WINRT             14


// Determine target platform by compile environment macro.
#define CC_TARGET_PLATFORM             CC_PLATFORM_UNKNOWN

// mac
#if defined(CC_TARGET_OS_MAC) || defined(__APPLE__)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_MAC
#endif

// iphone
#if defined(CC_TARGET_OS_IPHONE)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_ANDROID
#endif

// win32
#if defined(_WIN32) && defined(_WINDOWS)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_LINUX
#endif

// marmalade
#if defined(MARMALADE)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM         CC_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM     CC_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM     CC_PLATFORM_NACL
#endif

// Emscripten
#if defined(EMSCRIPTEN)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM     CC_PLATFORM_EMSCRIPTEN
#endif

// tizen
#if defined(TIZEN)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM     CC_PLATFORM_TIZEN
#endif

// qt5
#if defined(CC_TARGET_QT5)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM     CC_PLATFORM_QT5
#endif

// WinRT (Windows Store App)
#if defined(WINRT)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM			CC_PLATFORM_WINRT
#endif

// WP8 (Windows Phone 8 App)
#if defined(WP8)
#undef  CC_TARGET_PLATFORM
#define CC_TARGET_PLATFORM			CC_PLATFORM_WP8
#endif


//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#ifndef CC_TARGET_PLATFORM)
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef __MINGW32__
#pragma warning (disable:4127) 
#pragma warning (disable:4996) 
#endif 
#endif  // CC_PLATFORM_WIN32


#endif