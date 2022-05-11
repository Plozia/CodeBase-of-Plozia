/*
========= Plozia =========
	Author:Plozia
	Problem:P1501 [国家集训队]Tree II
	Date:2022/4/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
typedef unsigned int uint;
const int MAXN = 1e5 + 5;
const uint P = 51061;
int n, q;
struct LCT
{
	uint sum, mul, add, fa, Son[2], val, Size;
	bool tag;
}lct[MAXN];
#define sum(p) lct[p].sum
#define mul(p) lct[p].mul
#define add(p) lct[p].add
#define fa(p) lct[p].fa
#define Son(p, x) lct[p].Son[x]
#define ls(p) lct[p].Son[0]
#define rs(p) lct[p].Son[1]
#define val(p) lct[p].val
#define tag(p) lct[p].tag
#define Size(p) lct[p].Size

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void Connect(int f, int s, int id) { fa(s) = f; Son(f, id) = s; }
bool RightSon(int f, int s) { return rs(f) == s; }
bool NotRoot(int p) { return ls(fa(p)) == p || rs(fa(p)) == p; }
void Update(int p) { sum(p) = (sum(ls(p)) + val(p) + sum(rs(p))) % P; Size(p) = Size(ls(p)) + Size(rs(p)) + 1; }
void Spread(int p)
{
	if (tag(p))
	{
		if (ls(p)) { tag(ls(p)) ^= 1; std::swap(ls(ls(p)), rs(ls(p))); }
		if (rs(p)) { tag(rs(p)) ^= 1; std::swap(ls(rs(p)), rs(rs(p))); }
		tag(p) = 0;
	}
	if (ls(p))
	{
		sum(ls(p)) = (1ll * sum(ls(p)) * mul(p) + 1ll * add(p) * Size(ls(p))) % P;
		mul(ls(p)) = mul(ls(p)) * mul(p) % P; add(ls(p)) = (1ll * add(ls(p)) * mul(p) + add(p)) % P;
		val(ls(p)) = (1ll * val(ls(p)) * mul(p) + add(p)) % P;
	}
	if (rs(p))
	{
		sum(rs(p)) = (1ll * sum(rs(p)) * mul(p) + 1ll * add(p) * Size(rs(p))) % P;
		mul(rs(p)) = mul(rs(p)) * mul(p) % P; add(rs(p)) = (1ll * add(rs(p)) * mul(p) + add(p)) % P;
		val(rs(p)) = (1ll * val(rs(p)) * mul(p) + add(p)) % P;
	}
	mul(p) = 1, add(p) = 0;
}
void PushAll(int p) { if (NotRoot(p)) PushAll(fa(p)); Spread(p); }

void Rotate(int p)
{
	int f = fa(p), gf = fa(f), id = RightSon(f, p);
	Connect(f, Son(p, id ^ 1), id);
	fa(p) = gf; if (NotRoot(f)) Son(gf, RightSon(gf, f)) = p;
	Connect(p, f, id ^ 1);
	Update(f); Update(p);
}
void Splay(int p)
{
	PushAll(p);
	while (NotRoot(p))
	{
		int f = fa(p), gf = fa(f);
		if (NotRoot(f))
			if (RightSon(f, p) == RightSon(gf, f)) Rotate(f);
			else Rotate(p);
		Rotate(p);
	}
}

void Access(int p)
{
	for (int x = 0; p; x = p, p = fa(p)) { Splay(p); rs(p) = x; Update(p); }
}

void MakeRoot(int p)
{
	Access(p); Splay(p); tag(p) ^= 1; std::swap(ls(p), rs(p));
}

int FindRoot(int p)
{
	Access(p); Splay(p);
	while (ls(p))
	{
		Spread(p);
		p = ls(p);
	}
	Splay(p); return p;
}

void Link(int x, int y)
{
	MakeRoot(x); if (FindRoot(y) == x) return ;
	fa(x) = y;
}
void Cut(int x, int y)
{
	MakeRoot(x);
	if (FindRoot(y) != x || fa(y) != x || ls(y)) return ;
	fa(y) = rs(x) = 0; Update(x);
}
void Split(int x, int y)
{
	MakeRoot(x); Access(y); Splay(y);
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) sum(i) = val(i) = Size(i) = mul(i) = 1;
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); Link(x, y); }
	while (q--)
	{
		char ch = getchar(); while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
		int x = Read(), y = Read();
		if (ch == '+')
		{
			uint c = Read(); Split(x, y);
			add(y) = (add(y) + c) % P; val(y) = (val(y) + c) % P; sum(y) = (sum(y) + c * Size(y)) % P;
		}
		if (ch == '-') { int u = Read(), v = Read(); Cut(x, y); Link(u, v); }
		if (ch == '*')
		{
			int c = Read(); Split(x, y);
			mul(y) = mul(y) * c % P; add(y) = add(y) * c % P; sum(y) = sum(y) * c % P; val(y) = val(y) * c % P;
		}
		if (ch == '/') { Split(x, y); printf("%d\n", (int)sum(y)); }
	}
	return 0;
}