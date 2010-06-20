TARGET=game

OBJ=actor.o \
	game.o \
	kernel.o  \
	main.o  \
	actors/player.o \
	components/transform.o \
	components/sprite.o

CFLAGS=-Wall -g -O0 -I.
LDFLAGS=-lglfw

$(TARGET): $(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)
