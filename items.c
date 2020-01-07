#include "items.h"

bool ARMOR = false; //True if the player is wearing armor and false if the player is not
extern struct memoryItems *itemsMemory; //Pointer to the beginning of the memoryItems linked list holding all the dynamically created Item structures

/*
*Function to creates a Item structure and set all of its components to the parameters passed in
*Parameters:
    name = string of the name of the item
    description = string of the description of the item
    nextEntry = pointer to next Item structure in linked list of Items
*Returns:
    A pointer to the Item structure created
*/
struct Item *itemCreate(char *name, char *description, struct Item *nextEntry){
    struct Item *items = (struct Item *)malloc(sizeof(struct Item)); //Dynamically allocates memory for a new Item structure using malloc
    
    //Sets all the components of the new Room structure equal to the corresponding parameters passed in
    items->name = name; 
    items->description = description;
    items->next = nextEntry;

    //Adds each dynamically allocated room into a memory list
    struct memoryItems *temp = itemsMemory; //Sets a temporary memoryItems structure equal to the extern itemsMemory pointer
    
    //Finds the end of the memoryItems linked list
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createMemoryItems(); //Creates a new memoryItems structure and stores it in the next empty space in the memoryItems linked list pointed to by itemsMemory
    temp->next->itemPointer = items; //Sets this new memoryItems itemPointer component to the newly created items

    return items;
}

/*
*Creates item sword for the dark room. Item with no name or description serves as the head to the linked list of Items- will not be able to be seen or taken until room is not dark
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *darkRoomItems(){
    struct Item *darkItems = itemCreate("", "",
                    itemCreate("sword", "a bladed weapon used for slashing and thrusting", NULL));
    return darkItems;
}

/*
*Creates item lion key for the L1 monster room. Item with no name or description serves as the head to the linked list of Items- will not be added to the room until monster dead
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *monsterL1Items(){
       struct Item *monsterItems = itemCreate("lion key", "a bronze key in the shape of a lion's head", NULL);
    return monsterItems;
}

/*
*Creates item goat key for the B1 monster room. Item with no name or description serves as the head to the linked list of Items- will not be added to the room until monster dead
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *monsterB1Items(){
       struct Item *monsterItems = itemCreate("goat key", "an iron key in the shape of a goat's head", NULL);
    return monsterItems;
}

/*
*Creates item snake key for the snake room. Item with no name or description serves as the head to the linked list of Items
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *snakeRoomItems(){
    struct Item *snakeItems = itemCreate("", "",
                    itemCreate("snake key", "an emerald key in the shape of a snake's head", NULL));
    return snakeItems;
}

/*
*Creates item barrel for the heavy room. Item with no name or description serves as the head to the linked list of Items
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *heavyRoomItems(){
    struct Item *heavyItems = itemCreate("", "",
                    itemCreate("barrel", "a very very heavy barrel filled with sand", NULL));
    return heavyItems;
}

/*
*Creates item armor for the armor room. Item with no name or description serves as the head to the linked list of Items
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *armorRoomItems(){
       struct Item *armorItems = itemCreate("", "",
                                        itemCreate("armor", "armour that protects the body with steel plates", NULL));
        return armorItems;
}

/*
*Creates item flashlight for the flashlight room. Item with no name or description serves as the head to the linked list of Items
*Return:
    struct Item pointer to the beginning of the created list of Items
*/
struct Item *flashlightRoomItems(){
      struct Item *flashlightItems = itemCreate("", "",
                                        itemCreate("flashlight", "a portable hand-held electric light, luckily batteries are included", NULL));
        return flashlightItems;
}

/*
*Creates an Item with no name or description to serve as the head to the linked list of Items for rooms that initially have no items so Items can be added
*Return:
    struct Item pointer to the beginning of the created Item linked list head
*/
struct Item *nullItems(){
       struct Item *noItems = itemCreate("", "", NULL);
        return noItems;
}


/*
*Creates an Item with no name or description to serve as the head to the inventory Items linked list so Items can be added
*Returns
    struct Item pointer to the beginning of the created Item linked list head for the inventory
*/
struct Item *inventoryCreate(){
    struct Item *inventory = itemCreate("", "", NULL);
    return inventory;
}

