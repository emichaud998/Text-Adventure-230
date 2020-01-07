Our implementation of our text adventure game, called Dungeon Escape, is ran from the main function in the adventure.c file, with supporting functions to allow the game to work 
found in the rooms.c and items.c files, which contain functions that work with the rooms and items in the game respectively. The rooms.c file contains a function called 
roomCreate(), which allocates struct Rooms dynamically by using malloc, according to their definition declared in the rooms.h file. The room_setup() function creates all 11 
rooms that can be moved to in the game, giving each of them a name, description, a list of items found in the room, and sets up if they are dark, have a monster, or whether or 
not they can be entered (if the door to them is locked). These boolean fields restrict the player from doing specific actions in certain rooms, such as being able to see or 
pick up items in a room that is dark. This function also sets up the direction connections between the rooms, connecting them north, south, east, west, up, or down. The Room 
structure contains a struct Item pointer as one of its fields, which contains a linked list of the items that are found in the room, allowing each of the rooms to have items.  

The items.c file contains the function itemCreate(), which allocates struct Items dynamically by using malloc, according to their definition declared in the items.h file. They 
contain a name field, description, and a struct Item pointer which points to the next Item in the linked list of items in each room/inventory. This file also has functions to 
create lists of specific Items found in every room. Rooms with no items to start are given a single struct Item with no name or description to serve as the head and allows 
items to be added or removed from the room during the game. A function to create another single struct Item with no name or description is set up as the inventory list, and the 
pointer to this list is returned to the main function to serve as the avatar's inventory, allowing items to be added to it or removed from it during the game. 

For each of the functions roomCreate() and itemCreate(), struct memoryRooms and struct memoryItems are also created respectively from the createMemoryRooms() and 
createMemoryItems() functions in adventure.c. Each dynamically created struct Room and struct Item is added to the end of the list of memoryRooms and memoryItems which are 
pointed to by the external pointers roomsMemory and itemsMemory. These lists of all the dynamically created objects are then all freed to deallocate the memory at the end of 
the main function using the freeRoomMemory() and freeItemMemory() functions. 

The game allows the player's "avatar" to navigate/interact with the environment by reading in a line typed in by the user to the standard input file, which is read and stored 
into the array "buffer" until the new line character is reached. The line typed in is then checked to see if the first word in "buffer" is one of the commands that allows the 
player to do some specific action. If the first word is one of the commands, the rest of the line typed in after "go" is stored in the character pointer "action". If the first 
word in "buffer" is equal to "go", "action" will be set to the rest of the line typed in which should be a direction. This passed in with a pointer to the current room the 
player is in to the function move() to move the avatar to the next room in the direction specified by the line pointed to by "action", if a direction was indeed typed in and it 
is a valid direction to go. 

If the first word is "take" or "drop" or "use", "action" points to the rest of the line typed in after "drop"/take"/"use", which should be an item in the player's inventory for 
"drop" and "use" or in the current room for "take". This is then passed in with pointers to the player's inventory and currentRoom to the function 
item_take()/item_drop()/item_use(). item_take() checks if "action" points to the name of a valid item in the current room and removes the item from the current room and adds it 
to the player's inventory using the functions item_add(), item_remove(), and item_swap(). item_drop() does the same thing but reversed in that it checks if "action" points to 
the name of an item in the player's inventory, and removes it from the inventory and adds it to the current room. Some items have special properties such as the barrel, which 
cannot be picked up unless the player's inventory is empty, and the 3 keys (goat, lion, and snake) which combine to form the chimera key when they are all collected using the 
checkKeys() function. Another example is that dropping the flashlight in a room that is dark causes the player to die from a creature hiding in the dark.

item_use() checks if the line pointed to by "action" is the name of an item found in the player's inventory, and if it is, calls several different functions relating to the 
specific item the player is trying to use. Each of these functions for each item in turn also call specific functions for the rooms the items can be used in. Using the sword, 
for example, calls a function useSword() which checks if the player is in a room with a monster, and then calls a function for that specific room to kill the monster in that 
room, with the exception of the final boss room in which the player can only kill the monster and win the game if they also are wearing armor, defined by the external global 
boolean variable ARMOR. Using the flashlight calls the function darkRoom(), which sets the rooms isDark value to false and changes the description of the room so that the 
player can now see and take items from the room. Using the chimera key calls a function chimeraKeyRoom(), which checks to make sure the player is in the room in which the 
locked door is in and sets the canEnter field of the room that is locked to true so the player can now enter. The other items have the same general function.  

If the command typed in is "Mamba" or "mamba", the secretWord() function is called, which checks to see if the player is in the room in which this secret room unlocks the door 
to the armory, and if it is the canEnter of the armory room is set to true.

If the first word stored in "buffer" is "inventory", the inventoryList() function is called which prints all the items and their descriptions in the player's inventory. "look" 
allows the player to see the room by calling the function room_look(), which prints the description of the current room and the items in that room. Typing in "help" prints the 
instructions of the game defined by the macros HELP, which is defined in the adventure.h file. Typing in "quit" sets the boolean value quit to true and breaks out of the while 
loop so that the game ends. The game proceeds in this fashion, reading in lines typed in by the user to stdin, until either the boolean value alive becomes false, indicating 
the player has died, the boolean value wonGame becomes true indicating the player has won the game, which is checked with the gameWin() function after the player uses an item 
to see if the player is in the final room and if the monster has been killed, or if currentRoom becomes NULL, which happens when a move causes the player to die, such as trying 
to leave a room with a monster in it. The game is then over as the player has either quit, died and lost, or survived and won the final battle.

Video Demonstration:
https://youtu.be/EyXynXRdlsM