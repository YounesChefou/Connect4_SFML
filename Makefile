CC = g++
CFLAGS = -Wall  #Compiler Flags
CXXFLAGS = -g #Cpp Flags
SRCS = pop.cpp Jeu.cpp # Window version of game
SRCS_TXT = Jeu.cpp main.cpp # Terminal version
SRC_DIR = src
BUILD_DIR = build
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES = -Iinclude/
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o) #Substitution : pop.cpp => build/pop.o
OBJS_TXT = $(SRCS_TXT:%.cpp=$(BUILD_DIR)/%.o)
TARGET = connect4
TXT_TARGET = connect4_text

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)
   
$(TXT_TARGET) : $(OBJS_TXT)
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDLIBS) -Iinclude -c $^ -o $@

clean:
	rm $(TARGET) build/*.o

clean_txt:
	rm $(TXT_TARGET) build/*.o