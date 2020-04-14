SHELL		= /bin/bash

#TOOL_PREFIX = aarch64-linux-gnu-
TOOL_PREFIX = aarch64-elf-

AS			= $(TOOL_PREFIX)as
LD			= $(TOOL_PREFIX)ld
CC			= $(TOOL_PREFIX)gcc
NM			= $(TOOL_PREFIX)nm
OBJCOPY 	= $(TOOL_PREFIX)objcopy
OBJDUMP 	= $(TOOL_PREFIX)objdump
COPY		= cp
MKDIR		= mkdir
MOVE		= mv
REMOVE		= rm -f
REMOVEDIR	= rm -rf
HIDE		=
ifeq ($(HIDE),@)
MAKE		= make --no-print-directory
else
MAKE		= make
endif

TOPDIR		:= $(shell /bin/pwd)
MAKERULES	= $(TOPDIR)/Rules.make
BUILDDIR	= $(TOPDIR)/build
OBJDIR		= $(BUILDDIR)/objs

INC = -I$(TOPDIR)/include -I$(TOPDIR)/FreeRTOS/include -I$(TOPDIR)/FreeRTOS/portable/GCC/RaspberryPi
CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only -mcpu=cortex-a72 $(INC)
AFLAGS = -D__ASSEMBLY__ $(CFLAGS)

export BUILDDIR OBJDIR MAKERULES TOPDIR AFLAGS CFLAGS
export CC LD NM STRIP OBJCOPY OBJDUMP MAKE COPY REMOVE HIDE

.DEFAULT_GOAL := all

build_folder: clean
	@if [ -d $(BUILDDIR) ]; then echo "$(BUILDDIR) exist"; else $(MKDIR) -p $(BUILDDIR); fi
	@if [ -d $(OBJDIR) ]; then echo "$(OBJDIR) exist"; else $(MKDIR) $(OBJDIR); fi

SUBDIRS = source
BUILDDIRS = $(SUBDIRS:%=build-%)
$(BUILDDIRS):
	$(HIDE) $(MAKE) -C $(@:build-%=%) all

$(COPY_BOJS):
	$(COPY) *.obj $(OBJDIR)

.PHONY: all clean

OBJS_LIST = $(OBJDIR)/*.o

all: build_folder $(BUILDDIRS)
	$(LD) -T rpi4b.ld -o firmware.elf $(OBJS_LIST)
	$(NM) firmware.elf | grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | sort > firmware.map
	$(OBJDUMP) -D -S firmware.elf > firmware.dump
	$(OBJCOPY) -O binary firmware.elf kernel8.img

CLEANDIRS = $(SUBDIRS:%=clean-%)
$(CLEANDIRS):
	$(HIDE) $(MAKE) -C $(@:clean-%=%) clean

clean: $(CLEANDIRS)
	$(HIDE) $(REMOVEDIR) $(BUILDDIR)
	$(HIDE) $(REMOVE) *.dump
	$(HIDE) $(REMOVE) *.map
	$(HIDE) $(REMOVE) *.elf
	$(HIDE) $(REMOVE) *.img
