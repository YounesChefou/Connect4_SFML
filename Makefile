CC = g++
# CFLAGS = -c
SOURCES = pop.cpp
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = connect4

$(TARGET): pop.o
	$(CC) -o $@ pop.o $(LDLIBS)
   
%.o: %.c
	$(CC) -c pop.cpp