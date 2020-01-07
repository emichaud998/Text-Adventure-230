//Header File for working with Rooms 

//If this header file has already been defined, do not recompile it. If not, define ADVENTURE_H and compile header file
#ifndef ROOMS_H
#define ROOMS_H

//Includes important C standard libraries
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//Room data structure
struct Room{
    char *name; //Name of the room
    char *description; //Description of the room
    struct Item *items; //Pointer to a list of Items found in the room
    struct Room *north; //Pointer to the room north
    struct Room *south; //Pointer to the room south
    struct Room *east; //Pointer to the room east
    struct Room *west; //Pointer to the room west
    struct Room *up; //Pointer to the room up
    struct Room *down; //Pointer to the room down
    
    bool canEnter; //True if the door into the room is unlocked, false if the door into the room is locked
    bool isDark; //True if the room is dark and you cannot see
    bool monster; //True if there is a monster that is alive in the room, false if there is no monster or the monster is dead
};

//Includes items header file and adventure header file (must define room structure first before including these files)
#include "items.h"
#include "adventure.h"

//Defines macros for Room Descriptions
#define STARTROOM "You are in a dimly lit room with chains on the walls. There are doors leading to the north, the west, and the south.\n"\
                        "There is also a staircase leading up."
#define DARKROOM "A blanket of darkness surrounds you. You cannot safely search or navigate the room."
#define L1MONSTER "An ugly ogre notices you and readies his masive club. He grunts as he stumbles towards you kicking bones out of the way."
#define LOCKROOM "You are in a room with walls covered in murals and giant statues depicting a lion, a goat, and a snake. An ironclad door \n"\
                        "with an engraved headless animal and three empty slots for the heads leads to the east. There is another door that leads \n"\
                        "south and a staircase that leads down in the corner."
#define SNAKEDOOR "You are in a room that is mostly full of cages with embalming tools strewn about. A strange door to the south has an engraved \n"\
                        "question that reads \"I giveth the kiss of death.\" The door has two large snake statues on either side. There is also a \n"\
                        "staircase that leads down."
#define ARMORY "You are in a room that looks like it is about to collapse. The ceiling is caving in and there is debris everywhere. \n"\
                        "The room seems to resemble an old armory. There is a door that leads north."
#define SCALEROOM "You are in a room that has a door to the east that is connected to a scale that will only activate under a heavy weight. \n"\
                        "There is also a door to the south and a staircase leading up."
#define SNAKEKEY "You are in a room that is crawling with snakes. There are stone serpent statues in each corner. There are remains of a human \n"\
                        "body holding a crumpled note, it reads \"The answer is Mamba.\" There is a door to the west."
#define FLASHLIGHTROOM "You are in a strange room full of modern equipment unlike any of the previous rooms. Machines are beeping and electricity \n"\
                        "seems to be flowing. There is a door that leads north and south."
#define B1MONSTER "A troll is awoken and you only see its three eyes. Its blood drenched fur smells of rotten flesh. Lumbering toward you, it roars."
#define NEWMONSTERL1 "The ogre lays lifeless in the center of the room which is drenched in blood and littered with bones and other human remains. \n"\
                        "There is a door to the north."
#define NEWMONSTERB1 "The dead troll lays propped against the stone wall. Animal carcass and feces scatter the damp dungeon floor. The smell of death \n"\
                        "is in the air. There is a door to the north."
#define LITDARKROOM "You are in an arsenal that has mostly been stripped clean. Broken weapons lay around in a clutter of steel. There is a door to the east."
#define CHIMERABOSSROOM "You are in a long throne room full of gold and precious gems. The Chimera looks at you with its three heads. One head of a lion \n"\
                        "on the front, one head of a goat on the torso, and a snake head as a tail. The Chimera roars as it lunges towards you. You see \n"\
                        "fire blazing from its mouth."

//Defines macros for events that happen in the game
#define DROPFLASH "The flashlight thuds on the ground. The darkness surrounds you and you hear something sneaking up on you. You turn to run, but trip over \n"\
                        "something metal. The flashlight flickers on and you see a ghostly figure before the darkess returns and you are strangled to death.\n"
#define OGREKILL "The ogre swings its large club which hurls you across the room into the stone wall. As you struggle to get up the ogre clobbers you with his club.\n"
#define TROLLKILL "The troll slashes at you with its claws. As you try to get away it grabs you and rips you limb from limb. The last thing you see is its three beady eyes.\n"
#define CHIMERALEAVEKILL "You run to the door, but struggle to get it open. It seems to be locked from the other side. As you try to pry it open, the \n"\
                        "Chimera pounces on you. The snake head bites you and you are injected with its lethal venom.\n"
