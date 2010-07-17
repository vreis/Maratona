#include <cstdio>

int s, t, n, w;

void hor() {
    for (int i = 0; i < w; i++)
        printf("*");
    printf("\n");
}

void gr() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) printf("*");
        for (int j = 0; j < s; j++) printf(".");
    }
    for (int j = 0; j < t; j++) printf("*");
    printf("\n");
}

int main() {
    int ct=1;
    while (1) {
        scanf("%d%d%d", &s, &t, &n);
        if (s == 0 && t == 0 && n == 0) break;

        printf("Case %d:\n", ct++);
        w = n*(t+s) + t;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < t; j++) hor(); 
            for (int j = 0; j < s; j++) gr(); 
        }
        for (int j = 0; j < t; j++) hor();
        printf("\n");
    }
    return 0;
}
