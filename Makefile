CC = g++
CFLAGS := -Wall -std=c++11
LDFLAGS :=
BUILD_DIR := bin
OBJ_DIR := obj
SOURCE_DIR := src

client_script := ledclient.sh
module_name := ledcontrol
headers := $(wildcard $(SOURCE_DIR)/*.h)
objs := main.o tLED.o tLEDCommandResult.o tLEDCommand.o tLEDHelper.o tLEDControlServer.o tPipe.o


objs_full := $(foreach obj, $(objs), $(OBJ_DIR)/$(obj))

out_dirs := $(OBJ_DIR) $(BUILD_DIR)

.PHONY: clean all default

default: directories $(module_name) $(client_script)
all: default

directories:
		mkdir -p $(out_dirs)

$(module_name): $(objs_full)
		$(CC) $(LDFLAGS) $(objs_full) -o $(BUILD_DIR)/$@

.SUFFIXES: .cpp .o

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(headers)
		$(CC) $(CFLAGS) -c -o $@ $<

$(client_script):
		cp $(SOURCE_DIR)/$(client_script) $(BUILD_DIR)/$(client_script)
		chmod 770 $(BUILD_DIR)/$(client_script)

clean:
		-rm -f $(OBJ_DIR)/*
		-rm -f $(BUILD_DIR)/$(module_name)
		-rm -f $(BUILD_DIR)/$(client_script)