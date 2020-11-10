#include <stdio.h>
#include "../Header/boolean.h"
#include "../Header/jam.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
    return ((H >= 0 && H <= 23) && (M >= 0 && M <= 59));
}
/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{
    JAM J;

    Hour(J) = HH;
    Minute(J) = MM;
    return J;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
{
    int H, M;
    boolean done;

    done = false;

    while(!done) {
        scanf("%d %d ", &H, &M);
        if (!IsJAMValid(H, M)) {
            printf("Jam tidak valid\n");
        } else {
            done = true;
        }
    }
    *J = MakeJAM(H, M);

}

void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.
   Jika jam / menit / detik hanya satu digit, tuliskan satu digit tanpa 0 di depannya. */
{
    printf("%d:%d", Hour(J), Minute(J));
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToMenit (JAM J)
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
{
    return (Hour(J)*60 + Minute(J));
}

JAM MenitToJAM (long N)
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 1440, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 1440, baru N1 dikonversi menjadi JAM */
{
    long N1; 
    int H, M;

    N1 = N % 1440;
    H = N1 / 60;
    M = (N1 % 60);
    return (MakeJAM(H, M));
}

JAM NextNMenit (JAM J, int N)
/* Mengirim N detik setelah J dalam bentuk JAM */
{
    return (MenitToJAM(JAMToMenit(J) + N));
}

JAM PrevNMenit (JAM J, int N)
/* Mengirim N detik sebelum J dalam bentuk JAM */
{
    if (JAMToMenit(J) < N) {
        return (MenitToJAM(JAMToMenit(J) + 1440 - N));
    } else {
        return (MenitToJAM(JAMToMenit(J) - N));
    }
}

/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
    if (JAMToMenit(JAw) > JAMToMenit(JAkh)) {
        return (JAMToMenit(JAkh) + 1440 - JAMToMenit(JAw));
    } else {
        return (JAMToMenit(JAkh) - JAMToMenit(JAw));
    }
}
