/*
========= Plozia =========
    Author:Plozia
    Problem:P4148 简单题
    Date:2022/1/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e5 + 5;
const double alpha = 0.725;
int a[MAXN], d[MAXN], cntn, n, Root;
struct node { int x, y, val; } s[MAXN];
struct kdtree
{
    int ls, rs, Minx, Miny, Maxx,  Maxy, lazy, Size; LL val;
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
    #define Minx(p) tree[p].Minx
    #define Maxx(p) tree[p].Maxx
    #define Miny(p) tree[p].Miny
    #define Maxy(p) tree[p].Maxy
    #define val(p) tree[p].val
    #define lazy(p) tree[p].lazy
    #define Size(p) tree[p].Size
}tree[MAXN];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp1(const int &fir, const int &sec) { return s[fir].x < s[sec].x; }
bool cmp2(const int &fir, const int &sec) { return s[fir].y < s[sec].y; }

void Make_a(int p)
{
    if (!p) return ;
    Make_a(ls(p)); a[++cntn] = p; Make_a(rs(p));
}

void Update(int p)
{
    val(p) = val(ls(p)) + val(rs(p)) + 1ll * s[p].val;
    Size(p) = Size(ls(p)) + Size(rs(p)) + 1;
    Minx(p) = Maxx(p) = s[p].x; Miny(p) = Maxy(p) = s[p].y;
    if (ls(p))
    {
        Minx(p) = Min(Minx(p), Minx(ls(p))); Maxx(p) = Max(Maxx(p), Maxx(ls(p)));
        Miny(p) = Min(Miny(p), Miny(ls(p))); Maxy(p) = Max(Maxy(p), Maxy(ls(p)));
    }
    if (rs(p))
    {
        Minx(p) = Min(Minx(p), Minx(rs(p))); Maxx(p) = Max(Maxx(p), Maxx(rs(p)));
        Miny(p) = Min(Miny(p), Miny(rs(p))); Maxy(p) = Max(Maxy(p), Maxy(rs(p)));
    }
}

int Build(int l, int r)
{
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    double avex = 0, avey = 0, valx = 0, valy = 0;
    for (int i = l; i <= r; ++i) avex += s[a[i]].x, avey += s[a[i]].y;
    avex /= (r - l + 1), avey /= (r - l + 1);
    for (int i = l; i <= r; ++i) valx += (s[a[i]].x - avex) * (s[a[i]].x - avex), valy += (s[a[i]].y - avey) * (s[a[i]].y - avey);
    if (valx > valy) std::nth_element(a + l, a + mid, a + r + 1, cmp1), d[a[mid]] = 1;
    else std::nth_element(a + l, a + mid, a + r + 1, cmp2), d[a[mid]] = 2;
    ls(a[mid]) = Build(l, mid - 1); rs(a[mid]) = Build(mid + 1, r);
    Update(a[mid]); return a[mid];
}

void Check(int &p)
{
    if (Size(p) * alpha <= Size(ls(p)) || Size(p) * alpha <= Size(rs(p)))
    {
        cntn = 0; Make_a(p); p = Build(1, cntn);
    }
}

void Insert(int &p, int x)
{
    if (!p) { p = x; Update(p); return ; }
    if (d[p] == 1)
    {
        if (s[x].x <= s[p].x) Insert(ls(p), x);
        else Insert(rs(p), x);
    }
    else
    {
        if (s[x].y <= s[p].y) Insert(ls(p), x);
        else Insert(rs(p), x);
    }
    Update(p); Check(p);
}

int Query(int p, int r1, int c1, int r2, int c2)
{
    if (!p || Minx(p) > r2 || Maxx(p) < r1 || Miny(p) > c2 || Maxy(p) < c1) return 0;
    if (r1 <= Minx(p) && r2 >= Maxx(p) && c1 <= Miny(p) && c2 >= Maxy(p)) return val(p);
    int val = 0;
    if (s[p].x >= r1 && s[p].x <= r2 && s[p].y >= c1 && s[p].y <= c2) val += s[p].val;
    val += Query(ls(p), r1, c1, r2, c2);
    val += Query(rs(p), r1, c1, r2, c2);
    return val;
}

int main()
{
    Read(); int lastans = 0;
    for (; ; )
    {
        int opt = Read();
        if (opt == 3) break ;
        if (opt == 1)
        {
            ++n; s[n].x = Read() ^ lastans, s[n].y = Read() ^ lastans, s[n].val = Read() ^ lastans;
            Insert(Root, n);
        }
        else if (opt == 2)
        {
            int r1 = Read() ^ lastans, c1 = Read() ^ lastans, r2 = Read() ^ lastans, c2 = Read() ^ lastans;
            if (r1 > r2) std::swap(r1, r2); if (c1 > c2) std::swap(c1, c2);
            printf("%d\n", lastans = Query(Root, r1, c1, r2, c2));
        }
    }
    return 0;
}