PROGRAM = main
PROGRAM_SRC_DIR =. ./src
VERSION=version

MAJOR=0
MINOR=2
ifeq ($(wildcard version.build),)
BUILD=0
else
BUILD=$(shell cat version.build)
endif

CFLAGS = $(C_CXX_FLAGS) -std=gnu99 $(EXTRA_CFLAGS) -DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -DBUILD=$(BUILD)

include $(HOME)/esp-open-rtos/common.mk

version:
ifeq ($(wildcard version.build),)
	@echo 0 > version.build
else
	@echo $$(($(BUILD)+1)) > version.build
endif
