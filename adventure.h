//Header file for main functions

//If this header file has already been defined, do not recompile it. If not, define ADVENTURE_H and compile header file
#ifndef ADVENTURE_H 
#define ADVENTURE_H 

//Includes important C standard libraries 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//Includes rooms header file and items header file
#include "rooms.h"
#include "items.h"

//Memory structure to hold all rooms dynamically created in a linked list to be freed at the end
struct memoryRooms{
    struct Room *roomPointer; //Pointer to a Room structure
    struct memoryRooms *next; //Pointer to next memoryRooms structure in list 
};

//Memory structure to hold all items dynamically created in a linked list to be freed at the end
struct memoryItems{
    struct Item *itemPointer; //Pointer to an Item structure
    struct memoryItems *next; //Pointer to next memoryItems structure in list
};

//Defines the macros for the length of the array "buffer" to be used in main 
#define MAX_LINE_LENGTH 50

//Defines macros HELP to be the instructions of the game
#define HELP "Instructions:\n"\
"1. Type \"go\" with a direction(\"north\", \"south\", \"east\", \"west\", \"up\", and \"down\") to move.\n"\
"2. Type \"look\" to get information about your surroundings.\n"\
"3. Type \"inventory\" to see what you are holding.\n"\
"4. Type \"use\" with an item to use that item.\n"\
"5. Type \"take\" with an item to take that item.\n"\
"6. Type \"drop\" with an item to drop an item in your inventory.\n"\
"7. Type \"help\" to get these instructions again.\n"\
"8. Type \"quit\" to exit the game.\n"

//Function prototypes
void readLine(char buffer[MAX_LINE_LENGTH]); //Reads in the next line from the standard input document
void help(); //Prints out the instructions of the game
bool gameWin(struct Room *curRoom); //Checks to see if the user has won the game
struct memoryRooms *createMemoryRooms(); //Creates the memoryRooms structure to hold all the dynamically created Room structures
struct memoryItems *createMemoryItems(); //Creates the memoryItems structure to hold all the dynamically created Item structures
void freeRoomMemory(); //Frees all the dynamically created Room and memoryRoom structures
void freeItemMemory(); //Frees all the dynamically created Item and memoryItem structures

#endif