/*
*Prints the list of inventory items
*Parameters
    inventory = the players inventory containing the list of all the items they are carrying
*/
void inventoryList(struct Item *inventory){
    struct Item *c = inventory->next; //Creates temporary Item pointer to navigate through the inventory list starting from Item after the head of list

    //If first Item is NULL, the inventory is empty
    if (c == NULL){
        printf("You are not carrying anything. \n\n");
        return;
    }

    //Goes through the inventory linked list of Items until NULL is reached printing out all the Item names and their descriptions 
    printf("You are currently holding the following: \n");
    while (c!=NULL){
        printf("%s: %s \n", c->name, c->description);
        c = c->next;
    }
    printf("\n");
    return;
}

/*
*Prints the item in the room when using the look command
*Parameters
    roomItem = the name of an item in a room to be printed
*/
void lookItems(char *roomItem){
    //Compares the name of roomItem to armor and prints message if armor is in room
    if (strcmp(roomItem, "armor") == 0){
        printf("There is armor nearby. \n");
        return;
    }

    //Compares the name of roomItem to chimera key and prints message if chimera key is in room
    if (strcmp(roomItem, "chimera key") == 0){
        printf("The chimera key is on the ground. \n");
        return;
    }

    //Compares the name of roomItem to barrel and prints message if barrel is in room
    else if (strcmp(roomItem, "barrel") == 0){
        printf("There is a barrel that looks very heavy. \n");
        return;
    }

    //Compares the name of roomItem to sword and prints message if sword is in room
    else if (strcmp(roomItem, "sword") == 0){
        printf("There is a sword nearby. \n");
        return;
    }

    //Compares the name of roomItem to flashlight and prints message if flashlight is in room
    else if (strcmp(roomItem, "flashlight") == 0){
        printf("There is a flashlight on the ground. \n");
        return;
    }
    
    //Compares the name of roomItem to lion key and prints message if lion key is in room
    else if (strcmp(roomItem, "lion key") == 0){
        printf("The lion key is laying on the floor. \n");
        return;
    }
    
    //Compares the name of roomItem to snake key and prints message if snake key is in room
    else if (strcmp(roomItem, "snake key") == 0){
        printf("The snake key is laying on the floor. \n");
        return;
    }
    
    //Compares the name of roomItem to goat key and prints message if goat key is in room
    else if (strcmp(roomItem, "goat key") == 0){
        printf("The goat key is laying on the floor. \n");
        return;
    }

    return;
}

/*
*Finds an item in a list of inventory/room items
*Parameters:
    list = list of Items (either Items in inventory or Items in room)
    itemName = name of Item to be removed
*Returns:
    Found Item pointer or NULL if Item not in list
*/
struct Item *findItem(struct Item *list, char *itemName){
    struct Item *temp = list->next; //Creates temporary Item pointer to navigate through the inventory list starting from Item after the head of list
    
