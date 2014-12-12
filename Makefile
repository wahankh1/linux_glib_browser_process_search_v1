#
#  Copyright 2014 Wahankh <dev@wahankh.co.uk>
#
#  2014-12-7T19:12+0000

TARGET=monix
CC=gcc -std=c99
CFLAGS=-Wall -I. `pkg-config --cflags --libs glib-2.0 gio-2.0`

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/%.o)

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS+=-DDEBUG -g
else
	CFLAGS+=-DNDEBUG
endif

$(TARGET): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)
	
$(OBJ): obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: clean
clean:
	rm -Rf obj $(TARGET)
