#made by foxstar(dennis) -> https://github.com/dennis0324
.PHONY: all clean

_COLOR_BEGIN := $(shell tput setaf 13)
_COLOR_END := $(shell tput sgr0)

PROJECT_NAME := main
PROJECT_FULL_NAME := mindou/main

PROJECT_PREFIX := $(_COLOR_BEGIN)$(PROJECT_FULL_NAME):$(_COLOR_END)

BINARY_PATH := ./
INCLUDE_PATH := include
INCLUDE_PATH += ./
LIBRARY_PATH := lib
SOURCE_PATH := src

#현재 libs에 있는 모든 헤더 파일 넣기
#DIRECTORY = $(shell find ../libs -mindepth 1 -maxdepth 10 -type d)
INCLUDE_PATH += $(DIRECTORY)

# 현재 소스 파일 위치
SOURCES := $(wildcard $(SOURCE_PATH)/*.c)

# c -> o 파일 변환
OBJECTS := $(SOURCES:.c=.o)

TARGETS := $(BINARY_PATH)/$(PROJECT_NAME).out

HOST_PLATFORM := UNKNOWN

ifeq ($(OS),Windows_NT)
	ifeq "$(findstring ;,$(PATH))" ";"
		PROJECT_PREFIX := $(PROJECT_FULL_NAME):
	endif

# MINGW-W64 or MSYS2...?
	HOST_PLATFORM := WINDOWS
else
	UNAME = $(shell uname 2>/dev/null)

	ifeq ($(UNAME),Linux)
		HOST_PLATFORM = LINUX
	endif
endif

CC := gcc
# CFLAGS := -O2 
CFLAGS := $(INCLUDE_PATH:%=-I%)
LDFLAGS := $(LIBRARY_PATH:%=-L%)

PLATFORM := $(HOST_PLATFORM)

ifeq ($(PLATFORM),WINDOWS)
	TARGETS := $(BINARY_PATH)/$(PROJECT_NAME).exe

	ifneq ($(HOST_PLATFORM),WINDOWS)
		CC := x86_64-w64-mingw32-gcc
	endif
endif

all: pre-build build post-build

pre-build:
	@echo "$(PROJECT_PREFIX) Using: '$(CC)' to build this project."
	
	@echo "path: $(INCLUDE_PATH)"
    
build: $(TARGETS)

$(SOURCE_PATH)/%.o: $(SOURCE_PATH)/%.c
	@echo "$(PROJECT_PREFIX) Compiling: $@ (from $<)"
	@$(CC) -g $(CFLAGS) $(CDEBUG) -c $< -o $@ 
    
$(TARGETS): $(OBJECTS)
	@mkdir -p $(BINARY_PATH)
	@echo "$(PROJECT_PREFIX) Linking: $(TARGETS)"
	$(CC) -g $(OBJECTS) -o $(TARGETS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(WEBFLAGS)
    
post-build:
	@echo "$(PROJECT_PREFIX) Build complete."

clean:
	@echo "$(PROJECT_PREFIX) Cleaning up."
	@rm -rf $(BINARY_PATH)/*.exe
	@rm -rf $(BINARY_PATH)/*.out
	@rm -rf $(SOURCE_PATH)/*.o