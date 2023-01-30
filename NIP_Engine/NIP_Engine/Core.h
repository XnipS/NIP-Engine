#pragma once
#include <signal.h>

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) ||  \
    defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32__) || defined(__NT__)
#define Q_DECL_EXPORT __declspec(dllexport)
#define Q_DECL_IMPORT __declspec(dllimport)
#else
#define Q_DECL_EXPORT __attribute__((visibility("default")))
#define Q_DECL_IMPORT __attribute__((visibility("default")))
#endif

#if defined(NIP_ENGINE_LIBRARY)
#define NIP_ENGINE_API Q_DECL_EXPORT
#else
#define NIP_ENGINE_API Q_DECL_IMPORT
#endif

#define BIT(x) (1 << x)

// TODO Define in compiler later
#define NE_ENABLE_ASSERTS

#ifdef NE_ENABLE_ASSERTS
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) ||  \
    defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32__) || defined(__NT__)
#define NE_ASSERT(x, ...)                             \
  {                                                   \
    if (!(x)) {                                       \
      NE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                 \
    }                                                 \
  }
#define NE_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!(x)) {                                            \
      NE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                      \
    }                                                      \
  }
#else
#define NE_ASSERT(x, ...)                             \
  {                                                   \
    if (!(x)) {                                       \
      NE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      raise(SIGTRAP);                                 \
    }                                                 \
  }
#define NE_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!(x)) {                                            \
      NE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      raise(SIGTRAP);                                      \
    }                                                      \
  }
#endif
#else
#define NE_ASSERT (x, ...)
#define NE_CORE_ASSERT (x, ...)
#endif