#define YOUKILLOGRE "The ogre swings his massive club at you, but you slash at his arm with your sword. The ogre drops his weapon giving you the perfect \n"\
                        "opportunity to strike. A precise stab to the stomach makes the ogre fall to his knees and drop a shiny metallic object. Another \n"\
                        "swing of your sword finishes him. You have killed the ogre.\n"
#define YOUKILLTROLL "You dodge the slashes of the troll's claws. You parry another swipe and slash the troll's leg. The troll lets out a roar and drops \n"\
                        "a shiny metallic object. The massive beast falls. You plunge your sword into the middle of the three eyes. You have killed the troll.\n"
#define YOUKILLCHIMERA "The Chimera pounces at you baring its teeth. You dodge the lion head and cut off the goat head from its torso. The enraged Chimera \n"\
                        "shreiks in pain, it turns and breathes fire. Your armor protects you from the inferno. The Chimera bites at you with its snake head \n"\
                        "which you successfully parry and slice off. In a final effort, the Chimera charges and opens its jaws, prepared to crush you with its \n"\
                        "feline teeth. You wait for the last moment and  plunge your sword down its throat. You have killed the Chimera.\n"
#define NOARMOR "The Chimera pounces at you baring its teeth. You dodge the lion head and cut off the goat head from its torso. The enraged Chimera shreiks \n"\
                        "in pain, it turns and breathes fire. Your unprotected skin ignites instantly, you probably should have found some armor. The Chimera \n"\
                        "leaps forward and closes its razor sharp teeth on you as you burn.\n"
#define CHIMERATAKEKILL "While you are distracted, the Chimera rams you with its goat horns knocking you over. You are dazed and on the ground. \n"\
                        "The Chimera sinks its feline teeth into your flesh.\n"
# define CHIMERAMOVEKILL "You try to run but get trapped at a dead end with no where else to go. You hear the Chimera growl behind you as it slowly \n"\
                        "creeps towards you. As you turn around the Chimera charges forward and pierces you with it's sharp claws.\n"

//Function Prototypes 
struct Room *roomCreate(char *name, char *description, struct Item *items, struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Room *up, struct Room *down, bool enter, bool dark, bool monster); //Creates a Room structure
void room_exit_north(struct Room* current, struct Room* other); //Connects the "other" room north of the "current" room and the "current" room south of the "other" room
void room_exit_south(struct Room* current, struct Room* other); //Connects the "other" room south of the "current" room and the "current" room north of the "other" room
void room_exit_west(struct Room* current, struct Room* other); //Connects the "other" room west of the "current" room and the "current" room east of the "other" room
void room_exit_east(struct Room* current, struct Room* other); //Connects the "other" room east of the "current" room and the "current" room west of the "other" room
void room_exit_up(struct Room* current, struct Room* other); //Connects the "other" room up from the "current" room and the "current" room down from the "other" room
void room_exit_down(struct Room* current, struct Room* other); //Connects the "other" room down from the "current" room and the "current" room up from the "other" room
struct Room *room_setup(); //Creates all the rooms needed for the game and connects them to each other in the proper orientation
void room_look(struct Room *curRoom); //Prints out the description of the room the player is looking in
struct Room *move_north(struct Room *curRoom); //Moves the player north
struct Room *move_south(struct Room *curRoom); //Moves the player south
struct Room *move_east(struct Room *curRoom); //Moves the player east
struct Room *move_west(struct Room *curRoom); //Moves the player west
struct Room *move_up(struct Room *curRoom); //Moves the player up
struct Room *move_down(struct Room *curRoom); //Moves the player down
bool darkRoomCheck(struct Room *curRoom); //Checks if the room the player is in is dark when dropping the flashlight and kills the player if it is
void darkRoomLeave(struct Room *curRoom); //Makes the dark room dark again after leaving
bool monsterRoomLeave(struct Room *curRoom, char *direction); //Kills the player if they try to leave when there is a living monster in the room
struct Room *move(struct Room *curRoom, char *direction); //Moves the player in the direction typed in
void chimeraKeyRoom(struct Room *curRoom); //Unlocks the door into the final room to the final boss if player uses the key
bool scaleRoom(struct Room *curRoom, struct Item *inventory); //Unlocks the scale door if the player uses the barrel
void monsterRoomL1(struct Room *curRoom); //Kills the ogre monster on L1 when the player uses the sword
void monsterRoomB1(struct Room *curRoom); //Kills the troll monster on L1 when the player uses the sword
bool escapeRoom(struct Room *curRoom); //Kills the chimera monster on L1 when the player uses the sword
void darkRoom(struct Room *curRoom); //Makes the dark room lit so player can now see when they use the flashlight
void secretWord(struct Room *curRoom); //Unlocks the door into the armory when the player says the secret word "Mamba"

#endif 
