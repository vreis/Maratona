#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define llint long long int

struct pt {
    llint x, y;

    pt(llint x, llint y): x(x), y(y) {} 
    pt() {}
    llint operator%(const pt &a) const { return x*a.y - y*a.x; }
    pt operator-(const pt &a) const { return pt(x-a.x, y-a.y); }
    llint mod() const { return (x*x+y*y); }
    bool operator<(const pt &a) const {
        if (a.x == x) return y < a.y;
        return x < a.x;
    }
};

llint area2(pt a, pt b, pt c) {
    return (b-a)%(c-a);
}

pt pivo;

bool cmp(const pt &a, const pt &b) {
    llint x;
    if ((x = (a-pivo)%(b-pivo)) == 0) 
        return (a-pivo).mod() < (b-pivo).mod();
    return x > 0;
}

int main() {
    int N, n;
    llint len_ini;
    long double len;
    pt v[200], hull[200];
    int top, k, i;

    scanf("%d", &N);
    while (N--) {
        scanf("%lld%d", &len_ini, &n);

        for (i = 0; i < n; i++) {
            scanf("%lld%lld", &v[i].x, &v[i].y);
        }

        // Graham Scan
        pivo = *min_element(v, v+n);
        //printf("pivo %lld,%lld\n", pivo.x, pivo.y);
        sort(v, v+n, cmp);
        // inverte a ordem dos pontos que fecham o hull
        for (k = n-2; k >= 0 && area2(v[0], v[n-1], v[k]) == 0; k--);
        reverse(v+(k+1), v+n);
        //for (i = 0; i < n; i++) printf("%lld,%lld\n", v[i].x, v[i].y);
        top = 0; i = 0;
        while (i < n) {
            while (top > 1 && area2(hull[top-2], hull[top-1], v[i]) <= 0) {
                //printf("remove %lld,%lld\n", v[top-1].x, hull[top-1].y);
                top--; 
            }
            hull[top++] = v[i++];
        }

        len = 0;
        for (i = 0; i < top; i++) {
            unsigned long long aa, bb;
            if (hull[i].x > hull[(i+1)%top].x)
                aa = hull[i].x-hull[(i+1)%top].x;
            else  aa = hull[(i+1)%top].x-hull[i].x;
            if (hull[i].y > hull[(i+1)%top].y)
                bb = hull[i].y-hull[(i+1)%top].y;
            else
               bb = hull[(i+1)%top].y-hull[i].y;
            //printf("hull %lld,%lld  len %llf\n", hull[i].x, hull[i].y, len);
            len += sqrt(aa*aa+bb*bb);
        }
        if (len > len_ini)
            printf("%.5llf\n", len);
        else printf("%lld.00000\n", len_ini);
        
    }

    return 0;
}
