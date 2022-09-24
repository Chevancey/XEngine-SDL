#ifdef LIB_COMPILING
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif