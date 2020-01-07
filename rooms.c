#include "rooms.h"

extern bool ARMOR; //True if the player is wearing armor and false if the player is not
extern struct memoryRooms *roomsMemory; //Pointer to the beginning of the memoryRooms linked list holding all the dynamically created Room structures

/*
*Function to creates a Room structure and set all of its components to the parameters passed in
*Parameters:
    name = string of the name of the room
    description = string of the description of the room
    items = Pointer to a linked list of items found in the room
    north = pointer to a Room to the north of the room being created
    south = pointer to a Room to the south of the room being created
    east = pointer to a Room to the east of the room being created
    west = pointer to a Room to the west of the room being created
    up = pointer to a Room upwards of the room being created
    down = pointer to a Room downwards of the room being created
    enter = true if this room can be entered (unlocked) and false if the room cannot be entered (locked)
    dark = true if the room is dark (cannot see or do anything) or false if the room is not dark
    monster = true if there is a monster that is alive in the room and false if monster is dead or there is no monster
*Returns:
    A pointer to the Room structure created
*/ 
struct Room *roomCreate(char *name, char *description, struct Item *items, struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Room *up, struct Room *down, bool enter, bool dark, bool monster){
    struct Room *room = (struct Room *)malloc(sizeof(struct Room)); //Dynamically allocates memory for a new Room structure using malloc
    
    //Sets all the components of the new Room structure equal to the corresponding parameters passed in
    room->name = name;
    room->description = description;
    room->items = items;
    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
    room->up = up;
    room->down = down;  
    room->canEnter = enter;
    room->isDark = dark;
    room->monster = monster;

    //Adds each dynamically allocated room into a memory list
    struct memoryRooms *temp = roomsMemory; //Sets a temporary memoryRooms structure equal to the extern roomsMemory pointer

    //Finds the end of the memoryRooms linked list
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createMemoryRooms(); //Creates a new memoryRooms structure and stores it in the next empty space in the memoryRooms linked list pointed to by roomsMemory
    temp->next->roomPointer = room; //Sets this new memoryRooms roomPointer component to the newly created room

    return room;    
}

/*
*Function to create an exit North from current to other room
*Parameters:
    current = Room to create exit North from- set South of other
    other = Room to be set North of current
*/
void room_exit_north(struct Room* current, struct Room* other){
    current->north = other;
    other->south = current;
} 

/*
*Function to create an exit South from current to other room
*Parameters:
    current = Room to create exit South from- set North of other
    other = Room to be set South of current
*/
void room_exit_south(struct Room* current, struct Room* other){
    current->south = other;
    other->north = current;
}

/*
*Function to create an exit West from current to other room
*Parameters:
    current = Room to create exit West from- set East of other
    other = Room to be set West of current
*/
void room_exit_west(struct Room* current, struct Room* other){
    current->west = other;
    other->east = current;
}

/*
*Function to create an exit East from current to other room
*Parameters:
    current = Room to create exit East from- set West of other
    other = Room to be set East of current
*/
void room_exit_east(struct Room* current, struct Room* other){
    current->east = other;
    other->west = current;
}

/*
*Function to create an exit up from current to other room
*Parameters:
    current = Room to create exit up from- set down from other
    other = Room to be set up from current
*/
void room_exit_up(struct Room* current, struct Room* other){
    current->up = other;
    other->down = current;
}

/*
*Function to create an exit down from current to other room
*Parameters:
    current = Room to create exit down from- set up from other
    other = Room to be set down from current
*/
void room_exit_down(struct Room* current, struct Room* other){
    current->down = other;
    other->up = current;
}

/*
*Creates and sets up all the rooms needed for the game
*Return:
    A pointer to the starting room of the game
*/
struct Room *room_setup(){
    //Creates all the rooms needed in the game- descriptions are macros defined in the rooms.h header
    struct Room *startingL1 = roomCreate("starting room", STARTROOM, nullItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, false);
    struct Room *darkL1 = roomCreate("dark room", DARKROOM, darkRoomItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, true, false);
    struct Room *monsterL1 = roomCreate("monster room L1", L1MONSTER, nullItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, true);
    struct Room *lockDoorL1 = roomCreate("locked room", LOCKROOM, nullItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, false);
    struct Room *escapeRoomL1 = roomCreate("escape room", CHIMERABOSSROOM, nullItems(), NULL, NULL, NULL, NULL, NULL, NULL, false, false, true);
    struct Room *weightRoomL2 = roomCreate("snake door room", SNAKEDOOR, heavyRoomItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, false);
    struct Room *armoryL2 = roomCreate("armory", ARMORY, armorRoomItems(), NULL, NULL, NULL, NULL, NULL, NULL, false, false, false);
    struct Room *weightSwitchRoom = roomCreate("scale room",SCALEROOM, nullItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, false);
    struct Room *flashlightRoomB1 = roomCreate("flashlight room", FLASHLIGHTROOM, flashlightRoomItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, false);
    struct Room *snakeRoom = roomCreate("snake key room", SNAKEKEY, snakeRoomItems(), NULL, NULL, NULL, NULL, NULL, NULL, false, false, false);
    struct Room *monsterB1 = roomCreate("monster room B1", B1MONSTER, nullItems(), NULL, NULL, NULL, NULL, NULL, NULL, true, false, true);
    
