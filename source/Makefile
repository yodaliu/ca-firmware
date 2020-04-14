
include $(MAKERULES)

SUBDIRS = hal sys

BUILDDIRS = $(SUBDIRS:%=build-%)

all: $(BUILDDIRS)
$(BUILDDIRS):
	$(HIDE) $(MAKE) -C $(@:build-%=%) all

CLEANDIRS = $(SUBDIRS:%=clean-%)

cleansubs: $(CLEANDIRS)
$(CLEANDIRS): 
	$(HIDE) $(MAKE) -C $(@:clean-%=%) clean

clean: cleansubs
	$(HIDE) $(REMOVE) *.o
	$(HIDE) $(REMOVE) *.su
	$(HIDE) $(REMOVE) *.flags

.PHONY: subdirs $(SUBDIRS)
.PHONY: subdirs $(BUILDDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all clean cleansubs