    //Goes through the inventory linked list of Items until NULL is reached to find Item
    while (temp != NULL){

        //If the name of a Item in the list equals the itemName passed in, returns a pointer to it
        if (strncmp(temp->name, itemName, 5) == 0){
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

/*
*Removes item from list
*Parameters:
    items = list of Items to remove Items from
    curItem = name of Item to be removed
*Returns:
    Pointer to found Item to be removed
*/
struct Item *item_remove(struct Item *items, char *curItem){
    struct Item *temp = items->next; //Creates temporary Item pointer to navigate through the inventory list starting from Item after the head of list
    struct Item *prev = items; //Keeps track of the Item prior to the one temp points to in order to remove the Item after it
    
    //Goes through list of items to find item with the same name as curItem and remove it from Items list, then return a pointer to removed Item
    while (temp != NULL){
        if (strncmp(temp->name, curItem, 4) == 0){
            prev->next = temp->next;
            temp->next = NULL;
            return temp;
        }
        temp = temp->next;
        prev = prev->next;
    }
    return NULL;
}

/*
*Adds item to a list of 
*Parameters:
    lsit = list of Items to add Items to
    item = Item structure to be added
*Returns:
    Pointer to found Item to added
*/
struct Item *item_add(struct Item *list, struct Item *item){
    struct Item *itemsList = list; //Creates temporary Item pointer to navigate through the list of Items starting from Item after the head of list
    
    //Finds the end of the memoryItems linked list
    while (itemsList->next != NULL){
        itemsList = itemsList->next;
    }

    itemsList->next = item; //Adds item to the end of the list of Items
    return item;
}

/*
*Switches item from inventory/room and places the item in the room/inventory
*Parameters:
    currentItem = list of Items to remove from
    itemDest = list of Items to add to
    nameItem = name of the Item to swap
*Returns:
    Pointer to Item that is swapped or NULL if item was not found in the currentItem list
*/
struct Item *item_swap(struct Item *currentItem, struct Item *itemDest, char *nameItem){
    struct Item *insertItem = item_remove(currentItem, nameItem); //Checks if item with name given by nameItem is found in list of Items currentItem
    
    //If item is found in the list insert the item into the Item list itemDest
    if (insertItem != NULL){
        insertItem = item_add(itemDest, insertItem);
        return insertItem;
    }
    return NULL;
}

/*
*Drops an item from inventory into the room
*Parameters:
    inventory = player's inventory containing list of Items they are carrying
    curRoom = room player is currently in
    nameItem = name of item to be dropped
*Returns:
    True if using an item did not result in a death
    False if using an item resulted in a death
*/
bool item_drop(struct Item *inventory, struct Room *curRoom, char *nameItem){
    struct Item *room = curRoom->items; //List of items in the current room
    bool alive = true; //Initially sets alive to true

    //If the first Item in the inventory list is NULL the inventory is empty
    if (inventory->next == NULL){
        printf("You aren't carrying anything. \n\n");
        return alive;
    }
    
    //If there is a monster in the current room that is alive dropping an item results in death
    if (curRoom->monster){
        bool alive = monsterRoomAction(curRoom); //Checks which monster room you are in and returns false if you died 
        if (!alive){
            return false;
        }
    }

    struct Item *dropItem = item_swap(inventory, room, nameItem); //Take the item given by nameItem out of inventory Items list and places it into room Items list
    
    //If the nameItem was not found in inventory list the player is not holding that item
    if (dropItem == NULL){
        printf("You are not holding an item with that name. \n\n");
        return alive;
    }

    else{

        //If the item being dropped is armor, sets the players armor to false
        if (strncmp(nameItem, "armor", 5) == 0){
            printf("You have taken off your armor \n\n");
            ARMOR = false;
            return alive;
        }

        //If the item being dropped is flashlight, checks if in the dark room which results in a death
        else if (strncmp(nameItem, "flashlight", 5) == 0){
            bool alive = darkRoomCheck(curRoom);
            if (!alive){
                return false;
            }
        }

        printf("Ok. \n\n");
        return alive;
    }
}

/*
*Picks up an item from room and places it in inventory
*Parameters:
    curRoom = current room the player is in to take Item from
    inventory = player's inventory containing list of Items they are carrying
    nameItem = name of Item to be taken from room
*Return:
    False if killed through action of taking item
    True if the player is still alive after this action
*/
bool item_take(struct Room *curRoom, struct Item *inventory, char *nameItem){
    struct Item *room = curRoom->items; //List of items in the current room
    
    //If the first Item in the room list is NULL the current room has no items
    if (room->next == NULL){
        printf("There are no items to take in the room. \n\n");
        return true;
    }

    //If player is carrying the barrel, cannot pick up any more items
    if (findItem(inventory, "barrel") != NULL){
        printf("You can't pick anything up while carrying the barrel. \n\n");
        return true;
    }

    //If Item to be taken from the room is the barrel, cannot pick it up if player is holding any other items
    if (strncmp(nameItem, "barrel", 5) == 0){
        if (inventory->next != NULL){
            printf("This barrel is very heavy. Maybe if you empty your pockets you will be able to pick it up \n\n");
            return true;
        }
    }
    
    //If the room is dark, player cannot pick up anything
    if (curRoom->isDark){
        printf("You cannot see anything it is too dark. \n\n");
        return true;
    }

    //If there is a monster in the current room that is alive, taking an item results in death
    if(curRoom->monster){
        bool alive = monsterRoomAction(curRoom);
        if (!alive){
            return false;
        }   
    }

    struct Item *takeItem = item_swap(room, inventory, nameItem); //Take the item given by nameItem out of room Items list and places it into inventory Items list
    
    //If the item is not found in the room Items list, the item is not in the room and cannot be taken
    if (takeItem == NULL){
        printf("There is no item in the room with that name. \n\n");
        return true;
    }

    else{

        //Tells the player to use their armor to put it on
        if (strncmp(nameItem, "armor", 5) == 0){
            printf("Ok. You can use the armor to put it on! \n\n");
            return true;
        }

        //If the item taken from the room is the lion/goat/snake key, calls function that checks if player has all 3 keys in inventory and combines them into the master chimera key
        if ((strncmp(nameItem, "lion key", 4) == 0) || (strncmp(nameItem, "goat key", 4) == 0) || (strncmp(nameItem, "snake key", 5) == 0)){
            bool key = checkKeys(inventory); //Checks if player has all three keys and combines them to form master key
            
            //If all three keys were found, returns true
            if (key){
                return true;
            }
        }
        
        //If the item being taken from the room is the barrel and the player is in the scale room and the room controlled by the scale is unlocked, taking the barrel causes the door to relock
        if ((strncmp(nameItem, "barrel", 5) == 0) && (strcmp(curRoom->name, "scale room") == 0) && (curRoom->east->canEnter)){
            bool scale = scaleRoom(curRoom, inventory); //Taking the barrel changes the canEnter of the east room back to false indicating it has relocked
            
            //If taking the barrel caused the room to relock, returns true
            if (scale){
                return true;
            }
        }
        
        printf("Ok. \n\n");
        return true;
    }
}

/*
*Uses an item in a specific room
*Parameters
    curRoom = current room the player is in
    inventory = player's inventory containing list of Items they are carrying
    nameItem = name of the Item to be used
*Return:
    False if using an item resulted in a death
    True if using an item did not result in a death
*/
bool item_use(struct Room *curRoom, struct Item *inventory, char *nameItem){
    //If item to be used cannot be found and NULL is returned, item is not in the player's inventory
    if (findItem(inventory, nameItem) == NULL){
        printf("You are not carrying that item. \n\n");
        return true;
    }

    //If the item to be used is armor, calls function to put on armor
    else if (strncmp(nameItem, "armor", 5) == 0){
        useArmor();
        return true;
    }

    //If the item to be used is the chimera key, calls function for unlocking the door if in the correct room
    else if (strncmp(nameItem, "chimera key", 5) == 0){
        chimeraKeyRoom(curRoom); //Checks if player is in the room that chimera key unlocks the door to the next room if in correct room
        return true;
    }

    //If the item to be used is the barrel, calls function for unlocking the door connected to the scale when using the barrel in the correct room
    else if (strncmp(nameItem, "barrel", 5) == 0){
        scaleRoom(curRoom, inventory); //Checks if the player is in the scale room and unlocks the door to the next room if in the correct room
        return true;
    }

    //If the item to be used is the sword, calls function that checks if player is in a room with a monster and returns true if lived and killed monster or false if died
    else if (strncmp(nameItem, "sword", 5) == 0){
        bool alive = useSword(curRoom); //Checks if you are in a room with a monster and returns true if lived and killed monster or false if died
        return alive;
    }

    //If the item to be used is the flashlight, calls function that checks if player is in the dark room and makes it lit if it is still dark 
    else if (strncmp(nameItem, "flashlight", 5) == 0){
        darkRoom(curRoom); //Checks if player is in dark room and if it is dark, if it is using the flashlight causes the room to no longer be dark
        return true;
    }

    //If nameItem is none of these items, it is not an item that can be used 
    else{
        printf("This item cannot be used. \n\n");
        return true;
    }
}

/*
*Checks to see if player has all three keys in inventory, if they do it combines them into a master chimera key
*Parameters:
    inventory = the player's inventory containing a list of all Items player is carrying
*Return:
    True if player had all 3 keys and they combined into the chimera key
    False otherwise
*/
bool checkKeys(struct Item *inventory){
    struct Item *temp = inventory->next; //Creates temporary Item pointer to navigate through the list of Items starting from Item after the head of list
    int count = 0; //Counts the number of keys are in the player's inventory
    
    //Goes through list of Items in inventory and increases count if lion/goat/snake key is found
    while (temp != NULL){
        if ((strncmp(temp->name, "lion key", 4) == 0) || (strncmp(temp->name, "goat key", 4) == 0) || (strncmp(temp->name, "snake key", 5) == 0)){
            count++;
        }
        temp = temp->next;
    }
    
    //If player has all 3 keys they are combined into the chimera key
    if (count == 3){
        printf("You have collected all three keys. They have combined to form the master chimera key! \n\n");
        
        //Removes the 3 keys from the player's inventory
        item_remove(inventory, "snake key"); 
        item_remove(inventory, "goat key");
        item_remove(inventory, "lion key");

        struct Item *masterKey = itemCreate("chimera key", "a key depicting the 3 heads of a lion, a goat, and a snake", NULL); //Chimera key Item is created
        item_add(inventory, masterKey); //Chimera key added to inventory
        
        return true;
    }
    
    else{
        return false;
    }
}

/*
*Checks if player is in a room with a monster that is alive when performing an action other than using the sword- kills player if there is a monster
*Parameters:
    curRoom = current Room the player is in
*Return:
    False if you die trying to take an item in the room a monster is in
    True if you are not in a room with a monster or if monster is already dead
*/
bool monsterRoomAction(struct Room *curRoom){
    //If player is in the room with the ogre, prints message for ogre killing player defined by OGREKILL and returns false for a death
    if (strcmp(curRoom->name, "monster room L1") == 0){
        printf(OGREKILL);
        printf("\n");
        return false;
    }

    //If player is in the room with the troll, prints message for the troll killing player defined by TROLLKILL and returns false for a death
    else if (strcmp(curRoom->name, "monster room B1") == 0){
        printf(TROLLKILL);
        printf("\n");
        return false;
    }

    //If player is in the final room with the chimera, prints message for the chimera killing player defined by CHIMERAKILL and returns false for a death
    else if (strcmp(curRoom->name, "escape room") == 0){
        printf(CHIMERATAKEKILL);
        printf("\n");
        return false;
    }
    else{
        return true;
    }
}

/*
*Puts armor on the player
/*/
void useArmor(){
    printf("You put on the armor for protection. \n\n");
    ARMOR = true; //Sets global variable to armor to true
}    

/*
*Checks if player is in a room with a monster that is alive when using the sword and prints associated message based on monster
*Parameters:
    curRoom = current Room the player is in
*Return:
    False if you die trying to kill the monster
    True if you kill the monster and survive
*/
bool useSword(struct Room *curRoom){
    //If player is in the room with the ogre, calls function for killing the ogre if still alive
    if (strcmp(curRoom->name, "monster room L1") == 0){
        monsterRoomL1(curRoom); //Function for killing ogre in monster room L1
        return true;
    }

    //If player is in the room with the troll, calls function for killing the troll if still alive
    else if (strcmp(curRoom->name, "monster room B1") == 0){
        monsterRoomB1(curRoom); //Function for killing troll in monster room B1
        return true;
    }

    //If player is in the room with the boss chimera, calls function for battle between chimera and player and returns true if the player won or false if player died 
    else if (strcmp(curRoom->name, "escape room") == 0){
        bool alive = escapeRoom(curRoom); //Function that checks if player defeated chimera and won the game
        return alive;
    }

    //If the player is not in one of these monster rooms, the sword cannot be used 
    else{
        printf("This item cannot be used here. \n\n");
    }
}
