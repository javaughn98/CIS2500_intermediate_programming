#include "../include/tictactoe.h"


int main(int argc, char *argv[]) {

unsigned short arg;
char b3[10];
int i = 0;
struct strategy_struct record;
FILE *fp;

if(argc < 1) {
  printf("Error!!! Too few arguments\n");
  return 0;
}

fp = fopen("strategyfile.bin", "rb+");
arg = atoi(argv[1]);


for(i = 0; i < 19683; i++) {
  b3fromus(b3,i);
  if(get_move(b3) == (arg + '0')) {
    if (winner(i) != ' ') {
      record.best_move = -1;
      record.winner = winner(i);
      set_record(fp, i, record);
    /*  printf("[%d], ", i);*/
    }
    else{
      evaluate_move(fp, i, &record);
      set_record(fp, i, record);
    }
  }
}

fclose(fp);


  return 0;
}
