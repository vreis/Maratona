#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;

// the maximum number of vertices
#define NN 2024

// adjacency matrix (fill this up)
// If you fill adj[][] yourself, make sure to include both u->v and v->u.
int cap[NN][NN], deg[NN], adj[NN][NN];

// BFS stuff
int q[NN], prev[NN];

int dinic( int n, int s, int t )
{
    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( prev, -1, sizeof( prev ) );
        int qf = 0, qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], i = 0, v; i < deg[u]; i++ )
                if( prev[v = adj[u][i]] == -1 && cap[u][v] )
                    prev[q[qb++] = v] = u;

        // see if we're done
        if( prev[t] == -1 ) break;

        // try finding more paths
        for( int z = 0; z < n; z++ ) if( cap[z][t] && prev[z] != -1 )
        {
            int bot = cap[z][t];
            for( int v = z, u = prev[v]; u >= 0; v = u, u = prev[v] )
                bot = min(bot, cap[u][v]);
            if( !bot ) continue;

            cap[z][t] -= bot;
            cap[t][z] += bot;
            for( int v = z, u = prev[v]; u >= 0; v = u, u = prev[v] )
            {
                cap[u][v] -= bot;
                cap[v][u] += bot;
            }
            flow += bot;
        }
    }

    return flow;
}

char v[NN];

void dfs(int u) {
	v[u] = 1;
	for (int i = 0; i < deg[u]; i++)
		if (!v[adj[u][i]] && (cap[u][adj[u][i]] > 0))
			dfs(adj[u][i]);
}

void do_cover(int n, int k) {
	memset(v, 0, sizeof v);
	dfs(0);
	for (int i = 1; i <= k; i++)
		if (!v[i]) printf(" r%d", i);
	for (int i = k+1; i <= n; i++)
		if (v[i]) printf(" c%d", i-k);
}

int main() {
	int r, c, n;
	while (1) {
		scanf("%d %d %d", &r, &c, &n);
		if (r == 0) break;

		memset(cap, 0, sizeof cap);
		memset(deg, 0, sizeof deg);

		for (int i = 1; i <= r; i++) { adj[0][deg[0]++] = i; adj[i][deg[i]++] = 0; cap[0][i] = 1; cap[i][0] = 0; }
		for (int i = 1; i <= c; i++) { adj[r+i][deg[r+i]++] = r+c+1; adj[r+c+1][deg[r+c+1]++] = r+i; cap[r+i][r+c+1] = 1; cap[r+c+1][r+i] = 0; }

		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			adj[a][deg[a]++] = r+b; cap[a][r+b] = 1;
			adj[r+b][deg[r+b]++] = a; cap[r+b][a] = 0;
		}

		int flow = dinic(r+c+2, 0, r+c+1);
		printf("%d", flow);
		do_cover(r+c, r);
		printf("\n");
	}
}
