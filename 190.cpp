#include <cstdio>
#include <cmath>

struct pt {
    double x, y;
    pt() {}
    pt(double x, double y): x(x), y(y) {}
    pt operator-(const pt &a) { return pt(x-a.x,y-a.y); }
    double operator%(const pt &a) { return x*a.y - y*a.x; }
    double operator*(const pt &a) { return x*a.x + y*a.y; }
    pt operator+(const pt &a) { return pt(x+a.x,y+a.y); }
};

int cmp(double a, double b = 0.0) {
    if (fabs(a-b) < 1e-6) return 0;
    return (a < b) ? -1 : 1;
}

struct line {
    double a, b, c; // ax+by+c = 0
    line() {}
    line(double a, double b, double c): a(a), b(b), c(c) { fix(); }
    line(pt p, pt q) {
        pt A = p-q;
        a = A.y; b = -A.x; c = p%q;
        fix();
    }
    void fix() {
        if (cmp(a) == 0) {
            c /= b; b /= b;
        } else {
            b /= a; c /= a; a /= a;
        }
        if ( cmp(a) < 0 || 
            !cmp(a) && cmp(b) < 0) {
            a *= -1; b *= -1; c *= -1;
        }
    }
    
    line perp(pt p) { return line(-b, a, b*p.x-a*p.y); }
};

pt inter(line r, line s) {
    pt A = pt(r.a, s.a), B = pt(r.b, s.b), C = pt(r.c, s.c);
    return pt((B%C)/(A%B), (A%C)/(B%A));
}

struct circ {
    pt c; double r;
    circ() {}
    circ(pt c, double r): c(c),r(r) {}
};

circ find_circ(pt a, pt b, pt c) {
    line r(a, b), s(b, c);
    pt x = inter(r.perp(pt((a+b).x/2, (a+b).y/2)), s.perp(pt((b+c).x/2, (b+c).y/2)));
    return circ(x, sqrt((x-a)*(x-a)));
}

int main() {
    pt a, b, c;
    while (scanf("%lf%lf %lf%lf %lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) > 0) {
        circ C = find_circ(a, b, c);
        char s1, s2;
        s1 = cmp(C.c.x)<0?'+':'-';
        s2 = cmp(C.c.y)<0?'+':'-';
        printf("(x %c %.3lf)^2 + (y %c %.3lf)^2 = %.3lf^2\n", s1, fabs(C.c.x), s2, fabs(C.c.y), C.r);
        double d, e, f;
        char s3;
        d = -2*C.c.x; e = -2*C.c.y;
        f = C.c.x*C.c.x + C.c.y*C.c.y - C.r*C.r;
        s1 = cmp(d)>=0?'+':'-';
        s2 = cmp(e)>=0?'+':'-';
        s3 = cmp(f)>=0?'+':'-';
        printf("x^2 + y^2 %c %.3lfx %c %.3lfy %c %.3lf = 0\n\n", s1, fabs(d), s2, fabs(e), s3, fabs(f));
    }
}
