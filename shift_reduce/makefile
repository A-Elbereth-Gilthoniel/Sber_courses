TARGET = prog

PREF_SRC = ./src/
PREF_OBJ = ./obj/

CC = g++
LEX = flex

SRC = $(filter-out $(LEX_OUT), $(wildcard $(PREF_SRC)*.cpp))
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

LEX_SRC = $(PREF_SRC)lexer.l
LEX_OUT = $(PREF_SRC)lexer.cpp
LEX_H = $(PREF_SRC)lexer.h
LEX_OBJ = $(PREF_OBJ)lexer.o

OBJ += $(LEX_OBJ)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp $(LEX_OBJ)
	$(CC) -c $< -o $@

$(LEX_OBJ) : $(LEX_OUT)
	$(CC) -c $(LEX_OUT) -o $@

$(LEX_OUT) : $(LEX_SRC)
	$(LEX) -o $@ $<

.PHONY : clean
clean :
	rm -f $(PREF_OBJ)*.o $(TARGET) $(LEX_OUT) $(LEX_H)

