// ======================================Include Kebutuhan ADT============================================
#include "../Header/Input.h"
#include "../Header/matriks.h"
#include "../Header/boolean.h"
#include "../Header/mesinkar.h"
#include "../Header/mesinkata.h"
#include "../Header/stackt2.h"
#include "../Header/point.h"
#include "../Header/arrayPair.h"
#include "../Header/jam.h"
#include "../Header/wahana.h"
#include "../Header/graph.h"
#include "../Header/bintree.h"
#include "../Header/arrayTriplet.h"
#include "../Header/list_linkedlist.h"
#include "../Header/queue.h"
#include <stdio.h>
#include <stdlib.h>
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
#define EXIT_GAME 10
// =======================================================================================================

// =========================Pendefinisian global variabel yang akan dipakai===============================
Kata namaPlayer; Kata CKata; Kata NamaSaveFile, NamaLoadFile;
int cmap, state, pmoney, count_aksi, need_money, need_time, NewPengunjung; 
MATRIKS map[5], mapRoom;
POINT playerpos ;
Stack aksi;
TabInt Materials, Inventory, need_material, HargaBuild, MaterialBuild, ActionTime;
Triplet_TabInt UpgradeCosts, UpgradeEffect;
JAM time ;
Wahana wahana;
boolean EndKata;
ListNode *link[20] = { 0 }; // Inisialisasi semua linked list dengan null, untuk load game bisa dilakukan add upgrade manual
char ChoosenWahana;
Queue MGLOBAL, QGLOBAL; 
Graph denah;
struct SaveDat {
  int cmap;
	int state;
	POINT playerpos;
	int pmoney;
	JAM time;
	Wahana wahana;
	int count_aksi, need_money, need_time;
	TabInt Inventory, need_material;
	Stack aksi;
	Kata link[20]; 
	MATRIKS map[5];
};
// =======================================================================================================


// ==================================== Fungsi Save dan Load  =============================================
void SetupSaveGame (FILE *savefile){
	// Data - Data dinamis yang akan di save dan dimasukkan kedalam file akan di handle melalui fungsi ini
	
	// Pengisian Struct 
	struct SaveDat TempSave;
	TempSave.cmap = cmap;
	TempSave.state = state;
	TempSave.playerpos = playerpos;
	TempSave.pmoney = pmoney;
	TempSave.wahana = wahana;
	TempSave.count_aksi = count_aksi ; TempSave.need_money = need_money; TempSave.need_time = need_time;
	TempSave.Inventory = Inventory;
	TempSave.aksi = aksi;
	TempSave.time = time;
	for( int i = 0; i < 20;i++){
		printf("Save File");printf("\n");
		printKata(saveUpgrade(&link[i]));printf("\n");
		TempSave.link[i] = saveUpgrade(&link[i]);
	}
	TempSave.need_material = need_material;
	for (int i = 0; i < 5; i++) TempSave.map[i] = map[i];
	
	// Penulisan struct kedalam file
	fwrite(&TempSave, sizeof(struct SaveDat), 1, savefile);
	if(fwrite != 0){
		printf("Contents to file written successfully!"); getchar();
	} else { 
		printf("Error writing file!"); getchar();
	}
	fclose(savefile);
}

void HandleSaveGame (){
	// Saat player akan mengesave-file maka fungsi ini akan melakukan prepare yang dibutuhkan seperti 
	// memasukkan nama file dll dan dilanjutkan dengan setupSaveGame

	// Deklarasi Kata
	Kata FILEPATH; FILEPATH.Length = 9; FILEPATH.TabKata[0] = '.'; FILEPATH.TabKata[1] = '.'; FILEPATH.TabKata[2] ='/';  FILEPATH.TabKata[3] ='S';  FILEPATH.TabKata[4] ='a';  FILEPATH.TabKata[5] = 'v'; FILEPATH.TabKata[6] ='e';  FILEPATH.TabKata[7] ='s';  FILEPATH.TabKata[8] ='/'; 
	NamaSaveFile.Length = 0;NamaSaveFile.TabKata[0]='X'; //Pengganti strcpy;
	NamaSaveFile = KataConcat(NamaSaveFile,FILEPATH); NamaSaveFile = KataConcat(NamaSaveFile,namaPlayer);
	
	// Membuka file dan memvalidasi apakah filenya tidak error
	FILE *savefile;
	savefile = fopen(NamaSaveFile.TabKata, "w");
	if (savefile){
		if (savefile== NULL){ 
			fclose(savefile);
			printf("Error File Content, Press anything to continue"); getchar();
		} else {
			SetupSaveGame(savefile);
		} 
	} else {
		fclose(savefile);
		printf("Invalid File Name, Press anything to continue"); getchar();
	}

}


void SetupLoadGame (FILE *loadfile){
	// Data - Data dinamis yang akan di load dan dimasukkan kedalam game akan di handle melalui fungsi ini

	// Pengisian Global Variable dengan Struct
	struct SaveDat TempSave;
	fread(&TempSave, sizeof(struct SaveDat), 1, loadfile);
	cmap = TempSave.cmap; 	
	state = TempSave.state;		
	playerpos = TempSave.playerpos;	
	pmoney = TempSave.pmoney;	
	wahana = TempSave.wahana;
	count_aksi = TempSave.count_aksi; need_money = TempSave.need_money; need_time = TempSave.need_time;
	Inventory = TempSave.Inventory;
	aksi = TempSave.aksi;
	time = TempSave.time;
	// Akuisisi Upgrade dari struct
	for(int i=0;i<20;i++){
		Kata SENTINEL; SENTINEL.TabKata[0]='X';SENTINEL.Length=1;
		int y=10;
		int index=0;int realLength=0;
		if(!IsKataSama(TempSave.link[i],SENTINEL)){
			while(index<TempSave.link[i].Length){
				Kata data;
				realLength = 0;
				while(TempSave.link[i].TabKata[index]!=' ' && index<TempSave.link[i].Length){
					data.TabKata[realLength] = TempSave.link[i].TabKata[index];
					index++;
					realLength++;
				}
				data.Length = realLength;
				addUpgrade(&link[i],data);
				index++; //Untuk skip spasi
				if(TempSave.link[i].TabKata[index]=='X') break;
			}
		}
	}
	need_material = TempSave.need_material;
	for (int i = 0; i < 5; i++) map[i] = TempSave.map[i];
	fclose(loadfile);
	CopyMATRIKS(map[cmap], &mapRoom);
}

void SetupNewGame (){

	// Data - Data dinamis sebagai data starter saat player melakukan new game akan di inisialisasi di sini

	// Pembacaan data-data newgame
 	NewPengunjung =1;
	ArrayPair_MakeEmpty(&need_material);
	ArrayPair_BacaIsi(&need_material, "../Saves/Inventory.txt");
	cmap = 0;
	state = MAIN_DAY;
	GenerateQueue(&QGLOBAL,wahana);
	MakeEmpty_Queue(&MGLOBAL, 10);
	Absis(playerpos) = 1; Ordinat(playerpos)= 1;
	pmoney = 10000 ;
	bacaWahana(&wahana, "../file/wahana.txt");
	count_aksi = 0 ; need_money = 0 ;
	ArrayPair_MakeEmpty(&Inventory); ArrayPair_BacaIsi(&Inventory, "../Saves/Inventory.txt");
	CreateEmpty(&aksi);	
	Hour(time) = 9 ; Minute(time) = 0 ;
	CopyMATRIKS(map[cmap], &mapRoom);
}
// =======================================================================================================

