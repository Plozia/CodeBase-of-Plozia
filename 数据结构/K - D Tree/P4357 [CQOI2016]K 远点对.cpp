/*
========= Plozia =========
	Author:Plozia
	Problem:P4357 [CQOI2016]K 远点对
	Date:2022/1/13
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, k;
struct node { LL x, y; } a[MAXN];
struct kdtree
{
	int ls, rs;
	LL Minx, Miny, Maxx, Maxy;
	#define ls(p) tree[p].ls
	#define rs(p) tree[p].rs
	#define Minx(p) tree[p].Minx
	#define Miny(p) tree[p].Miny
	#define Maxx(p) tree[p].Maxx
	#define Maxy(p) tree[p].Maxy
}tree[MAXN];
priority_queue < LL, std::vector <LL>, std::greater <LL> > q;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
LL Square(LL x) { return x * x; }
LL Calc(LL x, LL y) { return Max(Square(a[x].x - Minx(y)), Square(a[x].x - Maxx(y))) + Max(Square(a[x].y - Miny(y)), Square(a[x].y - Maxy(y))); }
bool cmp1(const node &fir, const node &sec) { return fir.x < sec.x; }
bool cmp2(const node &fir, const node &sec) { return fir.y < sec.y; }

void Update(int p)
{
	Minx(p) = Maxx(p) = a[p].x; Miny(p) = Maxy(p) = a[p].y;
	if (ls(p)) Minx(p) = Min(Minx(ls(p)), Minx(p)), Maxx(p) = Max(Maxx(ls(p)), Maxx(p)), Miny(p) = Min(Miny(ls(p)), Miny(p)), Maxy(p) = Max(Maxy(ls(p)), Maxy(p));
	if (rs(p)) Minx(p) = Min(Minx(rs(p)), Minx(p)), Maxx(p) = Max(Maxx(rs(p)), Maxx(p)), Miny(p) = Min(Miny(rs(p)), Miny(p)), Maxy(p) = Max(Maxy(rs(p)), Maxy(p));
}

int Build(int l, int r)
{
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	double avex = 0, avey = 0, valx = 0, valy = 0;
	for (int i = l; i <= r; ++i) avex += a[i].x, avey += a[i].y;
	avex /= (r - l + 1), avey /= (r - l + 1);
	for (int i = l; i <= r; ++i) valx += (a[i].x - avex) * (a[i].x - avex), valy += (a[i].y - avey) * (a[i].y - avey);
	if (valx > valy) std::nth_element(a + l, a + mid, a + r + 1, cmp1);
	else std::nth_element(a + l, a + mid, a + r + 1, cmp2);
	ls(mid) = Build(l, mid - 1); rs(mid) = Build(mid + 1, r);
	Update(mid); return mid;
}

void Ask(int l, int r, int x)
{
	if (l > r) return ;
	int mid = (l + r) >> 1; LL tmp = Square(a[mid].x - a[x].x) + Square(a[mid].y - a[x].y);
	if (tmp > q.top()) { q.pop(); q.push(tmp); }
	LL vall = Calc(x, ls(mid)), valr = Calc(x, rs(mid));
	if (vall > q.top() && valr > q.top())
	{
		if (vall > valr) { Ask(l, mid - 1, x); if (valr > q.top()) Ask(mid + 1, r, x); }
		else { Ask(mid + 1, r, x); if (vall > q.top()) Ask(l, mid - 1, x); }
	}
	else if (vall > q.top()) Ask(l, mid - 1, x);
	else if (valr > q.top()) Ask(mid + 1, r, x);
}

int main()
{
	n = Read(), k = Read() * 2;
	for (int i = 1; i <= n; ++i) a[i].x = Read(), a[i].y = Read();
	Build(1, n); for (int i = 1; i <= k; ++i) q.push(0);
	for (int i = 1; i <= n; ++i) Ask(1, n, i);
	printf("%lld\n", q.top()); return 0;
}