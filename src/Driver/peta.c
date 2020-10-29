#include "../Header/input.h"
#include "../Header/matriks.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include <stdio.h>
#include <string.h>


// Pendefinisian State dari game
#define FASE_MENU 0
#define FASE_GAME 1
#define MAIN_DAY 2
#define PREPARATION_DAY 3

// Pendefinisian variabel yang akan dipakai
int cmap;
int state;
MATRIKS map[5], mapRoom;
// POINT player l;
int px,py;



void GameSetup (){
	// Setup awal untuk memulai game
	cmap = 0;
	BacaMATRIKS(&map[1], "../file/1.txt");
	BacaMATRIKS(&map[0], "../file/0.txt");
	BacaMATRIKS(&map[2], "../file/2.txt");
	BacaMATRIKS(&map[3], "../file/3.txt");
	px = 1 ;
	py = 1 ;
	state = FASE_GAME;
	CopyMATRIKS(map[cmap], &mapRoom);
}

void PrintJudul (){
	// printf("%s\n","==================================================================");
	// printf("%s\n","==================================================================");  
	// printf("%s\n","*     __    __ _ _ _         __    __                  _          ");
	// printf("%s\n","*    / / /\ \ (_| | |_   _  / / /\ \ \__ _ _ __   __ _| | ___   _ ");   
	// printf("%s\n","*    \ \/  \/ | | | | | | | \ \/  \/ / _` | '_ \ / _` | |/ | | | |");   
	// printf("%s\n","*     \  /\  /| | | | |_| |  \  /\  | (_| | | | | (_| |   <| |_| |");   
	// printf("%s\n","*      \/  \/ |_|_|_|\__, |   \/  \/ \__,_|_| |_|\__, |_|\_\\__, |");   
	// printf("%s\n","*               __   |___/         _     _       |___/      |___/ ");   
	// printf("%s\n","*              / / /\ \ \___  _ __| | __| |                       ");   
	// printf("%s\n","*              \ \/  \/ / _ \| '__| |/ _` |                       ");   
	// printf("%s\n","*               \  /\  | (_) | |  | | (_| |                       ");   
	// printf("%s\n","*                \/  \/ \___/|_|  |_|\__,_|                       ");   
	// printf("%s\n","*                                                                 ");
	printf("%s\n","==================================================================");
	printf("%s\n","==================================================================");                                 
}

void PrintGame() {
	if (Elmt(mapRoom,px,py) == '>' || Elmt(mapRoom,px,py) == '<' || Elmt(mapRoom,px,py) == '^' || Elmt(mapRoom,px,py) == 'V' ) {
		switch (Elmt(mapRoom,px,py)){
		case '>':
			if (cmap == 0) {
				cmap = 1;
				px = 2 ;
				py = 1 ;
			} else {
				cmap = 2;
				px = 2 ;
				py = 1 ;
			}
			break;
		case '^':
			if (cmap == 3) {
				cmap = 0;
				px = 5 ;
				py = 6 ;
			} else {
				cmap = 1;
				px = 3 ;
				py = 2 ;
			}
			break;
		case '<':
			if (cmap == 1) {
				cmap = 0;
				px = 3 ;
				py = 11;
			} else {
				cmap = 3;
				px = 3 ;
				py = 7 ;
			}
			break;
		default:
			if (cmap == 0) {
				cmap = 3;
				px = 1 ;
				py = 4 ;
			} else {
				cmap = 2;
				px = 1 ;
				py = 4 ;
			}
			break;
		}
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,px,py);
	printf("%s\n","                                                                  ");
}

void PrintMain(){
	switch (state) {
	case FASE_GAME:
		PrintGame();
		break;
	
	default:
	printf("%s","Bukan state game");
		break;
	}
}

boolean IsBisaDilewati(char c){
	return (c=='^' || c=='>' || c=='<' || c=='V' || c=='-');
}

void BacaInput(){
	int inpt = GetInput();
	switch (state) {
	case FASE_GAME:
		if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,px-1,py))) {
			px = px -1;
		} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,px,py-1))) {
			py = py -1;
		} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,px+1,py))) {
			px = px +1;
		} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,px,py+1))) {
			py = py +1 ;
		} else {

		}
		break; 
	
	default:
		printf("%s","Input tidak valid");
		break;
	}
}

void UserInterface(){
	clrscr();
	PrintJudul();
	printf("%s\n", "Hello Guys");
	PrintMain();
	printf("%s\n","==================================================================");
	printf("%s\n","=================================================================="); 
	BacaInput();
	UserInterface();
}


int main(){
	printf("%s\n","==================================================================");
	GameSetup();
	TulisMATRIKS(map[0],0,0);
	UserInterface();
}