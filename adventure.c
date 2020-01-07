#include "adventure.h" //Includes the adventure header file

struct memoryRooms *roomsMemory; //Global pointer to list of dynamically created rooms- can be accessed by the other files
struct memoryItems *itemsMemory; //Global pointer to list of dynamically created items- can be accessed by the other files

/*
*Reads in a line until '\n' that the player types in to the standard input file and stores the line in buffer array
*Parameters:
    buffer = char array buffer to store the line read in from the standard input file
*/
void readLine(char buffer[MAX_LINE_LENGTH]){
    fgets(buffer, MAX_LINE_LENGTH, stdin);
}

/*
*Prints the instructions of the game when the user types in "help"
*HELP is defined to be the instructions of the game in the adventure.h header file
*/
void help(){
    printf(HELP);
    printf("\n");
}

/*
*Checks if at the end of the game the player is in the final boss room and the monster is dead
*Parameters:
    curRoom = The room the player is currently in
*Return:
    True if the game has been won- in final room and monster dead
    False if the game was not won- not in final room or final monster not dead and defeated player 
*/
bool gameWin(struct Room *curRoom){
    //Compares the name of the curRoom to the name of the final room ("escape room") and checks if there is an alive monster in curRoom
    if ((strcmp(curRoom->name, "escape room") == 0) && (!curRoom->monster)){ 
        return true;
    }
    
    return false;
}

/*
*Creates a memoryRooms structure to hold dynamically created Room structures to be freed later
*roomPointer points to a Room structure
*next points to the next memoryRooms structure in a linked list of memoryRooms holding all the dynamically created Room structures
*Return:
    A pointer to the newly created memoryRooms structure
*/
struct memoryRooms *createMemoryRooms(){
    struct memoryRooms *roomsMemory = (struct memoryRooms *)malloc(sizeof(struct memoryRooms)); //Dynamically creates the memoryRooms structure using malloc
    roomsMemory->roomPointer = NULL;
    roomsMemory->next = NULL;
}

/*
*Creates a memoryRoom structure to hold dynamically created Item structures to be freed later
*itemPointer points to an Item structure
*next points to the next memoryItems structure in a linked list of memoryItems holding all the dynamically created Item structures
*Return:
    A pointer to the newly created memoryItems structure
*/
struct memoryItems *createMemoryItems(){
    struct memoryItems *itemsMemory = (struct memoryItems *)malloc(sizeof(struct memoryItems)); //Dynamically creates the memoryItems structure using malloc
    itemsMemory->itemPointer = NULL;
    itemsMemory->next = NULL;
}

/*
*Frees the memory taken up by all the dynamically created Room structures and frees the dynamically created memoryRooms structures in the linked list pointed to
 by the global pointer memoryRooms.
*Sets all the pointers to NULL once all the allocated memory has been freed
*/
void freeRoomMemory(){
    struct memoryRooms *temp = roomsMemory; //temporary pointer set to roomsMemory (points to the beginning of the linked list of memoryRooms holding all the Rooms)
    struct memoryRooms *next = roomsMemory; //next pointer used to get the next memoryRooms in the linked list while temp is being freed
    
    //Goes through all the memoryRooms structures in the list, freeing all the Rooms and memoryRooms until it reaches NULL indicating the end of the list
    while (temp != NULL){
        next = temp->next; //Set to the next memoryRooms after temp so temp can be freed without losing the rest of the linked list
        free(temp->roomPointer); //Frees the Room pointed to by roomPointer
        free(temp); //Frees the memoryRoom structure
        temp = next; //temp is set to the next memoryRooms structure in the linked list
    }
    
    //All the pointers are set to NULL to prevent dangeling pointers
    temp = NULL;
    next = NULL;
    roomsMemory = NULL;
}

/*
*Frees the memory taken up by all the dynamically created Item structures and frees the dynamically created memoryItems structures in the linked list pointed to
 by the global pointer memoryItems.
*Sets all the pointers to NULL once all the allocated memory has been freed
*/
void freeItemMemory(){
    struct memoryItems *temp = itemsMemory; //temporary pointer set to itemsMemory (points to the beginning of the linked list of memoryItems holding all the Items)
    struct memoryItems *next = itemsMemory; //next pointer used to get the next memoryItems in the linked list while temp is being freed
    
    //Goes through all the memoryItems structures in the list, freeing all the Items and memoryItems until it reaches NULL indicating the end of the list
    while (temp != NULL){
        next = temp->next; //Set to the next memoryItems after temp so temp can be freed without losing the rest of the linked list
        free(temp->itemPointer); //Frees the Item pointed to by itemPointer
        free(temp); //Frees the memoryItem structure
        temp = next; //temp is set to the next memoryItems structure in the linked list
    }

    //All the pointers are set to NULL to prevent dangeling pointers
    temp = NULL;
    next = NULL;
    itemsMemory = NULL;
}


