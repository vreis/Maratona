#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int p[2000], c[2000], s[2000], id[2000];
    int n, k, aux;

    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 1; i <= n; i++) scanf("%d%d", &p[i], &c[i]);

        s[0] = 999999999; c[0] = 999999999; id[0] = 0;
        s[1] = c[1]; k = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = k; j >= 0; j--)
                if (s[j] >= p[i])
                    if (j == k) {
                        k++;
                        s[k] = min(c[i], s[j]-p[i]);
                        id[k] = i;
                    } else {
                        aux = min(c[i], c[id[j]]-p[i]);
                        if (aux > s[j+1]) {
                            s[j+1] = aux;
                            id[j+1] = i;
                        }
                    }
        }

        printf("%d\n", k);
    }
}
