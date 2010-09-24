#include <cstdio>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

map<string,int> m;

#define NN 2024
// Inputs (populate these).
int deg[NN];
int adj[NN][NN];
// Union-Find.
int uf[NN];
int FIND( int x ) { return uf[x] == x ? x : uf[x] = FIND( uf[x] ); }
void UNION( int x, int y ) { uf[FIND( x )] = FIND( y ); }

int dfsn[NN], dfsnext;
// mindfsn[u] is the smallest DFS number reachable from u.
int mindfsn[NN];
// The O(1)-membership stack containing the vertices of the current component.
int comp[NN], ncomp;
bool incomp[NN];
void dfs( int n, int u ) {
	dfsn[u] = mindfsn[u] = dfsnext++;
	incomp[comp[ncomp++] = u] = true;
	for( int i = 0, v; v = adj[u][i], i < deg[u]; i++ ) {
		if( !dfsn[v] ) dfs( n, v );
		if( incomp[v] ) mindfsn[u] = min(mindfsn[u], mindfsn[v]);
	}
	if( dfsn[u] == mindfsn[u] ) {
		// u is the root of a connected component. Unify and forget it.
		do {
			UNION( u, comp[--ncomp] );
			incomp[comp[ncomp]] = false;
		} while( comp[ncomp] != u );
	}
}
void scc( int n ) {
	// Init union-find and DFS numbers.
	for( int i = 0; i < n; i++ ) dfsn[uf[i] = i] = ncomp = incomp[i] = 0;
	dfsnext = 1;
	for( int i = 0; i < n; i++ ) if( !dfsn[i] ) dfs( n, i );
}


void doisSat_insere(int a, int b) {
	adj[a^1][deg[a^1]++] = b;
	adj[b^1][deg[b^1]++] = a;
}

// n eh o dobro da quantidade de variaveis
bool doisSat_ok(int n) {
	bool ok = true;
	scc(n);
	for (int i = 0; i < n && ok; i+= 2)
		ok = (FIND(i) != FIND(i+1));
	return ok;
}

int main() {
	int n, ct=1; 
	string s, as; 
	int k; 
	char ss[30], ass[30];
	int negA, negB, idA, idB;
	while (scanf("%d ", &n) > 0) {
		k = 0;
		memset(deg, 0, sizeof(deg));
		m.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s %s ", ss, ass); 
			negA = negB = 0;

			if (ss[0] == '!') { s = ss+1; negA = 1; }
			else s = ss;
			if (ass[0] == '!') { as = ass+1; negB = 1; }
			else as = ass;

			if (m.find(s) == m.end()) {
				m[s] = k; k += 2;
			}
			if (m.find(as) == m.end()) {
				m[as] = k; k += 2;
			}
			idA = m[s] + negA; idB = m[as] + negB;
			doisSat_insere(idA, idB);
		}

		printf("Instancia %d\n", ct++);
		if (doisSat_ok(k)) printf("sim\n\n");
		else printf("nao\n\n");
	}
	return 0;
}
