OBJS = src/Main.cpp

CC = g++

OBJ_NAME = Main

all :
	$(CC) $(OBJS) -std=c++11 -o $(OBJ_NAME)
	