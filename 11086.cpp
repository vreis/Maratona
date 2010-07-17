#include <cstdio>
#include <cstring>

#define MAX 1024*1024+10

char c[MAX];

int main() {
    int k;

    memset(c, 0, sizeof(c));
    for (int i = 2; i*i < MAX; i++)
        if (c[i] == 0)
            for (int j = i*i; j < MAX; j+= i) c[j] = 1;
    for (int i = 4; 2*i < MAX; i++)
        if (c[i] == 1)
            for (int j = 2*i; j < MAX; j+= i) c[j] = 0;

    while (scanf("%d", &k) > 0) {
        int n, s;
        s = 0;
        for (int i = 0; i < k; i++) {
            scanf("%d", &n);
            s += c[n];
        }
        printf("%d\n", s);
    }
    return 0;
}
