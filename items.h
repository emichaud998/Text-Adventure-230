//Header file for working with Items

//If this header file has already been defined, do not recompile it. If not, define ADVENTURE_H and compile header file
#ifndef ITEMS_H
#define ITEMS_H

//Includes important C standard libraries
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//Includes rooms header file and adventure header file
#include "rooms.h"
#include "adventure.h"

//Item data structure
struct Item{
    char *name; //Name of the Item
    char *description; //Description of the Item
    struct Item *next; //Pointer to the next Item in a linked list of Item structures
};

//Function Prototypes
struct Item *itemCreate(char *name, char *description, struct Item *nextEntry); //Dynamically creates Item structures
char  *item_name(struct Item *c); //Returns the Item's name
char *item_description(struct Item *c); //Returns the Item's description
struct Item *item_next(struct Item *c); //Returns the next Item in a linked list of Items
struct Item *darkRoomItems(); //Creates items in the dark room
struct Item *monsterL1Items(); //Creates items in the monster L1 room
struct Item *monsterB1Items(); //Creates items in the monster B1 room
struct Item *snakeRoomItems(); //Creates items in the snake room
struct Item *heavyRoomItems(); //Creates items in the heavy room
struct Item *armorRoomItems(); //Creates items in the armor room
struct Item *flashlightRoomItems(); //Creates items in the flashlight room
struct Item *nullItems(); //Creates an item with no name or description and points to NULL
struct Item *inventoryCreate(); //Creates Items linked list for the inventory
void inventoryList(struct Item *inventory); //Prints out inventory
void lookItems(char *roomItem); //Prints what items are in the room the player is looking in
struct Item *findItem(struct Item *list, char *itemName); //Finds and returns an Item in a given Item linked list
struct Item *item_remove(struct Item *items, char *curItem); //Removes an Item from a given Item linked list
struct Item *item_add(struct Item *inventory, struct Item *item); //Adds an Item to a given Item linked list
struct Item *item_swap(struct Item *currentItem, struct Item *itemDest, char *nameItem); //Swaps an Item from one Item linked list to another
bool item_drop(struct Item *inventory, struct Room *curRoom, char *nameItem); //Drops an item from players inventory
bool item_take(struct Room *curRoom, struct Item *inventory, char *nameItem); //Takes an item from a room and places it in the players inventory
bool item_use(struct Room *curRoom, struct Item *inventory, char *nameItem); //Allows a player to use an item to interact with surroundings
bool checkKeys(struct Item *inventory); //Checks if you have all 3 keys and combines them into one master key
bool monsterRoomAction(struct Room *curRoom); //Prints how you die from a certain monster if you try to do any action before using the sword and killing the monster in a room with a monster
void useArmor(); //Puts armor on the player
bool useSword(struct Room *curRoom); //Prints how you kill a certain monster when you use the sword against them

#endif
