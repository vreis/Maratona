#include <cstdio>
#include <map>
#include <utility>

using namespace std;

#define MAXN (1000*100+10)

int ehprimo[MAXN];

void crivo(int n) {
    int i, j;
    ehprimo[0] = ehprimo[1] = 0;
    ehprimo[2] = 1;
    for (i = 3; i <=n ; i++)
        ehprimo[i] = i%2;
    for (i = 3; i*i <= n; i += 2)
        if (ehprimo[i])
            for (j = i*i; j <= n; j += i)
                ehprimo[j] = 0;
}

#define NN 1010

int m[NN][NN];
int vale[NN][NN];
int tem42;

map<pair<int,int>, bool> pd;

bool ganha(int i, int j) {
	if (i == j) return vale[i][i];
	if (vale[i][j]) return true;

	if (pd.find(make_pair(i, j)) != pd.end()) return pd[make_pair(i, j)];


	for (int k = i; k < j; k++)
		if ((vale[i][k] && !ganha(k+1, j)) || 
			(vale[k+1][j] && !ganha(i, k))) {
			pd[make_pair(i, j)] = true;
			return true;
		}

	pd[make_pair(i, j)] = false;
	return false;
}

int main() {
    crivo(MAXN);
    
    int t, ct, n;
    scanf("%d", &t);
    for (ct = 1; ct <= t; ct++) {
        printf("Case %d: ", ct);
        scanf("%d %*d", &n);
        tem42 = 0;
		pd.clear();
        for (int i = 1; i <= n; i++){
            scanf("%d", &m[i][i]);
			if (m[i][i] > 0)
            vale[i][i] = ehprimo[m[i][i]];
			else vale[i][i] = 0;
            if (m[i][i] == 42) tem42 = 1;
        }
        
        if (tem42) { printf("Soha\n"); continue; }
        
        for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                m[i][j] = m[i][j-1] + m[j][j];
                
                if (m[i][j] > 0)
					vale[i][j] = ehprimo[m[i][j]];
                else vale[i][j] = 0;
            }
		}
            
        if(ganha(1, n)) printf("Soha\n");
        else printf("Tara\n");
    }
    return 0;   
}
