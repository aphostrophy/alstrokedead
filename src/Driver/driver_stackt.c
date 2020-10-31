#include <stdio.h>
#include "../Header/stackt.h"


int main(){
    infotype X;
    Stack S;
    scanf("%s", &X);
    CreateEmpty(&S);
    Push(&S, X);
    Push(&S, "Aku");
    Push(&S, "Makan");
    Push(&S, "Indomie");
    Push(&S, "Kuah");
    printf("%s", "Isi topnya adalah ");
    printf("%s\n", InfoTop(S));
    printf("%s\n", "Isi stacknya adalah");
    PrintStack(S);
    Reverse(&S);
    printf("%s\n", "Isi reverse stacknya adalah");
    PrintStack(S);
    Pop(&S, &X);
    printf("%s\n",X);
    Pop(&S, &X);
    printf("%s\n",X);
    return 0;
}