    //Connects all the rooms in the appropriate orientation for the game
    room_exit_north(startingL1, lockDoorL1);
    room_exit_west(startingL1, darkL1);
    room_exit_south(startingL1, monsterL1);
    room_exit_east(lockDoorL1, escapeRoomL1);
    room_exit_down(lockDoorL1, weightSwitchRoom);
    room_exit_up(startingL1, weightRoomL2);
    room_exit_south(weightRoomL2, armoryL2);
    room_exit_east(weightSwitchRoom, snakeRoom);
    room_exit_south(weightSwitchRoom, flashlightRoomB1);
    room_exit_south(flashlightRoomB1, monsterB1);

    return startingL1;
}

/*
*Allows the player to look in the room they are currently in
*Prints the description of the room and the items in the room
*Parameters:
    curRoom = the room the player is currently in and wants to look at
*/
void room_look(struct Room *curRoom){
    printf("%s \n", curRoom->description); //Prints the description of the room
    struct Item *roomItems = curRoom->items->next; //Stores the start of the linked list of items (skipping the blank head) in the room in into the Item pointer roomItems
    
    //If the current room the player is in is dark it will not print any of the items in the room and will return
    if (curRoom->isDark){
        printf("\n");
        return;
    }
    
    //Prints all the items and item descriptions in the roomItems list 
    while (roomItems != NULL){
        lookItems(roomItems->name);
        roomItems = roomItems->next;
    }
    printf("\n");
    return;
}

/*
*Moves the player north
*Parameters:
    curRoom = the room the player is currently in
*Return:
    A pointer to the room north of the current room if there is a room to the north
    A pointer to the same current room if there is no room to the north
*/
struct Room *move_north(struct Room *curRoom){
    //If there is no room to the north return the same room the player is currently in
    if (curRoom->north == NULL){
        printf("There is no way to go that direction. \n\n");
        return curRoom;
    }

    //If the room to the north is locked return the same room the player is currently in
    else if (!curRoom->north->canEnter){
        printf("The door is locked.\n\n");
        return curRoom;
    }

    //If there is a room to the north return a pointer to the room to the north
    else{
        return (curRoom->north);
    }
}

/*
*Moves the player south
*Parameters:
    curRoom = the room the player is currently in
*Return:
    A pointer to the room south of the current room if there is a room to the south
    A pointer to the same current room if there is no room to the south
*/
struct Room *move_south(struct Room *curRoom){
    //If there is no room to the south return the same room the player is currently in
    if (curRoom->south == NULL){
        printf("There is no way to go that direction. \n\n");
        return curRoom;
    }

    //If the room to the south is locked return the same room the player is currently in
    else if (!curRoom->south->canEnter){
        printf("The door is locked. \n\n");
        return curRoom;
    }

    //If there is a room to the south return a pointer to the room to the south
    else{
        return (curRoom->south);
    }
}

/*
*Moves the player east
*Parameters:
    curRoom = the room the player is currently in
*Return:
    A pointer to the room east of the current room if there is a room to the east
    A pointer to the same current room if there is no room to the east
*/
struct Room *move_east(struct Room *curRoom){
    //If there is no room to the east return the same room the player is currently in
    if (curRoom->east == NULL){
        printf("There is no way to go that direction. \n\n");
        return curRoom;
    } 

    //If the room to the east is locked return the same room the player is currently in      
    else if (!curRoom->east->canEnter){
        printf("The door is locked. \n\n");
        return curRoom;
    }

    //If there is a room to the east return a pointer to the room to the east
    else{
        return (curRoom->east);
    }
}

