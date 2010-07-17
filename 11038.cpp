#include <cstdio>

int main() {
    int n, m, k;
    char buf[100], *c;
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == -1 && m == -1) break;

        k = 0;
        do {
            sprintf(buf, "%d", n++);
            for (c = buf; *c; c++) k+= (*c=='0');
        } while (n <= m);

        printf("%d\n", k);
    }
}
