#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>

using namespace std;

#define MAXN 210

int nvertices;
int cap[MAXN][MAXN], fluxo[MAXN][MAXN];
char v[MAXN];

int dfs(int u, int t) {
	if (u == t) return 1;
	for (int i = 0; i < nvertices; i++)
		if (!v[i] && ((cap[u][i] - fluxo[u][i]) > 0)) {
			v[u] = 1;
			if (dfs(i, t)) {
				fluxo[u][i]++; fluxo[i][u]--;
				return 1;
			}
			v[u] = 0;
		}
	return 0;
}

int emparelha(int n, int s, int t) {
	int res = 0;
	nvertices = n;
	memset(fluxo, 0, sizeof fluxo);
	while (1) {
		memset(v, 0, sizeof v);
		if (!dfs(s, t)) break;
		res++;
	}

	return res;
}

int main() {
	int n, m, k, ct = 1;
	while (scanf("%d %d %d", &n, &m, &k) != EOF) {
		memset(cap, 0, sizeof cap);

		for (int i = 1; i <= n; i++) {
			int aux; scanf("%d", &aux);
			cap[m+i][n+m+1] = aux;
		}

		for (int i = 0; i < k; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			cap[b][m+a] = 1;
		}

		for (int i = 1; i <= m; i++) cap[0][i] = 1;

		printf("Instancia %d\n%d\n\n", ct++, emparelha(n+m+2, 0, n+m+1));
	}
	return 0;
}