/*
*Moves the player west
*Parameters:
    curRoom = the room the player is currently in
*Return:
    A pointer to the room west of the current room if there is a room to the west
    A pointer to the same current room if there is no room to the west
*/
struct Room *move_west(struct Room *curRoom){
    //If there is no room to the west return the same room the player is currently in
    if (curRoom->west == NULL){
        printf("There is no way to go that direction. \n\n");
        return curRoom;
    }

    //If the room to the west is locked return the same room the player is currently in 
    else if (!curRoom->west->canEnter){
        printf("The door is locked. \n\n");
        return curRoom;
    }

    //If there is a room to the west return a pointer to the room to the west
    else{
        return (curRoom->west);
    }
}

/*
*Moves the player up
*Parameters:
    curRoom = the room the player is currently in
*Return:
    A pointer to the room up from the current room if there is a room up
    A pointer to the same current room if there is no room up
*/
struct Room *move_up(struct Room *curRoom){
    //If there is no room up return the same room the player is currently in
    if (curRoom->up == NULL){
        printf("There is no way to go that direction. \n\n");
        return curRoom;
    }

    //If there is a room up return a pointer to the room to the west
    else{
        return (curRoom->up);
    }
}

/*
*Moves the player down
*Parameters:
    curRoom = the room the player is currently in
*Return:
    A pointer to the room down from the current room if there is a room down
    A pointer to the same current room if there is no room down
*/
struct Room *move_down(struct Room *curRoom){
    //If there is no room up return the same room the player is currently in
    if (curRoom->down == NULL){
        printf("There is no way to go that direction.\n\n");
        return curRoom;
    }

    //If there is a room up return a pointer to the room to the west
    else{
        return (curRoom->down);
    }
}

/*
*Function for moving between rooms
*Parameters:
    curRoom = the room the player is currently in
    direction = string containing direction typed in by player
*Returns:
    Pointer to the next room in the direction passed in if you can move there
    Same room you are in if you cannot move in that direction 
    NULL if a monster kills you when trying to move
*/
struct Room *move(struct Room *curRoom, char *direction){
    struct Room *nextRoom = curRoom; //Initially sets nextRoom (to be returned) to the room the player is currently in
    
    //If there is an alive monster in the room and you try to leave, returns false indicating you have died
    if (curRoom->monster){
        bool alive = monsterRoomLeave(curRoom, direction); //Function that prints appropriate death for the specific monster room you are in and returns false indicating a death
        
        //Returns NULL if you die
        if (!alive){
            return NULL;
        }
    }
    
    //Compares the string direction passed in with the name of each direction and moves the player according to the direction passed in 
    if (strncmp(direction, "north", 5) == 0){
        nextRoom = move_north(curRoom); //Sets nextRoom equal to the room returned after trying to move north
    }
    else if (strncmp(direction, "south", 5) == 0){
        nextRoom = move_south(curRoom); //Sets nextRoom equal to the room returned after trying to move south
    }
    else if (strncmp(direction, "east", 4) == 0){
        nextRoom = move_east(curRoom); //Sets nextRoom equal to the room returned after trying to move east
    }
    else if (strncmp(direction, "west", 4) == 0){
        nextRoom = move_west(curRoom); //Sets nextRoom equal to the room returned after trying to move west
    }
    else if (strncmp(direction, "up", 2) == 0){
        nextRoom = move_up(curRoom); //Sets nextRoom equal to the room returned after trying to move up
    }
    else if (strncmp(direction, "down", 4) == 0){
        nextRoom = move_down(curRoom); //Sets nextRoom equal to the room returned after trying to move down
    }
    else{
        printf("That is not a direction \n\n"); //If the direction passed in does not match any of the directions above, prints that it is not a direction
    }
    
    //If the nextRoom is equal to the current room passed in (indicating no move was made) return curRoom
    if (nextRoom == curRoom){
        return curRoom;
    }
    
    //Makes the dark room dark again after leaving if the player made it lit using the flashlight
    darkRoomLeave(curRoom);
    
    //Prints a message that the door locked when you move into the final room
    if (strcmp(nextRoom->name, "escape room") == 0){
        printf("The door locked behind you! \n\n");
    }
    
    //Prints out the description for the next room if you moved to a new room
    room_look(nextRoom);    
    
    return nextRoom;
}

