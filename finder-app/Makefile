CC=$(CROSS_COMPILE)gcc
CFLAGS= -g -Wall
COBJS=$(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all clean

all: clean $(COBJS) writer

writer:
	$(CC) $(CFLAGS) -o $@ $(COBJS)

clean:
	@rm -rf $(wildcard *.o) writer
