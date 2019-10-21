#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define ASIZE   256
#define XSIZE   100
#define TAM 1000
#define TRUE 1
#define FALSE 0

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// This is a popular one - I'll find a few versions
// ONE
void preBmBcTURBO(char *x, int m, int bmBc[]) {
    int i;
    for (i = 0; i < ASIZE; ++i)
        bmBc[i] = m;
    for (i = 0; i < m - 1; ++i)
        bmBc[x[i]] = m - i - 1;
}


void suffixesT(char *x, int m, int *suff) {
    int f = 0, g, i;

    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void preBmGsTURBO(char *x, int m, int bmGs[]) {

    int i, j, suff[XSIZE];

    suffixesT(x, m, suff);

    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    j = 0;
    for (i = m - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (; j < m - 1 - i; ++j)
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}
//@end
void printOut(int *x){
   int i;
   for (i = 0; i < 256; i++){
      printf("%d  ", x[i]);
   }
   printf("\n");
}

void naoEncaixa(char *t, char *patt, int *output){
    int i;
    int encaixa = FALSE;
    for (i = 0; i < (TAM/2); i++){
        if(output[i] == (strlen (t) - strlen (patt))){
            encaixa = TRUE;
            break;
        }
    }

    encaixa == TRUE ? printf("encaixa\n") : printf("nao encaixa\n");
}

void TurboBoyerMooreSearch(char *x, int m,char *y,int n, int *output) {
    
    int p = 0;
    
    int bcShift, i, j, shift, u, v, turboShift,
    bmGs[XSIZE], bmBc[ASIZE];
    
    /* Preprocessing */
    preBmGsTURBO(x, m, bmGs);
    preBmBcTURBO(x, m, bmBc);
    
    /* Searching */
    j = u = 0;
    shift = m;
    while (j <= n - m) {
        i = m - 1;
        while (i >= 0 && x[i] == y[i + j]) {
            --i;
            if (u != 0 && i == m - 1 - shift)
                i -= u;
        }
        if (i < 0) {
           
            output[p]=j;
            p++;
            shift = bmGs[0];
            u = m - shift;
        }
        else {
            v = m - 1 - i;
            turboShift = u - v;
            bcShift = bmBc[y[i + j]] - m + 1 + i;
            shift = MAX(turboShift, bcShift);
            shift = MAX(shift, bmGs[i]);
            if (shift == bmGs[i])
                u = MIN(m - shift, v);
            else {
                if (turboShift < bcShift)
                    shift = MAX(shift, u + 1);
                u = 0;
            }
        }
        j += shift;
    }
}

int main(){
    
    int u;
    int i;
    char t[TAM+1], patt[TAM+2];
    scanf("%d", &u);

    for (i = 0; i < u; i++){
        int k;
        int output[TAM/2] = {-1};
        for(k = 0; k < TAM/2; k++){
            output[k] = -1;
        }
        
        scanf("%s %s",&t,&patt);
        int m = (int) strlen(patt);
        int n = (int) strlen(t);
    
        TurboBoyerMooreSearch(patt, m, t, n, output);
        naoEncaixa(t, patt, output);
        
    }
    
    return 0;
}