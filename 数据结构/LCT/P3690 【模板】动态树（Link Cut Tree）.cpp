/*
========= Plozia =========
	Author:Plozia
	Problem:P3690 【模板】动态树（Link Cut Tree）
	Date:2022/4/12
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q;
struct LCT
{
	int fa, Son[2], val, sum;
	bool tag;
}spl[MAXN];
#define fa(p) spl[p].fa
#define Son(p, x) spl[p].Son[x]
#define val(p) spl[p].val
#define sum(p) spl[p].sum
#define tag(p) spl[p].tag

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
bool NotRoot(int p) { return Son(fa(p), 0) == p || Son(fa(p), 1) == p; }
bool RightSon(int f, int x) { return Son(f, 1) == x; }
void Update(int p) { sum(p) = sum(Son(p, 0)) ^ val(p) ^ sum(Son(p, 1)); }
void Spread(int p)
{
	if (!tag(p)) return ;
	tag(p) = 0;
	if (Son(p, 0)) { tag(Son(p, 0)) ^= 1; std::swap(Son(Son(p, 0), 0), Son(Son(p, 0), 1)); }
	if (Son(p, 1)) { tag(Son(p, 1)) ^= 1; std::swap(Son(Son(p, 1), 0), Son(Son(p, 1), 1)); }
}
void Rotate(int p)
{
	int f = fa(p), gf = fa(f), id = RightSon(f, p);
	Connect(f, Son(p, id ^ 1), id);
	fa(p) = gf; if (NotRoot(f)) Son(gf, RightSon(gf, f)) = p;
	Connect(p, f, id ^ 1);
	Update(f); Update(p);
}
void PushAll(int x)
{
	if (NotRoot(x)) PushAll(fa(x));
	Spread(x);
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
	for (int x = 0; p; x = p, p = fa(p))
	{
		Splay(p); Son(p, 1) = x; Update(p);
	}
}
void MakeRoot(int p)
{
	Access(p); Splay(p); tag(p) ^= 1; std::swap(Son(p, 0), Son(p, 1));
}
int FindRoot(int p)
{
	Access(p); Splay(p);
	while (Son(p, 0)) { Spread(p); p = Son(p, 0); }
	Splay(p); return p;
}

void Split(int x, int y)
{
	MakeRoot(x); Access(y); Splay(y);
}

void Link(int x, int y)
{
	MakeRoot(x); if (FindRoot(y) == x) return ;
	fa(x) = y;
}

void Cut(int x, int y)
{
	MakeRoot(x);
	if (FindRoot(y) != x || fa(y) != x || Son(y, 0)) return ;
	fa(y) = 0; Son(x, 1) = 0; Update(x);
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) val(i) = Read();
	while (q--)
	{
		int opt = Read(), x = Read(), y = Read();
		if (opt == 0) { Split(x, y); printf("%d\n", sum(y)); }
		if (opt == 1) { Link(x, y); }
		if (opt == 2) { Cut(x, y); }
		if (opt == 3) { Splay(x); val(x) = y; Update(x); }
	}
	return 0;
}