// =================================Fungsi Transisi Day ==================================================
void PrepToMainDay(){

	// Fungsi ini akan melakukan perubahan variabel global dari preparation day ke main day

	// Uang ,Waktu, Aksi, dan material dibutuhkan jadi 0. Queue pengunjung mulai di generate
  
  NewPengunjung = 1;
	need_money = 0;
	need_time = 0;
	for (int i = ArrayPair_GetFirstIdx(Inventory) ; i <= ArrayPair_GetLastIdx(Inventory) ; i ++){ 
		Pair_Cost(need_material,i) = 0 ;
	} 
	count_aksi = 0 ;
	GenerateQueue(&QGLOBAL,wahana);
	MakeEmpty_Queue(&MGLOBAL,10);
}
void MaintoPrepDay(){
	// Fungsi ini akan melakukan perubahan variabel global dari main day ke preparation day

	// Rubah semua wahana yang rusak menjadi bagus
	for (int i = 0 ; i < 8 ; i++){
		if(wahana.TI[i].status == 'B') {
			wahana.TI[i].status = 'G';
		}
	}
	// Kosongkan Antrian dan Kosongkan Array orang sedang naik Wahana
	EmptyQueue(&QGLOBAL);
	EmptyQueue(&MGLOBAL);
}
// =======================================================================================================

// =========================================Fungsi MainDay================================================

void UpdateWaktu(int n){
	// Fungsi ini akan melakukan perubahan waktu akibat suatu aksi dan melakukan standar pengecekan saat waktu berubah

	time = NextNMenit(time,n);
	// Standar pengecekan main-day : validasi waktu tutup, generate broken wahana, validasi dan kurangi waktu pengunjung
	if (state == MAIN_DAY) {
		if (JAMToMenit(time) >= 1260){
			state = PREPARATION_DAY;
			MaintoPrepDay();
		} else {
			int broke = rand() % 100;
			if(broke >= 95)  {
				int machine = rand() % 8;
				if(wahana.TI[machine].status == 'G') {
					wahana.TI[machine].status = 'B';
					printf("OH NO!!! "); printKata(wahana.TI[machine].nama); printf(" broke. Please repair it ASAP!!!\n"); 
					printf("Tekan tombol enter untuk melanjutkan permainan!!\n");
					getchar();
				}
			}
			LeaveWahanaBroke(&MGLOBAL,&QGLOBAL,wahana);
			ReduceTime(&MGLOBAL,n,wahana);
			LeaveQueueS(&QGLOBAL);
			LeaveQueueT(&MGLOBAL,&QGLOBAL,wahana);
			int pengunjungDatang = rand() % 100;
			if (pengunjungDatang >= 80 && QGLOBAL.TAIL<3 && IsAdaWahanaGood(wahana)){
				pengunjung P;
				GeneratePengunjung(&P,5+NewPengunjung,(QGLOBAL.P[QGLOBAL.TAIL].X+1),wahana);
				Enqueue(&QGLOBAL,P);
				NewPengunjung=NewPengunjung+1;
			}
		}
	}
	// Standar pengecekan preparation-day : validasi waktu buka
	if (state == PREPARATION_DAY && JAMToMenit(time) >= 540 && JAMToMenit(time) <= 580){
		PrepToMainDay();
		state = MAIN_DAY;
	}
}

boolean IsBisaDilewati(char c){
	// Return true apabila c adalah karakter yang bisa ditindih player
	return (c=='^' || c=='>' || c=='<' || c=='V' || c=='-'|| c=='X' || c=='O');
}

boolean IsBisaDibangun (int PbuildX, int PbuildY, int sizeX, int sizeY ){
	// Return true apabila player bisa membangun bangunan seukuran sizeX baris dan sizeY kolom  dengan titik (Pbuildx,PbuildY) sebagai titik(0,0)
	
	// Algoritma pengecekan
	if (PbuildX + sizeX > GetLastIdxBrs(mapRoom) || (PbuildY + sizeY > GetLastIdxKol(mapRoom))){
		return false;
	} else {
		boolean bisaDibangun = true ;
		for (int i = PbuildX; i < PbuildX + sizeX; i++) {
			for (int j = PbuildY; j < PbuildY + sizeY; j++){
				printf("%c",Elmt(mapRoom,i,j));printf(" ");
				if ((Elmt(mapRoom,i,j)!='-')){
					bisaDibangun = false;
				}
			}
			printf("\n");
		}
		return bisaDibangun;
	}
}

char getBangunanSekitar(){
	// Mereturn char dari bangunan yang ada di atas atau kanan atau kiri atau bawah player (hanya return salah satu). Jika tidak ada bangunan maka return *
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

void RepairWahana(Wahana *W, char id) {
	// Membetulkan wahana di sekitar yang statusnya 'b' yaitu broke jika tidak ada wahana yang rusak atau tidak ada wahana maka tidak terjadi apa apa namun waktu akan tetap berjalan
    char status = getStatus(W,id);
    if (status == 'B') {
        (*W).TI[GetIndex(W,id)].status = 'G';
    }
}

void HandleServe(){
	Kata Action, Nama_Wahana;
    char bangunan = getBangunanSekitar();
    if(bangunan=='A'){
        printf("Mau serve untuk wahana apa? : ");
        Kata SERVE;
        int kata_ke = 1;
        SERVE.TabKata[0] = 's';SERVE.TabKata[1] = 'e';SERVE.TabKata[2] = 'r';SERVE.TabKata[3] = 'v';SERVE.TabKata[4] = 'e';
        SERVE.Length = 5;
        STARTBUY();
        while(!EOP){
            int i = 0;
            CKata.Length=0;
            while(CC!=BLANK){
                CKata.TabKata[i] = CC;
                if(CC=='\n'){
                    break;
                }
                i++;
                CKata.Length=i;
                ADV();
            }
            if(kata_ke==1){
                Action = CKata;
            } else if(kata_ke==2){
                Nama_Wahana = CKata;
            }
            if(CC=='\n'){
                break;
            }
            kata_ke++;
            IgnoreBlank();
        }
        if(IsKataSama(Action, SERVE)){
			if(IsWahanaBenar(Nama_Wahana,wahana)){
				Serve(&QGLOBAL,&MGLOBAL,Nama_Wahana.TabKata[0],&wahana,&pmoney);
				UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,SERVE)));
			}
			else{
				printf("Masukan wahana salah! Tekan apapun untuk melanjutkan\n");
				getchar();				
			}
        }
        else{
            printf("Command salah! Tekan apapun untuk melanjutkan\n");
            getchar();
        }
    }
    else{
		printf("Tidak ada antrian di sekitar Anda");
		getchar();       
    }
}

