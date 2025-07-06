#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <config.h>

#include <log.h>


int main(int argc, char *argv[]) {
	log_init(stdout, LOG_LEVEL_TRACE, true);

	LOG_INFO("cotton-init", "Starting %s %s compiled at %s %s", CONFIG_NAME, CONFIG_VERSION, CONFIG_COMPILE_TIME, CONFIG_COMPILE_DATE);


	log_setLevel(stdout, CONFIG_DEFAULT_VERBOSITY);
	LOG_INFO("cotton-init", "Set verbosity for stdout to %i", CONFIG_DEFAULT_VERBOSITY);

	{
		size_t totalLength = 0;
		for (int i = 0; i < argc; i++) {
			totalLength += strlen(argv[i]);
		}
		totalLength += (size_t)argc;

		char *result = calloc(totalLength, sizeof(char));

		for (int i = 0; i < argc; i++) {
			strcat(result, argv[i]);
			if (i < argc - 1) {
				strcat(result, " ");
			}
		}

		LOG_INFO("cotton-init", "Command line: %s", result);
		
		free(result);
	}

	return 0;
}