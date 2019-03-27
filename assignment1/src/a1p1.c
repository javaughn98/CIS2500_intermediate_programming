#include "../include/tictactoe.h"

int main (int argc, char *argv[]) {

  char b3[10];
  char board[60];
  int boardNumber;
  int i;
  unsigned short us;

    if(argc < 1) {
      printf("Error!!! Too few arguments\n");
      return 0;
    }
    us = atoi(argv[1]);

    boardNumber = us;
    printf("Board number: %d\n", boardNumber);
    b3fromus(b3, us);
    printf("Board b3: %9s\n", b3);
    printf("Board pic:\n");
    b3tous(b3);
    boardfromb3(board, b3);
    printf("%s\n", board);
    boardtob3(b3, board);
    printf("Move: %c\n", get_move(b3));
    printf("Turn: %c\n", get_turn(b3));
    printf("Winner: %c\n", winner(us));
  for(i = 0; i < 9; i++) {
    printf("%d -> %d", i, next(us,(i + '0')));
    printf("\n");
  }








  return 0;
}
