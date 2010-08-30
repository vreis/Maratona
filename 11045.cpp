#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>

using namespace std;

#define MAXN 50

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

int emparelha(int s, int t) {
	int mini, res = 0;

	memset(fluxo, 0, sizeof fluxo);
	while (1) {
		memset(v, 0, sizeof v);
		if (!dfs(s, t)) break;
		res++;
	}

	return res;
}

int main() {
	int t, n, m;
	map<string,int> ma;
	ma["XXL"] = 2; ma["XL"] = 3; ma["L"] = 4; ma["M"] = 5; ma["S"] = 6; ma["XS"] = 7;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d ", &n, &m);
		memset(cap, 0, sizeof cap);
		for (int i = 0; i < m; i++) {
			string a, b;
			cin >> a >> b;
			cap[8+i][ma[a]] = 1; cap[ma[a]][8+i] = 1;
			cap[8+i][ma[b]] = 1; cap[ma[b]][8+i] = 1;

			cap[0][8+i] = 1; cap[8+i][0] = 1;
		}

		for (int i = 0; i < 6; i++) {
			cap[i+2][1] = n/6;
			cap[1][i+2] = n/6;
		}

		nvertices = m+8;
		if (emparelha(0,1) == m)
			printf("YES\n");
		else
			printf("NO\n");
	}
}
