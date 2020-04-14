

include $(MAKERULES)

.PHONY: all clean

OBJS = heap_4.o

all:    $(OBJS) COPY_OBJS

%.o:%.c	
	$(HIDE) $(CC) $(CFLAGS) -c $< -o $@

%.o:%.S	
	$(HIDE) $(CC) $(AFLAGS) -c $< -o $@

%.o:%.s	
	$(HIDE) $(CC) $(AFLAGS) -c $< -o $@

clean:
	$(HIDE) $(REMOVE) *.o
	$(HIDE) $(REMOVE) *.su
	$(HIDE) $(REMOVE) *.flags
	$(HIDE) $(REMOVE) *.expand

