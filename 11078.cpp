#include <cstdio>

int main() {
    int max, n, a, dif, maxdif, T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        scanf("%d", &a);
        max = a;
        maxdif = -99999999;
        while (--n) {
            scanf("%d", &a);
            dif = max-a;
            if (dif > maxdif) maxdif = dif;
            if (a > max) max = a;
        }

        printf("%d\n", maxdif);
    }
}