void InputMainDay (int inpt) {
	JAM tutup; Hour(tutup) = 21; Minute(tutup) = 0;
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu

	// Algortima menerima input
	Kata W; W.TabKata[0] = 'w'; W.Length = 1;
	Kata A; A.TabKata[0] = 'a'; A.Length = 1;
	Kata S; S.TabKata[0] = 's'; S.Length = 1;
	Kata D; D.TabKata[0] = 'd'; D.Length = 1;
	Kata SERVE; SERVE.TabKata[0] = 's';SERVE.TabKata[1] = 'e';SERVE.TabKata[2] = 'r';SERVE.TabKata[3] = 'v';SERVE.TabKata[4] = 'e'; SERVE.Length = 5;
	Kata Detail; Detail.TabKata[0] = 'd'; Detail.TabKata[1] = 'e'; Detail.TabKata[2] = 't'; Detail.TabKata[3] = 'a'; Detail.TabKata[4] = 'i'; Detail.TabKata[5] = 'l'; Detail.Length = 6;
	Kata Repair; Repair.TabKata[0] = 'r'; Repair.TabKata[1] = 'e'; Repair.TabKata[2] = 'p'; Repair.TabKata[3] = 'a'; Repair.TabKata[4] = 'i'; Repair.TabKata[5] = 'r'; Repair.Length = 6;
	// Jika input command bergerak maka validasi dan ubah posisi player jika validasi sukses
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) -1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,W)));
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		Ordinat(playerpos) = Ordinat(playerpos) -1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,A)));
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		Absis(playerpos) = Absis(playerpos) + 1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,S)));
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		Ordinat(playerpos) = Ordinat(playerpos) +1 ;
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,D)));
	// Jika input pindah phase maka lakukan prosedur pindah phase
	// Jika input adalah tindakan untuk aksi lain maka lakukan tindakan itu
	} else if (inpt == INPUT_i){
		state = PREPARATION_DAY;
		Hour(time) = 21 ;
		Minute(time) = 0;
		MaintoPrepDay();
	} else if (inpt == INPUT_1 && Elmt(mapRoom, Absis(playerpos), Ordinat(playerpos)) == 'O') {
		state = OFFICE;
	} else if (inpt == INPUT_e) {
		state = EXIT_GAME;
	} else if (inpt == INPUT_2 && getBangunanSekitar() != 'A' && getBangunanSekitar() != '*') {
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Detail)));
		ChoosenWahana = getBangunanSekitar();
		state = DETAIL_WAHANA;
	} else if ( inpt == INPUT_3){
		char id = getBangunanSekitar();
		RepairWahana(&wahana, id);
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Repair)));
	} else if (inpt == INPUT_4){
		if (Durasi(time, tutup) >= Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,SERVE))){
			HandleServe();
		} else {
			printf("Waktu tidak mencukupi untuk serve!"); getchar();
		}
	}
}

void PrintMainDay() {
	// Ini adalah fungsi untuk menampilkan user interface sisi tengah saat state adalah MAIN_DAY
	JAM tutup;
	Hour(tutup) = 21;
	Minute(tutup) = 0;
	// Menampilkan informasi pada bagian inti game saat mainday
	if (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '>' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '<' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '^' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == 'V' ) {
		infotypePeta CurrentPos;
		CurrentPos.map = cmap;
		Absis(CurrentPos.p) = Absis(playerpos);
		Ordinat(CurrentPos.p) = Ordinat(playerpos);
		adrPeta P = SearchPeta(denah,CurrentPos);
		adrTerowongan T = Gerbang(P);
		P = Graph_Succ(T);
		cmap = idPeta(P).map;
		Absis(playerpos) = Absis(idPeta(P).p);
		Ordinat(playerpos) = Ordinat(idPeta(P).p);
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,Absis(playerpos),Ordinat(playerpos));
	printf("\n");
	printf("Nama : %s 	Uang: %d	Waktu tersisa: %d menit\n ", namaPlayer.TabKata, pmoney, Durasi(time, tutup));
	printf("Jam : ");
	TulisJAM(time);
	printf("\n");
	printBrokenWahana(&wahana);
	printf("\n");
	printf("=======================Queue antrian pengunjung===================================\n\n");
	PrintQueue(QGLOBAL, 1);
	printf("=====================Queue pengunjung yang sedang naik wahana=====================\n\n");
	PrintQueue(MGLOBAL,2);
	// Masih harus ngeprint data data seperti queue , broken wahana dll
}

// =======================================================================================================



// ========================================Fungsi Preparation Day=========================================


void HandleBuy() {
	// Ini adalah fungsi untuk melakukan prosedur buy dan validasi di dalamnya, prosedur ini dilakukan jika waktunya cukup

	// Deklarasi variabel lokal
	Kata Action, StackEl, Barang, Jumlah;
	Kata SPASI; SPASI.TabKata[0] = ' ' ; SPASI.Length = 1;
	int jumlah_int;

	printf("Selamat Datang ke Menu Pembelian\n");
	printf("Daftar Barang yang dapat dibeli: \n");
    ArrayPair_TulisIsiTabNumbering(Materials);printf("\n");
	printf("Masukkan Barang yang ingin dibeli: ");
	// Akuisisi dengan mesinkata, algoritma membosankan
   	int kata_ke = 1;
	Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.Length = 3;
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
		if(kata_ke==1){
			Action = CKata;
		} else if(kata_ke==2){
			Jumlah = CKata;
		} else if(kata_ke==3){
			Barang = CKata;
		}
		if(CC=='\n'){
			break;
		}
		kata_ke++;
		IgnoreBlank();
    }
	// End of algortima membosankan

	// Validasi apakah yang diketik benar benar "buy", apakah uang masih cukup dan validasi apakah waktu cukup.
	// Kalau memang valid maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, kalo tidak keluarkan pesan error
	jumlah_int = KataToInt(Jumlah);
	int materialIndex = ArrayPair_SearchByItem(Materials,Barang);
	if(IsKataSama(Action,BUY) && materialIndex != IdxUndef){
		if(pmoney>=jumlah_int*Pair_Cost(Materials,materialIndex)+need_money){
			need_money = need_money + jumlah_int*Pair_Cost(Materials,materialIndex);
			StackEl.Length=0; StackEl.TabKata[0] ='X';
			StackEl = KataConcat(StackEl,Action);StackEl = KataConcat(StackEl,SPASI);StackEl = KataConcat(StackEl,Jumlah);StackEl = KataConcat(StackEl,SPASI);StackEl = KataConcat(StackEl,Barang);
			Push(&aksi,StackEl);
			count_aksi = count_aksi + 1;
			need_time = need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUY));
			Pair_Cost(Inventory,materialIndex) += jumlah_int;
			
		} else{ // Uang tidak cukup
			printf("Uang tidak cukup! Tekan apapun untuk melanjutkan\n");
			getchar();
		}
	} else{
		printf("Command salah! Tekan apapun untuk melanjutkan\n");
		getchar();
	}

}

