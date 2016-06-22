#OBJS specifies which files to compile as part of the project
OBJS = ../include/SDLEngine.cpp ../include/general.cpp main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=gnu++0x -I/usr/local/include
DBG_COMPILER_FLAGS = -w -std=gnu++0x --coverage -fprofile-arcs -ftest-coverage -I/usr/local/include

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -L/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
DBG_LINKER_FLAGS = -L/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lcppunit -fprofile-arcs -lgcov

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug : $(OBJS)
	$(CC) $(OBJS) $(DBG_COMPILER_FLAGS) $(DBG_LINKER_FLAGS) -o $(OBJ_NAME)
