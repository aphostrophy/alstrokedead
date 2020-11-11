// ======================================Include Kebutuhan ADT============================================
#include "../Header/Input.h"
#include "../Header/matriks.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include "../Header/stackt.h"
#include "../Header/point.h"
#include "../Header/arrayPair.h"
#include "../Header/jam.h"
#include "../Header/wahana.h"
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
#define INVENTORY 9
// =======================================================================================================

// =========================Pendefinisian global variabel yang akan dipakai===============================
int cmap;
int state;
MATRIKS map[5], mapRoom;
POINT playerpos ;
int pmoney;
Stack aksi;
int count_aksi, need_money;
TabInt Materials, Inventory;
JAM time ;
Wahana wahana;

// Dan masih banyak variabel lain , sambil menunggu adt jadi
// =======================================================================================================

// =========================================Fungsi MainDay================================================

void UpdateWaktu(int n){
	time = NextNMenit(time,n);
	int broke = rand() % 2000;
	if(broke == 69 || broke == 420 || broke == 34) {
		int machine = rand() % 8;
		if(wahana.TI[machine].status == 'G') {
			wahana.TI[machine].status = 'B';
			printf("OH NO!!! %s broke. Please repair it ASAP!!!\n", wahana.TI[machine].nama);
			printf("Tekan tombol enter untuk melanjutkan permainan!!\n");
			getchar();
		}
	}

	if (state == MAIN_DAY && JAMToMenit(time) >= 1260) {
		state = PREPARATION_DAY;
	} else if (state == PREPARATION_DAY && JAMToMenit(time) >= 540 && JAMToMenit(time) <= 560){
		state = MAIN_DAY;
	}
}

boolean IsBisaDilewati(char c){
	// Return true apabila c adalah karakter yang bisa ditindih player
	return (c=='^' || c=='>' || c=='<' || c=='V' || c=='-'|| c=='P' || c=='O');
}

char getBangunanSekitar(){
	if (Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos))!='*' && Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos))!='O' &&Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos))!='-'){
		return Elmt(mapRoom, Absis(playerpos)+1, Ordinat(playerpos));
	} else if (Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1)!='*' && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1)!='O' &&Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1)!='-'){
		return Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)+1);
	} else if (Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos))!='*' && Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos))!='O' &&Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos))!='-'){
		return Elmt(mapRoom, Absis(playerpos)-1, Ordinat(playerpos));
	} else if (Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1)!='*' && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1)!='O' &&Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1)!='-'){
		return Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)-1);
	} else {
		return '*';
	}
}

void InputMainDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_i){
		state = PREPARATION_DAY;
		Hour(time) = 21 ;
		Minute(time) = 0;
	} else if (inpt == INPUT_1 && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)) == 'O') {
		state = OFFICE;
	} else if (inpt == INPUT_2 && getBangunanSekitar() != 'A' && getBangunanSekitar() != '*') {
		printDetailWahana(&wahana, getBangunanSekitar());	
		getchar();
	}
}

void PrintMainDay() {
	JAM tutup;
	Hour(tutup) = 21;
	Minute(tutup) = 0;
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
	printf("Nama : %s 	Uang: %d	Waktu tersisa: %d menit\n ", "stranger", pmoney, Durasi(time, tutup));
	printf("%s","Jam : ");
	TulisJAM(time);
	printf("\n");
	printBrokenWahana(&wahana);
	printf("%s\n","");
	// Masih harus ngeprint data data seperti queue , broken wahana dll
}

// =======================================================================================================

// ========================================Fungsi Preparation Day=========================================
void HandleBuy() {
	char action[100] ; char method[100] ; char barang[100]; char jumlah[100];
	int jumlah2;
	printf("Selamat Datang ke Menu Pembelian\n");
	printf("Daftar Barang yang dapat dibeli: \n");
    ArrayPair_TulisIsiTabNumbering(Materials);printf("\n");
	printf("Masukkan Barang yang ingin dibeli: ");
	scanf("%s",&method); scanf("%s",&jumlah); scanf("%s",&barang);getchar();
	jumlah2 = atoi(jumlah);
	// Validasi apakah yang diketik benar benar "buy"
	// Validasi apakah uang masih cukup dan validasi apakah waktu cukup , kalau ada validasi lain jg sabi
	// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, kalo tidak keluarkan pesan error
	strcpy(action,""); strcat(action,method); strcat(action," "); strcat(action,jumlah); strcat(action," "); strcat(action,barang);
	Push(&aksi,action);
}

