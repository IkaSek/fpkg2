CC:=cc
CFLAGS:=-Wall -Wextra -O0 -g -Iinclude -std=gnu23 -pthread -I. -I../spec
LDFLAGS:=-pthread -lpam
SRC:=$(shell find . -type f -name '*.c' -not -path './Plugs/*')
OBJ:=$(patsubst %.c,%.o,$(SRC))
SPEC:=$(shell find ../spec/ -name '*.sp.toml' -type f)
SPEC2H:= $(patsubst %.sp.toml, %.sp.h, $(SPEC))

all: fpkg
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -c
%.sp.h: %.sp.toml
	../spec/spec2h.py $<
fpkg: $(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJ) -o fpkg
.PHONY: all
clean:
	rm -rf $(OBJ) fpkg