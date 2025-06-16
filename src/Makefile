CC:=cc
CFLAGS:=-Wall -Wextra -O0 -g -Iinclude -std=c99 -pthread -I.
LDFLAGS:=-pthread -lpam
SRC:=$(shell find . -type f -name '*.c' ! -name 'Plugs/*.c')
OBJ:=$(patsubst %c,%o,$(SRC))

all: fpkg
compile: $(OBJ:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -c
fpkg: compile
	$(CC) $(LDFLAGS) $(CFLAGS) $(SRC) -o fpkg
.PHONY: all