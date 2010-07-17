#include <cstdio>
#include <cstring>

struct pt {
    int x, y;

    pt() {}
    pt(int x, int y): x(x), y(y) {}
    int operator%(const pt &a) { return x*a.y - a.x*y; }
    pt operator-(const pt& a) { return pt(x-a.x, y-a.y); }
    bool operator==(const pt &a) { return (x == a.x && y == a.y); }
    bool operator<(const pt &a) {
        return (x < a.x) || (x == a.x && y < a.y);
    }
};

int ccw(pt a, pt b, pt c) {
    int aux = (b-a)%(c-a);
    if (aux == 0) return 0;
    if (aux < 0) return -1;
    return 1;
}

struct seg {
    pt a, b;

    bool inter(seg &s) {
        return (ccw(a, b, s.a)*ccw(a, b, s.b) < 0) &&
               (ccw(s.a, s.b, a)*ccw(s.a, s.b, b) < 0);
    }
};

int cmp(int x) {
    if (x == 0) return 0;
    if (x < 0) return -1;
    return 1;
}

bool seg_intersect(pt p, pt q, pt r, pt s) {
      pt A = q - p, B = s - r, C = r - p, D = s - q;
        int a = cmp(A % C) + 2 * cmp(A % D);
          int b = cmp(B % C) + 2 * cmp(B % D);
            if (a == 3 || a == -3 || b == 3 || b == -3) return false;
              if (a || b || p == r || p == s || q == r || q == s) return true;
                int t = (p < r) + (p < s) + (q < r) + (q < s);
                  return t != 0 && t != 4;
}


int main() {
    int n, tot, ent;
    seg s[1010];
    char v[1010];

    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        memset(v, 0, n);

        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", &s[i].a.x, &s[i].a.y, &s[i].b.x, &s[i].b.y);

        tot = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++)
                if (seg_intersect(s[i].a, s[i].b, s[j].a, s[j].b)) {
                //if (s[i].inter(s[j])) { 
                    tot++;
                    v[i] = 1; v[j] = 1;
                }
        }
        
        for (int i = 0; i < n; i++)
            if (v[i] == 0) tot+= 2;
        printf("%d\n", tot);
    }
}
