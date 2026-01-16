CC = g++
CFLAGS = -Wall  #Compiler Flags
CXXFLAGS = -g #Cpp Flags
SRCS = Game_SFML.cpp Connect4.cpp Connect4_SFML.cpp # SFML version of game
SRCS_TXT = Connect4.cpp Game_CLI.cpp # CLI version
SRC_DIR = src
BUILD_DIR = build
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCL_DIR = include
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o) #Substitution : X.cpp => build/X.o
OBJS_TXT = $(SRCS_TXT:%.cpp=$(BUILD_DIR)/%.o)
TARGET = connect4
TXT_TARGET = connect4_cli

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)
   
$(TXT_TARGET) : $(OBJS_TXT)
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDLIBS) -I$(INCL_DIR) -c $^ -o $@

clean:
	rm $(TARGET) $(TXT_TARGET) $(BUILD_DIR)/*.o