void HandleBuild(){
	// Ini adalah fungsi untuk melakukan prosedur build dan validasi di dalamnya, prosedur ini dilakukan jika waktunya cukup

	// Deklarasi variabel lokal
	Kata SbuildX; Kata SbuildY; Kata SbuildMap; Kata SsizeBaris; Kata SsizeKolom;
	int PbuildX = 0; int PbuildY = 0; int PbuildMap = cmap; int sizeBaris; int sizeKolom;  //Membangun di koordinat (PbuildX,Pbuildy) di peta PbuildMap
	printf("Selamat Datang ke Menu Pembangunan\n");
	printf("Ingin membangun diposisi mana (w/a/s/d): \n");
	Kata Choice,BUILD,StackEl;
   	int kata_ke = 1;
    BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d';
    BUILD.Length = 5;
	
	// Algoritma akuisisi dengan mesinkata, algoritma membosankan
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
			ADV();
		}
		if(kata_ke==1){
			Choice = CKata;
		}
		if(CC=='\n'){
			break;
		}
		kata_ke++;
		IgnoreBlank();
	}
	// End of algoritma membosankan
	// Mendapatkan lokasi mau dibangun dimana beserta ukurannnya lalu divalidasi
	if(Choice.TabKata[0]=='w' || Choice.TabKata[0]=='a' || Choice.TabKata[0]=='s' || Choice.TabKata[0]=='d'){
		if (Choice.TabKata[0] == 'w') { PbuildX = Absis(playerpos) -1 ; PbuildY = Ordinat(playerpos) ;} 
		else if (Choice.TabKata[0] == 'a' ){ PbuildX = Absis(playerpos) ; PbuildY = Ordinat(playerpos)-1 ;} 
		else if (Choice.TabKata[0] == 's' ){ PbuildX = Absis(playerpos) +1 ; PbuildY = Ordinat(playerpos) ;} 
		else if (Choice.TabKata[0] == 'd' ){ PbuildX = Absis(playerpos)  ; PbuildY = Ordinat(playerpos) + 1 ;}
		printf("Masukkan Ukuran Wahana dengan titik wasd yang barusan dipilih sebagai koordinat (0.0) bangunan\n");
		printf("Masukkan dalam bentuk <baris Kolom>: ");
		scanf("%d %d", &sizeBaris, &sizeKolom); getchar();
		if (IsBisaDibangun(PbuildX,PbuildY,sizeBaris,sizeKolom)){
			printf("Daftar Bangunan yang dapat dibangun: \n");
			printNotBuilded(&wahana);
			printf("Masukkan Bangunan yang ingin dibangun: ");
			Kata Method, Bangunan;
			// Algoritma akuisisi dengan mesinkata, algoritma membosankan
			STARTBUY();
			while(!EOP && !EOL){
				int i = 0;
				CKata.Length=0;
				if(kata_ke==1){
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
						ADV();
					}
					Method = CKata;
				} else if(kata_ke==2){
					while(true){
						if(CC=='\r'){
							CC ='\n';
						}
						if(CC=='\n'){
							break;
						}
						CKata.TabKata[i] = CC;
						i++;
						CKata.Length=i;
						ADV();
					}
					Bangunan = CKata;
				}
				if(CC=='\n'){
					break;
				}
				kata_ke++;
				IgnoreBlank();
			}
			// End of algoritma membosankan

			// Validasi apakah yang diketik benar benar "build", apakah uang masih cukup, waktu cukup, dan bahan bangunan cukup.
			// Kalau memang valid maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, dan tambah bangunan yang dibutuhkan, kalo tidak keluarkan pesan error
			if(IsKataSama(Method,BUILD)){
				int bangunanIndex = ArrayPair_SearchByItem(HargaBuild,Bangunan);
				Kata AMBER;
				AMBER.TabKata[0] = 'A'; AMBER.TabKata[1] = 'm'; AMBER.TabKata[2] = 'b'; AMBER.TabKata[3] = 'e'; AMBER.TabKata[4] = 'r';
				AMBER.Length = 5;
				int materialIndex = ArrayPair_SearchByItem(Materials,AMBER);
				int banyakAmberdibutuhkan = Pair_Cost(MaterialBuild,ArrayPair_SearchByItem(MaterialBuild,Bangunan));
				if (pmoney < Pair_Cost(HargaBuild,bangunanIndex)+need_money){
					printf("Uang Tidak Mencukupi!");getchar();
				} else if (Pair_Cost(Inventory,materialIndex) < banyakAmberdibutuhkan){
					printf("Bahan Bangunan Tidak Mencukupi!");getchar();
				} else {
					Kata SPASI; SPASI.TabKata[0] = ' ' ; SPASI.Length = 1;
					Pair_Cost(need_material,materialIndex) = Pair_Cost(need_material,materialIndex) + banyakAmberdibutuhkan ;
					need_money = need_money + Pair_Cost(HargaBuild,bangunanIndex);
					for (int i = PbuildX; i < PbuildX + sizeBaris; i++) {
						for (int j = PbuildY; j < PbuildY + sizeKolom; j++){
							Elmt(map[PbuildMap],i,j) = Bangunan.TabKata[0]; 
						}
					}
					SbuildX = IntToKata(PbuildX); SbuildY = IntToKata(PbuildY); SbuildMap = IntToKata(PbuildMap); SsizeBaris = IntToKata(sizeBaris); SsizeKolom = IntToKata(sizeKolom);
					StackEl.Length=0; StackEl.TabKata[0]='X';
					StackEl = KataConcat(StackEl,Method); StackEl = KataConcat(StackEl,SPASI);StackEl = KataConcat(StackEl,Bangunan); StackEl = KataConcat(StackEl,SPASI); StackEl = KataConcat(StackEl,SbuildX); StackEl = KataConcat(StackEl,SPASI); StackEl = KataConcat(StackEl,SbuildY); StackEl = KataConcat(StackEl,SPASI); StackEl = KataConcat(StackEl,SbuildMap); StackEl = KataConcat(StackEl,SPASI);
					StackEl = KataConcat(StackEl,SsizeBaris); StackEl = KataConcat(StackEl,SPASI);StackEl = KataConcat(StackEl,SsizeKolom);
					Push(&aksi,StackEl);
					count_aksi = count_aksi + 1;
					(wahana).TI[GetIndex(&wahana, Bangunan.TabKata[0])].status ='O';
					need_time = need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUILD));
				}
			} else{
				printf("Invalid Command!");getchar();
			}	
		} else {
			printf("Tidak Bisa Membangun disitu");getchar();
		}
	} else{
		printf("Masukan yang diterima hanya w/a/s/d!");getchar();
		
	}

}

void HandleUpgrade(){
	// Ini adalah fungsi untuk melakukan prosedur upgrade dan validasi di dalamnya, prosedur ini dilakukan jika waktunya cukup

	// Deklarasi variabel lokal
	Kata Action, Nama_Upgrade, StackEl;
	Kata SPASI; SPASI.TabKata[0] = ' ' ; SPASI.Length = 1;
	// Dapatkan bangunan di sekitar, jika tidak ada beri pesan kesalahan, jika ada lanjukan prosedur
	// Validasi apakah yang diketik benar benar "upgrade"
	// Validasi apakah uang validasi apakah waktu cukup, validasi apakah bahan bangunan cukup untuk upgrade
	// Validasi juga apakah masih punya upgrade dan jika punya validasi upgrade yang diketik adalah hal yang benar
	// Kalo memang sabi maka push ke stack, tambah waktu yang dibtuhkan , tambah uang yang dibutuhkan, tambah bahan bangunan yang dibutuhkan, kalo tidak keluarkan pesan error
	char bangunan = getBangunanSekitar();
	if (bangunan != '*'){
		int indexWahana = bintree_findIndex(bangunan);
		printf("Selamat Datang ke Menu Upgrade\n");
		printf("Daftar Upgrade: \n");
		PrintAvailableUpgrade(bangunan, &link[indexWahana]);
		// Ambil upgrade dari si bangunan dengan state sekarang
		printf("Masukkan Upgrade yang ingin dilakukan: ");
		Kata UPGRADE;
		int kata_ke = 1;
		UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e';
		UPGRADE.Length = 7;
		// Akuisisi dengan mesinkata , algoritma membosankan	
		STARTBUY();
		while(!EOP){
			int i = 0;
			CKata.Length=0;
			while(CC!=BLANK){
				CKata.TabKata[i] = CC;
				if(CC=='\n'){
					break;
				}
				i++;
				CKata.Length=i;
				ADV();
			}
			if(kata_ke==1){
				Action = CKata;
			} else if(kata_ke==2){
				Nama_Upgrade = CKata;
			}
			if(CC=='\n'){
				break;
			}
			kata_ke++;
			IgnoreBlank();
		}
		// End of algoritma membosankan	
		if(IsKataSama(Action, UPGRADE)){
			arrKata arrChild;
			findChild('S', &link[0], &arrChild);
			if(IsKataSama(Nama_Upgrade,arrChild.TI[0]) || IsKataSama(Nama_Upgrade,arrChild.TI[1])){
				IdxType id = ArrayTriplet_SearchByNama(UpgradeCosts, Nama_Upgrade);
				Kata bahan = Triplet_Bahan(UpgradeCosts,id);
				Kata IDBANGUNAN; IDBANGUNAN.TabKata[0] = bangunan; IDBANGUNAN.Length=0;
				IdxType idInventory = ArrayPair_SearchByItem(Inventory,bahan);
				IdxType idNeed = ArrayPair_SearchByItem(need_material,bahan);
				int inventorySupply = Pair_Cost(Inventory,idInventory); //Mendapatkan jumlah di inventory
				int needMaterial = Pair_Cost(need_material,idNeed);
				if(inventorySupply>=needMaterial){
					addUpgrade(&link[indexWahana], Nama_Upgrade);
					Pair_Cost(need_material,idNeed) = needMaterial + Triplet_Cost(UpgradeCosts,id);
					StackEl.Length=0; StackEl.TabKata[0] ='X';
					StackEl = KataConcat(StackEl,lowerCaseKata(Action)); StackEl = KataConcat(StackEl,SPASI); StackEl = KataConcat(StackEl, IDBANGUNAN); StackEl = KataConcat(StackEl,SPASI); StackEl = KataConcat(StackEl,Nama_Upgrade);
					Push(&aksi,StackEl);
					return;
				} else{
					printf("Not enough materials");
				}
			} else{
				printf("Upgrade tidak ditemukan");
			}
		} else{
			printf("Command salah! Tekan apapun untuk melanjutkan\n");
		}
	} else{
		printf("Tidak ada wahana di sekitar Anda");
	}
	getchar();
}

