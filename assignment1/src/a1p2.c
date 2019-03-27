#include "../include/tictactoe.h"
#include <stdio.h>



int main (){
int i;
FILE *ptr;

struct strategy_struct game;

ptr = fopen("strategyfile.bin", "wb+");
game.best_move = -1;
game.winner = ' ';



for(i = 0; i < 19683; i++){
  fwrite(&game, sizeof(struct strategy_struct), 1, ptr);

}

fclose(ptr);
return 0;
}