int main (void){

    //Welcomes to the game and prints instructions
    printf("Welcome to Dungeon Escape!\n");
    help(); //Function to print the instructions of the game

    roomsMemory = createMemoryRooms(); //Creates the first memoryRooms structure for the beginning of the linked list pointed to by roomsMemory
    itemsMemory = createMemoryItems(); //Creates the first memoryItems structure for the beginning of the linked list pointed to by itemsMemory

    struct Item *inventory = inventoryCreate(); //Creates the inventory for the game and sets the struct Item pointer inventory to the beginning of the inventory list of Items
    struct Room *currentRoom = room_setup(); //Creates all the rooms for the game and returns the starting room to the struct Room pointer currentRoom
    
    char buffer[MAX_LINE_LENGTH]; //buffer array is initalized with the MAX_LINE_LENGTH defined in adventure.h and is used to hold to lines read in through the standard input after calling readLine()
    char *action; //Points to what is left in the array buffer (a direction or item) after the command word (go/use/take/drop)
    bool quit = false; //Initially set to false and becomes to true if the player quits the game
    bool alive = true; //Represents if the player is alive- true to start and becomes to false if the player dies in the game
    bool wonGame = false; //Initially set to false because the game has not been won and becomes true if the game has been won

    room_look(currentRoom); //Prints the description of the starting room the player is in

    /*
    *While loop will continue while alive is true (player is alive), wonGame is false (the player has not won yet), and currentRoom is not NULL (the player hasn't died trying to move)
    *reads in a command typed in by the player to the standard input and does the command the player typed in until the game is over
    */
    while (alive && !wonGame && (currentRoom != NULL)){
        printf("What's next? ");
        readLine(buffer); //Reads in a command typed in by the user to the standard input and stores the line in the array buffer

        //Allows the player to move if the first word in buffer is go
        if (strncmp(buffer, "go", 2) == 0){

            //Stores the next word after go in action if there was another word typed in
            if (buffer[3] != '\0'){ //Checks if there were more words typed after "go " in buffer
                action = buffer+3; //Sets action char pointer to the string after "go " in buffer- should be a direction
                currentRoom = move(currentRoom, action); //Function to move the player in the direction typed in and pointed to by action- sets currentRoom to NULL if the move resulted in a death
            }
            //If nothing is typed in after "go " the while loop goes back to the start and the player begins their turn again
            else{
                printf("Need a direction. \n\n");
                continue;   
            }   
        }
        
        //Allows the player to use a specific item if the first word stored in buffer is use
        else if (strncmp(buffer, "use", 3) == 0){
            if (buffer[4] != '\0'){ //Checks if there were more words typed after "use " in buffer
                action = buffer+4; //Sets action char pointer to the string after "use " in buffer- should be name of an item in inventory
                alive = item_use(currentRoom, inventory, action); //Function to use an item found in the inventory- false if resulted in death
                wonGame = gameWin(currentRoom); //Checks if using the item caused the game to be won (this could happen when the player uses the sword)
            }
            //If nothing is typed in after "use " the while loop goes back to the start and the player begins their turn again
            else{
                printf("Need an item. \n\n");
                continue;
            }
        }       

        //Allows the player to take a specific item in a room if the first word stored in buffer is take
        else if (strncmp(buffer, "take", 4) == 0){
            if (buffer[5] != '\0'){ //Checks if there were more words typed after "take " in buffer
                action = buffer+5; //Sets action char pointer to the string after "take " in buffer- should be name of an item in the current room
                alive = item_take(currentRoom, inventory, action); //Function to take an item found in the current room of player- false if resulted in death
            }
            //If nothing is typed in after "take " the while loop goes back to the start and the player begins their turn again
            else{
                printf("Need an item. \n\n");
                continue;
            }
        }

        //Allows the player to drop a specific item from their inventory into the current room if the first word stored in buffer is drop
        else if (strncmp(buffer, "drop", 4) == 0){
            if (buffer[5] != '\0'){ //Checks if there were more words typed after "drop " in buffer
                action = buffer+5; //Sets action char pointer to the string after "drop " in buffer- should be name of an item in inventory
                alive = item_drop(inventory, currentRoom, action); //Function to drop an item found in the player's inventory - false if this action caused a death
            }
            //If nothing is typed in after "drop " the while loop goes back to the start and the player begins their turn again
            else{
                printf("Need an item. \n\n");
                continue;
            }
        }

        //Prints out the inventory if the first word in buffer is inventory
        else if (strncmp(buffer, "inventory", 9) == 0){
            inventoryList(inventory); //Function to print the items being held in the player's inventory
        }

        //Allows the player to look at the room by getting the description of the current room and the items in that room if the first word stored in buffer is look
        else if (strncmp(buffer, "look", 4) == 0){
            room_look(currentRoom); //Function to print description of current room and items in the room
        }

        //Unlocks the secret door into the armory if the first word stored in buffer is Mamba or mamba
        else if ((strncmp(buffer, "Mamba", 5) == 0) || (strncmp(buffer, "mamba", 5) == 0)){
            secretWord(currentRoom); //Function to unlock the door if the secret word was said in the right room
        }
        
        //Prints out the instructions if the first word stored in buffer is help
        else if (strncmp(buffer, "help", 4) == 0){
            help(); //Prints the instructions
        }
        
        //Causes the game to exit and quit if the first word stored in buffer is quit
        else if (strncmp(buffer, "quit", 4) == 0){
            quit = true; 
            break; //Breaks out of the while loop since the game is over
        }
        
        //If the first word stored in buffer is not any of the listed command words, while loop starts over and a new line is read into buffer
        else{
            printf("I don't understand that. \n\n");
        }
    }
    
    //Prints out appropriate message if player quit game- quit set to true
    if (quit){
        printf("You quit the game.\n");
        printf("GAME OVER. \n");
    }

    //Prints out appropriate message if the player died during the game 
    else if (alive == false || currentRoom == NULL){ //If alive was set to false or currentRoom equals NULL this implies the player died
        printf("You have died.\n"); 
        printf("GAME OVER.\n");
    }
    
    //Prints out appropriate message if the player has won the game- wonGame set to true
    else if(wonGame){
        printf("You have defeated the Chimera and escaped! \n");
        printf("YOU WIN. \n");
    }

    //Functions to free all the dynamically created structures
    freeItemMemory();
    freeRoomMemory();

    return 0;
}
