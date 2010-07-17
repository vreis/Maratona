#include <cstdio>
#include <cstring>

int m[100][100];

int main() {
    char s[100], n;
    while (1) {
        scanf("%s%n ", s, &n);
        if (strcmp(s, "*") == 0) break;

        for (int i = 0; i < n; i++)
            m[i][i] = 1;

        for (int j = 1; j < n; j++)
            for (int i = 0; i < n-j; i++) {
                int min = n;
                for (int k = i+1; k <= i+j; k++) {
                    int a = m[i][k-1]+m[k][i+j];
                    if (a < min) min = a;
                    int tam = k-i;
                    if ((tam-1 == i+j-k) && (tam < min))
                        if (strncmp(s, s+tam, tam) == 0) min = tam;
                }
                m[i][i+j] = min;
            }
        printf("%d\n", m[0][n-1]);
    }
    return 0;
}
