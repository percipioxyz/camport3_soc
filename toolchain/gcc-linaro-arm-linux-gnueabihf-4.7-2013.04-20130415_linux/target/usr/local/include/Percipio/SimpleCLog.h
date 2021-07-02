///#ifndef __ANDROID__

#ifndef Foundation_SimpleCLog_INCLUDED
#define Foundation_SimpleCLog_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>

#if defined (ANDROID_NDK)
    #include <android/log.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int  SCL_SetLogFile(FILE* file);
int  SCL_SetLogFileByName(const char* file);
int  SCL_SetLogFileByFd(const int fd);
void SCL_SetFileSizeLimit(unsigned int size);
void SCL_CloseLogFile();

int  SCL_SetGlobalLogPrefix(const char* format);
    /// Set log prefix for global log
    ///
    ///   * %d - zero-padded day of month (01 .. 31)
    ///   * %f - space-padded day of month ( 1 .. 31)
    ///   * %m - zero-padded month (01 .. 12)
    ///   * %o - space-padded month ( 1 .. 12)
    ///   * %Y - year with century (1970)
    ///   * %H - hour (00 .. 23)
    ///   * %M - minute (00 .. 59)
    ///   * %S - second (00 .. 59)
    ///   * %i - millisecond (000 .. 999)
    ///   * %% - percent sign

void SCL_ClearGlobalLogPrefix();

int  SCL_LogPrint_(int level, const char *fmt, ...);
    /// Send format string to log, like printf().

int  SCL_LogVprint_(int level, const char *fmt, va_list ap);
    /// Send format string to log, like vprintf().

void SCL_SetLogLevel(int level);

#ifdef __cplusplus
}
#endif

#define LOGRAW(level, fmt, ...)       SCL_LogPrint_(level, fmt, ##__VA_ARGS__)
#define VLOGRAW(level, fmt, ap)       SCL_LogVprint_(level, fmt, ap)


/// Log prefix can be defined in each file or each module.
/// Only work in printf() like logs.
/// If you want to know where the log printed, you can define as follows:
///     #define XYZ_LOG_PREFIX         "<%s>"
///     #define XYZ_LOG_PREFIX_ARG     __FUNCTION__
/// Or you wanna which thread print this, you should define:
///     #define XYZ_LOG_PREFIX         "<0x%x>"
///     #define XYZ_LOG_PREFIX_ARG     (uint32_t)pthread_self()
///
/// For example:
///     #define XYZ_LOG_PREFIX      "<%s> "
///     #define XYZ_LOG_PREFIX_ARG  __FUNCTION__
#ifndef XYZ_LOG_PREFIX
#   define XYZ_LOG_PREFIX
#endif
#ifdef XYZ_LOG_PREFIX_ARG
#   define __XYZ_LOG_PREFIX_ARG     ,XYZ_LOG_PREFIX_ARG // add seperator ','
#else
#   define __XYZ_LOG_PREFIX_ARG
#endif

#define XYZ_LOG_LEVEL_VERBOSE       1   ///< lowest priority, print tracing log
#define XYZ_LOG_LEVEL_DEBUG         2   ///< print debug info
#define XYZ_LOG_LEVEL_INFO          3   ///< normally print
#define XYZ_LOG_LEVEL_WARN          4   ///< warning information
#define XYZ_LOG_LEVEL_ERROR         5   ///< error information
#define XYZ_LOG_LEVEL_PANIC         6   ///< system panic information
// following log levels are for debug
#define XYZ_LOG_LEVEL_NO_LOG        7   ///< print none normal log, normally used in debugging
#define XYZ_LOG_LEVEL_TMP_DEBUG     8   ///< temporary debug info, printed
#define XYZ_LOG_LEVEL_NEVER         9   ///< never print any log, normally used in debugging

#define XYZ_LOG_PREFIX_VERBOSE      "[V]"
#define XYZ_LOG_PREFIX_DEBUG        "[D]"
#define XYZ_LOG_PREFIX_INFO         "[I]"
#define XYZ_LOG_PREFIX_WARN         "[W]"
#define XYZ_LOG_PREFIX_ERROR        "[E]"
#define XYZ_LOG_PREFIX_PANIC        "[P]"
#define XYZ_LOG_PREFIX_TMP_DEBUG    "[T]"

