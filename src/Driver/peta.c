// ======================================Include Kebutuhan ADT============================================
#include "../Header/Input.h"
#include "../Header/matriks.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/stackt.h"
#include "../Header/point.h"
#include <stdio.h>
#include <string.h>
// =======================================================================================================

// ======================================Pendefinisian State di dalam Game================================
#define MAIN_MENU 0
#define NEW_GAME 1
#define LOAD_GAME 2
#define MAIN_DAY 3
#define PREPARATION_DAY 4
#define OFFICE 5
#define OFFICE_DETAIL 6
#define OFFICE_REPORT 7
#define DETAIL_WAHANA 8
// =======================================================================================================

// =========================Pendefinisian global variabel yang akan dipakai===============================
int cmap;
int state;
MATRIKS map[5], mapRoom;
POINT playerpos ;
int pmoney;
Stack aksi;
int count_aksi, need_money;
// Dan masih banyak variabel lain , sambil menunggu adt jadi
// =======================================================================================================

// =========================================Fungsi MainDay================================================

boolean IsBisaDilewati(char c){
	// Return true apabila c adalah karakter yang bisa ditindih player
	return (c=='^' || c=='>' || c=='<' || c=='V' || c=='-'|| c=='P');
}

void InputMainDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
	} else if (inpt == INPUT_i){
		state = PREPARATION_DAY;
	} else {

	}
}

void PrintMainDay() {
	// Menampilkan informasi pada bagian inti game saat mainday
	if (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '>' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '<' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '^' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == 'V' ) {
		switch (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos))){
		case '>':
			if (cmap == 0) {
				cmap = 1; Absis(playerpos) = 2; Ordinat(playerpos) = 1;
			} else {
				cmap = 2; Absis(playerpos) = 2; Ordinat(playerpos) = 1;
			}
			break;
		case '^':
			if (cmap == 3) {
				cmap = 0; Absis(playerpos) = 5; Ordinat(playerpos) = 6;
			} else {
				cmap = 1; Absis(playerpos) = 3; Ordinat(playerpos) = 2;
			}
			break;
		case '<':
			if (cmap == 1) {
				cmap = 0; Absis(playerpos) = 3; Ordinat(playerpos) = 11;
			} else {
				cmap = 3;  Absis(playerpos) = 3; Ordinat(playerpos) = 7;
			}
			break;
		default:
			if (cmap == 0) {
				cmap = 3; Absis(playerpos) = 1; Ordinat(playerpos) = 4;
			} else {
				cmap = 2; Absis(playerpos) = 1; Ordinat(playerpos) = 4;
			}
			break;
		}
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,Absis(playerpos),Ordinat(playerpos));
	printf("%s\n","");
	printf("Nama : %s 	Uang: %d	Waktu tersisa: %d\n", "stranger", pmoney, 0);
	// Masih harus ngeprint data data seperti queue , broken wahana dll
}

// =======================================================================================================

// ========================================Fungsi Preparation Day=========================================
void InputPreparationDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
	} else if (inpt == INPUT_i){
		state = MAIN_DAY;
	} else {

	}
}


void PrintPreparationDay() {
	// Menampilkan informasi pada bagian inti game saat preparation day
	if (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '>' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '<' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '^' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == 'V' ) {
		switch (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos))){
		case '>':
			if (cmap == 0) {
				cmap = 1; Absis(playerpos) = 2; Ordinat(playerpos) = 1;
			} else {
				cmap = 2; Absis(playerpos) = 2; Ordinat(playerpos) = 1;
			}
			break;
		case '^':
			if (cmap == 3) {
				cmap = 0; Absis(playerpos) = 5; Ordinat(playerpos) = 6;
			} else {
				cmap = 1; Absis(playerpos) = 3; Ordinat(playerpos) = 2;
			}
			break;
		case '<':
			if (cmap == 1) {
				cmap = 0; Absis(playerpos) = 3; Ordinat(playerpos) = 11;
			} else {
				cmap = 3;  Absis(playerpos) = 3; Ordinat(playerpos) = 7;
			}
			break;
		default:
			if (cmap == 0) {
				cmap = 3; Absis(playerpos) = 1; Ordinat(playerpos) = 4;
			} else {
				cmap = 2; Absis(playerpos) = 1; Ordinat(playerpos) = 4;
			}
			break;
		}
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,Absis(playerpos),Ordinat(playerpos));
	printf("%s\n","");
	printf("Nama : %s		Uang: %d		Waktu tersisa: %d\n", "stranger", pmoney, 0);
	printf("Aksi yang akan dilakukan : %d		Uang yang dibutuhkah: %d		Waktu yang dibutuhkan: %d\n", count_aksi, need_money, 0);
	// Masih harus ngeprint data data seperti stack dll
}

