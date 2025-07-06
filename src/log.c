#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include <threads.h>

#include <errno.h>

#include <time.h>

#include <log.h>

struct log_stream_s {
	FILE* stream;
	int16_t logLevel;
	bool color;
};

struct log_stream_s log_outputStreams_g[LOG_MAX_STREAMS] = { 0 };
mtx_t log_streamLock_g;

int32_t log_init(FILE* defaultStream, int16_t defaultLogLevel, bool color) {
	if(mtx_init(&log_streamLock_g, mtx_plain) != thrd_success) {
		return -1;
	}

	log_setLevel(defaultStream, defaultLogLevel);
	return log_addFileStream(defaultStream, defaultLogLevel, color);
}

int32_t log_deinit(void) {
	mtx_destroy(&log_streamLock_g);
	return 0;
}

int16_t log_getLevel(FILE* stream) {
	for(size_t i = 0; i < LOG_MAX_STREAMS; i++) {
		if(log_outputStreams_g[i].stream != stream) continue;
		return log_outputStreams_g[i].logLevel;
	}
	return -0xff;
}

int32_t log_setLevel(FILE* stream, int16_t level) {
	for(size_t i = 0; i < LOG_MAX_STREAMS; i++) {
		if(log_outputStreams_g[i].stream != stream) continue;
		log_outputStreams_g[i].logLevel = level;
		return 0;
	}
	return -1;
}

int32_t log_addFileStream(FILE* stream, int16_t logLevel, bool color) {
	mtx_lock(&log_streamLock_g);
	for(size_t i = 0; i < LOG_MAX_STREAMS; i++) {
		if(log_outputStreams_g[i].stream != NULL) continue;
		log_outputStreams_g[i].stream = stream;
		log_outputStreams_g[i].logLevel = logLevel;
		log_outputStreams_g[i].color = color;
		mtx_unlock(&log_streamLock_g);
		return 0;
	}
	mtx_unlock(&log_streamLock_g);
	return ENFILE;
}

int32_t log_removeFileStream(FILE* stream) {
	mtx_lock(&log_streamLock_g);
	for(size_t i = 0; i < LOG_MAX_STREAMS; i++) {
		if(log_outputStreams_g[i].stream == stream) {
			log_outputStreams_g[i].stream = NULL;
			mtx_unlock(&log_streamLock_g);
			return 0;
		}
	}
	mtx_unlock(&log_streamLock_g);
	return EBADF;
}

void log_internalCustomLog(const char* file, const char* function, uint32_t line, const char* logType, int16_t logLevel, const char* color, const char* tag, const char* fmt, ...) {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);

	struct tm* timeinfo = localtime(&ts.tv_sec);

	char buffer[64] = {0};

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	mtx_lock(&log_streamLock_g);
	va_list args;
	va_start(args, fmt);
	
	for(size_t i = 0; i < LOG_MAX_STREAMS; i++) {
		if(log_outputStreams_g[i].stream == NULL) continue;
		if(log_outputStreams_g[i].logLevel < logLevel) continue;
		fprintf(log_outputStreams_g[i].stream, "%s%s.%03ld [%s] %s:%i (%s) %s: ", log_outputStreams_g[i].color == true ? color : "", buffer, ts.tv_nsec / 1000000, logType, file, line, function, tag);

		va_list argsCopy;
		va_copy(argsCopy, args);
		vfprintf(log_outputStreams_g[i].stream, fmt, argsCopy);
		va_end(argsCopy);

		fprintf(log_outputStreams_g[i].stream, "%s\n", log_outputStreams_g[i].color == true ? LOG_COLOR_NORMAL : "");
	}

	va_end(args);
	mtx_unlock(&log_streamLock_g);
	return;
}