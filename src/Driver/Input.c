// ADT INPUT_1
// ADT Input1 digunakan untuk membaca masukan yang berupa char seperti WASD dan beberapa input lain.
// Input lain yang berupa string akan memanfaatkan mesinkar dan mesinkata


#include "../Header/Input.h"
#include <conio.h>
#include <stdio.h>

int GetInput(){
    int c;
    c = getch();
    return c;
}