/*
*Checks if player is currently in the dark room and dropped flashlight which results in a death
*Parameters:
    curRoom = the room the player is currently in 
*Return:
    False if you died by dropping flashlight in dark room
    True if you are not in the dark room and dropped flashlight
*/
bool darkRoomCheck(struct Room *curRoom){
    //Checks if player is in the dark room
    if (strcmp(curRoom->name, "dark room") == 0){
        printf(DROPFLASH); //Prints message of death by dropping flashlight- DROPFLASH is macro defined in rooms.h header
        printf("\n");
        return false;
    }
    return true;
}

/*
*Makes the dark room dark again after leaving if it is not dark
*Parameters:
    curRoom = the room the player is currently in
*/
void darkRoomLeave(struct Room *curRoom){
    //Checks if the player is in the dark room and if it is not dark
     if ((strcmp(curRoom->name, "dark room") == 0) && (!curRoom->isDark)){
        curRoom->isDark = true; //Sets the current room back to being dark by setting isDark to true
        curRoom->description = DARKROOM; //Sets the description of the current room back to the description of the room when it is dark
        return;
    }

    return;
}

/*
*Prints out the message of how player dies to a specific monster depending on what room player currently in
*Parameters:
    curRoom = the room the player is currently in
    direction = the direction the player is moving
*Returns:
    False if you die trying to leave the room a monster is in
    True otherwise
*/
bool monsterRoomLeave(struct Room *curRoom, char *direction){
    //If the current room is in the room with the ogre, prints the message defined by OGREKILL
    if (strcmp(curRoom->name, "monster room L1") == 0){
        printf(OGREKILL);
        printf("\n");
        return false;
    }

    //If the current room is in the room with the troll, prints the message defined by TROLLKILL
    else if (strcmp(curRoom->name, "monster room B1") == 0){
        printf(TROLLKILL);
        printf("\n");
        return false;
    }

    //If the current room is in the room with the chimera boss, prints the message defined by CHIMERALEAVEKILL if player tries to leave in the direction they came from, or CHIMERAMOVEKILL if player tries to move in any other direction
    else if (strcmp(curRoom->name, "escape room") == 0){
        if (strncmp(direction, "west", 4) == 0){
            printf(CHIMERALEAVEKILL);
            printf("\n");
            return false;
        }
        else{
            printf(CHIMERAMOVEKILL);
            printf("\n");
            return false;
        }
    }
    else{
        return true;
    }
}

/*
*Checks if player is in the room before the final boss room and if the door to the final room is locked and unlocks it so the player can now enter
*Parameters:
    curRoom = room the player is currently in
*/
void chimeraKeyRoom(struct Room *curRoom){
    //Checks if player in the room before the final room (called locked room) and if the door that leads to that room (to the east) is locked (canEnter will be false) 
    if ((strcmp(curRoom->name, "locked room") == 0) && (!curRoom->east->canEnter)){
        printf("The key fits perfectly into the door and the door unlocks! \n\n");
        curRoom->east->canEnter = true; //Sets the final rooms canEnter to true allowing the player to enter 
        return;
    }

    //If not in the correct room prints message that item cannot be used 
    else{
        printf("This item cannot be used here. \n\n");
        return;
    }
}

/*
*Checks if the player is in the room with the scale for the barrel, if the door using the barrel unlocks is locked it unlocks it, if the door is unlocked taking the barrel causes it to relock
*Parameters:
    curRoom = room the player is currently in
    inventory = the players inventory of items
*Return:
    True if the using/taking the barrel caused a change in the room
    False if the barrel cannot be used in the current room the player is in
*/
bool scaleRoom(struct Room *curRoom, struct Item *inventory){
    //Checks if curRoom is the "scale room"
    if (strcmp(curRoom->name, "scale room") == 0){

        //If the door to the east in "scale room" is locked, using the barrel unlocks the door
        if(!curRoom->east->canEnter){
            printf("Placing the heavy barrel on the scale caused the door to unlock! \n\n");
            item_swap(inventory, curRoom->items, "barrel"); //Removes the barrel from the player's inventory and places it into the room
            curRoom->east->canEnter = true; //Sets the canEnter of the east room of curRoom to true allowing player to now enter that room
            return true;
        }

        //If the canEnter of the east room of curRoom is true, taking the barrel causes the door to relock
        else if (curRoom->east->canEnter){
            printf("Picking up the barrel caused the door to lock again! \n\n");
            curRoom->east->canEnter = false; //Sets the canEnter of the east room of curRoom to false making it so the player can no longer enter the room
            return true;            
        }

    }
    //If not in the scale room, return false
    else{
        printf("This item cannot be used here. \n\n");
        return false;
    }
}