void HandleUndo(){
	// Ini adalah fungsi untuk melakukan prosedur undo dan validasi di dalamnya, prosedur ini dilakukan jika waktunya cukup

	// Deklarasi variabel lokal
	Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.Length = 3;
	Kata BUILD; BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d'; BUILD.Length = 5;
	Kata UPGRADE; UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e'; UPGRADE.Length = 7;
	
	// Jika stack tidak kosong maka undo elemen top, jika stack kosong maka tidak melakukan apa apa
	if(!IsEmptyStack(aksi)){
		infotype x ;
		Pop(&aksi,&x);
		if (x.TabKata[0] == 'b' && x.TabKata[2] == 'y'){
			// Jika yang di undo adalah buy maka kuraNGI item di inventory kurangi uang dan waktu yang dibutuhkan yang bersesuaian
			int n; Kata Benda;
			AkuisisiBuyV2(x,&n,&Benda);
			int materialIndex = ArrayPair_SearchByItem(Materials,Benda);
			need_money = need_money - n*Pair_Cost(Materials,materialIndex);
			count_aksi = count_aksi - 1;
			need_time = need_time - Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUY));
			Pair_Cost(Inventory,materialIndex) -= n;
		} else if (x.TabKata[0] == 'b' && x.TabKata[2] == 'i') {
			// Jika yang di undo adalah build maka kurangi uang, waktu, dan material yang dibutuhkan yang bersesuaian, ubah kembali petak wahana menjadi '-' dan ubah status ke n
			int PbuildX; int PbuildY; int PbuildMap; Kata Bangunan; int sizeBaris; int sizeKolom;
			AkuisisiBuildV2(x,&PbuildX,&PbuildY,&PbuildMap,&Bangunan,&sizeBaris,&sizeKolom);
			// Kurangi waktu yang dibutuhkan dari buy
			Kata AMBER;
			AMBER.TabKata[0] = 'A'; AMBER.TabKata[1] = 'm'; AMBER.TabKata[2] = 'b'; AMBER.TabKata[3] = 'e'; AMBER.TabKata[4] = 'r';
			AMBER.Length = 5;
			int materialIndex = ArrayPair_SearchByItem(Materials,AMBER);
			int n = Pair_Cost(MaterialBuild,ArrayPair_SearchByItem(MaterialBuild,Bangunan)); 
			int bangunanIndex = ArrayPair_SearchByItem(HargaBuild,Bangunan);
			need_money = need_money - Pair_Cost(HargaBuild,bangunanIndex); // Kurangi uang yang dibutuhkan dari membangun bangunan
			Pair_Cost(need_material,materialIndex)= Pair_Cost(need_material,materialIndex) - n;
			count_aksi = count_aksi - 1;
			(wahana).TI[GetIndex(&wahana, Bangunan.TabKata[0])].status ='N';
			printf("Bangunan di (%d,%d) pada peta-%d dengan ukuran(%dx%d) akan di undo",PbuildX, PbuildY, PbuildMap, sizeBaris, sizeKolom); getchar();
			for (int i = PbuildX; i < PbuildX + sizeBaris; i++) {
				for (int j = PbuildY; j < PbuildY + sizeKolom; j++){
					Elmt(map[PbuildMap],i,j) = '-'; 
				}
			}
			need_time = need_time - Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUILD));
			
		} else if (x.TabKata[0] == 'u'){
			// Jika yang di undo adalah upgrade maka kurangi uang, waktu, dan material yang dibutuhkan yang bersesuaian, ubah kembali isi upgradenya
			char idWahana;Kata Nama_Upgrade;
			AkuisisiUpgrade(x, &idWahana, &Nama_Upgrade);
			int idxNode = bintree_findIndex(idWahana);
			IdxType id = ArrayTriplet_SearchByNama(UpgradeCosts, Nama_Upgrade);
			Kata bahan = Triplet_Bahan(UpgradeCosts,id);
			int materialRefund = Triplet_Cost(UpgradeCosts,id);
			IdxType idInventory = ArrayPair_SearchByItem(Inventory,bahan);
			int inventorySupply = Pair_Cost(Inventory,idInventory); //Mendapatkan jumlah di inventory
			Pair_Cost(Inventory,idInventory) = Pair_Cost(Inventory,idInventory) +materialRefund; 
			removeUpgrade(&link[idxNode]);
		}
	}
}

void HandleExecution(){
	infotype x;
	count_aksi = 0 ;
	UpdateWaktu(need_time);
	need_time = 0;
	pmoney = pmoney - need_money; // Kurangi uang dengan uang yang dibutuhkan
	need_money = 0 ;
	for (int i = ArrayPair_GetFirstIdx(Inventory) ; i <= ArrayPair_GetLastIdx(Inventory) ; i ++){ 
		Pair_Cost(Inventory,i) = Pair_Cost(Inventory,i) - Pair_Cost(need_material,i); // Kurangi material dengan semua material dibutuhkan
		Pair_Cost(need_material,i) = 0 ;
	} 
	Reverse(&aksi);
	while(!IsEmptyStack(aksi)){
		Pop(&aksi,&x);
		if (x.TabKata[0] == 'b' && x.TabKata[2] == 'y'){
			int n; Kata Benda;
			AkuisisiBuyV2(x,&n,&Benda);
			// printf("%c %d", benda[0] , n); getchar(); // Ini gw tes dengan ngeprint wkwk
			int materialIndex = ArrayPair_SearchByItem(Materials,Benda);
			// Pair_Cost(Inventory,materialIndex) += n; // Menambah jumlah barang di inventory
		} else if (x.TabKata[0] == 'b' && x.TabKata[2] == 'i') {
			int PbuildX; int PbuildY; int PbuildMap; Kata Bangunan; int sizeBaris; int sizeKolom;
			AkuisisiBuildV2(x,&PbuildX,&PbuildY,&PbuildMap,&Bangunan,&sizeBaris,&sizeKolom);
			(wahana).TI[GetIndex(&wahana, Bangunan.TabKata[0])].status ='G';
			(wahana).TI[GetIndex(&wahana, Bangunan.TabKata[0])].panjang = sizeBaris;
			(wahana).TI[GetIndex(&wahana, Bangunan.TabKata[0])].lebar =sizeKolom;
		} else if (x.TabKata[0] == 'u'){
			Kata KAPASITAS; KAPASITAS.TabKata[0] = 'K';KAPASITAS.TabKata[1] = 'A';KAPASITAS.TabKata[2] = 'P';KAPASITAS.TabKata[3] = 'A';KAPASITAS.TabKata[4] = 'S';KAPASITAS.TabKata[5] = 'I';KAPASITAS.TabKata[6] = 'T';KAPASITAS.TabKata[8] = 'A';KAPASITAS.TabKata[9] = 'S'; KAPASITAS.Length = 9;
			Kata HARGA; HARGA.TabKata[0] = 'H'; HARGA.TabKata[1] = 'A'; HARGA.TabKata[2] = 'R' ; HARGA.TabKata[3] = 'G'; HARGA.TabKata[4] = 'A'; HARGA.Length = 5;
			Kata DURASI; DURASI.TabKata[0] = 'D'; DURASI.TabKata[1] = 'U'; DURASI.TabKata[2] = 'R' ; DURASI.TabKata[3] = 'A'; DURASI.TabKata[4] = 'S'; DURASI.TabKata[5] = 'I'; DURASI.Length = 6;
			char idWahana;Kata Nama_Upgrade;
			AkuisisiUpgrade(x, &idWahana, &Nama_Upgrade);

			int idxTripletBahan = ArrayTriplet_SearchByNama(UpgradeEffect, Nama_Upgrade);

			if(IsKataSama(Triplet_Bahan(UpgradeEffect,idxTripletBahan),HARGA)){
				printf("Harga");
				int idxTripletEffect = ArrayTriplet_SearchByNama(UpgradeEffect,Nama_Upgrade);
				wahana.TI[GetIndex(&wahana, idWahana)].harga += Triplet_Cost(UpgradeEffect,idxTripletEffect);
				printf("%d",Triplet_Cost(UpgradeEffect,idxTripletEffect));
			} else if(IsKataSama(Triplet_Bahan(UpgradeEffect,idxTripletBahan),KAPASITAS)){
				printf("Kapasitas");
				int idxTripletEffect = ArrayTriplet_SearchByNama(UpgradeEffect,Nama_Upgrade);
				wahana.TI[GetIndex(&wahana, idWahana)].kapasitas += Triplet_Cost(UpgradeEffect,idxTripletEffect);
				printf("%d",Triplet_Cost(UpgradeEffect,idxTripletEffect));
			} else if(IsKataSama(Triplet_Bahan(UpgradeEffect,idxTripletBahan),DURASI)){
				printf("Durasi");
				int idxTripletEffect = ArrayTriplet_SearchByNama(UpgradeEffect,Nama_Upgrade);
				wahana.TI[GetIndex(&wahana, idWahana)].durasi -= Triplet_Cost(UpgradeEffect,idxTripletEffect);
				printf("%d",Triplet_Cost(UpgradeEffect,idxTripletEffect));
			}


			printf("upgrade"); getchar();
		}
	}
}

