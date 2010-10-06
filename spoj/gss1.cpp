#include <cstdio>
#include <algorithm>

#define NN 53000

int val[NN];

using namespace std;

struct segt {
	segt *e,* d;
	int le, ld;
	int mi, mf, t, m;

	segt(int le, int ld): le(le), ld(ld), e(NULL), d(NULL) {
		if (le == ld) { // folha
			mi = mf = t = m = val[le-1];
		} else {
			int mid = (le+ld)/2;
			e = new segt(le, mid);
			d = new segt(mid+1, ld);

			mi = max(e->t + d->mi, e->mi);
			mf = max(d->t + e->mf, d->mf);
			t = e->t + d->t;
			m = max(e->mf+d->mi, max(e->m, d->m));
		}
	}
	segt(int mi, int mf, int t, int m): mi(mi), mf(mf), t(t), m(m), e(NULL), d(NULL) {}
	segt() : e(NULL), d(NULL) {}

	//~segt() { delete e; delete d; }
};

#define inf 999999

segt query(segt *x, int i, int j) {
	if (i > x->ld || j < x->le) 
		return segt(-inf, -inf, -inf, -inf);
	
	if (i <= x->le && x->ld <= j)
		return *x;

	segt se = query(x->e, i, j);
	segt sd = query(x->d, i, j);
	
	segt res;
	res.mi = max(se.t + sd.mi, se.mi);
	res.mf = max(sd.t + se.mf, sd.mf);
	res.t = se.t + sd.t;
	res.m = max(se.mf+sd.mi, max(se.m, sd.m));

	return res;
}


int main() {
	segt *raiz;
	int n, m, a, b;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &val[i]);

	raiz = new segt(1, n);

	scanf("%d", &m);
	while (m--) {
		scanf("%d %d", &a, &b);
		printf("%d\n", query(raiz, a, b).m);
	}

	return 0;
}
