CC = g++
# CFLAGS = -c
SOURCES = pop.cpp
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = connect4

$(TARGET): pop.o Jeu.o
	$(CC) -o $@ pop.o Jeu.o $(LDLIBS)
   
connect4_text : main.o Jeu.o
	$(CC) -o $@ main.o Jeu.o
	
%.o: %.c
	$(CC) -c %.cpp

clean:
	rm $(TARGET) connect4_text *.o 