// ADT INPUT_1
// ADT Input1 digunakan untuk membaca masukan yang berupa char seperti WASD dan beberapa input lain.
// Input lain yang berupa string akan memanfaatkan mesinkar dan mesinkata
// Memanfaatkan header conio.h

#ifndef input_H
#define input_H

#include <conio.h>
#include <stdio.h>

#define clrscr() system("cls")
#define INPUT_ENTER 13
#define INPUT_SPACE 32
#define INPUT_W 87
#define INPUT_A 65
#define INPUT_S 83
#define INPUT_D 68
#define INPUT_w 119
#define INPUT_a 97
#define INPUT_s 115
#define INPUT_d 100
#define INPUT_i 105
#define INPUT_j 106
#define INPUT_k 107
#define INPUT_l 108
#define INPUT_I 73
#define INPUT_J 74
#define INPUT_K 75
#define INPUT_L 76
#define INPUT_1 49
#define INPUT_2 50
#define INPUT_3 51
#define INPUT_4 52
#define INPUT_5 53
#define INPUT_6 54
#define INPUT_7 55
#define INPUT_8 56
#define INPUT_9 57
#define INPUT_ENTER 13
#define INPUT_SPACE 32
#define INPUT_BACKSPACE 32


int GetInput();
// Get input adalah fungsi yang menerima nilai ASCII dari input user

#endif
