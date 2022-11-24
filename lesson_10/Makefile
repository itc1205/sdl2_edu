CC = clang++

C_FLAGS = -w

OBJ_NAME = build/main

OBJS = main.cpp src/game_class.cpp src/texture.cpp

L_FLAGS = -lSDL2 -lSDL2_image

all $(OBJS):
	$(CC) $(C_FLAGS) $(OBJS) $(L_FLAGS) -o $(OBJ_NAME)