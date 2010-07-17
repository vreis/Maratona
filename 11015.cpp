#include <cstdio>

#define max 30

int g[max][max];
int n, m;
char nomes[max][20];

int main() {
    int tot, mi, mip, ct=1;
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;
        
        for (int i = 1; i <= n; i++) scanf(" %s", &nomes[i]);
        
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                if (i == j) g[i][i] = 0; else
                g[i][j] = 999999;
        
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            g[a][b] = c; g[b][a] = c;
        }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j<= n; j++)
                    if (g[i][j] > g[i][k] + g[k][j]) g[i][j] = g[i][k] + g[k][j];

        mi = 99999999; mip = -1;
        for (int i = 1; i<=n; i++) {
            tot = 0; 
            for (int j = 1; j <=n; j++) tot += g[i][j];
            if (mi > tot) { mi = tot; mip = i; }
        }

        printf("Case #%d : %s\n", ct++, nomes[mip]);

    }
}
