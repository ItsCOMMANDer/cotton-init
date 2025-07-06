#ifndef COTTON_INIT_H
#define COTTON_INIT_H

#include <log.h>

#define CONFIG_VERSION "0.0.0-indev"

#define CONFIG_NAME "cotton-init"
#define CONFIG_DEFAULT_VERBOSITY LOG_LEVEL_TRACE

#define CONFIG_COMPILE_TIME __TIME__
#define CONFIG_COMPILE_DATE __DATE__

#endif