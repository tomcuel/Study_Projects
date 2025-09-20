#include "Move.h"

#include <stdlib.h>
#include <stdio.h>

int main (){

    Move* move = Create_Move(1,2,3,4);

    printf("Move: %d %d %d %d\n", move->previous_row, move->previous_col, move->destination_row, move->destination_col);

    Change_Move(move, 5, 6, 7, 8);

    printf("Modified Move: %d %d %d %d\n", move->previous_row, move->previous_col, move->destination_row, move->destination_col);

    Move* copied_move = Copy_Move(move);

    printf("Copied Move: %d %d %d %d\n", copied_move->previous_row, copied_move->previous_col, copied_move->destination_row, copied_move->destination_col);

    Destroy_Move(move);

    return EXIT_SUCCESS;
}