void InputPreparationDay (int inpt) {
	// Mengelola input yang diterima konsol saat main day dan tindakan yang dilakukan setelah input itu
	JAM buka; Hour(buka) = 9; Minute(buka) = 0;
	Kata W; W.TabKata[0] = 'w'; W.Length = 1;
	Kata A; A.TabKata[0] = 'a'; A.Length = 1;
	Kata S; S.TabKata[0] = 's'; S.Length = 1;
	Kata D; D.TabKata[0] = 'd'; D.Length = 1;
	Kata BUY; BUY.TabKata[0] = 'b'; BUY.TabKata[1] = 'u'; BUY.TabKata[2] = 'y'; BUY.Length = 3;
	Kata BUILD; BUILD.TabKata[0] = 'b'; BUILD.TabKata[1] = 'u'; BUILD.TabKata[2] = 'i';BUILD.TabKata[3] = 'l'; BUILD.TabKata[4] ='d'; BUILD.Length = 5;
	Kata UPGRADE; UPGRADE.TabKata[0] = 'u';UPGRADE.TabKata[1] = 'p';UPGRADE.TabKata[2] = 'g';UPGRADE.TabKata[3] = 'r';UPGRADE.TabKata[4] = 'a';UPGRADE.TabKata[5] = 'd';UPGRADE.TabKata[6]= 'e'; UPGRADE.Length = 7;
	if (inpt == INPUT_w && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)-1,Ordinat(playerpos)))) {
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,W))){
			Absis(playerpos) = Absis(playerpos) -1 ;
			UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,W)));
		} else {
			printf("Waktu tidak mencukupi untuk bergerak!"); getchar();
		}
	} else if (inpt == INPUT_a && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)-1))) {
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,A))){
			Ordinat(playerpos) = Ordinat(playerpos) -1 ;
			UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,A)));
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
	} else if (inpt == INPUT_s && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos)+1,Ordinat(playerpos)))) {
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,S))){
			Absis(playerpos) = Absis(playerpos) + 1 ;
			UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,S)));
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
	} else if (inpt == INPUT_d && IsBisaDilewati(Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)+1))) {
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,D))){
			Ordinat(playerpos) = Ordinat(playerpos) +1 ;
			UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,D)));
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
		
	} else if (inpt == INPUT_i){
		state = MAIN_DAY;
		Hour(time) = 9 ;
		Minute(time) = 0;
		while(!IsEmptyStack(aksi)){
			HandleUndo();
		}
		PrepToMainDay();
	} else if (inpt == INPUT_b){
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUY))){
			HandleBuy();
		} else {
			printf("Waktu tidak mencukupi untuk buy!"); getchar();
		}
	} else if (inpt == INPUT_1){
		state = INVENTORY;
	} else if (inpt == INPUT_e) {
		state = EXIT_GAME;
	} else if (inpt == INPUT_l) {
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,BUILD))){
			HandleBuild();
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
	} else if(inpt == INPUT_k) { 
		if (Durasi(time, buka) >= need_time + Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,UPGRADE))){
			HandleUpgrade();
		} else {
			printf("Waktu tidak mencukupi untuk build!"); getchar();
		}
	} else if (inpt == INPUT_j){
		HandleUndo();
	} else if (inpt == INPUT_2){
		HandleExecution();
	} else if (inpt == INPUT_7){
		HandleSaveGame();
	} 
}


void PrintPreparationDay() {
	// Menampilkan informasi pada bagian inti game saat preparation day
	JAM buka;
	Hour(buka) = 9;
	Minute(buka) = 0;
	if (Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '>' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '<' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == '^' || Elmt(mapRoom,Absis(playerpos),Ordinat(playerpos)) == 'V' ) {
		infotypePeta CurrentPos;
		CurrentPos.map = cmap;
		Absis(CurrentPos.p) = Absis(playerpos);
		Ordinat(CurrentPos.p) = Ordinat(playerpos);
		adrPeta P = SearchPeta(denah,CurrentPos);
		adrTerowongan T = Gerbang(P);
		P = Graph_Succ(T);
		cmap = idPeta(P).map;
		Absis(playerpos) = Absis(idPeta(P).p);
		Ordinat(playerpos) = Ordinat(idPeta(P).p);
	}
	CopyMATRIKS(map[cmap], &mapRoom);
	TulisMATRIKS(mapRoom,Absis(playerpos),Ordinat(playerpos));
	printf("\n");

	printf("Nama : %s		Uang: %d		Waktu sebelum buka: %d menit\n", namaPlayer.TabKata, pmoney, Durasi(time, buka));
	printf("Material yang dibutuhkan: ");ArrayPair_TulisIsiTab(need_material);printf("\n");
	printf("Aksi yang akan dilakukan : %d		Uang yang dibutuhkan: %d		Waktu yang dibutuhkan: %d\n", count_aksi, need_money, need_time);
	printf("Jam : ");
	TulisJAM(time);
	printf("\n");printf("====================================================================================");
	printf("\n");printf("Stack of Your Action");
	printf("\n");PrintStack(aksi);
	printf("====================================================================================");printf("\n");
	
}