void HandleBuild(){
	char action[100] ; char method[100] ; char bangunan[100]; char choice; char SbuildX[100]; char SbuildY[100]; char SbuildMap[100];
	int PbuildX = 0; int PbuildY = 0; int PbuildMap = cmap;  //Membangun di koordinat (PbuildX,Pbuildy) di peta PbuildMap
	printf("Selamat Datang ke Menu Pembangunan\n");
	printf("Ingin membangun diposisi mana (w/a/s/d): \n");
	scanf("%c",&choice);
	// Mendapatkan lokasi mau dibangun dimana
	if (choice == 'w') { PbuildX = Absis(playerpos) -1 ; PbuildY = Ordinat(playerpos) ;} 
	else if (choice == 'a' ){ PbuildX = Absis(playerpos) ; PbuildY = Ordinat(playerpos)-1 ;} 
	else if (choice == 's' ){ PbuildX = Absis(playerpos) +1 ; PbuildY = Ordinat(playerpos) ;} 
	else if (choice == 'd' ){ PbuildX = Absis(playerpos)  ; PbuildY = Ordinat(playerpos) + 1 ;}
	printf("Daftar Bangunan yang dapat dibangun: \n");
	printNotBuilded(&wahana);
	printf("Masukkan Bangunan yang ingin dibangun: ");
	scanf("%s",&method); scanf("%s",&bangunan); getchar();
	// Validasi apakah yang diketik benar benar "build"
	// Validasi apakah uang masih cukup dan validasi apakah waktu cukup , validasi apakah bahan bangunan cukup
	// Validasi apakah tempat yang dipilih emang bisa dibangun, dan kalo ada validasi lagi juga sabi
	// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, tambah bahan bangunan yang dibutuhkan, kalo tidak keluarkan pesan error
	sprintf(SbuildX, "%d", PbuildX); sprintf(SbuildY, "%d", PbuildY); sprintf(SbuildMap, "%d", PbuildMap); sprintf(SbuildY, "%d", PbuildY);
	// itoa(PbuildY, SbuildY, 10); itoa(PbuildX, SbuildX, 10); itoa(PbuildMap, SbuildMap, 10);
	strcpy(action,""); strcat(action,method); strcat(action," "); strcat(action,bangunan); strcat(action," "); strcat(action,SbuildX);strcat(action," "); strcat(action,SbuildY);strcat(action," "); strcat(action,SbuildMap);
	Push(&aksi,action);
}

void HandleUpgrade(){
	char action[100] ; char method[100] ; char upgrade[100]; 
	char bangunan = getBangunanSekitar();
	if (bangunan != '*'){
		printf("Selamat Datang ke Menu Upgrade\n");
		printf("Daftar Upgrade: \n");
		// Ambil upgrade dari si bangunan dengan state sekarang
		printf("Masukkan Upgrade yang ingin dilakukan: ");
		scanf("%s",&method); scanf("%s",&upgrade);
		// Validasi apakah yang diketik benar benar "upgrade"
		// Validasi apakah uang masih cukup dan validasi apakah waktu cukup , validasi apakah bahan bangunan cukup untuk upgrade
		// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, tambah bahan bangunan yang dibutuhkan, kalo tidak keluarkan pesan error
		strcpy(action,""); strcat(action,method); strcat(action," "); strcat(action,upgrade);
		Push(&aksi,action);
	}

}

