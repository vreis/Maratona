#include <cstdio>
#include <cstring>

#define max 1010

int c[1010], p[1010], eh[1010];

int main() {
    for (int i = 0; i < max; i++) c[i] = (i&1); 
    c[2] = 1;
    for (int i = 3; i < max; i += 2) {
        if (c[i] == 1)
        for (int j = i*i; j < max; j+= i)
            c[j] = 0;
    } 
    int k = 1;
    for (int i = 2; i < max; i++)
        if (c[i] == 1) { p[k] = i; c[i] = k++; }
    memset(eh, 0, sizeof(eh));

    for (int i = 1; i < k-1; i++) {
        if (p[i]+p[i+1]+1 > max) break;
        else if (c[p[i]+p[i+1]+1] != 0) eh[c[p[i]+p[i+1]+1]] = 1;
    }

    int n,K, ct=0;
    scanf("%d %d", &n, &K);
    for (int i = 0; i < k && p[i] <= n; i++) {
        ct += eh[i];
    }
    if (ct >= K) printf("YES\n");
    else printf("NO\n");
}
