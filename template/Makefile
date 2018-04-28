CFLAGS   = -Wall -Wextra -mtune=native `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = %{APPNAMELC}

.PHONY: all
all: $(TARGETS)

%{APPNAMELC}: $(srcdir)helper.c $(srcdir)main.c
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