// =======================================================================================================


// =========================================Fungsi Umum===================================================
void GameSetup (){
	// Setup awal untuk memulai game
	cmap = 0;
	BacaMATRIKS(&map[1], "../file/1.txt");
	BacaMATRIKS(&map[0], "../file/0.txt");
	BacaMATRIKS(&map[2], "../file/2.txt");
	BacaMATRIKS(&map[3], "../file/3.txt");
	Absis(playerpos) = 1;
	Ordinat(playerpos)= 1;
	state = MAIN_DAY;
	CopyMATRIKS(map[cmap], &mapRoom);
	CreateEmpty(&aksi);
	count_aksi = 0 ;
	need_money = 0 ;
	pmoney = 10000 ;
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
	printf("%s\n","			Willy Wangky World						 ");
	printf("%s\n","==================================================================");                                 
}

void PrintMain(){
	switch (state) {
	case MAIN_MENU:
		// Kebutuhan menu
		break;
	case NEW_GAME:
		// Kebutuhan newgame
		break;
	case LOAD_GAME:
		// Kebutuhan load game
		break;
	case MAIN_DAY:
		PrintMainDay();
		break;
	case PREPARATION_DAY:
		PrintPreparationDay();
		break;
	case OFFICE:
		// List menu office diprint dan dipilih
		break;
	case OFFICE_DETAIL:
		// Detail 
		break;
	case OFFICE_REPORT:
		// PrintPreparationDay();
		break;
	case DETAIL_WAHANA:
		// PrintPreparationDay();
		break;
	
	default:
	printf("%s","Bukan state game");
		break;
	}
}


void BacaInput(){
	int inpt = GetInput();
	switch (state) {
	case MAIN_MENU:
		// Input yang ada di main menu
		break;
	case NEW_GAME:
		// Input saat player mau new game
		break;
	case LOAD_GAME:
		// Input saat player mau load game
		break;
	case MAIN_DAY:
		InputMainDay(inpt);
		break;
	case PREPARATION_DAY:
		InputPreparationDay(inpt);
		break; 
	case OFFICE:
		// Input saat mengakses office
		break;
	case OFFICE_DETAIL:
		// Input saat mengakses office detail
		break;
	case OFFICE_REPORT:
		//Input saat mengakses office report
		break;
	case DETAIL_WAHANA:
		// Input saat menunjukan detail wahana
		break;
	default:
		printf("%s","Input tidak valid");
		break;
	}
}

void PrintFooter(){
	printf("%s\n","				Tombol aksi						 	 ");
	switch (state) {
	case MAIN_MENU:
		printf("%s\n","w : atas  s : bawah	 enter : pilih menu");
		break;
	case MAIN_DAY:
		printf("%s\n","	Main Day");
		printf("%s\n","	w : atas a : kiri  s : bawah  d: kanan i: masuk ke preparation day");
		break;
	case PREPARATION_DAY:
		printf("%s\n","	Preparation Day");
		printf("%s\n","	w : atas a : kiri  s : bawah  d: kanan i: masuk ke main day");
		break;
	case NEW_GAME:
		printf("%s\n","					       Masukkan Nama 						 ");
		printf("%s\n","		   ketik enter untuk next, ketik lainnya untuk back	     ");
		break;
	
	default:
		printf("%s\n","					       Masukkan Nama 						 ");
		printf("%s\n","		   ketik enter untuk next, ketik lainnya untuk back	     ");
		break;
	}
}
void UserInterface(){
	clrscr();
	PrintJudul();
	printf("%s\n","		Have fun working with this!!				");
	PrintMain();
	printf("%s\n","==================================================================");
	PrintFooter();
	printf("%s\n","=================================================================="); 
	BacaInput();
	UserInterface();
}
// =======================================================================================================

int main(){
	GameSetup();
	UserInterface();
}