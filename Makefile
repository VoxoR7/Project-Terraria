include Makefile.conf

CC = gcc
PROG = project

#SDL_DIR=$(HOME)/SDL2
#SDLLIB_DIR=$(SDL_DIR)/lib
#SDLINC_DIR=$(SDL_DIR)/include
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin
INC_DIR=include

SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(wildcard $(SRC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: MSG $(BIN_DIR)/$(PROG) MSG_FIN

MSG:
	$(MSG_DEBUG)
	$(MSG_WARNING)
	$(MSG_DEBUT_COMPIL)

MSG_FIN:
	$(MSG_FIN_COMPIL)
	$(MSG_DEBUG)
	$(MSG_WARNING)

$(BIN_DIR)/$(PROG): $(OBJ)
	$(MSG_COMPIL)
	$(CC) $^ -o $@  $(LIBS) $(INCLUDES) -I./$(INC_DIR) $(CFLAGS)

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(MSG_COMPIL)
	$(CC) -o $@ -c $< $(LIBS) $(INCLUDES) -I./$(INC_DIR) $(CFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o

mrproper: clean
	rm -f $(BIN_DIR)/$(PROG)

mrproperm:mrproper all
