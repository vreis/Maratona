#include <cstdio>
#include <cstring>

int main() {
    int ct, i;
    char buf[10000];
    scanf("%d", &ct);
    while (ct--) {
        int n; scanf("%d", &n);
        if (n == 0) printf("0\n"), continue; 
        if (n == 1) printf("1\n"), continue;
        buf[0] = '1'; buf[1] = '0'; buf[2] = 0;
        i = 1; n -= 2;
        while (n--) {
            if (buf[i] == '0') {
                if (buf[i-1] == '1') buf[++i] = '0';
                else buf[i] = '1';
            } else {
                if (buf[i-1] == '0') {
                    buf[i-1] = '1';
                    buf[i]
                }
            }
        }
    }
    return 0;
}
