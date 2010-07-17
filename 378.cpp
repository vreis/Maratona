#include <cstdio>
#include <cmath>

struct pt {
    double x, y;
    pt() {}
    pt(double x, double y): x(x), y(y) {}
    pt operator-(const pt &a) { return pt(x-a.x,y-a.y); }
    double operator%(const pt &a) { return x*a.y - y*a.x; }
};

int cmp(double a, double b = 0.0) {
    if (fabs(a-b) < 1e-6) return 0;
    return (a < b) ? -1 : 1;
}

struct line {
    double a, b, c; // ax+by+c = 0
    line() {}
    line(double a, double b, double c): a(a), b(b), c(c) { }
    line(pt p, pt q) {
        pt A = p-q;
        if (cmp(A.x) != 0) {
            a = A.y/A.x;
            b = -1;
            c = (p%q)/A.x;
        } else {
            a = -1;
            b = 0;
            c = -(p%q)/A.y;
        }
    }

};

pt inter(line r, line s) {
    pt A = pt(r.a, s.a), B = pt(r.b, s.b), C = pt(r.c, s.c);
    return pt((B%C)/(A%B), (A%C)/(B%A));
}

int main() {
    int N;
    scanf("%d", &N);
    printf("INTERSECTING LINES OUTPUT\n");
    while (N--) {
        pt p0, p1, p2, p3;
        scanf("%lf%lf%lf%lf %lf%lf%lf%lf", &p0.x, &p0.y, &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
        line r = line(p0,p1);
        line s = line(p2,p3);
        if (cmp(r.a, s.a) == 0 && cmp(r.b, s.b) == 0) {
            if (cmp(r.c, s.c) == 0)
                printf("LINE\n");
            else
                printf("NONE\n");
        } else {
            pt p = inter(r,s);
            printf("POINT %.2lf %.2lf\n", p.x, p.y);
        }
    }
    printf("END OF OUTPUT\n");
}
