BIN = bin
SRC = src
INC = /usr/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -std=c++14 -Wall
OBJ = main.o Models/Game.o Models/Board.o Models/Screens/Screen.o Models/Screens/ScreenPlay.o Models/Stages/StageBackground.o Models/Stages/StageBoard.o
TARGET = $(BIN)/game
CC = g++
DEPS = $(patsubst %, $(BIN)/%, $(OBJ))

default: $(TARGET)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CC) $(FLAGS) -I$(INC) -c $^ -o $@  

$(TARGET): $(DEPS)
	$(CC) $(DEPS) $(LIBS) $(FLAGS) -o $@

.PHONY: clean
clean:
	-rm -f $(DEPS) $(BIN)/$(TARGET)