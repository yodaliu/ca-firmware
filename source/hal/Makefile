
include $(MAKERULES)

.PHONY: all clean

OBJS = aarch64.o auxi.o gicv2.o gpio.o mbox.o timer.o uart.o

all:    $(OBJS) COPY_OBJS

%.o:%.c
	$(HIDE) $(CC) $(CFLAGS) -O0 -c $< -o $@

%.o:%.S
	$(HIDE) $(CC) $(AFLAGS) -c $< -o $@

%.o:%.s
	$(HIDE) $(CC) $(AFLAGS) -c $< -o $@

clean:
	$(HIDE) $(REMOVE) *.o
	$(HIDE) $(REMOVE) *.su
	$(HIDE) $(REMOVE) *.flags
	$(HIDE) $(REMOVE) *.expand