void InputOffice() {
	char input[100];
	Kata INPUT;
	Kata EXIT; EXIT.TabKata[0] = 'E'; EXIT.TabKata[1] = 'X'; EXIT.TabKata[2] = 'I'; EXIT.TabKata[3] = 'T'; EXIT.Length = 4;
	Kata REPORT; REPORT.TabKata[0] = 'R'; REPORT.TabKata[1] = 'E'; REPORT.TabKata[2] = 'P'; REPORT.TabKata[3] = 'O'; REPORT.TabKata[4] = 'R'; REPORT.TabKata[5] = 'T'; REPORT.Length = 6;
	Kata DETAILS; DETAILS.TabKata[0] = 'D'; DETAILS.TabKata[1] = 'E'; DETAILS.TabKata[2] = 'T'; DETAILS.TabKata[3] = 'A'; DETAILS.TabKata[4] = 'I'; DETAILS.TabKata[5] = 'L'; DETAILS.TabKata[6] = 'S'; DETAILS.Length=7;
	Kata Office; Office.TabKata[0] = 'o'; Office.TabKata[1] = 'f'; Office.TabKata[2] = 'f'; Office.TabKata[3] = 'i'; Office.TabKata[4] = 'c'; Office.TabKata[5] = 'e'; Office.Length = 6;
	// Akuisisi dengan mesinkata , algoritma membosankan
	STARTBUY();
	while(!EOL){
		IgnoreBlank();
		int i = 0;
		while(CC!=EOL){
			if(CC=='\n'){
				break; // Pengaman kadang EOL ga kedetect
			}
			INPUT.TabKata[i]=CC;
			i++;
			ADV();
		}
		INPUT.Length = i;
		break;
	}
	if(IsKataSama(DETAILS,INPUT)) {
		printf("Daftar Wahana :\n");
		printListWahana(&wahana);
		printf("\n");

		printf("Masukkan ID Wahana yang ingin dilihat detailnya : ");
		scanf("%c", &ChoosenWahana); getchar();
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Office)));
		state = OFFICE_DETAIL;
	} else if (IsKataSama(REPORT,INPUT)) {
		printf("Daftar Wahana :\n");
		printListWahana(&wahana);
		printf("\n");

		printf("Masukkan ID Wahana yang ingin dilihat reportnya : ");
		scanf("%c", &ChoosenWahana); getchar();
		UpdateWaktu(Pair_Cost(ActionTime,ArrayPair_SearchByItem(ActionTime,Office)));
		state = OFFICE_REPORT;
	} else if (IsKataSama(EXIT,INPUT)) {
		state = MAIN_DAY;
	}
	// End of algoritma membosankan
}

// =======================================================================================================


// =========================================Fungsi Umum===================================================
void SetupMainMenu(){
	// Setup awal untuk memulai game
	ArrayPair_MakeEmpty(&Materials);
	ArrayPair_MakeEmpty(&HargaBuild);
	ArrayPair_MakeEmpty(&MaterialBuild);
	ArrayPair_MakeEmpty(&ActionTime);
	ArrayTriplet_MakeEmpty(&UpgradeEffect);
	ArrayTriplet_MakeEmpty(&UpgradeCosts);
	BacaMATRIKS(&map[1], "../file/1.txt");
	BacaMATRIKS(&map[0], "../file/0.txt");
	BacaMATRIKS(&map[2], "../file/2.txt");
	BacaMATRIKS(&map[3], "../file/3.txt");
	ArrayPair_BacaIsi(&Materials, "../Saves/Materials.txt");
	ArrayPair_BacaIsi(&HargaBuild, "../Saves/HargaBuild.txt");
	ArrayPair_BacaIsi(&MaterialBuild, "../Saves/MaterialBuild.txt");
	ArrayPair_BacaIsi(&ActionTime, "../Saves/ActionPrice.txt");
	ArrayTriplet_BacaIsi(&UpgradeEffect, "../Saves/UpgradeEffect.txt");
	ArrayTriplet_BacaIsi(&UpgradeCosts, "../Saves/HargaUpgrade.txt");
	BuildTree();
	bacaUpgrade("../Saves/Upgrade.txt");
	BacaGraph(&denah,"../file/graph.txt");
	state = MAIN_MENU;
}


void PrintJudul (){
	// printf("%s\n","==================================================================");
	// printf("%s\n","==================================================================");  
	// printf("%s\n","*     __    __ _ _ _         __    __                  _          ");
	// printf("%s\n","*    / / /\\ \\ (_| | |_   _  / / /\\ \\ \\__ _ _ __   __ _| | ___   _ ");   
	// printf("%s\n","*    \\ \\/  \\/ | | | | | | | \\ \\/  \\/ / _` | '_ \\ / _` | |/ | | | |");   
	// printf("%s\n","*     \\  /\\  /| | | | |_| |  \\  /\\  | (_| | | | | (_| |   <| |_| |");   
	// printf("%s\n","*      \\/  \\/ |_|_|_|\\__, |   \\/  \\/ \\__,_|_| |_|\\__, |_|\\_ \\__, |");   
	// printf("%s\n","*               __   |___/         _     _       |___/      |___/ ");   
	// printf("%s\n","*              / / /\\ \\ \\___  _ __| | __| |                       ");   
	// printf("%s\n","*              \\ \\/  \\/ / _ \\| '__| |/ _` |                       ");   
	// printf("%s\n","*               \\  /\\  | (_) | |  | | (_| |                       ");   
	// printf("%s\n","*                \\/  \\/ \\___/|_|  |_|\\__,_|                       ");   
	// printf("%s\n","*                                                                 ");
	printf("%s\n","====================================================================================");
	printf("\t\t\t\t%s\n","Willy Wangky World");
	printf("%s\n","====================================================================================");                                 
}

