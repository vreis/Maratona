#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

#define max 1010

struct arc {
    int v, c;
    arc() {}
    arc(int v, int c): v(v), c(c) {}
    bool operator<(const arc &a) const { return c < a.c; }
};

arc g[max][max];
int d[max], v[max], id[max];

int main() {
    priority_queue<arc> q;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%*d");
    int m, a, b, c, soma;

    memset(d, 0, sizeof(d));
    memset(id, 0, sizeof(id));
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        g[a][d[a]++] = arc(b, c);
       // g[b][d[b]++] = arc(a, c);
        id[b]++;
    }
    memset(v, 0, sizeof(v));
    for (int i = 1; i <=n;i++) if (id[i] == 0) {q.push(arc(i, 0)); break; }
    soma = 0;

    while (!q.empty()) {
        arc x = q.top(); q.pop();
        if (v[x.v] == 1) continue;
        v[x.v] = 1; soma += x.c;
        for (int i = 0; i < d[x.v]; i++)
            q.push(g[x.v][i]);
    }
    int conexo = 1;
    for (int i = 1; i <= n && conexo; i++)
        if (v[i] == 0)  conexo = 0;

    if (conexo)
        printf("%d\n", soma);
    else printf("-1\n");

    return 0;
}
