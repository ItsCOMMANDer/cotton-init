#ifndef COTTON_INIT_LOG_H
#define COTTON_INIT_LOG_H

#include <stdint.h>

#define LOG_LEVEL_TRACE 4
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_FATAL -1

#define LOG_COLOR_TRACE "\x1b[38;2;160;160;160m"
#define LOG_COLOR_DEBUG "\x1b[38;2;0;255;255m"
#define LOG_COLOR_INFO "\x1b[38;2;0;255;0m"
#define LOG_COLOR_WARN "\x1b[38;2;255;255;0m"
#define LOG_COLOR_ERROR "\x1b[38;2;255;85;85m"
#define LOG_COLOR_FATAL "\x1b[38;2;255;0;0m"

#define LOG_COLOR_NORMAL "\x1b[39m"

#define LOG_MAX_STREAMS 16


#define LOG_TRACE(tag, fmt, ...) log_internalCustomLog(__FILE__, __func__, __LINE__, "TRACE", LOG_LEVEL_TRACE, LOG_COLOR_TRACE, tag, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(tag, fmt, ...) log_internalCustomLog(__FILE__, __func__, __LINE__, "DEBUG", LOG_LEVEL_DEBUG, LOG_COLOR_DEBUG, tag, fmt, ##__VA_ARGS__)
#define LOG_INFO(tag, fmt, ...) log_internalCustomLog(__FILE__, __func__, __LINE__, "INFO", LOG_LEVEL_INFO, LOG_COLOR_INFO, tag, fmt, ##__VA_ARGS__)
#define LOG_WARN(tag, fmt, ...) log_internalCustomLog(__FILE__, __func__, __LINE__, "WARN", LOG_LEVEL_WARN, LOG_COLOR_WARN, tag, fmt, ##__VA_ARGS__)
#define LOG_ERROR(tag, fmt, ...) log_internalCustomLog(__FILE__, __func__, __LINE__, "ERROR", LOG_LEVEL_ERROR, LOG_COLOR_ERROR, tag, fmt, ##__VA_ARGS__)
#define LOG_FATAL(tag, fmt, ...) log_internalCustomLog(__FILE__, __func__, __LINE__, "FATAL", LOG_LEVEL_FATAL, LOG_COLOR_FATAL, tag, fmt, ##__VA_ARGS__)

int32_t log_init(FILE* defaultStream, int16_t defaultLogLevel, bool color);
int32_t log_deinit(void);
void log_internalCustomLog(const char* file, const char* function, uint32_t line, const char* logType, int16_t logLevel, const char* color, const char* tag, const char* fmt, ...);
int16_t log_getLevel(FILE* stream);
int32_t log_setLevel(FILE* stream, int16_t level);
int32_t log_addFileStream(FILE* stream, int16_t logLevel, bool color);
int32_t log_removeFileStream(FILE* stream);

#endif