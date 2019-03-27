#include <stdio.h>
#include "../include/tictactoe.h"
#include <stdlib.h>

unsigned short b3tous(char b3[10]) {

  unsigned short us;
  int i;
  int value = 1;

  for (i = 8; i >= 0; i--) {
    b3[i] = b3[i] - '0';
    us = us + (b3[i] * value);
    value = value * 3;
  }

return us;
}

void b3fromus(char b3[10], unsigned short us) {

  int i;

  b3[9] = '\0';

  for(i = 8; i >= 0; i--) {
    b3[i] = (us % 3) + '0';
    us = us / 3;
  }

}



void boardfromb3(char board[60], char b3[10]) {

  int secNumber;
  int piece = 0;
  int b = 1;
  int i;
  int index;

  strcpy( board, "   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \0");

  for (i = 0; i < 9; i++ ) {
    index = (3 * piece + b);
    secNumber = (piece / 3) * 12;
    index = index + secNumber;
    b++;
    piece++;

  switch (b3[i]) {

    case 0:
      board[index] = ' ';
      break;

    case 1:
      board[index] = 'O';
      break;

    case 2:
      board[index] = 'X';
      break;

    default:
      fprintf( stderr, "Error: bad value in b3\n");
      exit(-1);
      break;

  }
}

}

void boardtob3( char b3[10], char board[60] ) {

  int secondNumber;
  int piece = 0;
  int b = 1;
  int i;
  const int m = 3;
  int index;

  for (i = 0; i < 9; i++ ) {
    index = (m * piece + b);
    secondNumber = (piece / 3) * 12;
    index = index + secondNumber;
    b++;
    piece++;

    switch (board[index]) {

      case ' ':
      b3[i] = '0';
      break;

      case 'O':
      b3[i] = '1';
      break;

      case 'X':
      b3[i] = '2';
      break;

      default:
      fprintf( stderr, "Error: bad value in b3\n");
      exit(-1);
      break;

    }
  }

}


char get_move( char b3[10]) {

int move = 0;
int i;

for (i = 0; i < 9; i++) {
  if (b3[i] != '0') {
    move = move + 1;
  }
}

return move + '0';
}

char get_turn (char b3[10]) {

char turn;
char number;

  number = get_move(b3);

  if (((number - '0') % 2) == 0 ) {
    turn = '2';
  }
  else {
    turn = '1';
  }
return turn;
}

char winner( unsigned short us ){

char winner = ' ';
char b3[10];
int i;
int j;
int k;
int l;

  b3fromus(b3, us);

  if (get_move(b3) == '9') {
    winner = '0';
  }

  for( i = 0, j = 0, k = 1, l = 2; i < 3; i++) {
    if ((b3[j] == '2') && (b3[k] == '2') && (b3[l] == '2')) {
      winner = '2';
      }
    else if((b3[j] == '1') && (b3[k] == '1') && (b3[l] == '1')){
      winner = '1';
      }
      j = j + 3;
      k = k + 3;
      l = l + 3;
  }

  for( i = 0, j = 0, k = 3, l = 6; i < 3; i++) {
    if ((b3[j] == '2') && (b3[k] == '2') && (b3[l] == '2')) {
      winner = '2';
    }
    else if((b3[j] == '1') && (b3[k] == '1') && (b3[l] == '1')){
      winner = '1';
    }
    j = j + 1;
    k = k + 1;
    l = l + 1;
  }

  for( i = 0; i < 9; i++) {
    if ((b3[0] == '2') && (b3[4] == '2') && (b3[8] == '2')) {
      winner = '2';
    }
    else if((b3[0] == '1') && (b3[4] == '1') && (b3[8] == '1')){
      winner = '1';
    }
  }

  for( i = 0; i < 9; i++) {
    if ((b3[2] == '2') && (b3[4] == '2') && (b3[6] == '2')) {
      winner = '2';
    }
    else if((b3[2] == '1') && (b3[4] == '1') && (b3[6] == '1')){
      winner = '1';
    }
  }

return winner;
}


unsigned short next(unsigned short us, char pos) {


char newb3[10];
unsigned short newNum = 0;
char move1;

  b3fromus(newb3, us);
  move1 = get_turn(newb3);

    if (newb3[pos - '0'] == '0') {
      newb3[pos - '0'] = move1;
      fflush(stdout);
    }
    else{
      return 0;
    }

 newNum = b3tous(newb3);

return newNum;
}

void get_record( FILE *fp, unsigned short us, struct strategy_struct *record ) {

  fseek(fp,sizeof(struct strategy_struct)*us, SEEK_SET);
  fread(record, sizeof(struct strategy_struct), 1, fp);

}

void set_record(FILE *fp, unsigned short us, struct strategy_struct record) {
  fseek(fp,sizeof(struct strategy_struct)*us, SEEK_SET);
  fwrite(&record, sizeof(struct strategy_struct), 1, fp);
}

void evaluate_move(FILE *fp, unsigned short us, struct strategy_struct *file) {

  int i;
  struct strategy_struct rec;
  char b3[10];
  int tempvar;
  int found_tie;
  int legal_move;



  for (i = 0; i < 9; i++) {
    b3fromus(b3, us);
      if(next(us, i +'0') != 0) {
        get_record(fp, next(us, i + '0'), &rec);

        if (rec.winner == get_turn(b3)) {
          file->best_move = i + '0';
          file->winner = rec.winner;
          set_record(fp, us, *file);
          return;
        }
        if(rec.winner == 0 + '0'){
          tempvar = i ;
          found_tie = 1;
        }
        else{
          legal_move = i;
        }
      }
  }
  if (found_tie == 1){
    file->best_move = tempvar;
    file->winner = 0 + '0';
  }
  else if(found_tie == 0){
    file->best_move = legal_move + '0';
    file->winner = winner(us);
  }




}
