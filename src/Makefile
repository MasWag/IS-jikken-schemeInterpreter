CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -std=gnu11 -Wall -g -D NODISPLAY

all: scheme

scheme: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

check-syntax:
	$(CC) $(CFLAGS) -o nul -S ${CHK_SOURCES}
clean:
	rm -f *.o *flymake* scheme

test:scheme
	./runtest	
