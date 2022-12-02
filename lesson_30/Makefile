CC = clang++

C_FLAGS = -w

OBJ_NAME = build/main

OBJS = main.cpp src/game_class.cpp src/texture.cpp src/button.cpp src/timer.cpp src/dot.cpp

L_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all:
	$(CC) $(C_FLAGS) $(OBJS) $(L_FLAGS) -o $(OBJ_NAME)

optimize:
	$(CC) $(C_FLAGS) -O2 $(OBJS) $(L_FLAGS) -o $(OBJ_NAME)_optimized
