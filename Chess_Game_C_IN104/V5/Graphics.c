#include "Graphics.h"


// for the printing of the timer, we will use the font array
const int font[10][FONT_WIDTH] = {
    {0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E}, // 0
    {0x00, 0x00, 0x42, 0x82, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00}, // 1
    {0x00, 0x42, 0x87, 0x89, 0x91, 0xA1, 0xC1, 0x42, 0x00, 0x00}, // 2
    {0x42, 0x81, 0x81, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 3
    {0x18, 0x28, 0x48, 0x88, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x00}, // 4
    {0xF2, 0x91, 0x91, 0x91, 0x91, 0x91, 0x89, 0x86, 0x00, 0x00}, // 5
    {0x7E, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x0E, 0x00, 0x00}, // 6
    {0x80, 0x80, 0x81, 0x82, 0x84, 0x88, 0x90, 0xE0, 0x00, 0x00}, // 7
    {0x76, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 8
    {0x72, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x7E, 0x00, 0x00}  // 9
};

// Define the colon character
const int colon[FONT_HEIGHT_COLON] = {
    0x00, // .....
    0x00, // .....
    0x00, // .....
    0x18, // ...xx
    0x18, // ...xx
    0x00, // .....
    0x18, // ...xx
    0x18  // ...xx
};


Button** Create_Buttons(int number_of_buttons){
    Button** Buttons = (Button**)malloc(number_of_buttons * sizeof(Button*));
    // looking for a malloc error
    if (Buttons == NULL){
        printf("Error: malloc failed in Create_Buttons\n");
        return NULL;
    }

    // for each button, we create it
    for (int i = 0; i < number_of_buttons; i++){
        Buttons[i] = (Button*)malloc(sizeof(Button));
        // looking for a malloc error
        if (Buttons[i] == NULL){
            printf("Error: malloc failed in Create_Buttons\n");
            return NULL;
        }
        // setting the state to UNACTIVE for every button
        Buttons[i]->state = UNACTIVE;
    }

    // buttons for the load menu : game play choice
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.y = 50;
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.w = 300;
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.h = 200;

    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x = 250;
    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y = 300;
    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w = 300;
    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h = 200;

    Buttons[PLAYER_VS_AI_BUTTON]->rect.x = WINDOW_WIDTH-250-300;
    Buttons[PLAYER_VS_AI_BUTTON]->rect.y = 300;
    Buttons[PLAYER_VS_AI_BUTTON]->rect.w = 300;
    Buttons[PLAYER_VS_AI_BUTTON]->rect.h = 200;

    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x = 250;
    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w = 300;
    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h = 200;

    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.x = WINDOW_WIDTH-250-300;
    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.y = 650;
    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.w = 300;
    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.h = 200;


    // buttons for the color choice menu
    Buttons[COLOR_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[COLOR_CHOICE_BUTTON]->rect.y = 50;
    Buttons[COLOR_CHOICE_BUTTON]->rect.w = 300;
    Buttons[COLOR_CHOICE_BUTTON]->rect.h = 200;

    Buttons[BLACK_COLOR_BUTTON]->rect.x = 250;
    Buttons[BLACK_COLOR_BUTTON]->rect.y = 300;
    Buttons[BLACK_COLOR_BUTTON]->rect.w = 300;
    Buttons[BLACK_COLOR_BUTTON]->rect.h = 200;

    Buttons[WHITE_COLOR_BUTTON]->rect.x = WINDOW_WIDTH-550;
    Buttons[WHITE_COLOR_BUTTON]->rect.y = 300;
    Buttons[WHITE_COLOR_BUTTON]->rect.w = 300;
    Buttons[WHITE_COLOR_BUTTON]->rect.h = 200;
    
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x = 50;
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h = 150;

    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 - 70 - 225;
    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h = 150;

    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 + 70;
    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h = 150;

    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 225;
    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.h = 150;


    // buttons for the difficulty choice menu
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.y = 50;
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.w = 300;
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.h = 200;

    Buttons[EASY_DIFFICULTY_BUTTON]->rect.x = 100;
    Buttons[EASY_DIFFICULTY_BUTTON]->rect.y = 300;
    Buttons[EASY_DIFFICULTY_BUTTON]->rect.w = 300;
    Buttons[EASY_DIFFICULTY_BUTTON]->rect.h = 200;

    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.y = 300;
    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.w = 300;
    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.h = 200;

    Buttons[HARD_DIFFICULTY_BUTTON]->rect.x = WINDOW_WIDTH-400;
    Buttons[HARD_DIFFICULTY_BUTTON]->rect.y = 300;
    Buttons[HARD_DIFFICULTY_BUTTON]->rect.w = 300;
    Buttons[HARD_DIFFICULTY_BUTTON]->rect.h = 200;

    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.x = 50;
    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.h = 150;

    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.x = WINDOW_WIDTH/2 - 70 - 225;
    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.h = 150;

    Buttons[BACK_BUTTON_IA_CHOICE]->rect.x = WINDOW_WIDTH/2 + 70;
    Buttons[BACK_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[BACK_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[BACK_BUTTON_IA_CHOICE]->rect.h = 150;

    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 225;
    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.h = 150;


    // buttons for the time choice menu
    Buttons[TIME_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[TIME_CHOICE_BUTTON]->rect.y = 50;
    Buttons[TIME_CHOICE_BUTTON]->rect.w = 300;
    Buttons[TIME_CHOICE_BUTTON]->rect.h = 200;

    Buttons[SHORT_BLITZ_BUTTON]->rect.x = 100;
    Buttons[SHORT_BLITZ_BUTTON]->rect.y = 50;
    Buttons[SHORT_BLITZ_BUTTON]->rect.w = 300;
    Buttons[SHORT_BLITZ_BUTTON]->rect.h = 200;

    Buttons[LONG_BLITZ_BUTTON]->rect.x = WINDOW_WIDTH-300-100;
    Buttons[LONG_BLITZ_BUTTON]->rect.y = 50;
    Buttons[LONG_BLITZ_BUTTON]->rect.w = 300;
    Buttons[LONG_BLITZ_BUTTON]->rect.h = 200;

    Buttons[SHORT_BUTTON]->rect.x = 100;
    Buttons[SHORT_BUTTON]->rect.y = 300;
    Buttons[SHORT_BUTTON]->rect.w = 300;
    Buttons[SHORT_BUTTON]->rect.h = 200;

    Buttons[MODERATE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[MODERATE_BUTTON]->rect.y = 300;
    Buttons[MODERATE_BUTTON]->rect.w = 300;
    Buttons[MODERATE_BUTTON]->rect.h = 200;

    Buttons[LONG_BUTTON]->rect.x = WINDOW_WIDTH-400;
    Buttons[LONG_BUTTON]->rect.y = 300;
    Buttons[LONG_BUTTON]->rect.w = 300;
    Buttons[LONG_BUTTON]->rect.h = 200;

    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x = 50;
    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w = 225;
    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h = 150;

    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x = WINDOW_WIDTH/2 - 70 - 225;
    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y = 650;
    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w = 225;
    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h = 150;

    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.x = WINDOW_WIDTH/2 + 70;
    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.y = 650;
    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.w = 225;
    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.h = 150;

    Buttons[LOAD_BUTTON]->rect.x = WINDOW_WIDTH - 50 - 225;
    Buttons[LOAD_BUTTON]->rect.y = 650;
    Buttons[LOAD_BUTTON]->rect.w = 225;
    Buttons[LOAD_BUTTON]->rect.h = 150;


    // buttons for the chessboard
    Buttons[START_BUTTON]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[START_BUTTON]->rect.y = 50;
    Buttons[START_BUTTON]->rect.w = 170;
    Buttons[START_BUTTON]->rect.h = 100;

    Buttons[RESTART_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[RESTART_BUTTON_IN_GAME]->rect.y = 200;
    Buttons[RESTART_BUTTON_IN_GAME]->rect.w = 170;
    Buttons[RESTART_BUTTON_IN_GAME]->rect.h = 100;

    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.y = 350;
    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.w = 170;
    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.h = 100;

    Buttons[QUIT_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[QUIT_BUTTON_IN_GAME]->rect.y = 500;
    Buttons[QUIT_BUTTON_IN_GAME]->rect.w = 170;
    Buttons[QUIT_BUTTON_IN_GAME]->rect.h = 100;

    Buttons[UNDO_BUTTON]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[UNDO_BUTTON]->rect.y = 750;
    Buttons[UNDO_BUTTON]->rect.w = 170;
    Buttons[UNDO_BUTTON]->rect.h = 100;

    Buttons[PAWN_PROMOTION_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[PAWN_PROMOTION_BUTTON]->rect.y = 50;
    Buttons[PAWN_PROMOTION_BUTTON]->rect.w = 170;
    Buttons[PAWN_PROMOTION_BUTTON]->rect.h = 100;

    Buttons[QUEEN_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[QUEEN_BUTTON]->rect.y = 250;
    Buttons[QUEEN_BUTTON]->rect.w = 170;
    Buttons[QUEEN_BUTTON]->rect.h = 100;

    Buttons[ROOK_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[ROOK_BUTTON]->rect.y = 400;
    Buttons[ROOK_BUTTON]->rect.w = 170;
    Buttons[ROOK_BUTTON]->rect.h = 100;

    Buttons[BISHOP_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[BISHOP_BUTTON]->rect.y = 550;
    Buttons[BISHOP_BUTTON]->rect.w = 170;
    Buttons[BISHOP_BUTTON]->rect.h = 100;

    Buttons[KNIGHT_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[KNIGHT_BUTTON]->rect.y = 700;
    Buttons[KNIGHT_BUTTON]->rect.w = 170;
    Buttons[KNIGHT_BUTTON]->rect.h = 100;


    // buttons for the victory menu
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.x = 50;
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.y = 50;
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.w = 300;
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.h = 200;

    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH-50-300;
    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.y = 50;
    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.w = 300;
    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.h = 200;

    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.x = 50;
    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.y = 650;
    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.w = 300;
    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.h = 200;

    Buttons[UNDO_ENDING_MOVE_BUTTON]->rect.x = WINDOW_WIDTH-50-300;
    Buttons[UNDO_ENDING_MOVE_BUTTON]->rect.y = 650;
    Buttons[UNDO_ENDING_MOVE_BUTTON]->rect.w = 300;
    Buttons[UNDO_ENDING_MOVE_BUTTON]->rect.h = 200;


    // return the array of buttons
    return Buttons;
}


void Reset_Buttons_State(Button** Buttons){
    // for each button, we set the state to UNACTIVE
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
        Buttons[i]->state = UNACTIVE;
    }
}


void Destroy_Buttons(int number_of_buttons, Button** Buttons){
    // for each button, we free it
    for (int i = 0; i < number_of_buttons; i++){
        if (Buttons[i] != NULL){
            free(Buttons[i]);
        }
    }

    // free the array of buttons
    if (Buttons != NULL){
        free(Buttons);
    }
}


void Show_Load_Menu(SDL_Renderer* renderer, int menu_type, Button** Buttons, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move){
    
    SDL_Rect rect_full_screen;
    rect_full_screen.x = 0;
    rect_full_screen.y = 0;
    rect_full_screen.w = WINDOW_WIDTH;
    rect_full_screen.h = WINDOW_HEIGHT;
    add_image_to_render("../Images/Buttons/wall_paper.bmp", renderer, rect_full_screen);

    // if the menu is the gameplay choice menu
    if (menu_type==GAMEPLAY_CHOICE){
        
        // buttons to choose a 1vs1 game
        if (Buttons[PLAYER_VS_PLAYER_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Two_Player_Button.bmp", renderer, Buttons[PLAYER_VS_PLAYER_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Two_Player_Button.bmp", renderer, Buttons[PLAYER_VS_PLAYER_BUTTON]->rect);
        }
        // buttons to choose a 1vsIA game
        if (Buttons[PLAYER_VS_AI_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_One_Player_Button.bmp", renderer, Buttons[PLAYER_VS_AI_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_One_Player_Button.bmp", renderer, Buttons[PLAYER_VS_AI_BUTTON]->rect);
        }

        // button to quit the game
        add_image_to_render("../Images/Buttons/Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_GAME_CHOICE]->rect);

        // button to go to the next menu
        add_image_to_render("../Images/Buttons/Next_Button.bmp", renderer, Buttons[NEXT_BUTTON_GAME_CHOICE]->rect);

        // add the button to see that we're in the gameplay choice menu
        add_image_to_render("../Images/Buttons/Gameplay_Choice_Button.bmp", renderer, Buttons[GAMEPLAY_CHOICE_BUTTON]->rect);

    }

    // if the menu is linked to the color choice 
    else if (menu_type == COLOR_CHOICE){
        
        // adding the black color button 
        if (Buttons[BLACK_COLOR_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Black_Button.bmp", renderer, Buttons[BLACK_COLOR_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Black_Button.bmp", renderer, Buttons[BLACK_COLOR_BUTTON]->rect);
        }
        // adding the white color button
        if (Buttons[WHITE_COLOR_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_White_Button.bmp", renderer, Buttons[WHITE_COLOR_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_White_Button.bmp", renderer, Buttons[WHITE_COLOR_BUTTON]->rect);
        }

        // button to quit the IA choice menu and the game also
        add_image_to_render("../Images/Buttons/Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_IA_CHOICE]->rect);

        // button to go back to the main menu
        add_image_to_render("../Images/Buttons/Main_Menu_Button.bmp", renderer, Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect);

        // button to go back to the gameplay choice menu, with a back button
        add_image_to_render("../Images/Buttons/Back_Button.bmp", renderer, Buttons[BACK_BUTTON_IA_CHOICE]->rect);

        // button to go to the next menu
        add_image_to_render("../Images/Buttons/Next_Button.bmp", renderer, Buttons[NEXT_BUTTON_IA_CHOICE]->rect);

        // button to see that we're in the color choice menu
        add_image_to_render("../Images/Buttons/Color_Choice_Button.bmp", renderer, Buttons[COLOR_CHOICE_BUTTON]->rect);

    }

    // if the menu is the difficulty choice menu of the IA 
    else if (menu_type==DIFFICULTY_CHOICE){

        // adding the easy difficulty button
        if (Buttons[EASY_DIFFICULTY_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Easy_Button.bmp", renderer, Buttons[EASY_DIFFICULTY_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Easy_Button.bmp", renderer, Buttons[EASY_DIFFICULTY_BUTTON]->rect);
        }
        // adding the moderate difficulty button
        if (Buttons[MODERATE_DIFFICULTY_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Moderate_Button.bmp", renderer, Buttons[MODERATE_DIFFICULTY_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Moderate_Button.bmp", renderer, Buttons[MODERATE_DIFFICULTY_BUTTON]->rect);
        }
        // adding the hard difficulty button
        if (Buttons[HARD_DIFFICULTY_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Hard_Button.bmp", renderer, Buttons[HARD_DIFFICULTY_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Hard_Button.bmp", renderer, Buttons[HARD_DIFFICULTY_BUTTON]->rect);
        }

        // button to quit the IA choice menu and the game also
        add_image_to_render("../Images/Buttons/Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_IA_CHOICE]->rect);

        // button to go back to the main menu
        add_image_to_render("../Images/Buttons/Main_Menu_Button.bmp", renderer, Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect);

        // button to go back to the gameplay choice menu, with a back button
        add_image_to_render("../Images/Buttons/Back_Button.bmp", renderer, Buttons[BACK_BUTTON_IA_CHOICE]->rect);

        // button to go to the next menu
        add_image_to_render("../Images/Buttons/Next_Button.bmp", renderer, Buttons[NEXT_BUTTON_IA_CHOICE]->rect);

        // button to see that we're in the difficulty choice menu
        add_image_to_render("../Images/Buttons/Difficulty_of_the_IA_Button.bmp", renderer, Buttons[DIFFICULTY_CHOICE_BUTTON]->rect);
        
    }

    // if the menu is the time choice menu
    else if (menu_type==TIME_CHOICE){
        
        // short blitz button
        if (Buttons[SHORT_BLITZ_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Short_Blitz_Button.bmp", renderer, Buttons[SHORT_BLITZ_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Short_Blitz_Button.bmp", renderer, Buttons[SHORT_BLITZ_BUTTON]->rect);
        }
        // long blitz button
        if (Buttons[LONG_BLITZ_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Long_Blitz_Button.bmp", renderer, Buttons[LONG_BLITZ_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Long_Blitz_Button.bmp", renderer, Buttons[LONG_BLITZ_BUTTON]->rect);
        }
        // short game button
        if (Buttons[SHORT_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Short_Time_Button.bmp", renderer, Buttons[SHORT_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Short_Time_Button.bmp", renderer, Buttons[SHORT_BUTTON]->rect);
        }
        // moderate game button
        if (Buttons[MODERATE_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Moderate_Time_Button.bmp", renderer, Buttons[MODERATE_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Moderate_Time_Button.bmp", renderer, Buttons[MODERATE_BUTTON]->rect);
        }
        // long game button
        if (Buttons[LONG_BUTTON]->state == ACTIVE){
            add_image_to_render("../Images/Buttons/Active_Long_Time_Button.bmp", renderer, Buttons[LONG_BUTTON]->rect);
        }
        else{
            add_image_to_render("../Images/Buttons/Unactive_Long_Time_Button.bmp", renderer, Buttons[LONG_BUTTON]->rect);
        }

        // button to quit the time choice menu and the game also 
        add_image_to_render("../Images/Buttons/Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_TIME_CHOICE]->rect);

        // button to load the game
        add_image_to_render("../Images/Buttons/Load_Button.bmp", renderer, Buttons[LOAD_BUTTON]->rect);

        // button to go back to the main menu
        add_image_to_render("../Images/Buttons/Main_Menu_Button.bmp", renderer, Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect);

        // button to go back to the IA choice menu, with a back button
        add_image_to_render("../Images/Buttons/Back_Button.bmp", renderer, Buttons[BACK_BUTTON_TIME_CHOICE]->rect);

        // button to see that we're in the time choice menu
        add_image_to_render("../Images/Buttons/Time_Choice_Button.bmp", renderer, Buttons[TIME_CHOICE_BUTTON]->rect);

    }

    // we draw if needed the rectangle around a selected piece
    // if a piece is clicked, we draw a red boundary around it
    if (is_clicked_1 == 1 && is_clicked_2 == 0){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderDrawRect(renderer, &draw_red_boundary_move); 
        // we draw the line around the piece 
        // we wanted to make it thicker so here is a way to do it, don't know if it's the best way

        // Draw top line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + i);
        }

        // Draw right line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y + draw_red_boundary_move.h);
        }

        // Draw bottom line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + draw_red_boundary_move.h - i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + draw_red_boundary_move.h - i);
        }

        // Draw left line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + i, draw_red_boundary_move.y, draw_red_boundary_move.x + i, draw_red_boundary_move.y + draw_red_boundary_move.h);
        }
    }

}   


void Show_Chess_Board(SDL_Renderer* renderer, Piece*** board, Move_Log_array* Move_Log_Array, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move){


    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    // making the empty chessboard
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            rect.x = j * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
            rect.y = i * SQUARE_SIZE+WINDOW_TOP_MARGIN;
            if ((i + j) % 2 == 0) {
                // case light square
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255); // light square color
            }
            else {
                // case dark square
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255); // dark square color
            }
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // if a check is happening, we draw a red square on the case where the king is before printing the pieces
    if (Is_Check(WHITE, board) == true){
        Piece* white_king = Get_King(WHITE, board);
        SDL_Rect rect_check;
        rect_check.x = white_king->col * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
        rect_check.y = white_king->row * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        rect_check.w = SQUARE_SIZE;
        rect_check.h = SQUARE_SIZE;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderFillRect(renderer, &rect_check);
    }
    if (Is_Check(BLACK, board) == true){
        Piece* black_king = Get_King(BLACK, board);
        SDL_Rect rect_check;
        rect_check.x = black_king->col * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
        rect_check.y = black_king->row * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        rect_check.w = SQUARE_SIZE;
        rect_check.h = SQUARE_SIZE;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderFillRect(renderer, &rect_check);
    }

    // if there was a move before, we can show it by coloring the previous move cases (previous and destination) in a green / yellow color as in chess.com
    if (Move_Log_Array->actual_size > 0){
        SDL_Rect rect_previous_move;
        rect_previous_move.x = Move_Log_Array->Move_Log[Move_Log_Array->actual_size-1]->move->previous_col * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
        rect_previous_move.y = Move_Log_Array->Move_Log[Move_Log_Array->actual_size-1]->move->previous_row * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        rect_previous_move.w = SQUARE_SIZE;
        rect_previous_move.h = SQUARE_SIZE;
        SDL_SetRenderDrawColor(renderer, 153, 204, 51, 100); 
        SDL_RenderFillRect(renderer, &rect_previous_move);

        SDL_Rect rect_destination_move;
        rect_destination_move.x = Move_Log_Array->Move_Log[Move_Log_Array->actual_size-1]->move->destination_col * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
        rect_destination_move.y = Move_Log_Array->Move_Log[Move_Log_Array->actual_size-1]->move->destination_row * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        rect_destination_move.w = SQUARE_SIZE;
        rect_destination_move.h = SQUARE_SIZE;
        SDL_SetRenderDrawColor(renderer, 153, 204, 51, 100);        
        SDL_RenderFillRect(renderer, &rect_destination_move);
    }

    // making the pieces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]->is_alive) {

                char* name_piece;

                switch (board[i][j]->type) {
                    case PAWN:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/white_pawn.bmp";
                        }
                        else {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/black_pawn.bmp";
                        }
                        break;
                    case KNIGHT:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/white_knight.bmp";
                        }
                        else {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/black_knight.bmp";
                        }
                        break;
                    case BISHOP:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/white_bishop.bmp";
                        }
                        else {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/black_bishop.bmp";
                        }
                        break;
                    case ROOK:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/white_rook.bmp";
                        }
                        else {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/black_rook.bmp";
                        }
                        break;
                    case QUEEN:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/white_queen.bmp";
                        }
                        else {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/black_queen.bmp";
                        }
                        break;
                    case KING:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/white_king.bmp";
                        }
                        else {
                            name_piece = "../Images/BMP_Chess_Game_Pieces/black_king.bmp";
                        }
                        break;
                }

                /* Define destination rectangle */
                SDL_Rect destRect = {board[i][j]->col * SQUARE_SIZE+WINDOW_LEFT_MARGIN, board[i][j]->row * SQUARE_SIZE+WINDOW_TOP_MARGIN, SQUARE_SIZE, SQUARE_SIZE}; // Adjust the coordinates and size as needed here

                /* Add image to renderer */
                add_image_to_render(name_piece, renderer, destRect);
            }      
        }
    }


    // adding the letters on the bottom side of the chessboard to help the player to know where he is
    for (int i = 0; i < BOARD_SIZE; i++) {
        char letter = 'A' + i;

        switch (letter){
            case 'A':
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawLetterA(renderer, WINDOW_LEFT_MARGIN+1*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'B':
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawLetterB(renderer, WINDOW_LEFT_MARGIN+2*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'C':
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawLetterC(renderer, WINDOW_LEFT_MARGIN+3*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'D':
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawLetterD(renderer, WINDOW_LEFT_MARGIN+4*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'E':
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawLetterE(renderer, WINDOW_LEFT_MARGIN+5*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'F':
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawLetterF(renderer, WINDOW_LEFT_MARGIN+6*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'G':
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawLetterG(renderer, WINDOW_LEFT_MARGIN+7*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
            case 'H':
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawLetterH(renderer, WINDOW_LEFT_MARGIN+8*SQUARE_SIZE-5-15, WINDOW_TOP_MARGIN+8*SQUARE_SIZE-5-15, 15, 15);
                break;
        }

    }
    // adding the numbers on the left side of the chessboard to help the player to know where he is
    for (int i = 0; i < BOARD_SIZE; i++) {
        int number = i+1;
        switch (number){
            case 1 : 
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawNumber1(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+7*SQUARE_SIZE+5, 15, 15);
                break;
            case 2 :
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawNumber2(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+6*SQUARE_SIZE+5, 15, 15);
                break;
            case 3 :
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawNumber3(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+5*SQUARE_SIZE+5, 15, 15);
                break;
            case 4 :
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawNumber4(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+4*SQUARE_SIZE+5, 15, 15);
                break;
            case 5 :
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawNumber5(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+3*SQUARE_SIZE+5, 15, 15);
                break;
            case 6 :
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawNumber6(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+2*SQUARE_SIZE+5, 15, 15);
                break;
            case 7 :
                SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
                drawNumber7(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+1*SQUARE_SIZE+5, 15, 15);
                break;
            case 8 :
                SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
                drawNumber8(renderer, WINDOW_LEFT_MARGIN+5, WINDOW_TOP_MARGIN+0*SQUARE_SIZE+5, 15, 15);
                break;
        }

    }

    // if a piece is clicked, we draw a red boundary around it
    if (is_clicked_1 == 1 && is_clicked_2 == 0){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderDrawRect(renderer, &draw_red_boundary_move); 
        // we draw the line around the piece 
        // we wanted to make it thicker so here is a way to do it, don't know if it's the best way

        // Draw top line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + i);
        }

        // Draw right line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y + draw_red_boundary_move.h);
        }

        // Draw bottom line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + draw_red_boundary_move.h - i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + draw_red_boundary_move.h - i);
        }

        // Draw left line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + i, draw_red_boundary_move.y, draw_red_boundary_move.x + i, draw_red_boundary_move.y + draw_red_boundary_move.h);
        }
    }

}


void Show_Captured_Pieces(SDL_Renderer* renderer, Captured_Piece_and_Score* captured_pieces){
    
    SDL_Rect rect;
    rect.w = 2*SQUARE_SIZE/10;
    rect.h = 2*SQUARE_SIZE/10;

    // showing the white piece captured piece above the chessboard
    for (int i=0; i<captured_pieces->number_of_white_pieces_captured; i++){
        rect.x = WINDOW_LEFT_MARGIN + i*(2*SQUARE_SIZE/10-10);
        rect.y = 3*SQUARE_SIZE/10/2;
        switch (captured_pieces->white_pieces_captured[i]->type){
            case PAWN:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_pawn.bmp", renderer, rect);
                break;
            case KNIGHT:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_knight.bmp", renderer, rect);
                break;
            case BISHOP:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_bishop.bmp", renderer, rect);
                break;
            case ROOK:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_rook.bmp", renderer, rect);
                break;
            case QUEEN:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_queen.bmp", renderer, rect);
                break;
        }
    }

    // showing the black piece captured under the chessboard
    for (int i=0; i<captured_pieces->number_of_black_pieces_captured; i++){
        rect.x = WINDOW_LEFT_MARGIN + i*(2*SQUARE_SIZE/10-10);
        rect.y = WINDOW_HEIGHT-WINDOW_TOP_MARGIN + 3*SQUARE_SIZE/10/2;
        switch (captured_pieces->black_pieces_captured[i]->type){
            case PAWN:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_pawn.bmp", renderer, rect);
                break;
            case KNIGHT:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_knight.bmp", renderer, rect);
                break;
            case BISHOP:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_bishop.bmp", renderer, rect);
                break;
            case ROOK:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_rook.bmp", renderer, rect);
                break;
            case QUEEN:
                add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_queen.bmp", renderer, rect);
                break;
        }
    }

    // the show of the score is still to be done 
}


void Show_Log(SDL_Renderer* renderer, Move_Log_array* log){

}


void Show_Digit(SDL_Renderer* renderer, int digit, int x, int y, const int font[10][FONT_WIDTH]) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
    for (int i = 0; i < FONT_HEIGHT; i++) {
        for (int j = 0; j < FONT_WIDTH; j++) {
            if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                SDL_RenderDrawPoint(renderer, x + j, y + i);
            }
        }
    }
}


void Show_Colon(SDL_Renderer* renderer, int x_colon, int y_colon, const int colon[FONT_HEIGHT_COLON]){
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
    for (int i = 0; i < FONT_HEIGHT_COLON; i++) {
        for (int j = 0; j < FONT_WIDTH_COLON; j++) {
            if (colon[i] & (1 << (FONT_WIDTH_COLON - j - 1))) {
                SDL_RenderDrawPoint(renderer, x_colon + j, y_colon + i);
            }
        }
    }
}


void Show_Updated_Timer(SDL_Renderer* renderer, int time_player_white, int time_player_black, int player_playing){

    // the area where we will show the timer will be on the right side of the board, the active timer will have a white background, the other will have a light grey background
    // both timer will be print in black in the same area
    SDL_Rect dest_rect_playing;
    dest_rect_playing.x = WINDOW_LEFT_MARGIN + 6*SQUARE_SIZE;
    dest_rect_playing.w = 200;
    dest_rect_playing.h = 50;
    SDL_Rect dest_rect_not_playing;
    dest_rect_not_playing.x = WINDOW_LEFT_MARGIN + 6*SQUARE_SIZE;
    dest_rect_not_playing.w = 200;
    dest_rect_not_playing.h = 50;


    int number;
    int x;
    int y;
    int x_colon;
    int y_colon;
    int number_digits_done;


    // if the player that is playing is the player 1, so the white player
    if (player_playing == Player1){

        // we set the color of the renderer to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // we draw the rectangle for the timer of the player 1 in white 
        dest_rect_playing.y = WINDOW_HEIGHT - 50;
        SDL_RenderFillRect(renderer, &dest_rect_playing);

        // we set the color of the renderer to dark grey
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        // we draw the rectangle for the timer of the player 2 in dark grey
        dest_rect_not_playing.y = 0;
        SDL_RenderFillRect(renderer, &dest_rect_not_playing);
        

        // we print the timer of the player 1 in black in the rectangle that is white, because he is playing
        // we first print the seconds with this function 
        number = time_player_white % 60;
        number_digits_done = 0;
        x = dest_rect_playing.x + dest_rect_playing.w - FONT_WIDTH/2;
        y = dest_rect_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


        // printing the ":" symbols bewteen the two numbers
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        Show_Colon(renderer, x_colon, y_colon, colon);
        

        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_white / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


        // we print the timer of the player 2 in black in the rectangle that is grey, because he is not playing
        // we first print the seconds with this function 
        number = time_player_black % 60;
        number_digits_done = 0;
        x = dest_rect_not_playing.x + dest_rect_not_playing.w - FONT_WIDTH/2;
        y = dest_rect_not_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        Show_Colon(renderer, x_colon, y_colon, colon);


        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_black / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);            
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


    }
    // if the player that is playing is the player 2, so the black player
    else if (player_playing == Player2){

        // we set the color of the renderer to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // we draw the rectangle for the timer of the player 2 in white 
        dest_rect_playing.y = 0;
        SDL_RenderFillRect(renderer, &dest_rect_playing);

        // we set the color of the renderer to dark grey
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        // we draw the rectangle for the timer of the player 1 in dark grey
        dest_rect_not_playing.y = WINDOW_HEIGHT - 50;
        SDL_RenderFillRect(renderer, &dest_rect_not_playing);


        // we print the timer of the player 1 in black in the rectangle that is grey, because he is not playing
        // we first print the seconds with this function 
        number = time_player_white % 60;
        number_digits_done = 0;
        x = dest_rect_not_playing.x + dest_rect_not_playing.w - FONT_WIDTH/2;
        y = dest_rect_not_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        Show_Colon(renderer, x_colon, y_colon, colon);


        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_white / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


        // we print the timer of the player 2 in black in the rectangle that is white, because he is playing
        // we first print the seconds with this function 
        number = time_player_black % 60;
        number_digits_done = 0;
        x = dest_rect_playing.x + dest_rect_playing.w - FONT_WIDTH/2;
        y = dest_rect_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        Show_Colon(renderer, x_colon, y_colon, colon);

        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_black / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            Show_Digit(renderer, 0, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            Show_Digit(renderer, digit, x, y, font);
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                Show_Digit(renderer, 0, x, y, font);
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

    }

}


void Show_Menu_Button_in_Game(SDL_Renderer* renderer, Button** Buttons, bool is_pawn_promotion_happening, int color_promoted_pawn){
    
    // display the start buttons
    if (Buttons[START_BUTTON]->state == UNACTIVE){
        add_image_to_render("../Images/Buttons/Unactive_Start_Button.bmp", renderer, Buttons[START_BUTTON]->rect);
    }
    else if (Buttons[START_BUTTON]->state == ACTIVE){
        add_image_to_render("../Images/Buttons/Active_Start_Button.bmp", renderer, Buttons[START_BUTTON]->rect);
    }

    // display others buttons
    add_image_to_render("../Images/Buttons/Restart_Button.bmp", renderer, Buttons[RESTART_BUTTON_IN_GAME]->rect);
    add_image_to_render("../Images/Buttons/New_Game_Button.bmp", renderer, Buttons[NEW_GAME_BUTTON_IN_GAME]->rect);
    add_image_to_render("../Images/Buttons/Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_IN_GAME]->rect);

    // display the undo button 
    if (Buttons[UNDO_BUTTON]->state == UNACTIVE){
        add_image_to_render("../Images/Buttons/Unactive_Undo_Button.bmp", renderer, Buttons[UNDO_BUTTON]->rect);
    }
    else if (Buttons[UNDO_BUTTON]->state == ACTIVE){
        add_image_to_render("../Images/Buttons/Active_Undo_Button.bmp", renderer, Buttons[UNDO_BUTTON]->rect);
    }

    // we display the pawn promotion buttons : always but active or unactive 
    if (is_pawn_promotion_happening == false){
        add_image_to_render("../Images/Buttons/Unactive_Pawn_Promotion_Button.bmp", renderer, Buttons[PAWN_PROMOTION_BUTTON]->rect);
    }
    else if (is_pawn_promotion_happening == true){
        add_image_to_render("../Images/Buttons/Active_Pawn_Promotion_Button.bmp", renderer, Buttons[PAWN_PROMOTION_BUTTON]->rect);
    }

    // we then print at the place of the log on the render, the differents buttons concerning the pawn promotion
    if (is_pawn_promotion_happening == true){

        // if the color of the pawn that is promoted is white
        if (color_promoted_pawn == WHITE){
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_queen.bmp", renderer, Buttons[QUEEN_BUTTON]->rect);
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_rook.bmp", renderer, Buttons[ROOK_BUTTON]->rect);
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_bishop.bmp", renderer, Buttons[BISHOP_BUTTON]->rect);
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/white_knight.bmp", renderer, Buttons[KNIGHT_BUTTON]->rect);
        }
        // if the color of the pawn that is promoted is black
        else if (color_promoted_pawn == BLACK){
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_queen.bmp", renderer, Buttons[QUEEN_BUTTON]->rect);
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_rook.bmp", renderer, Buttons[ROOK_BUTTON]->rect);
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_bishop.bmp", renderer, Buttons[BISHOP_BUTTON]->rect);
            add_image_to_render("../Images/BMP_Chess_Game_Pieces/black_knight.bmp", renderer, Buttons[KNIGHT_BUTTON]->rect);
        }
      
    }

}


void Draw_Filled_Circle(SDL_Renderer *renderer, int center_col, int center_row, int radius) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red
    int x, y, dl;
    for (y = -radius; y <= radius; y++) {
        dl = (int)sqrt(radius * radius - y * y);
        for (x = -dl; x <= dl; x++) {
            SDL_RenderDrawPoint(renderer, center_col + x, center_row + y);
        }
    }
}


void Show_Trajectory(SDL_Renderer* renderer, Piece*** board, Move* move, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Tiles_Pawn* Pawn_Move_State, int is_clicked_1, int is_clicked_2, bool is_click_board){

    // there is something to do only when one clicked is done on a piece
    if (is_clicked_1 == 1 && is_clicked_2 == 0 && is_click_board == true){
        // set the color of the renderer to red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // we need to draw the trajectory of the piece that is clicked : it will be a red circle on the center of each case it can go to 
     
        // if the piece is a rook (or a queen) 
        if (board[move->previous_row][move->previous_col]->type == ROOK || board[move->previous_row][move->previous_col]->type == QUEEN){
            
            // we need to draw the trajectory of the rook (and the queen, since it's the same as the rook but with the bishop's trajectory too)
            // we first draw the trajectory of the rook in the direction of the top
            for (int i = move->previous_row-1; i >= 0; i--){
                // while we don't have a piece on the way
                if (board[i][move->previous_col]->type == NOTHING){
                    Draw_Filled_Circle(renderer, move->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[i][move->previous_col]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle on the piece
                else if (board[i][move->previous_col]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, move->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }
            // we then draw the trajectory of the rook in the direction of the bottom
            for (int i = move->previous_row+1; i < 8; i++){
                // while we don't have a piece on the way
                if (board[i][move->previous_col]->type == NOTHING){
                    Draw_Filled_Circle(renderer, move->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[i][move->previous_col]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle on the piece
                else if (board[i][move->previous_col]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, move->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }
            // we then draw the trajectory of the rook in the direction of the left
            for (int j = move->previous_col-1; j >= 0; j--){
                // while we don't have a piece on the way
                if (board[move->previous_row][j]->type == NOTHING){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, move->previous_row*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[move->previous_row][j]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle on the piece
                else if (board[move->previous_row][j]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, move->previous_row*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }
            // we then draw the trajectory of the rook in the direction of the right
            for (int j = move->previous_col+1; j < 8; j++){
                // while we don't have a piece on the way
                if (board[move->previous_row][j]->type == NOTHING){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, move->previous_row*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[move->previous_row][j]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle on the piece
                else if (board[move->previous_row][j]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, move->previous_row*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }

        }

        // if the piece is a bishop (or a queen)      
        if (board[move->previous_row][move->previous_col]->type == BISHOP || board[move->previous_row][move->previous_col]->type == QUEEN){
            
            // we need to draw the trajectory of the bishop (and the queen, since it's the same as the bishop but with the rook's trajectory too)
            // we first draw the trajectory of the bishop in the direction of the top left
            for (int i = move->previous_row-1, j = move->previous_col-1; i >= 0 && j >= 0; i--, j--){
                // while we don't have a piece on the way
                if (board[i][j]->type == NOTHING){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[i][j]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle on the piece
                else if (board[i][j]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }
            // we then draw the trajectory of the bishop in the direction of the top right
            for (int i = move->previous_row-1, j = move->previous_col+1; i >= 0 && j < 8; i--, j++){
                // while we don't have a piece on the way
                if (board[i][j]->type == NOTHING){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[i][j]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle
                else if (board[i][j]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }
            // we then draw the trajectory of the bishop in the direction of the bottom left
            for (int i = move->previous_row+1, j = move->previous_col-1; i < 8 && j >= 0; i++, j--){
                // while we don't have a piece on the way
                if (board[i][j]->type == NOTHING){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[i][j]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle
                else if (board[i][j]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }
            // we then draw the trajectory of the bishop in the direction of the bottom right
            for (int i = move->previous_row+1, j = move->previous_col+1; i < 8 && j < 8; i++, j++){
                // while we don't have a piece on the way
                if (board[i][j]->type == NOTHING){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                }
                // if we have a piece of the same color, we stop the trajectory
                else if (board[i][j]->color == board[move->previous_row][move->previous_col]->color){
                    break;
                }
                // if we have a piece of the other color, we stop the trajectory and we draw the circle
                else if (board[i][j]->color != board[move->previous_row][move->previous_col]->color){
                    Draw_Filled_Circle(renderer, j*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, i*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    break;
                }
            }

        }

        // if the piece is a knight
        if (board[move->previous_row][move->previous_col]->type == KNIGHT){

            // we need to draw the trajectory of the knight
            // we first draw the trajectory of the knight in the direction of the top left
            if (move->previous_row-2 >= 0 && move->previous_col-1 >= 0 && (board[move->previous_row-2][move->previous_col-1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-2][move->previous_col-1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the top right
            if (move->previous_row-2 >= 0 && move->previous_col+1 < 8 && (board[move->previous_row-2][move->previous_col+1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-2][move->previous_col+1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the right top
            if (move->previous_row-1 >= 0 && move->previous_col+2 < 8 && (board[move->previous_row-1][move->previous_col+2]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-1][move->previous_col+2]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the right bottom
            if (move->previous_row+1 < 8 && move->previous_col+2 < 8 && (board[move->previous_row+1][move->previous_col+2]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+1][move->previous_col+2]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the bottom right
            if (move->previous_row+2 < 8 && move->previous_col+1 < 8 && (board[move->previous_row+2][move->previous_col+1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+2][move->previous_col+1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the bottom left
            if (move->previous_row+2 < 8 && move->previous_col-1 >= 0 && (board[move->previous_row+2][move->previous_col-1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+2][move->previous_col-1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the left bottom
            if (move->previous_row+1 < 8 && move->previous_col-2 >= 0 && (board[move->previous_row+1][move->previous_col-2]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+1][move->previous_col-2]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the knight in the direction of the left top
            if (move->previous_row-1 >= 0 && move->previous_col-2 >= 0 && (board[move->previous_row-1][move->previous_col-2]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-1][move->previous_col-2]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }

        }

        // if the piece is a king
        if (board[move->previous_row][move->previous_col]->type == KING){

            // we need to draw the trajectory of the king
            // we first draw the trajectory of the king in the direction of the top
            if (move->previous_row-1 >= 0 && (board[move->previous_row-1][move->previous_col]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-1][move->previous_col]->type == NOTHING)){
                Draw_Filled_Circle(renderer, move->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the top right
            if (move->previous_row-1 >= 0 && move->previous_col+1 < 8 && (board[move->previous_row-1][move->previous_col+1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-1][move->previous_col+1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the right
            if (move->previous_col+1 < 8 && (board[move->previous_row][move->previous_col+1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row][move->previous_col+1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, move->previous_row*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the bottom right
            if (move->previous_row+1 < 8 && move->previous_col+1 < 8 && (board[move->previous_row+1][move->previous_col+1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+1][move->previous_col+1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the bottom
            if (move->previous_row+1 < 8 && (board[move->previous_row+1][move->previous_col]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+1][move->previous_col]->type == NOTHING)){
                Draw_Filled_Circle(renderer, move->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the bottom left
            if (move->previous_row+1 < 8 && move->previous_col-1 >= 0 && (board[move->previous_row+1][move->previous_col-1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row+1][move->previous_col-1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the left
            if (move->previous_col-1 >= 0 && (board[move->previous_row][move->previous_col-1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row][move->previous_col-1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, move->previous_row*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // we then draw the trajectory of the king in the direction of the top left
            if (move->previous_row-1 >= 0 && move->previous_col-1 >= 0 && (board[move->previous_row-1][move->previous_col-1]->color != board[move->previous_row][move->previous_col]->color || board[move->previous_row-1][move->previous_col-1]->type == NOTHING)){
                Draw_Filled_Circle(renderer, (move->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }

            // adding the possibility to do the rock move
            Move* rock_king_move = Create_Move(0, 0, 0, 0);
            // long white rock
            Change_Move(rock_king_move,7,4,7,0);
            if (board[move->previous_row][move->previous_col]->color == WHITE && Is_Rock_Possible(rock_king_move, State_Of_Rock_and_Check, board) != NO_ROCK){
                Draw_Filled_Circle(renderer, 0*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, 7*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // short white rock
            Change_Move(rock_king_move,7,4,7,7);
            if (board[move->previous_row][move->previous_col]->color == WHITE && Is_Rock_Possible(rock_king_move, State_Of_Rock_and_Check, board) != NO_ROCK){
                Draw_Filled_Circle(renderer, 7*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, 7*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // long black rock
            Change_Move(rock_king_move,0,4,0,0);
            if (board[move->previous_row][move->previous_col]->color == BLACK && Is_Rock_Possible(rock_king_move, State_Of_Rock_and_Check, board) != NO_ROCK){
                Draw_Filled_Circle(renderer, 0*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, 0*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            // short black rock
            Change_Move(rock_king_move,0,4,0,7);
            if (board[move->previous_row][move->previous_col]->color == BLACK && Is_Rock_Possible(rock_king_move, State_Of_Rock_and_Check, board) != NO_ROCK){
                Draw_Filled_Circle(renderer, 7*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, 0*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
            }
            Destroy_Move(rock_king_move);

        }
        
        // if the piece is a pawn
        if (board[move->previous_row][move->previous_col]->type == PAWN){

            Move* move_pawn = Create_Move(move->previous_row, move->previous_col, 0,0);

            // if the pawn is white
            if (board[move->previous_row][move->previous_col]->color == WHITE){
                // the Is_Move_Valid_Pawn function will be used to know if the move is valid or not (including the en passant move)

                // we change the move of the pawn, going up (row-1)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row-1, move_pawn->previous_col);
                if (move_pawn->previous_row-1>=0){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, move_pawn->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                // we change the move of the pawn, going up twice, only if we're at the beggining (row-2)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row-2, move_pawn->previous_col);
                if (move_pawn->previous_row-2>=0){   
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, move_pawn->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row-2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                // we change the move of the pawn, going up and right (row-1, col+1)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row-1, move_pawn->previous_col+1);
                if (move_pawn->previous_row-1>=0 && move_pawn->previous_col+1<8){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, (move_pawn->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                // we change the move of the pawn, going up and left (row-1, col-1)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row-1, move_pawn->previous_col-1);
                if (move_pawn->previous_row-1>=0 && move_pawn->previous_col-1>=0){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, (move_pawn->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                
            }

            // if the pawn is black
            else if (board[move->previous_row][move->previous_col]->color == BLACK){
                // the Is_Move_Valid_Pawn function will be used to know if the move is valid or not (including the en passant move)

                // we change the move of the pawn, going down (row+1)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row+1, move_pawn->previous_col);
                if (move_pawn->previous_row+1<8){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, move_pawn->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                // we change the move of the pawn, going up twice, only if we're at the beggining (row+2)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row+2, move_pawn->previous_col);
                if (move_pawn->previous_row+2<8){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, move_pawn->previous_col*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row+2)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                // we change the move of the pawn, going down and right (row+1, col+1)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row+1, move_pawn->previous_col+1);
                if (move_pawn->previous_row+1<8 && move_pawn->previous_col+1<8){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, (move_pawn->previous_col+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                // we change the move of the pawn, going down and left (row+1, col-1)
                Change_Move(move_pawn, move_pawn->previous_row, move_pawn->previous_col, move_pawn->previous_row+1, move_pawn->previous_col-1);
                if (move_pawn->previous_row+1<8 && move_pawn->previous_col-1>=0){
                    if (Is_Move_Valid_Pawn(move_pawn, board, Pawn_Move_State) == true){
                        Draw_Filled_Circle(renderer, (move_pawn->previous_col-1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN, (move_pawn->previous_row+1)*SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN, 10);
                    }
                }
                
            }

            Destroy_Move(move_pawn);
        }

    }

}


void Show_Victory_Menu(SDL_Renderer* renderer, Button** Buttons, int looser_player, Players* players){
  
    // if there is a looser, we show the victory or defeat image
    if (looser_player == Draw_Player){
        SDL_Rect Rect_final_screen_draw = {WINDOW_WIDTH/4, WINDOW_HEIGHT/4, WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
        add_image_to_render("../Images/Buttons/Draw.bmp", renderer, Rect_final_screen_draw);
    }
    else if (looser_player != -1){
        SDL_Rect Rect_final_screen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

        // when we play against the IA, we can add the images of victory and defeat, otherwise, bewteen two human players, we need to do diffent things
        if (looser_player == Player1 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == IA){
            add_image_to_render("../Images/Buttons/defeat.bmp", renderer, Rect_final_screen);
        }
        else if (looser_player == Player1 && players->is_player1_an_IA == IA && players->is_player2_an_IA == HUMAN){
            add_image_to_render("../Images/Buttons/victory.bmp", renderer, Rect_final_screen);
        }
        else if (looser_player == Player2 && players->is_player1_an_IA == IA && players->is_player2_an_IA == HUMAN){
            add_image_to_render("../Images/Buttons/defeat.bmp", renderer, Rect_final_screen);
        }
        else if (looser_player == Player2 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == IA){
            add_image_to_render("../Images/Buttons/victory.bmp", renderer, Rect_final_screen);
        }

        // we need to print a message to say which player won when it's between two human players
        // if the player 1 lost
        if (looser_player == Player1 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == HUMAN){
            add_image_to_render("../Images/Buttons/victory.bmp", renderer, Rect_final_screen);

            SDL_Rect Rect_pos = {WINDOW_WIDTH/2-200, 150, 400,200};
            // we show that the player 2 (and its corresponding color) won
            if (players->player2_color == WHITE){
                add_image_to_render("../Images/Buttons/WHITE_PLAYER.bmp", renderer, Rect_pos);
            }
            else if (players->player2_color == BLACK){
                add_image_to_render("../Images/Buttons/BLACK_PLAYER.bmp", renderer, Rect_pos);
            }
        }

        // if the player 2 lost
        if (looser_player == Player2 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == HUMAN){
            add_image_to_render("../Images/Buttons/victory.bmp", renderer, Rect_final_screen);

            SDL_Rect Rect_pos = {WINDOW_WIDTH/2-200, 150, 400,200};
            // we show that the player 1 (and its corresponding color) won
            if (players->player1_color == WHITE){
                add_image_to_render("../Images/Buttons/WHITE_PLAYER.bmp", renderer, Rect_pos);
            }
            else if (players->player1_color == BLACK){
                add_image_to_render("../Images/Buttons/BLACK_PLAYER.bmp", renderer, Rect_pos);
            }        
        }
    }

    // showing the buttons linked to the final screen
    add_image_to_render("../Images/Buttons/Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_VICTORY_MENU]->rect);
    add_image_to_render("../Images/Buttons/Restart_Button.bmp", renderer, Buttons[RESTART_BUTTON_VICTORY_MENU]->rect);
    add_image_to_render("../Images/Buttons/New_Game_Button.bmp", renderer, Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect);
    add_image_to_render("../Images/Buttons/Unactive_Undo_Button.bmp", renderer, Buttons[UNDO_ENDING_MOVE_BUTTON]->rect);
}                     