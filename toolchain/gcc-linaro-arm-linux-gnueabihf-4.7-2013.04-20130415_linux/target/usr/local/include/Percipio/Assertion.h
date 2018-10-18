#ifndef Foundation_Assertion_INCLUDED
#define Foundation_Assertion_INCLUDED


#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL    ASSERT_LEVEL_RELEASE
#endif

#define ASSERT_LEVEL_DEBUG      0
#define ASSERT_LEVEL_RELEASE    1
#define ASSERT_LEVEL_NO_ASSERT  2
#define ASSERT_LEVEL_TEMP       3
#define ASSERT_LEVEL_NEVER      4

#define ASSERT_BASE(cond) \
            do{ \
                if(!(cond)) { \
                    ABORT_FMT("Assertion failed at %s:%d\n", __FILE__, __LINE__); \
                } \
            }while(0)


#define ASSERT_FMT_BASE(cond, fmt,...) \
            do{ \
                if(!(cond)) { \
                    LOGPRAW("Assertion failed at %s:%d\n", __FILE__, __LINE__); \
					LOGPRAW(fmt, ##__VA_ARGS__); \
                    ABORT(); \
                } \
            }while(0)

#if ASSERT_LEVEL <= ASSERT_LEVEL_DEBUG
#   define ASSERT_D(cond)               ASSERT_BASE(cond)
#   define ASSERT_FMT_D(cond, fmt,...)   ASSERT_FMT_BASE(cond, fmt, ##__VA_ARGS__)
#else
#   define ASSERT_D(cond)
#   define ASSERT_FMT_D(cond, fmt,...)
#endif

#if ASSERT_LEVEL <= ASSERT_LEVEL_RELEASE
#   define ASSERT_R(cond)               ASSERT_BASE(cond)
#   define ASSERT_FMT_R(cond, fmt,...)   ASSERT_FMT_BASE(cond, fmt, ##__VA_ARGS__)
#else
#   define ASSERT_R(cond)
#   define ASSERT_FMT_R(cond, fmt,...)
#endif

#if ASSERT_LEVEL <= ASSERT_LEVEL_TEMP
#   define ASSERT_T(cond)               ASSERT_BASE(cond)
#   define ASSERT_FMT_T(cond, fmt,...)   ASSERT_FMT_BASE(cond, fmt, ##__VA_ARGS__)
#else
#   define ASSERT_T(cond)
#   define ASSERT_FMT_T(cond, fmt,...)
#endif

#define _ASSERTD        ASSERT_T
#define _ASSERTR        ASSERT_T
#define _ASSERTFMTD     ASSERT_FMT_T
#define _ASSERTFMTR     ASSERT_FMT_T

#define xASSERT_D(...)
#define xASSERT_R(...)
#define xASSERT_FMT_D(...)
#define xASSERT_FMT_R(...)

// defined killed style
#define KILL_SEGV()     (*(int*)0 = 0)
#define ABORT()         KILL_SEGV()

#define ABORT_FMT(fmt, ...) \
    do{ \
        LOGPRAW("Abort at %s:%d. " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
        ABORT(); \
    }while(0)


#endif
