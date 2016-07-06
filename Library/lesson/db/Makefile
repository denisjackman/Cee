#OBJS specifies which files to compile as part of the project
DB_OBJS = newdb.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
DB_COMPILER_FLAGS = -w $(shell /usr/local/mysql/bin/mysql_config --cflags )

#LINKER_FLAGS specifies the libraries we're linking against
DB_LINKER_FLAGS = $(shell /usr/local/mysql/bin/mysql_config --libs )

#OBJ_NAME specifies the name of our exectuable
DB_OBJ_NAME = newdb

#This is the target that compiles our executable
all : $(DB_OBJS)
	$(CC) $(DB_OBJS) $(DB_COMPILER_FLAGS) $(DB_LINKER_FLAGS) -o $(DB_OBJ_NAME)
