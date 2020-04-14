
include $(MAKERULES)

SUBDIRS = portable/MemMang portable/GCC/RaspberryPi
BUILDDIRS = $(SUBDIRS:%=build-%)

OBJS = event_groups.o list.o queue.o stream_buffer.o tasks.o timers.o

all: $(BUILDDIRS) $(OBJS) COPY_OBJS
$(BUILDDIRS): 
	$(HIDE) $(MAKE) -C $(@:build-%=%) all

%.o:%.c 
	$(HIDE) $(CC) $(CFLAGS) -c $< -o $@

%.o:%.S 
	$(HIDE) $(CC) $(AFLAGS) -c $< -o $@

%.o:%.s 
	$(HIDE) $(CC) $(AFLAGS) -c $< -o $@

CLEANDIRS = $(SUBDIRS:%=clean-%)

cleansubs: $(CLEANDIRS)
$(CLEANDIRS): 
	$(HIDE) $(MAKE) -C $(@:clean-%=%) clean

clean: cleansubs
	$(HIDE) $(REMOVE) *.o
	$(HIDE) $(REMOVE) *.su
	$(HIDE) $(REMOVE) *.flags
	$(HIDE) $(REMOVE) *.expand

.PHONY: all clean cleansubs
