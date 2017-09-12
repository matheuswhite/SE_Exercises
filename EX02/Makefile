MAJOR=0
MINOR=1
ifeq ($(wildcard version.build),)
BUILD=0
else
BUILD=$(shell cat version.build)
endif

MAIN=main.c
EXEC=test
BUILDDIR=build
SRCDIR=src
OBJDIR=$(BUILDDIR)/obj
CFLAGS += -DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -DBUILD=$(BUILD)

EXECPATH=$(BUILDDIR)/$(EXEC)
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:.c=.o)

all: $(OBJECTS) version
	$(CC) $(CFLAGS) $(MAIN) $(addprefix $(OBJDIR)/,$(notdir $(OBJECTS))) -o $(EXECPATH)

show_raw_main:
	$(CC) $(CFLAGS) -E $(MAIN)

%.o: %.c | mkdirobjdir
	$(COMPILE.c) -o $(addprefix $(OBJDIR)/,$(notdir $@)) $<

mkdirobjdir:
	mkdir -p $(OBJDIR)

run:
	@$(EXECPATH)

clean:
	$(RM) -r $(BUILDDIR)

version:
ifeq ($(wildcard version.build),)
	@echo 0 > version.build
else
	@echo $$(($(BUILD)+1)) > version.build
endif
	@echo Current firmware version $(MAJOR).$(MINOR).$(BUILD)

rebuild: clean all
