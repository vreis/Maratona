#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <algorithm>

using namespace std;

#define QTT 10 // quantidade de Big nums
#define MOD 10 // base (10^9)
#define DIGS "1" // o numero de digitos decimais da base (MOD)
#define TAM 1000 // o numero deve ter no max 10^(9*TAM) digitos

unsigned long long bn[QTT][TAM];
int nb[QTT];
char sb[QTT]; // 1 positivo... -1 negativo

void imprime(int a) {
    int i = nb[a] - 1;
    if (sb[a] < 0) printf("-");
    printf("%llu", bn[a][i--]);
    for (; i >= 0; i--)
        printf("%0"DIGS"llu", bn[a][i]);
}

void intto(long long a, int b) {
    sb[b] = (a < 0) ? -1 : 1;
    a *= sb[b];

    for (nb[b] = 0; a != 0; nb[b]++) {
        bn[b][nb[b]] = a%MOD;
        a /= MOD;
    }
}

void zera(int a) {
    sb[a] = nb[a] = 1;
    for (int i = 0; i < TAM; i++)
        bn[a][i] = 0;
}

void strto(char *s, int a) {
    int i = 0, b = 1;
    zera(a);
    for (int n = strlen(s)-1; n >= 0; n--) {
        if (s[n] == '-')  { sb[a] = -1; break; }
        bn[a][i] += b*(s[n]-'0');
        b *= 10;
        if (b == MOD && n > 0) { b = 1; i++; }
    }
    nb[a] = i+1;
}

// a comparacao eh em valor absoluto!
// 1 'a' eh maior - 0 iguais - -1 'b' eh maior
int compare(int a, int b) {
    if( nb[a] != nb[b] )
        return (nb[a] > nb[b]) ? 1 : -1;
    else {
        int i;
        for (i = nb[a]-1; (i >= 0) && (bn[a][i] == bn[b][i]); i--) ;
        if (bn[a][i] == bn[b][i]) return 0;
        return (bn[a][i] > bn[b][i]) ? 1 : -1;
    }
}

void soma(int a, int b, int c) {
    int i, cc;
    long long unsigned acc = 0;
    if (sb[a] == sb[b]) {
        nb[c] = max(nb[a], nb[b]);
        for (i = 0; i < nb[c]; i++) {
            bn[c][i] = bn[a][i] + bn[b][i] + acc;
            acc = bn[c][i]/MOD;
            bn[c][i] %= MOD;
        }
        if (acc > 0) bn[c][nb[c]++] = acc;
    } else {
        if ((cc = compare(a, b)) == 0) zera(c);
        else {
            if (cc == -1) swap(a, b); // a eh sempre o maior
            for (i = 0; i < nb[a]; i++) {
                bn[c][i] = bn[a][i] - bn[b][i] - acc;
                acc = 0;
                if (bn[c][i] < 0) {
                    acc = 1;
                    bn[c][i] += MOD;
                }
            }
            for (nb[c] = nb[a]; bn[nb[c]-1] == 0; nb[c]--) ;
            sb[c] = sb[a];
        }
    }
}

void mult(int a, int b, int c) {
    unsigned long long i, j, acc;
    zera(c);
    sb[c] = sb[a]*sb[b];
    for (i = 0; i < nb[a]; i++) {
        for (j = 0, acc = 0; j < nb[b]; j++) {
            bn[c][i+j] += acc + (bn[a][i]*bn[b][j]);
            acc = bn[c][i+j] / MOD;
            bn[c][i+j] %= MOD;
        }
        if (acc) bn[c][i+j] += acc;
    }

    for (i = TAM-1, nb[c] = 0; i >= 0 && !nb[c]; i--)
        if (bn[c][i]) nb[c] = i+1;
}

void desloca(int a) {
	for (int i = nb[a]++; i > 0; i--) 
		bn[a][i] = bn[a][i-1];
}

void div(int num, int div, int r, int q) {
	int k = nb[num]-1;
	unsigned long long iq;
	zera(r); zera(q);
	for (int k = nb[num]-1; k >= 0; k--) {
		bn[r][0] = bn[num][k];
		for (iq = 0, sb[div] = -1; compare(r, div) >= 0; iq++)
			soma(r, div, r);
		if (iq > 0) {
			desloca(q);
			bn[q][0] = iq;
		}
		desloca(r);
	}
}

int main() {
	char buf[120];
	zera(1);
	while (1) {
		gets(buf);
		strto(buf, 0);
		if (nb[0] == 1 && bn[0][0] == 0) break;

		soma(0, 1, 1);
	}
	imprime(1);
	printf("\n");
}
