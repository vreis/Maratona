#include <cstdio>
#include <algorithm>

#define NN 33000

char str[NN];

using namespace std;

struct segt {
	segt *e,* d;
	int le, ld;
	int ab, fe;

	segt(int le, int ld): le(le), ld(ld), e(NULL), d(NULL) {
		if (le == ld) { // folha
			if (str[le-1] == '(') {
				ab = 1; fe = 0;
			} else {
				ab = 0; fe = 1;
			}
		} else {
			int mid = (le+ld)/2;
			e = new segt(le, mid);
			d = new segt(mid+1, ld);
			fe = e->fe + max(0, d->fe - e->ab);
			ab = d->ab + max(0, e->ab - d->fe);
		}
	}

	~segt() { delete e; delete d; }
};

void flip(segt *x, int pos) {
	if (x->le == x->ld && x->ld == pos) {
		int aux = x->ab;
		x->ab = x->fe;
		x->fe = aux;
	} else {
		if (pos <= (x->le+x->ld)/2)
			flip(x->e, pos);
		else 
			flip(x->d, pos);

		x->fe = x->e->fe + max(0, x->d->fe - x->e->ab);
		x->ab = x->d->ab + max(0, x->e->ab - x->d->fe);
	}
}


int main() {
	segt *raiz;
	for (int ct = 1; ct <= 10; ct++) {
		int n, m;
		printf("Test %d:\n", ct);
		scanf("%d %s %d ", &n, str, &m);
		raiz = new segt(1, n);
		for (int i = 0; i < m; i++) {
			int x;
			scanf("%d ", &x);
			if (x == 0) {
				if (raiz->ab == 0 && raiz->fe == 0) printf("YES\n");
				else printf("NO\n");
			} else flip(raiz, x);
		}
		delete raiz;
	}
	return 0;
}
