SRC = rooms.c items.c adventure.c
OBJ = rooms.o items.o adventure.o
INCL = rooms.h items.h adventure.h 
PROG = textAdventure.out

$(PROG) : $(OBJ)
	gcc $(OBJ) -o $(PROG)
$(OBJ) : $(SRC)
$(OBJ) : $(INCL)