void HandleUndo(){
	if(!IsEmptyStack(aksi)){
		infotype x ;
		Pop(&aksi,&x);
		if (x[0] == 'b' && x[2] == 'y'){
			char benda[100]; int n; 
			AkuisisiBuy(x,&n,benda);
			printf("%c %d", benda[0] , n); getchar(); // Ini gw tes dengan ngeprint wkwk
			// Karena input sudah bisa di parse maka sisanya mestinya mudah
			// Kurangi waktu yang dibutuhkan dari buy
			// Kurangi uang yang dibutuhkan dari buy material 'benda' ini sejumlah 'n'
		} else if (x[0] == 'b' && x[2] == 'i') {
			int PbuildX; int PbuildY; int PbuildMap; char bangunan[100];
			AkuisisiBuild(x,&PbuildX,&PbuildY,&PbuildMap,bangunan);
			printf("%d %d %d %c", PbuildX,PbuildY,PbuildMap,bangunan[0]); getchar(); // Ini gw tes dengan ngeprint wkwk
			// Karena input sudah bisa di parse maka sisanya mestinya mudah
			// Kurangi waktu yang dibutuhkan dari buy
			// Kurangi uang yang dibutuhkan dari buy material 'benda' ini sejumlah 'n'
		} else if (x[0] == 'u'){
			printf("upgrade"); getchar();
		}
	}
}

void HandleExecution(){
	infotype x;
	// Tambah waktu sekarang dengan waktu dibutuhkan total
	// Kurangi uang dengan uang yang dibutuhkan 
	// Kurangi material dengan semua material dibutuhkan
	Reverse(&aksi);
	while(!IsEmptyStack(aksi)){
		Pop(&aksi,&x);
		if (x[0] == 'b' && x[2] == 'y'){
			char benda[100]; int n; 
			AkuisisiBuy(x,&n,benda);
			printf("%c %d", benda[0] , n); getchar(); // Ini gw tes dengan ngeprint wkwk
			// Karena input sudah bisa di parse maka sisanya mestinya mudah
			// Tambah material 'benda' di inventory sesuai jumlah 'n'
		} else if (x[0] == 'b' && x[2] == 'i') {
			int PbuildX; int PbuildY; int PbuildMap; char bangunan[100];
			AkuisisiBuild(x,&PbuildX,&PbuildY,&PbuildMap,bangunan);
			// Karena input sudah bisa di parse maka sisanya mestinya mudah
			Elmt(map[PbuildMap],PbuildX,PbuildY) = bangunan[0];
			// Set Status dari wahana yang dibabngun menjadi aktif
		} else if (x[0] == 'u'){
			printf("upgrade"); getchar();
		}
	}
}

void InputPreparationDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
		UpdateWaktu(1);
	} else if (inpt == INPUT_i){
		state = MAIN_DAY;
		Hour(time) = 9 ;
		Minute(time) = 0;
		infotype x;
		while(!IsEmptyStack(aksi)){
			Pop(&aksi,&x);
		}
	} else if (inpt == INPUT_b){
		HandleBuy();
	} else if (inpt == INPUT_1){
		state = INVENTORY;
	} else if (inpt == INPUT_l) {
		HandleBuild();
	} else if(inpt == INPUT_k) { 
		HandleUpgrade();
	} else if (inpt == INPUT_j){
		HandleUndo();
	} else if (inpt == INPUT_2){
		HandleExecution();
	}
}


void PrintPreparationDay() {
	// Menampilkan informasi pada bagian inti game saat preparation day
	JAM buka;
	Hour(buka) = 9;
	Minute(buka) = 0;
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
	printf("Nama : %s		Uang: %d		Waktu tersisa: %d menit\n", "stranger", pmoney, Durasi(time, buka));
	printf("Aksi yang akan dilakukan : %d		Uang yang dibutuhkan: %d		Waktu yang dibutuhkan: %d\n", count_aksi, need_money, 0);
	printf("%s","Jam : ");
	TulisJAM(time);
	printf("\n");
	printBrokenWahana(&wahana);
	// Tulis Material yang dibutuhkan
	printf("%s\n","");
	printf("%s\n","==================================================================");
	printf("%s\n","Stack of Your Action");
	PrintStack(aksi);
	printf("%s\n","==================================================================");
	// Masih harus ngeprint data data seperti stack dll
}

