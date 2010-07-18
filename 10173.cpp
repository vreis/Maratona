#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

/*
   UVa 10173 - Smallest Bounding Rectangle
   Algoritmo O(n^2), vai girando o convex hull
 */

using namespace std;

int cmp(long double a, long double b = 0.0) { 
    if (fabs(a-b) < 1e-10) return 0;
    return (a<b)?-1:1;
}

struct pt {
    long double x, y;
    pt() {}
    pt(long double x, long double y): x(x), y(y) {}
    long double operator%(const pt& a) { return x*a.y-y*a.x; }
    pt operator-(const pt &a) const { return pt(x-a.x, y-a.y); }
    bool operator<(const pt &a) const { 
        return (cmp(x, a.x) < 0) || (cmp(x, a.x) == 0 && cmp(y, a.y) < 0); }
    long double operator*(const pt& a) { return x*a.x+y*a.y; }
};

pt pivo;

bool cmp_ang(const pt &a, const pt &b) {
    int v = cmp((a-pivo)%(b-pivo));
    return v > 0 || v == 0 && cmp((a-pivo)*(a-pivo), (b-pivo)*(b-pivo)) < 0;
}

int area(pt a, pt b, pt c) { return cmp((b-a)%(c-a)); }
long double cos_ang(pt a, pt b) {
    return (a*b)/(sqrt(a*a)*sqrt(b*b));
}
long double sin_ang(pt a, pt b) {
    return fabs(a%b)/(sqrt(a*a)*sqrt(b*b));
}

int main() {
    int n;
    pt v[1010];
    pt h[1010];
    int top, k;

    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++)
            scanf("%llf %llf", &v[i].x, &v[i].y);

        pivo = *min_element(v, v+n);
        sort(v, v+n, cmp_ang);
        for (k = n-2; k >= 0 && area(v[0], v[n-1], v[k]) == 0; k--);
        reverse(v+k+1, v+n);
        top = 0;
        for (int i = 0; i < n; i++) {
            while (top > 1 && area(h[top-2], h[top-1], v[i]) <= 0) top--;
            h[top++] = v[i];
        }
        if (top > 1 && area(h[top-2], h[top-1], v[0]) == 0) top--;

        int pmin[4];
        long double tcos, tsin, area = 1.0/0.0;

        for (int j = 0; j < top+1; j++) {
            memset(pmin, 0, sizeof(pmin));
            for (int i = 1; i < top; i++) {
                if (cmp(h[i].y, h[pmin[0]].y) < 0) pmin[0] = i;
                if (cmp(h[i].x, h[pmin[1]].x) > 0) pmin[1] = i;
                if (cmp(h[i].y, h[pmin[2]].y) > 0) pmin[2] = i;
                if (cmp(h[i].x, h[pmin[3]].x) < 0) pmin[3] = i;
            }
            
            if (cmp((h[pmin[1]].x-h[pmin[3]].x)*(h[pmin[2]].y-h[pmin[0]].y), area) < 0) 
                area = (h[pmin[1]].x-h[pmin[3]].x)*(h[pmin[2]].y-h[pmin[0]].y);

            tcos = cos_ang(h[(pmin[0]+1)%top]-h[pmin[0]], pt(1,0));
            tsin = -sin_ang(h[(pmin[0]+1)%top]-h[pmin[0]], pt(1,0));
            if (cmp(tcos, 1) == 0) { // se ja esta alinhado, pega proximo ang
                pmin[0] = (pmin[0]+1)%top;
                tcos = cos_ang(h[(pmin[0]+1)%top]-h[pmin[0]], pt(1,0));
                tsin = -sin_ang(h[(pmin[0]+1)%top]-h[pmin[0]], pt(1,0));
            }

            for (int i = 0; i < top; i++) {
                long double x, y;
                x = h[i].x*tcos - h[i].y*tsin;
                y = h[i].x*tsin + h[i].y*tcos;
                h[i].x = x; h[i].y = y;
            }
        }
        
        printf("%.4llf\n", area);
    }
    return 0;
}
