// ADT INPUT_1
// ADT Input1 digunakan untuk membaca masukan yang berupa char seperti WASD dan beberapa input lain.
// Input lain yang berupa string akan memanfaatkan mesinkar dan mesinkata

#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"

// == WINDOWS / MS-DOS

// #include "../Header/Input.h"
// #include <stdio.h>


// == LINUX (DEBIAN BASED) //

#include "Input.h"
#include <stdio.h>

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