void InputOffice() {
	char input[100];
	scanf("%s", &input);
	getchar();
	if(strcmp(input, "Details") == 0) {
		printf("Daftar Wahana :\n");
		printListWahana(&wahana);
		printf("\n");

		char id;
		printf("Masukkan ID Wahana yang ingin dilihat detailnya : ");
		scanf("%c", &id);
		getchar();
		printDetailWahana(&wahana, id);
		printf("\nTekan sembarang tombol untuk kembali ke menu office");
		getchar();
		UpdateWaktu(5);
	} else if (strcmp(input, "Report") == 0) {
		printf("Daftar Wahana :\n");
		printListWahana(&wahana);
		printf("\n");

		char id;
		printf("Masukkan ID Wahana yang ingin dilihat reportnya : ");
		scanf("%c", &id);
		getchar();
		printReportWahana(&wahana, id);
		printf("\nTekan sembarang tombol untuk kembali ke menu office");
		getchar();
		UpdateWaktu(5);
	} else if (strcmp(input, "Exit") == 0) {
		state = MAIN_DAY;
	}
}

// =======================================================================================================


// =========================================Fungsi Umum===================================================
void GameSetup (){
	// Setup awal untuk memulai game
	cmap = 0;
	ArrayPair_MakeEmpty(&Materials);
	ArrayPair_MakeEmpty(&Inventory);
	BacaMATRIKS(&map[1], "../file/1.txt");
	BacaMATRIKS(&map[0], "../file/0.txt");
	BacaMATRIKS(&map[2], "../file/2.txt");
	BacaMATRIKS(&map[3], "../file/3.txt");
	ArrayPair_BacaIsi(&Materials, "../Saves/Materials.txt");
	ArrayPair_BacaIsi(&Inventory, "../Saves/Inventory.txt");
	Absis(playerpos) = 1;
	Ordinat(playerpos)= 1;
	state = MAIN_DAY;
	CopyMATRIKS(map[cmap], &mapRoom);
	CreateEmpty(&aksi);
	count_aksi = 0 ;
	need_money = 0 ;
	pmoney = 10000 ;
	Hour(time) = 9 ;
	Minute(time) = 0 ;
	makeListWahana(&wahana);
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
		printf("\nSELAMAT DATANG DI OFFICE WILLY WANGKY'S WORLD!!!\n\n");
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
	case INVENTORY:
		printf("Inventory Anda\n");
		ArrayPair_TulisIsiTab(Inventory);printf("\n");
		break;
	default:
	printf("%s","Bukan state game");
		break;
	}
}


void BacaInput(){
	int inpt;
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
		inpt = GetInput();
		InputMainDay(inpt);
		break;
	case PREPARATION_DAY:
		inpt = GetInput();
		InputPreparationDay(inpt);
		break; 
	case OFFICE:
		// Input saat mengakses office
		InputOffice();
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
	case INVENTORY: 
	if (inpt == INPUT_ENTER){
		state = PREPARATION_DAY;
	}
		break ;
	default:
		printf("%s","Input tidak valid");
		break;
	}
}

void PrintFooter(){
	switch (state) {
	case MAIN_MENU:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","w : atas  s : bawah	 enter : pilih menu");
		break;
	case MAIN_DAY:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Main Day");
		printf("%s\n","	w : atas a : kiri  s : bawah  d: kanan i: masuk ke preparation day");
		break;
	case PREPARATION_DAY:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Preparation Day");
		printf("%s\n","	w : atas a : kiri  s : bawah  d: kanan i: masuk ke main day");
		printf("%s\n"," b: buy l : build k : upgrade j : undo 2 : execute 1 : inventory" ); 
		break;
	case INVENTORY:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","	Inventory ");
		printf("%s\n","	Tekan Enter untuk kembali ke Preparation Phase");
		break;
	case NEW_GAME:
		printf("%s\n","				Tombol aksi						 	 ");
		printf("%s\n","					       Masukkan Nama 						 ");
		printf("%s\n","		   ketik enter untuk next, ketik lainnya untuk back	     ");
		break;
	case OFFICE:
		printf("%s\n","		           Tombol aksi				 ");
		printf("\n%s\n","Details : Lihat Detail Wahana, Report : Melihat Report Wahana, \nExit : Keluar dari Office");
	default:
		printf("\n");
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