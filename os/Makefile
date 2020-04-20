
include $(MAKERULES)

SUBDIRS = FreeRTOS

BUILDDIRS = $(SUBDIRS:%=build-%)
CLEANDIRS = $(SUBDIRS:%=clean-%)

all: $(SUBDIRS)
$(SUBDIRS): $(BUILDDIRS)
$(SUBDIRS):
	$(HIDE) $(MAKE) -C $(@:build-%=%) all

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(HIDE) $(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(SUBDIRS)
.PHONY: subdirs $(BUILDDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all clean
