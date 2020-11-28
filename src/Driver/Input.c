// ADT INPUT_1
// ADT Input1 digunakan untuk membaca masukan yang berupa char seperti WASD dan beberapa input lain.
// Input lain yang berupa string akan memanfaatkan mesinkar dan mesinkata

#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"

// == WINDOWS / MS-DOS

// #include "../Header/Input.h"
// #include <conio.h>
// #include <stdio.h>

// int GetInput(){
//     int c;
//     c = getch();
//     return c;
// }

// == LINUX (DEBIAN BASED) //

#include "../Header/Input.h"
#include <stdio.h>
#include <termios.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

// // /* Read 1 character without echo */
// char getch() 
// {
//   return getch_(0);
// }

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

int GetInput(){
    Kata c;
    STARTBUY();
    while(!EOP && !EOL){
      int i = 0;
      CKata.Length=0;
      while(CC!=BLANK){
        if(CC=='\r'){
          CC ='\n';
        }
        if(CC=='\n'){
          break;
        }
        CKata.TabKata[i] = CC;
        i++;
        CKata.Length=i;
        // printf("%c",CC);
        ADV();
      }
      c = CKata;
      if(CC=='\n'){
        break;
      }
      IgnoreBlank();
    }
    return (int)c.TabKata[0];
}
