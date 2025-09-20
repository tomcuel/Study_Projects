# Introduction 

Here is a project to be carried out during a computer science course.
Our job is to code a chess game in C using the SDL library.
I keep upgrading it further than the presented version for my lesson from the V6 (up until V7 where it's completed)

# About SDL
Here's the website to find out more about this library (which allows us to make graphics and play on them, for example): 
- https://www.libsdl.org / https://wiki.libsdl.org/SDL2/FrontPage for everything, with installation setup or link to the code of the SDL 
- the wiki_lib is very useful to be able to easily search function, things that can be done and how to implement, it's making us gain time
- --> one way to do it is by searching from the type of category of functions that act on differents parts : https://wiki.libsdl.org/SDL2/APIByCategory
- --> the other way is by searching the name, but it requires to know well the library and what it can do : https://wiki.libsdl.org/SDL2/CategoryAPI
- I've tried to download the ttf extension to use fonts but I haven't been able to do so at the beginning, thus the graphics aren't quite what I could have done with it, but still I've been able do pretty much what I wanted, I succeed to make it work but too late, it will only be useful in other project related to improve it 

# What I need to do 
I will have various tasks to complete as part of this project: 
- reproduce the game of chess and its many rules 
- create a graphical interface that is fun to play on (with some tests to try, know how to use it)
- code an AI to play against, with different levels 

# Concerning the tests
- tests of the structure will be done separetely in specific folders, but things such as checking if a piece can move will done in the different versions of the game 

# To run this project : 
- do the command "make" to create all the .o and .x file to run them 
- do the command "make realclean" to clean all the .x and .o file everywhere in the project
- go to the directory you want and do the command "make" to create the .o and the .x file, to run your code
- because most of the directories will just be there for testing, to make it more practical to get used to the differents parts of the code

# To play the game : 
- click on buttons, depending on the button you will need to do it twice to make sure that it was really what was attended (to confirm it)
- some parameters to choose how to play the game will be chosen through differents menus
- to start the timer in the game, you will need to press only once the button start
- then you can play the game, but also quitting it or doing a lot of different things during it 
- a victory menu suggests you some ways you would like to continue the game into 

# Concerning what has been done :

## The test folders : 
- you fill find all the tests I've made, the name give you the idea of what has been done in those folders
## V1 :
- it was a first implementation of the render and the move I could do without any rules 
## V2 : 
- it was the adding of the different menu and how I could pass from one to another, a timer was created in the terminal (moves are still illegal)
## V3 : 
- I added a lot of features : 
- the showing of the timer and the captured piece
- move that were legal (without the check), including special moves (rock, en passant)
- udpate on the differents structures after the move
- implementation of the buttons in the menus
- the basic IA (!!! make the code crash here if level 2 and 3 are selected, and it doesn't work as expected, will be fixed in V4, no ending)
## V4 : 
- fixes the problems of the IA and add the intermediate level
- also adds the pawn promotion, the undo button
- and all that is related to the check (as well as Checkmate and Stalemate)
## V5 : 
- adding littles features linked to stalemate conditions
- parsing more into separate functions using references to others folders
- adding an IA using the alpha_beta_pruning algorithm with a very basic heuristic (will need to be upgraded later on), the depth need to be changed by hands in the IA.c file, but later on it will not be the case (warning a depth above 3 take very long for now)
## V6 : 
- The victory display menu is now a blur with the chess game in the background 
- Reversing the board when it's up to the black to play (1v1 game or 1vIA) 
- Fixing some bugs linked to the code 
- Timer will also work for the IA 
- Adding the IAvIA type of match where you can select which level of IA will play against which level of IA
- Changing how the menus looks concerning the difficulty choices and the gameplay mode 
- Warning : only the EASY and MEDIUM IA level are working in this version 
## V7 : 
- Adding the pause and the delay to be able to see the IA make its moves and to undo a certain amount of moves
- Sevelopment of the IA by changing the heuristic by ordering moves, suggesting moves depending on the state of the game
- Iterative deepening (transposition table to gain time with hashing function (string with letters corresponding to a board and score calculated for a certain move on this board) if possible, and an opening book) to make a compromise between searching the best play and managing time, but also suggestions concerning the moves to do depending on the part of the game we're in will not be done here, but I could have done it if the game was optimized for it, it should have consider bitboard on the first place instaed of array of structures to gain a lot of time during searchs
- I don't know why but IA Medium vs IA Hard in depth 2 does crash when the match is played between these two, it's mostly due to the game that isn't optimized, I could have use bitboard to represent things

# Structure of the code : 

## .h file : 
- - will have the explications concerning the description of the function and what I will used for 
- - will also give the parameters the function is taking 
- - code structure : 

#ifndef __FILENAME_H__
#define __FILENAME_H__


/////////////////////////////////////////////////////////////////////////////////////
// Filename Summary : 
/**
 *
 * 
 … 
 Resume of the different functions we can find on this file
 …
 *
**/
/////////////////////////////////////////////////////////////////////////////////////


#include <…>

…
…

#include <…>


/////////////////////////////////////////////////////////////////////////////////////
// Description of what the function is doing 
/**
 * @param parameter1 - description of parameter_1
 * @param parameter1 - description of parameter_2

 * …
 * …

 * @param parameter1 - description of parameter_n
**/ 
/////////////////////////////////////////////////////////////////////////////////////
header of the function 


…
make other function
…


/////////////////////////////////////////////////////////////////////////////////////
// Description of what the function is doing 
/**
 * @param parameter1 - description of parameter_1
 * @param parameter1 - description of parameter_2

 * …
 * …

 * @param parameter1 - description of parameter_n
**/ 
/////////////////////////////////////////////////////////////////////////////////////
header of the function 


#endif /* __FILENAME_H__ */


## .c file  : 
- - will not include the header, but it will be commented to know what are the things done inside the function
- - code structure : (spacing the code to make it easy to copy and to understand)

#include "filename.h"


function_1


function_2


…
…



function_n