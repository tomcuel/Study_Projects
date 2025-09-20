#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


/////////////////////////////////////////////////////////////////////////////////////
// Defining all the constants that will be used in the game
// size of things or enum to simplify the code
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Defining the constants linked to the size of the window for the game
// 
// It can be adapted to any size to change the visuals of the game
// But everything will be based on those, so everything will need to be changed
// Because the same rendering will not work if we don't want to place the things at the same place
//
// The render done here for the following configuration : 
// - the chessboard is a square of 800x800 (a square, a case for a piece is 100x100)
// - the board is placed on the left side of the window, with a marge of 50 on the left
// - the top and bottom margin will display the palyer name, what pieces have been taken, and the points in advantage or disadvantage in the match
// - the right side of the window is used to display the moves, the menu button, the go-back menu, and many others things we need to do
/////////////////////////////////////////////////////////////////////////////////////
#define WINDOW_WIDTH 1400 // total width of the window
#define WINDOW_LEFT_MARGIN 50 // marge on the left of the chessboard
#define WINDOW_RIGHT_MARGIN 450 // marge on the right of the chessboard to print things 

#define WINDOW_HEIGHT 900 // height of the window
#define WINDOW_TOP_MARGIN 50 // marge on the top of the chessboard
#define WINDOW_BOTTOM_MARGIN 50 // marge on the bottom of the chessboard

#define SQUARE_SIZE 100 // size of a square on the chessboard
#define WINDOW_BOARD_SIZE 800 // size of the chessboard in the window


// to print numbers
#define FONT_WIDTH 50
#define FONT_HEIGHT 50

// to print the ":"
#define FONT_WIDTH_COLON 5
#define FONT_HEIGHT_COLON 40

/////////////////////////////////////////////////////////////////////////////////////
// Defining the constants linked to the size of the board (8x8 for a chess game)
// and some of its pieces (32 pieces in total, 2 others piece a pion can be promoted to)
/////////////////////////////////////////////////////////////////////////////////////
#define BOARD_SIZE 8
#define NUMBER_OF_PIECES 32
#define NUMBER_OF_NEIGHBORS_PAWN 4 // number of neighbors a pawn can have : here we consider one for each diagonal, one on its right and one on its left

/////////////////////////////////////////////////////////////////////////////////////
// Defining the game mode
/////////////////////////////////////////////////////////////////////////////////////
enum {PLAYER_VS_PLAYER, PLAYER_VS_AI};


/////////////////////////////////////////////////////////////////////////////////////
// Defining the difficulty of the AI 
/////////////////////////////////////////////////////////////////////////////////////
enum {NONE, EASY, MEDIUM, HARD};


/////////////////////////////////////////////////////////////////////////////////////
// Defining the time mode of the game
/////////////////////////////////////////////////////////////////////////////////////
enum {SHORT_BLITZ, LONG_BLITZ, SHORT, MODERATE, LONG};


/////////////////////////////////////////////////////////////////////////////////////
// Defining which player is playing
/////////////////////////////////////////////////////////////////////////////////////
enum {Player1, Player2};


/////////////////////////////////////////////////////////////////////////////////////
// Defining if a player is the IA or not
/////////////////////////////////////////////////////////////////////////////////////
enum {HUMAN, IA};


/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the type of the menus to start the game (Load_Menu), but also the Chessboard and the victory menu
/////////////////////////////////////////////////////////////////////////////////////
enum {GAMEPLAY_CHOICE, COLOR_CHOICE, DIFFICULTY_CHOICE, TIME_CHOICE, CHESSBOARD_RENDER, VICTORY_MENU}; 


/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the check state 
/////////////////////////////////////////////////////////////////////////////////////
enum {NO_CHECK, BLACK_CHECK, WHITE_CHECK, BLACK_CHECKMATE, WHITE_CHECKMATE, DRAW};


/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the two colors of the pieces 
/////////////////////////////////////////////////////////////////////////////////////
enum {NO_COLOR, WHITE, BLACK};


/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the pieces
// NOTHING is used to represent an empty square
/////////////////////////////////////////////////////////////////////////////////////
enum {NOTHING, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};


/////////////////////////////////////////////////////////////////////////////////////
// Constants to define the value of each piece
/////////////////////////////////////////////////////////////////////////////////////
#define PAWN_VALUE 1
#define KNIGHT_VALUE 3
#define BISHOP_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9
#define KING_VALUE 1000


/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the type of the rock move
/////////////////////////////////////////////////////////////////////////////////////
enum {NO_ROCK, SHORT_ROCK, LONG_ROCK};

/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the type of the promotion of the pawn for an En-Passant move
/////////////////////////////////////////////////////////////////////////////////////
enum {NO_EN_PASSANT,RIGHT_EN_PASSANT, LEFT_EN_PASSANT};

/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the type the name of the different buttons in the menu, next to the chessboard
// there are 21 buttons in total, there will do an array of buttons to get their state
/////////////////////////////////////////////////////////////////////////////////////
#define NUMBER_OF_BUTTONS 34

enum { 
    // during gameplay choice 
    PLAYER_VS_PLAYER_BUTTON,
    PLAYER_VS_AI_BUTTON, 
    QUIT_BUTTON_GAME_CHOICE,
    NEXT_BUTTON_GAME_CHOICE,

    // during the choices concerning the color we want to have to play against the IA
    BLACK_COLOR_BUTTON,
    WHITE_COLOR_BUTTON,
    QUIT_BUTTON_COLOR_CHOICE,
    MAIN_MENU_BUTTON_COLOR_CHOICE,
    BACK_BUTTON_COLOR_CHOICE,
    NEXT_BUTTON_COLOR_CHOICE,
    
    // choosing the difficulty of the IA
    EASY_DIFFICULTY_BUTTON,
    MODERATE_DIFFICULTY_BUTTON,
    HARD_DIFFICULTY_BUTTON,
    QUIT_BUTTON_IA_CHOICE,
    MAIN_MENU_BUTTON_IA_CHOICE,
    BACK_BUTTON_IA_CHOICE,
    NEXT_BUTTON_IA_CHOICE,

    // choosing the time mode menu
    SHORT_BLITZ_BUTTON,
    LONG_BLITZ_BUTTON,
    SHORT_BUTTON,
    MODERATE_BUTTON,
    LONG_BUTTON,

    QUIT_BUTTON_TIME_CHOICE,
    MAIN_MENU_BUTTON_TIME_CHOICE,
    BACK_BUTTON_TIME_CHOICE,
    LOAD_BUTTON, 

    // in game buttons
    START_BUTTON, 
    RESTART_BUTTON_IN_GAME,
    NEW_GAME_BUTTON_IN_GAME,
    QUIT_BUTTON_IN_GAME,
    UNDO_BUTTON,

    // in the victory menu
    NEW_GAME_BUTTON_VICTORY_MENU,
    RESTART_BUTTON_VICTORY_MENU,
    QUIT_BUTTON_VICTORY_MENU
};


/////////////////////////////////////////////////////////////////////////////////////
// Enum taht represents the state of each buttons 
// UNACTIVE : the button is not active, it's not been clicked
// ACTIVE : the button is active, it's been clicked
/////////////////////////////////////////////////////////////////////////////////////
enum {UNACTIVE, ACTIVE};


#endif /* __CONSTANTS_H__ */