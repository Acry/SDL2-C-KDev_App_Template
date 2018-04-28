CC=gcc
CFLAGS   = -Wall -Wextra -mtune=native `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = SDL2_Demo_01

.PHONY: all
all: $(TARGETS)

SDL2_Demo_01: $(srcdir)helper.c $(srcdir)main.c
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

