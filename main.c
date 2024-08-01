
  //header files
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
 // ANSI color codes
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
 //global variables
#define token  '^'
#define food  '*'
#define wall  '#'
#define ghost  '@'
#define empty  ' '
char grid [15] [30];
int score = 0;
int tx = 8;
int ty = 15;

  //global functions

char window_1()
{
  system("cls");
  char w;
label_w:
  printf("\t\tWELCOME\n\t\t  TO\n\t\tPACMAN");
  printf("\n\n\n\t1. PLAY\n");
  printf("\t2. LEADERBOARD\n");
  printf("\t3. EXIT\n\t");
  //instructions add karna hai main menu
  w = getch();
  if (w != '1' && w != '2' && w != '3'){
    system("cls");
    printf("NOTE = enter correct response\n");
    goto label_w;
  }
  return w;
}

void instructions() {
  printf(GREEN "FOR MOVEMENT USE\n");
  printf("\tw or W for UP\n");
  printf("\ts or S for DOWN\n");
  printf("\ta or A for RIGHT\n");
  printf("\td or D for LEFT\n");
  printf("PRESS q or Q ANYTIME TO QUIT\n\n"RESET);  
}

void initialise() {
  //boundary
  for (int i = 0 ; i < 15 ; i++) {
    for (int j = 0 ; j < 30 ; j++) {
      if (i == 0 || j == 0 || j == 29 || i == 14) {
        grid [i][j] = wall;
      } else {
        grid [i][j] = empty;
      }
    }
  }  
  grid[8][15] = token;
//food
  int count;
  count = 30;
  while (count > 0) {
    int i = rand() % 13 + 1;
    int j = rand() % 28 + 1;
    if (grid[i][j] != token) {
      grid[i][j] = food;
    }
    count--;
  }
//ghost
  count = 20;
  while (count > 0) {
    int i = rand() % 13 + 1;
    int j = rand() % 28 + 1;
    if ( (grid[i][j] != food) && (grid[i][j] != token) ) {
      grid [i][j] = ghost;
      count--;
    }
  }
//a bit of seperator
  count = 3;
  while (count > 0) {
    int i = rand() % 13 + 1;
    for (int j = 0 ; j < 30 ; j++) {
      if ( j == 1 || j == 8 || j == 14 || (grid[i][j] == food) || (grid[i][j] == ghost) || (grid[i][j] == token) ) {
        continue;
      }
      grid [i][j] = wall;
    }
    count--;
  }
//innner walls
  count = 30;
  while (count > 0) {
    int i = rand() % 13 + 1;
    int j = rand() % 28 + 1;
    if ((grid[i][j] != wall) &&
        (grid[i][j] != food) &&
        (grid[i][j] != ghost) &&
        (grid[i][j] != token)) {
          grid[i][j] = wall;
          count--;
        }
  }
}

int printing(int x , int y) {
  instructions();
  tx += x;
  ty += y;
  if (grid [tx][ty] == ghost) {
   return 0;
  }
  else if(grid [tx][ty] == wall) {
    for (int i = 0 ; i < 15 ; i++) {
      for (int j = 0 ; j < 29 ; j++) {
        if (grid[i][j] == token) {
          printf(YELLOW "%c" RESET , grid[i][j]);
        } else if (grid[i][j] == ghost) {
          printf(RED "%c" RESET , grid[i][j]);
        } else if (grid[i][j] == food) {
          printf(CYAN "%c" RESET , grid[i][j]);
        } else {
          printf("%c" , grid[i][j]);
        }
      }
      printf("\n");
    }
    tx -= x;
    ty -= y;
  }
  else {
    if (grid [tx][ty] == food) {
      score++;
    }
    grid [tx][ty] = token;
    grid [tx - x][ty - y] = empty;
    for (int i = 0 ; i < 15 ; i++) {
      for (int j = 0 ; j < 29 ; j++) {
        if (grid[i][j] == token) {
          printf(YELLOW "%c" RESET , grid[i][j]);
        } else if (grid[i][j] == ghost) {
          printf(RED "%c" RESET , grid[i][j]);
        } else if (grid[i][j] == food) {
          printf(CYAN "%c" RESET , grid[i][j]);
        } else {
          printf("%c" , grid[i][j]);
        }
      }
      printf("\n");
    }
  }
  return 1;
}

char game_over () {
  system ("cls");
  char c;
label_g:
  printf(RED "\n\n\t\tGAME OVER\n\t  THANK YOU FOR PLAYING\n\n\n"RESET);
  printf("your current score = %d\n\n" , score);
  printf(GREEN"\tpress 0 for saving your score\n");
  printf("\tpress 1 for main menu\n\t"RESET);
  c = getch();
  if (c=='0') {}
  else if (c=='1') {}
  else {
    system ("cls");
    printf("please enter correct response: \n");
    goto label_g;
  }
  return c;
}

int main () {
  int c;
  printf(BLUE"\n\n\n\t\tPRESS ANY KEY TO CONTINUE..."RESET);
  c = getch();
  system("cls");
  instructions();
  initialise();
  for(int i = 0; i < 15 ; i++) {
    for (int j = 0 ; j < 30 ; j++) {
      if (grid[i][j] == token) {
          printf(YELLOW "%c" RESET , grid[i][j]);
        } else if (grid[i][j] == ghost) {
          printf(RED "%c" RESET , grid[i][j]);
        } else if (grid[i][j] == food) {
          printf(CYAN "%c" RESET , grid[i][j]);
        } else {
          printf("%c" , grid[i][j]);
        }
    }
    printf("\n");
  }
  while (1) {
    if (score == 30) {
      printf(GREEN"\n\n\nYour current score is %d", score);
      printf("\n\tCONGRATULATIONS\nPress any key to continue..."RESET);
      c = getch();
      break;
    }
    printf(GREEN"\n\n\nYour current score is %d", score);
    printf("\nPlease enter your move = "RESET);
  label:
    c = getch();
    system("cls");
    if (c != 'w' && c != 'W' &&
        c != 's' && c != 'S' &&
        c != 'a' && c != 'A' &&
        c != 'd' && c != 'D' &&
        c != 'q' && c != 'Q') {
          instructions();
          for (int i = 0 ; i < 15 ; i++) {
            for (int j = 0 ; j < 30 ; j++) {
              if (grid[i][j] == token) {
                printf(YELLOW "%c" RESET , grid[i][j]);
              } else if (grid[i][j] == ghost) {
                printf(RED "%c" RESET , grid[i][j]);
              } else if (grid[i][j] == food) {
                printf(CYAN "%c" RESET , grid[i][j]);
              } else {
                printf("%c" , grid[i][j]);
              }
            }
            printf("\n");
          }
          printf(GREEN"\n\n\nYour current score is %d", score);
          printf("\nPlease enter your correct respones");
          printf("\nPlease enter your move = "RESET);
          goto label;
        }
        int print = 1;
         if (c == 'w' || c == 'W') {
      print = printing (-1,0);
      if (print == 0) break;
    } 
    else if (c == 's' || c == 'S') {
      print = printing (1,0);
      if (print == 0) break;
    } 
    else if (c == 'a' || c == 'A') {
      print = printing (0,-1);
      if (print == 0) break;
    }
    else if (c == 'd' || c == 'D') {
      print = printing (0,1);
      if (print == 0) break;
    }
    else if (c == 'q' || c == 'Q') {
      break;
    }
  }
  system("cls");
  game_over();
  // printf("gameover");
  return 0;
}

