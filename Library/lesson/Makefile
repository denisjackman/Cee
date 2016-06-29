#OBJS specifies which files to compile as part of the project
OBJS = ../../include/gamefunction.cpp lesson.cpp
SDL_OBJS = SDLPixPlot.cpp
SCRAP_OBJS = ../../include/gamefunction.cpp  scrap.cpp
DB_OBJS = newdb.cpp
DUN_OBJS = dungeon.cpp
FIGHT_OBJS = ../../include/gamefunction.cpp  fight.cpp
MAZE_OBJS = maze.cpp
THREE_OBJS = threedun.cpp
TWO_OBJS = twodun.cpp
STUDY_OBJS = ../../include/rogue.cpp study.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=gnu++0x --coverage -fprofile-arcs -ftest-coverage
MAC_COMPILER_FLAGS = -w
SDL_COMPILER_FLAGS = -w -std=c89 -Wextra -pedantic-errors
DB_COMPILER_FLAGS = -w $(shell mysql_config --cflags )


#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lcppunit -fprofile-arcs -lgcov
MAC_LINKER_FLAGS =
SDL_LINKER_FLAGS = -lSDL2
DB_LINKER_FLAGS = $(shell mysql_config --libs)

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = lesson
SDL_OBJ_NAME = SDLPixPlot
SCRAP_OBJ_NAME = scrap
DB_OBJ_NAME = newdb
DUN_OBJ_NAME = dungeon
FIGHT_OBJ_NAME = fight
MAZE_OBJ_NAME = maze
THREE_OBJ_NAME = threedun
TWO_OBJ_NAME = twodun
STUDY_OBJ_NAME = study

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

Mac : $(OBJS)
	$(CC) $(OBJS) $(MAC_COMPILER_FLAGS) $(MAC_LINKER_FLAGS) -o $(OBJ_NAME)

SDL : $(SDL_OBJS)
	$(CC) $(SDL_OBJS) $(SDL_COMPILER_FLAGS) $(SDL_LINKER_FLAGS) -o $(SDL_OBJ_NAME)

scrap : $(SCRAP_OBJS)
	$(CC) $(SCRAP_OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(SCRAP_OBJ_NAME)

db : $(DB_OBJS)
	$(CC) $(DB_OBJS) $(DB_COMPILER_FLAGS) $(DB_LINKER_FLAGS) -o $(DB_OBJ_NAME)

dun : $(DUN_OBJS)
	$(CC) $(DUN_OBJS) $(MAC_COMPILER_FLAGS) $(MAC_LINKER_FLAGS) -o $(DUN_OBJ_NAME)

fight : $(FIGHT_OBJS)
	$(CC) $(SCRAP_OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(FIGHT_OBJ_NAME)

maze : $(MAZE_OBJS)
	$(CC) $(MAZE_OBJS) $(MAC_COMPILER_FLAGS) $(MAC_LINKER_FLAGS) -o $(MAZE_OBJ_NAME)

three : $(THREE_OBJS)
	$(CC) $(THREE_OBJS) $(MAC_COMPILER_FLAGS) $(MAC_LINKER_FLAGS) -o $(THREE_OBJ_NAME)

two : $(TWO_OBJS)
	$(CC) $(TWO_OBJS) $(MAC_COMPILER_FLAGS) $(MAC_LINKER_FLAGS) -o $(TWO_OBJ_NAME)

study : $(STUDY_OBJS)
	$(CC) $(STUDY_OBJS) $(MAC_COMPILER_FLAGS) $(MAC_LINKER_FLAGS) -o $(STUDY_OBJ_NAME)