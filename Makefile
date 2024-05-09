OBJS = main.cpp boid.cpp lib.cpp spatial_hash.cpp
CC = g++

OBJ_NAME = vivarium

FLAGS = -lraylib

all : $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(OBJ_NAME)