void PrintMain(){
	switch (state) {
	case MAIN_MENU:
		printf("\n			SELAMAT DATANG DI GAME WILLY WANGKY'S WORLD!!!\n");
		printf("	Silahkan pilih opsi main :\n");
		printf("	1.New Game\n");
		printf("	2.Load Game\n");
		printf("	Silahkan ketik menu dengan benar\n");
		break;
	case NEW_GAME:
		printf("\n		Silahkan masukkan nama pemain: \n");
		break;
	case LOAD_GAME:
		printf("\n		Silahkan masukkan nama pemain untuk diload: \n");
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
	case OFFICE_DETAIL: ;
		int idxLink = bintree_findIndex(ChoosenWahana);
		printDetailWahana(&wahana, ChoosenWahana,&link[idxLink]);
		break;
	case OFFICE_REPORT:
		printReportWahana(&wahana, ChoosenWahana);
		break;
	case DETAIL_WAHANA: ;
		int indexLink = bintree_findIndex(ChoosenWahana);
		printDetailWahana(&wahana, ChoosenWahana,&link[indexLink]);	
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
	Kata EXIT;
	EXIT.TabKata[0] = 'E'; EXIT.TabKata[1] = 'X'; EXIT.TabKata[2] = 'I'; EXIT.TabKata[3] = 'T'; EXIT.Length=4;
	int inpt;
	// char input[100]; char name[100]; 
	switch (state) {
	case MAIN_MENU: ;
		Kata NEWGAME; Kata LOADGAME; Kata INPUT;
		NEWGAME.TabKata[0]='N';	NEWGAME.TabKata[1]='E';	NEWGAME.TabKata[2]='W';	NEWGAME.TabKata[3]=' ';	NEWGAME.TabKata[4]='G';	NEWGAME.TabKata[5]='A';	NEWGAME.TabKata[6]='M';	NEWGAME.TabKata[7]='E'; NEWGAME.Length=8;
		LOADGAME.TabKata[0]='L'; LOADGAME.TabKata[1]='O'; LOADGAME.TabKata[2]='A'; LOADGAME.TabKata[3]='D'; LOADGAME.TabKata[4]=' '; LOADGAME.TabKata[5]='G'; LOADGAME.TabKata[6]='A'; LOADGAME.TabKata[7]='M'; LOADGAME.TabKata[8]='E'; LOADGAME.Length=9;
		// Akuisisi dengan mesinkata , algoritma membosankan
		STARTBUY();
		while(!EOL){
			IgnoreBlank();
			int i = 0;
			while(CC!=EOL){
				if(CC=='\n'){
					break; // Pengaman kadang EOL ga kedetect
				}
				INPUT.TabKata[i]=CC;
				i++;
				ADV();
			}
			INPUT.Length = i;
			break;
		}
		// End of algoritma membosankan
		if(IsKataSama(INPUT,NEWGAME)) {
			state = NEW_GAME;
		} else if (IsKataSama(INPUT,LOADGAME)) {
			state = LOAD_GAME;
		} else {
			printf("Anda memasukkan input yang salah !, ketik enter untuk melanjutkan");
			getchar();
		}
		break;
	case NEW_GAME: ; //Semicolon for Label Handling
		Kata NAMA;
		// Akuisisi dengan mesinkata , algoritma membosankan
		STARTBUY();
		while(!EOL){
			IgnoreBlank();
			int i = 0;
			while(CC!=EOL){
				if(CC=='\n'){
					break; // Pengaman kadang EOL ga kedetect
				}
				NAMA.TabKata[i]=CC;
				i++;
				ADV();
			}
			NAMA.Length = i;
			break;
		}
		// End of algoritma membosankan
		if(IsKataSama(EXIT,NAMA)) {
			state = MAIN_MENU;
		} else {
			// strcpy(namaPlayer, name);
			printf("Selamat bermain ");
			for(int i=0;i<NAMA.Length;i++){
				printf("%c", NAMA.TabKata[i]);
			}
			// strcpy(namaPlayer.TabKata,""); 
			namaPlayer.Length = 0;
			namaPlayer = KataConcat(namaPlayer,NAMA);
			printf(" semoga senang :)");
			getchar();
			SetupNewGame();
	
		}
		break;
	case LOAD_GAME: ; //Semicolon for Label Handling
		Kata FILEPATH;
		Kata EXIT; EXIT.TabKata[0] = 'E' ; EXIT.TabKata[1] = 'X' ; EXIT.TabKata[2] = 'I' ; EXIT.TabKata[3] = 'T' ; EXIT.Length = 4;
		FILEPATH.Length = 9;
		FILEPATH.TabKata[0] = '.'; FILEPATH.TabKata[1] = '.'; FILEPATH.TabKata[2] ='/';  FILEPATH.TabKata[3] ='S';  FILEPATH.TabKata[4] ='a';  FILEPATH.TabKata[5] = 'v'; FILEPATH.TabKata[6] ='e';  FILEPATH.TabKata[7] ='s';  FILEPATH.TabKata[8] ='/'; 
		STARTBUY();
		while(!EOL){
			IgnoreBlank();
			int i = 0;
			while(CC!=EOL){
				if(CC=='\n'){
					break; // Pengaman kadang EOL ga kedetect
				}
				NAMA.TabKata[i]=CC;
				i++;
				ADV();
			}
			NAMA.Length = i;
			break;
		}
		if(IsKataSama(NAMA,EXIT)) {
			state = MAIN_MENU;
		} else {
			NamaLoadFile.Length = 0;
			// strcpy(NamaLoadFile.TabKata,"");
			NamaLoadFile = KataConcat(NamaLoadFile,FILEPATH); NamaLoadFile = KataConcat(NamaLoadFile,NAMA);
			FILE *loadfile;
			loadfile = fopen(NamaLoadFile.TabKata, "r");
			if (loadfile){
				if (loadfile== NULL){ 
					printf("Error File Content, Press anything to continue"); getchar();
				} else {
					SetupLoadGame(loadfile);
					namaPlayer.Length = 0;  namaPlayer = KataConcat(namaPlayer,NAMA);
				} 
			} else {
				printf("Invalid File Name, Press anything to continue"); getchar();
			}

		}

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
		InputOffice();
		break;
	case OFFICE_DETAIL:
		getchar();
		state = OFFICE;
		break;
	case OFFICE_REPORT:
		getchar();
		state = OFFICE;
		break;
	case DETAIL_WAHANA:
		getchar();
		state = MAIN_DAY;
		break;
	case INVENTORY: 
		getchar();
		state = PREPARATION_DAY;
		break ;
	default:
		printf("%s","Input tidak valid");
		break;
	}
}

void PrintFooter(){
	switch (state) {
	case MAIN_MENU:
		printf("\t\t\t\t%s\n","Command Main Menu");
		printf("\t%s\n","Ketik menu yang ingin dipilih");
		break;
	case MAIN_DAY:
		printf("\t\t\t\t%s\n","Command Main Day");
		printf("%s\n","w : Atas\ta : Kiri\ts : Bawah\td : Kanan\ti : Preparation Day");
		printf("%s\n","1 : Enter Office\t2 : Lihat Detail Wahana\t\t3 : Repair Wahana\t 4:Serve ");
		printf("%s\n","e : Exit");
		break;
	case PREPARATION_DAY:
		printf("\t\t\t\t%s\n","Command Preparation Day");
		printf("%s\n","w : Atas\ta : Kiri\ts : Bawah\td: Kanan\ti: Main Day");
		printf("%s\n","b : Buy\t\tl : Build\tk : Upgrade\tj : Undo\te : Exit");
		printf("%s\n","1 : Inventory\t2 : Execute\t7 : Save");   
		break;
	case INVENTORY:
		printf("\t\t\t\t%s\n","Command Inventory");
		printf("\t%s\n","Tekan apapun untuk kembali ke Preparation Phase");
		break;
	case DETAIL_WAHANA:
		printf("\t\t\t\t%s\n","Command Detail Wahana");
		printf("\t%s\n","Tekan apapun untuk kembali ke main day");
		break;
	case NEW_GAME:
		printf("\t%s\n","Masukkan Nama Tanpa Spasi, Ketikkan 'Exit' untuk keluar");
		break;
	case LOAD_GAME:
		printf("\t%s\n","Masukkan Nama Tanpa Spasi, Ketikkan 'Exit' untuk keluar");
		break;
	case OFFICE:
		printf("\t\t\t\t%s","Command Office");
		printf("\n%s\n","\tDetails : Lihat Detail Wahana\tReport : Melihat Report Wahana, \n\tExit : Keluar dari Office");
		break;
	case OFFICE_REPORT:
		printf("\t\t\t\t%s","Command Office Report");
		printf("\t%s\n","	Tekan apapun untuk kembali ke Menu Office");
		break;
	case OFFICE_DETAIL:
		printf("\t\t\t\t%s","Command Office Detail");
		printf("\t%s\n","Tekan apapun untuk kembali ke Menu Office");
		break;
	default:
		printf("\n");
		break;
	}
}
void UserInterface(){
	clrscr();
	PrintJudul();
	printf("\t\t\t\t%s\n","Selamat bermain!!");
	PrintMain();
	printf("%s\n","===================================================================================="); 
	PrintFooter();
	printf("%s\n","===================================================================================="); 
}
// =======================================================================================================

int main(){
	SetupMainMenu();
	while (state != EXIT_GAME){
		UserInterface();
		BacaInput();
	}
	printf("\t\t\t\tTerimakasih telah bermain\n\n");
	printf("\t\tAuthor:\n");
    printf("\t\t13519043\tReihan Andhika Putra\n");
    printf("\t\t13519059\tDenilsen Axel Candiasa\n");
    printf("\t\t13519079\tJesson Gosal Yo\n");
    printf("\t\t13519131\tHera ShafiraJofiandy Leonata\n");
    printf("\t\t13519207\tRafidika Samekto\n");
}