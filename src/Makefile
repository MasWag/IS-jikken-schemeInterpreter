CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

scheme: $(OBJS)
	$(CC) $(OBJS) -o $@

%.o : %.c
	$(CC) -c $< -o $@

check-syntax:
	$(CC) -o nul -S ${CHK_SOURCES}
