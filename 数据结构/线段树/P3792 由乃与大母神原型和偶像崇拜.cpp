/*
========= Plozia =========
	Author:Plozia
	Problem:P3792 由乃与大母神原型和偶像崇拜
	Date:2022/2/27
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::map;
using std::set;
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
int Abs(int x) { return (x > 0) ? x : (-x); }
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

typedef long long LL;
const int MAXN = 5e5 + 5;
int n, m, a[MAXN], Pre[MAXN], Aft[MAXN], cnt, sta[MAXN], Top;
map <int, int> book;
set <int> s[MAXN];
struct node
{
	int l, r, Gcd, Maxn, Minn, PreNum, AftNum, PreMax;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define Gcd(p) tree[p].Gcd
	#define Maxn(p) tree[p].Maxn
	#define Minn(p) tree[p].Minn
	#define PreNum(p) tree[p].PreNum
	#define AftNum(p) tree[p].AftNum
	#define PreMax(p) tree[p].PreMax
	node operator +(const node &fir)
	{
		node c; c.l = l, c.r = fir.r, c.PreMax = Max(PreMax, fir.PreMax);
		c.Gcd = gcd(gcd(Gcd, fir.Gcd), Abs(fir.PreNum - AftNum));
		c.Maxn = Max(Maxn, fir.Maxn); c.Minn = Min(Minn, fir.Minn);
		c.AftNum = fir.AftNum; c.PreNum = PreNum; return c;
	}
}tree[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) { Gcd(p) = 0, Maxn(p) = Minn(p) = PreNum(p) = AftNum(p) = a[l], PreMax(p) = Pre[l]; return ; }
	int mid = (l + r) >> 1; Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

void Change(int p, int x, node val)
{
	if (x == 0) return ;
	if (l(p) == r(p)) { tree[p] = val; return ; }
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) Change(p << 1, x, val);
	else Change(p << 1 | 1, x, val);
	tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

node Ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return tree[p];
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid && r > mid) return Ask(p << 1, l, r) + Ask(p << 1 | 1, l, r);
	else if (l <= mid) return Ask(p << 1, l, r);
	else return Ask(p << 1 | 1, l, r);
}

void Work1(int lastans)
{
	int x = Read(), y = Read();
	Aft[Pre[x]] = Aft[x]; Pre[Aft[x]] = Pre[x];
	Change(1, Aft[x], (node){Aft[x], Aft[x], 0, a[Aft[x]], a[Aft[x]], a[Aft[x]], a[Aft[x]], Pre[Aft[x]]});
	s[book[a[x]]].erase(x);
	if (s[book[a[x]]].empty()) sta[++Top] = book[a[x]];
	a[x] = y; Pre[x] = Aft[x] = 0;
	if (book.find(y) == book.end())
	{
		int tmp = (Top == 0) ? ++cnt : (sta[Top--]);
		book[y] = tmp; s[tmp].insert(x);
		Change(1, x, (node){x, x, 0, y, y, y, y, 0});
		return ;
	}
	y = book[y];
	auto it = s[y].lower_bound(x);
	if (it == s[y].begin())
	{
		Aft[x] = *s[y].begin(); Pre[*s[y].begin()] = x;
		Change(1, x, (node){x, x, 0, a[x], a[x], a[x], a[x], 0});
		int tmp = *s[y].begin();
		Change(1, tmp, (node){tmp, tmp, 0, a[tmp], a[tmp], a[tmp], a[tmp], Pre[tmp]});
		s[y].insert(x);
	}
	else if (it == s[y].end())
	{
		--it;
		Pre[x] = *it; Aft[*it] = x;
		Change(1, x, (node){x, x, 0, a[x], a[x], a[x], a[x], Pre[x]});
		s[y].insert(x);
	}
	else
	{
		auto it2 = it; --it;
		Pre[x] = *it; Aft[x] = *it2;
		Aft[*it] = x; Pre[*it2] = x;
		Change(1, x, (node){x, x, 0, a[x], a[x], a[x], a[x], Pre[x]});
		int tmp = *it2;
		Change(1, tmp, (node){tmp, tmp, 0, a[tmp], a[tmp], a[tmp], a[tmp], Pre[tmp]});
		s[y].insert(x);
	}
}

void Work2(int &lastans)
{
	int l = Read(), r = Read(), k = 1;
	if (l > r) std::swap(l, r); node tmp = Ask(1, l, r);
	if (((tmp.Maxn - tmp.Minn) == 1ll * (r - l) * k) && (tmp.Gcd == k || !tmp.Gcd) && (tmp.PreMax < l || k == 0)) puts("damushen"), ++lastans;
	else puts("yuanxing");
}

int main()
{
	n = Read(), m = Read(); int lastans = 0;
	for (int i = 1; i <= n; ++i)
	{
		a[i] = Read();
		if (book.find(a[i]) == book.end())
		{
			book[a[i]] = ++cnt; s[book[a[i]]].insert(i);
		}
		else
		{
			Pre[i] = *--s[book[a[i]]].end();
			Aft[*--s[book[a[i]]].end()] = i;
			s[book[a[i]]].insert(i);
		}
	}
	Build(1, 1, n);
	for (int _ = 1; _ <= m; ++_)
	{
		int opt = Read();
		if (opt == 1) Work1(lastans);
		else Work2(lastans);
	}
	return 0;
}