#define LOGT(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_TMP_DEBUG, XYZ_LOG_PREFIX_TMP_DEBUG  XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGP(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_PANIC,     XYZ_LOG_PREFIX_PANIC      XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGE(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_ERROR,     XYZ_LOG_PREFIX_ERROR      XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGW(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_WARN,      XYZ_LOG_PREFIX_WARN       XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGI(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_INFO,      XYZ_LOG_PREFIX_INFO       XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGD(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_DEBUG,     XYZ_LOG_PREFIX_DEBUG      XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGV(fmt, ...)             SCL_LogPrint_(XYZ_LOG_LEVEL_VERBOSE,   XYZ_LOG_PREFIX_VERBOSE    XYZ_LOG_PREFIX fmt "\n" __XYZ_LOG_PREFIX_ARG, ##__VA_ARGS__)
#define LOGTRAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_TMP_DEBUG, fmt, ##__VA_ARGS__)
#define LOGPRAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_PANIC,     fmt, ##__VA_ARGS__)
#define LOGERAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_ERROR,     fmt, ##__VA_ARGS__)
#define LOGWRAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_WARN,      fmt, ##__VA_ARGS__)
#define LOGIRAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_INFO,      fmt, ##__VA_ARGS__)
#define LOGDRAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_DEBUG,     fmt, ##__VA_ARGS__)
#define LOGVRAW(fmt, ...)          SCL_LogPrint_(XYZ_LOG_LEVEL_VERBOSE,   fmt, ##__VA_ARGS__)

// For temporary debugging, always print, higher than XYZ_LOG_LEVEL_NO_LOG.
#define _LOGV       LOGT
#define _LOGD       LOGT
#define _LOGI       LOGT
#define _LOGW       LOGT
#define _LOGE       LOGT
#define _LOGP       LOGT

// For temporary debugging, never print
#define xLOGV(fmt, ...)
#define xLOGD(fmt, ...)
#define xLOGI(fmt, ...)
#define xLOGW(fmt, ...)
#define xLOGE(fmt, ...)
#define xLOGP(fmt, ...)

#endif // UTILS_LOG_H_

/*  
#else

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>


#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XYZ_LOG_PREFIX
#   define XYZ_LOG_PREFIX
#endif
#ifdef XYZ_LOG_PREFIX_ARG
#   define __XYZ_LOG_PREFIX_ARG     ,XYZ_LOG_PREFIX_ARG // add seperator ','
#else
#   define __XYZ_LOG_PREFIX_ARG
#endif

#define XYZ_LOG_LEVEL_VERBOSE       1   ///< lowest priority, print tracing log
#define XYZ_LOG_LEVEL_DEBUG         2   ///< print debug info
#define XYZ_LOG_LEVEL_INFO          3   ///< normally print
#define XYZ_LOG_LEVEL_WARN          4   ///< warning information
#define XYZ_LOG_LEVEL_ERROR         5   ///< error information
#define XYZ_LOG_LEVEL_PANIC         6   ///< system panic information
// following log levels are for debug
#define XYZ_LOG_LEVEL_NO_LOG        7   ///< print none normal log, normally used in debugging
#define XYZ_LOG_LEVEL_TMP_DEBUG     8   ///< temporary debug info, printed
#define XYZ_LOG_LEVEL_NEVER         9   ///< never print any log, normally used in debugging


int  SCL_SetLogFile(FILE* file);
int  SCL_SetLogFileByName(const char* file);
int  SCL_SetLogFileByFd(const int fd);
void SCL_CloseLogFile();

int  SCL_SetGlobalLogPrefix(const char* format);
    /// Set log prefix for global log
    ///
    ///   * %d - zero-padded day of month (01 .. 31)
    ///   * %f - space-padded day of month ( 1 .. 31)
    ///   * %m - zero-padded month (01 .. 12)
    ///   * %o - space-padded month ( 1 .. 12)
    ///   * %Y - year with century (1970)
    ///   * %H - hour (00 .. 23)
    ///   * %M - minute (00 .. 59)
    ///   * %S - second (00 .. 59)
    ///   * %i - millisecond (000 .. 999)
    ///   * %% - percent sign

void SCL_ClearGlobalLogPrefix();

int  SCL_LogPrint_(int level, const char *fmt, ...);
    /// Send format string to log, like printf().

int  SCL_LogVprint_(int level, const char *fmt, va_list ap);
    /// Send format string to log, like vprintf().

void SCL_SetLogLevel(int level);

#ifdef __cplusplus
}
#endif

#define  LOG_TAG    "tycam"
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGF(...)  __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)

#define  LOGVRAW(...)  LOGV(...)
#define  LOGDRAW(...)  LOGD(...)
#define  LOGIRAW(...)  LOGI(...)
#define  LOGWRAW(...)  LOGW(...)
#define  LOGERAW(...)  LOGE(...)
#define  LOGFRAW(...)  LOGF(...)


#endif
*/
