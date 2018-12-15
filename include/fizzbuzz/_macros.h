#ifndef FZ_MACROS
#define FZ_MACROS

#if defined(_MSC_VER) && defined(FZ_SHARED)

#if defined(FZ_IMPLEMENTATION)
#define FZ_EXPORT __declspec(dllexport)
#else
#define FZ_EXPORT __declspec(dllimport)
#endif

#else
#define FZ_EXPORT
#endif

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(__cplusplus)
#define FZ_BEGIN_HEADER extern "C" {
#define FZ_END_HEADER }
#else
#define FZ_BEGIN_HEADER
#define FZ_END_HEADER
#endif

#endif /* FZ_MACROS */
