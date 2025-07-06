ifdef DEBUG
DEBUGFLAGS := -g
endif

SILENTCMD := @
SILENTMSG := @echo

TARGET := build/init

CC := gcc
LD := gcc

CFLAGS := -Wall -Werror -Wextra -Wpedantic -Wconversion -Wshadow -std=c2x -Wno-error=unused-parameter
LDFLAGS := -static

SRC_DIRS := src

SRC_FILES := $(foreach file,$(SRC_DIRS), $(wildcard $(file)/*c))

OBJ_FILES := $(SRC_FILES:.c=.o)

INCLUDE_DIRS := include

INCLUDES := $(foreach include, $(INCLUDE_DIRS), -I$(include))

LIBS := c m

LIB := $(foreach library, $(LIBS), -l$(library))

all: $(TARGET)

debug:
	$(MAKE) all DEBUG=1


$(TARGET): $(OBJ_FILES)
	$(SILENTCMD)mkdir -p build
	$(SILENTMSG) $(LD) -o $@ $^ $(LDFLAGS) $(LIB) $(DEBUGFLAGS)
	$(SILENTCMD)$(LD) -o $@ $^ $(LDFLAGS) $(LIB) $(DEBUGFLAGS)

%.o: %.c
	$(SILENTMSG) $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^ $(DEBUGFLAGS)
	$(SILENTCMD)$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^ $(DEBUGFLAGS)

clean:
	$(SILENTMSG) rm $(OBJ_FILES) $(TARGET)
	$(SILENTCMD)rm -f $(OBJ_FILES) $(TARGET)
