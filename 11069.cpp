#include <cstdio>

int main() {
    int res[100], n;
    res[1] = 1;
    res[2] = 2;
    res[3] = 2;
    for (int i = 4; i < 90; i++)
        res[i] = res[i-3]+res[i-2];

    while (scanf("%d", &n) != EOF) printf("%d\n", res[n]);
}
