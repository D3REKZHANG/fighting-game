.PHONY: all clean

# Define compiler path on Windows
COMPILER_PATH      ?= C:/Strawberry/c/x86_64-w64-mingw32/bin

# Define default options
# One of PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM           ?= PLATFORM_DESKTOP

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= DEBUG

# Define default make program: Mingw32-make
MAKE = mingw32-make

# Define compiler flags:
#  -O0                  defines optimization level (no optimization, better for debugging)
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build -> do not use in debug builds
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS += -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

# resource file contains windows executable icon and properties
# -Wl,--subsystem,windows hides the console window
# CFLAGS += -Wl,--subsystem,windows

# Define include paths for required headers
# NOTE: Several external required libraries (stb and others)
INCLUDE_PATHS = -Ilib -Ilib/external -Iinclude

# Define library paths containing required libs.
LDFLAGS = -Llib -lraylib

# Libraries for Windows desktop compilation
# NOTE: WinMM library required to set high-res timer resolution
LDLIBS = -lopengl32 -lgdi32 -lwinmm

## Define a recursive wildcard function
#rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

## Define all source files required
#SRC_DIR = src
#OBJ_DIR = obj
#
## Define all object files from source files
#SRC = $(call rwildcard, *.c, *.cpp, *.h)
#OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_DIR = src

COMPILE = g++ ${SRC_DIR}/*.cpp -o game.exe $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)
RUN_DEBUG = gdb game -ex 'run'

# Default target entry
all:
	${COMPILE}
	${RUN_DEBUG}

build:
	${COMPILE}

start:
	${RUN_DEBUG}

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
#%.o: %.c
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	g++ -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

# Clean everything
clean:
	del *.o *.exe /s
	@echo Cleaning done

