#Variables
EXECUTABLE_NAME = preset
STANDARD=c99

#Toolchain
CC = gcc

#Flags
CFLAGS = -std=$(STANDARD) -Wall -Wextra -Werror -Wshadow -Wpedantic -MMD -MP
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2
LDFLAGS = 

#Directories
ROOT_DIR = .
INCLUDE_DIR = $(ROOT_DIR)/include
SRC_DIR = $(ROOT_DIR)/src
LIB_DIR = $(ROOT_DIR)/libs
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

#Files
TARGET = $(BIN_DIR)/$(EXECUTABLE_NAME)
LIBS = $(shell find $(LIB_DIR) -type f -name '*.a') 
SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

#Enables library dependencies to be resolved by the linked
LDLIBS = -Wl,--start-group $(LIBS) -Wl,--end-group

#Canned recipe for creating the build directories
define create_dirs
	@mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR) $(SRC_DIR) $(INCLUDE_DIR) $(LIB_DIR)
endef

.PHONY: all clean rebuild debug release run

all: $(TARGET)

clean: #-f tells rm to not complain if the directory doesn't exist
	rm -rf $(BUILD_DIR)

rebuild: clean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

release: CFLAGS += $(RELEASE_FLAGS)
release: clean all

run: all
	$(TARGET)

#Linking
$(TARGET): $(OBJS) $(LIBS)
	$(create_dirs)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

#Compiling
#|| means run the following command if the previous one (compilation)
#fails. That command is there to remove the related .o and .d files so
#they don't cause a problem with future compilations. It basically ensures
#the compiler will get stuck on the file with the actual error before
#proceeding with another one (which caused weird issues like deleting
#.o or .d files of files that come later in the compilation process, even
#if that file wasn't changed at all).
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(create_dirs)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@ || { rm -f $@ $(@:.o=.d); exit 1; }

#Make sure .d files are used (they allow .o files to be recompiled if a .h file they depend on is changed)
-include -I $(DEPS)
