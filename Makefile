CC      := gcc
CFLAGS  := -std=c11 \
           -I$(shell brew --prefix)/include \
           -Iinclude \
           $(shell sdl2-config --cflags) \
           -Wall -Wextra

LDFLAGS := $(shell sdl2-config --libs) \
           -lSDL2_ttf -lSDL2_image

SRC     := $(wildcard src/*.c)
OBJ     := $(SRC:src/%.c=build/%.o)
EXEC    := snake

all: $(EXEC)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf build $(EXEC)

.PHONY: all clean
