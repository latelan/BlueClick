#!Makefile

# ------------------------------------------------------------------------
#
# 项目的 Makefile 示例，对于此结构代码，该 Makefile 均通用。
#
# ------------------------------------------------------------------------
C_SOURCES = $(shell find . -name "*.cpp")
C_OBJECTS = $(patsubst %.cpp, %.o, $(C_SOURCES))

CC = g++
C_FLAGS = -D_REENTRANT -DSERVER_DEBUG -c -Wall -Iinclude -g
LINK_FLAGS = -L/usr/lib/mysql -lmysqlclient $(mysql_config --cflags) $(mysql_config --libs)
PROGRAM = server

all: $(C_OBJECTS) 
	@echo Link ...
	$(CC) $(C_OBJECTS) $(LINK_FLAGS) -o $(PROGRAM)

.cpp.o:
	@echo Compiler $< ...
	$(CC) $(C_FLAGS) $< -o $@

.PHONY:clean
clean:
	@echo Clean all ...
	$(RM) $(C_OBJECTS) $(PROGRAM)

