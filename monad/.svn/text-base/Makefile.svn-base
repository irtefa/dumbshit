CC = g++
CFLAGS = -Wall -Wshadow
EXENAME = monad
CCMONAD = ccmonad
OBJS = $(EXENAME).o help.o util.o monad_shared.o
CCOBJS = $(CCMONAD).o util.o monad_shared.o
IDFILE = .monadid
OPTIMIZE = off

ifeq ($(strip $(OPTIMIZE)),on)
CFLAGS += -O2 -DOPTIMIZE
else ifeq ($(strip $(OPTIMIZE)),off)
CFLAGS += -g -O0
else
$(warning Invalid value specified for OPTIMIZE. Should be on or off)
CFLAGS += -g -O0
endif

IS_LIBRT:=$(shell locate -l 1 -c librt.so)
ifeq ($(IS_LIBRT),0)
LIBRT=
else
LIBRT=-lrt
endif

all: $(EXENAME) $(CCMONAD) $(IDFILE)

$(IDFILE): $(OBJS)
	echo -e '$(EXENAME) identification file\n'\
'This file is used for $(EXENAME) directory identification\n'\
'Built by' `whoami` 'on' `hostname`'\n'\
'Build Date:' `date`> $(IDFILE)

$(EXENAME): $(OBJS) $(IDFILE)
	$(CC) $(CFLAGS) $(LIBRT) $(OBJS) -o $@

$(CCMONAD): $(CCOBJS) $(IDFILE)
	$(CC) $(CFLAGS) $(LIBRT) $(CCOBJS) -o $@

help.o: help.cpp $(wildcard *.h) README.cgo README_config.cgo README_tests.cgo LICENSE.cgo quotes.cga

CONVERT_TXT_TO_CGO=sed -e 's/"/\\"/g' -e 's/^/    << "/' -e 's/$$/" << endl/'
CONVERT_TXT_TO_CGA=sed -e 's/"/\\"/g' -e 's/^/"/' -e 's/$$/",/'

%.cgo: %.txt
	$(CONVERT_TXT_TO_CGO) $(@:.cgo=.txt) > $@

%.cga: %.txt
	$(CONVERT_TXT_TO_CGA) $(@:.cga=.txt) > $@

%.o : %.cpp $(wildcard *.h)
	$(CC) $(CFLAGS) -c $(@:.o=.cpp) -o $@

.PHONY: clean
clean:
	rm -f $(wildcard *.o) $(wildcard *.cgo) $(wildcard *.cga) $(EXENAME) $(CCMONAD) $(IDFILE) $(wildcard $(EXENAME)$(EXENAME)*)

.PHONY: clean.sh
clean.sh: $(EXENAME)
	./clean.sh
