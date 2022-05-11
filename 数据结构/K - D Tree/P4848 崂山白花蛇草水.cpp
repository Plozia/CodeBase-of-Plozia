/*
========= Plozia =========
	Author:Plozia
	Problem:P4848 崂山白花蛇草水
	Date:2022/3/18
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q;
struct NODE { int x, y, val; } s[MAXN], sp[MAXN * 20];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp1(const int &fir, const int &sec) { return sp[fir].x < sp[sec].y; }
bool cmp2(const int &fir, const int &sec) { return sp[fir].y < sp[sec].y; }

int a[MAXN], cnt = 0, d[MAXN * 20], cntkd, cntsgt, rootsgt;
const double alpha = 0.725;
struct KDTree
{
	int ls, rs, Minx, Maxx, Miny, Maxy, Size, Minnum, Maxnum, val;
	#define ls(p) tree[p].ls
	#define rs(p) tree[p].rs
	#define Minx(p) tree[p].Minx
	#define Maxx(p) tree[p].Maxx
	#define Miny(p) tree[p].Miny
	#define Maxy(p) tree[p].Maxy
	#define Size(p) tree[p].Size
	#define Minnum(p) tree[p].Minnum
	#define Maxnum(p) tree[p].Maxnum
	#define val(p) tree[p].val
}tree[MAXN * 20];
void Update(int p)
{
	val(p) = Minnum(p) = Maxnum(p) = sp[p].val;
	Minx(p) = Maxx(p) = sp[p].x, Miny(p) = Maxy(p) = sp[p].y;
	Size(p) = Size(ls(p)) + Size(rs(p)) + 1;
	if (ls(p)) Minx(p) = Min(Minx(p), Minx(ls(p))), Maxx(p) = Max(Maxx(p), Maxx(ls(p))), Miny(p) = Min(Miny(p), Miny(ls(p))), Maxy(p) = Max(Maxy(p), Maxy(ls(p))), Minnum(p) = Min(Minnum(ls(p)), Minnum(p)), Maxnum(p) = Max(Maxnum(p), Maxnum(ls(p)));
	if (rs(p)) Minx(p) = Min(Minx(p), Minx(rs(p))), Maxx(p) = Max(Maxx(p), Maxx(rs(p))), Miny(p) = Min(Miny(p), Miny(rs(p))), Maxy(p) = Max(Maxy(p), Maxy(rs(p))), Minnum(p) = Min(Minnum(rs(p)), Minnum(p)), Maxnum(p) = Max(Maxnum(p), Maxnum(rs(p)));
}
int Build(int l, int r)
{
	if (l > r) return 0; int mid = (l + r) >> 1;
	double valx = 0, valy = 0, avex = 0, avey = 0;
	for (int i = l; i <= r; ++i) avex += sp[a[i]].x, avey += sp[a[i]].y;
	avex /= r - l + 1, avey /= r - l + 1;
	for (int i = l; i <= r; ++i) valx += (sp[a[i]].x - avex) * (sp[a[i]].x - avex), valy += (sp[a[i]].y - avey) * (sp[a[i]].y - avey);
	if (valx > valy) std::nth_element(a + l, a + mid, a + r + 1, cmp1), d[a[mid]] = 1;
	else std::nth_element(a + l, a + mid, a + r + 1, cmp2), d[a[mid]] = 2;
	ls(a[mid]) = Build(l, mid - 1); rs(a[mid]) = Build(mid + 1, r);
	Update(a[mid]); return a[mid];
}
void Make_Node(int p)
{
	if (!ls(p)) Make_Node(ls(p));
	a[++cnt] = p;
	if (!rs(p)) Make_Node(rs(p));
	return ;
}
void Check(int &p)
{
	if (Size(p) * alpha <= Max(Size(ls(p)), Size(rs(p)))) { cnt = 0, Make_Node(p); p = Build(1, cnt); }
}
void Insert(int &p, int q)
{
	if (!p) { p = ++cntkd; sp[p] = s[q]; Update(p); return ; }
	if (d[p] == 1) { if (s[q].x <= sp[p].x) Insert(ls(p), q); else Insert(rs(p), q); }
	else { if (s[q].y <= sp[p].y) Insert(ls(p), q); else Insert(rs(p), q); }
	Update(p); Check(p); return ;
}
int r1, c1, r2, c2, k;
int Query(int p, int val)
{
	if (!p || Maxx(p) < r1 || Minx(p) > r2 || Maxy(p) < c1 || Miny(p) > c2) return 0;
	if (Minx(p) >= r1 && Maxx(p) <= r2 && Miny(p) >= c1 && Miny(p) <= c2)
	{
		if (Maxnum(p) <= val) return Size(p);
		if (Minnum(p) > val) return 0;
	}
	int flag = 0;
	if (sp[p].x >= r1 && sp[p].x <= r2 && sp[p].y >= c1 && sp[p].y <= c2) flag = (val(p) <= val);
	return Query(ls(p), val) + Query(rs(p), val) + flag;
}

struct SgT
{
	int Root;
}sgt[MAXN * 4];

void Change(int &p, int l, int r, int n)
{
	if (!p) p = ++cntsgt; Insert(sgt[p].Root, n);
	if (l == r) return ;
	int mid = (l + r) >> 1;
	if (s[n].val <= mid) Change(ls(p), l, mid, n);
	else Change(rs(p), mid + 1, r, n);
}

int Ask(int p, int l, int r, int k)
{
	if (p == 0) return 0; if (l == r) return l;
	int mid = (l + r) >> 1; int tmp = Query(sgt[p].Root, mid);
	if (tmp >= k) return Ask(ls(p), l, mid, k);
	return Ask(rs(p), mid + 1, r, k - tmp);
}

int main()
{
	n = Read(), q = Read(); int lst = 0; n = 0;
	while (q--)
	{
		int opt = Read();
		if (opt == 1)
		{
			++n; s[n].x = Read() ^ lst, s[n].y = Read() ^ lst, s[n].val = Read() ^ lst;
			Change(rootsgt, 0, 1000000000, n);
		}
		else
		{
			r1 = Read() ^ lst, c1 = Read() ^ lst, r2 = Read() ^ lst, c2 = Read() ^ lst, k = Read() ^ lst;
			if (r1 > r2) std::swap(r1, r2); if (c1 > c2) std::swap(c1, c2);
			lst = Ask(rootsgt, 0, 1000000000, k);
			if(lst == 0) puts("NAIVE!ORZzyz."); else printf("%d\n", lst);
		}
	}
	return 0;
}