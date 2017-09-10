CC	?= gcc
CFLAGS	?=
LDFLAGS	?=
LIBS	:= $(shell pkg-config --cflags --libs libfbsplash libfbsplashrender)

all: splash_ctl
splash_ctl: splash_ctl.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LIBS) -o $@

.PHONY: all splash_ctl
