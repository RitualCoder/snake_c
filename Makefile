# Makefile

# ─── Compilation native ────────────────────────────────────────
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

# ─── Compilation Emscripten → WebAssembly ────────────────────
EMCC     := emcc
EMFLAGS  := -O2 \
            -s USE_SDL=2 \
            -s USE_SDL_IMAGE=2 \
            -s SDL2_IMAGE_FORMATS='["png"]' \
            -s USE_SDL_TTF=2 \
            -s ALLOW_MEMORY_GROWTH=1 \
            --preload-file assets
WASM_OUT := snake.html
SHELL_FILE := src/web/index.html
STYLE_FILE := src/web/style.css

# ─── Règles ────────────────────────────────────────────────────
.PHONY: all native wasm clean

all: native

# ─ Native build ────────────────────────────────────────────────
native: $(EXEC)

build/%.o: src/%.c | build
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# ─ WebAssembly build ──────────────────────────────────────────
wasm: $(WASM_OUT) style_copy

# règle "virtuelle" pour copier le CSS
.PHONY: style_copy
style_copy:
	cp $(STYLE_FILE) . 

$(WASM_OUT):
	$(EMCC) src/*.c \
	  -Iinclude \
	  $(EMFLAGS) \
	  --shell-file $(SHELL_FILE) \
	  -o $(WASM_OUT)

# ─ Clean both builds ──────────────────────────────────────────
clean:
	rm -rf build $(EXEC) $(WASM_OUT) snake.js snake.wasm

# ensure build directory exists
build:
	mkdir -p build