/*
*Checks if player is in the dark room and if it is dark and sets isDark to false indicating that the room is no longer dark.
*If player is in the dark room but it is not dark, prints that the flashlight already used 
*If player not in the dark room, prints the item does not need to be used 
*Parameters:
    curRoom = room the player is currently in
*/
void darkRoom(struct Room *curRoom){
    //Checks if curRoom is the dark room
    if (strcmp(curRoom->name, "dark room") == 0){

        //if the room is dark, sets isDark to false indicating the room has brightened
        if (curRoom->isDark == true){
            printf("You used your flashlight to brighten the room so you can see! \n\n");
            curRoom->isDark = false; //Setting curRoom isDark to false so player can now look at room
            curRoom->description = LITDARKROOM; //Sets curRoom description to description of the room when it is lit as defined by LITDARKROOM
            return;
        }

        //Already used flashlight if curRoom is not dark
        else{
            printf("You already used the flashlight. \n\n");
            return;
        }
    }

    //If not in the dark room flashlight does not need to be used 
    else{
        printf("You do not need to use this item here. \n\n");
        return;
    }
}

/*
*Checks if player is in the room with the secret door when the player says the secret word
*If the secret door is locked, it is unlocked. If it is already unlocked, the player is told the door is already open
*Parameters:
    curRoom = room the player is currently in
*/
void secretWord(struct Room *curRoom){
    //Checks if player is in the snake door room
    if (strcmp(curRoom->name, "snake door room") == 0){

        //If the room to the south cannot be entered, sets canEnter to true indicating the door has been unlocked
        if (!curRoom->south->canEnter){
            printf("The secret word caused the door to unlock! \n\n");
            curRoom->south->canEnter = true; //Unlocks the door to the south using the secret room in the snake door room
            return;
        }

        //If the room to the south can be entered, it has already been unlocked
        else{
            printf("The door has already been opened. \n\n");
            return;
        }
    }

    //If not in the snake door room the secret word has no effect
    else{
        printf("The word has no effect here. \n\n");
    }
}

/*Checks if there is a monster that is alive in the current room and kills the ogre monster
*Parameters:
    curRoom = room the player is currently in
*/
void monsterRoomL1(struct Room *curRoom){
    //Checks if curRoom->monster is true indicating there is a monster alive
    if (curRoom->monster){
        printf(YOUKILLOGRE); //Prints message for killing the ogre 
        printf("\n");
        curRoom->monster = false; //Sets the current rooms monster equal to false indicating the monster is dead
        item_add(curRoom->items, monsterL1Items()); //Creates and adds a specific key item to the ogre room after the monster dies
        curRoom->description = NEWMONSTERL1; //Changes the description of the current room to the description after the monster dies (defined by NEWMONSTERL1)
        return;
    }

    //Prints that the ogre is already dead if curRoom->monster is false
    else{
        printf("The ogre is already dead. \n\n");
        return;
    }
}

/*Checks if there is a monster that is alive in the current room and kills the troll monster
*Parameters:
    curRoom = room the player is currently in
*/
void monsterRoomB1(struct Room *curRoom){
    //Checks if curRoom->monster is true indicating there is a monster alive
    if (curRoom->monster){
        printf(YOUKILLTROLL); //Prints message for killing the troll 
        printf("\n");
        curRoom->monster = false; //Sets the current rooms monster equal to false indicating the monster is dead
        item_add(curRoom->items, monsterB1Items()); //Creates and adds a specific key item to the troll room after the monster dies
        curRoom->description = NEWMONSTERB1; //Changes the description of the current room to the description after the monster dies (defined by NEWMONSTERB1)
        return;
    }

    //Prints that the ogre is already dead if curRoom->monster is false
    else{
        printf("The troll is already dead. \n\n");
        return;
    }
}

/*Checks if there is a monster that is alive in the current room and kills the chimera boss monster
*Parameters:
    curRoom = room the player is currently in
*Return:
    True if you kill the chimera and win
    False if the chimera kills you
*/
bool escapeRoom(struct Room *curRoom){
    //Checks if the monster in the current room is alive and that the player is wearing armor and kills the chimera
    if (curRoom->monster && ARMOR == true){
        printf(YOUKILLCHIMERA); //Prints message for killing chimera
        printf("\n");
        curRoom->monster = false; //Sets the current rooms monster equal to false indicating the monster is dead
        return true;
    }
    else{
        printf(NOARMOR); //If player is not wearing armor the player dies and false is returned
        return false;
    }
}
