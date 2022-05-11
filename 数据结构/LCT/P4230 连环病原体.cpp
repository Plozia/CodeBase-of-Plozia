/*
========= Plozia =========
	Author:Plozia
	Problem:P4230 连环病原体
	Date:2022/4/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 5, MAXM = 4e5 + 5;
int n, m;
LL sum1[MAXM], sum2[MAXM];
struct EDGE { int x, y; } Edge[MAXM];
struct LCT
{
	int fa, Son[2], tag;
}tree[MAXN];
#define fa(p) tree[p].fa
#define Son(p, x) tree[p].Son[x]
#define ls(p) tree[p].Son[0]
#define rs(p) tree[p].Son[1]
#define tag(p) tree[p].tag
#define RightSon(f, p) (rs(f) == p)
#define NotRoot(p) (ls(fa(p)) == p || rs(fa(p)) == p)

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void Connect(int f, int x, int id) { fa(x) = f; Son(f, id) = x; }
void Spread(int p)
{
	if (!tag(p)) return ;
	if (ls(p)) { tag(ls(p)) ^= 1; std::swap(ls(ls(p)), rs(ls(p))); }
	if (rs(p)) { tag(rs(p)) ^= 1; std::swap(ls(rs(p)), rs(rs(p))); }
	tag(p) = 0;
}
void Rotate(int p)
{
	int f = fa(p), gf = fa(f), id = RightSon(f, p);
	Connect(f, Son(p, id ^ 1), id);
	fa(p) = gf; if (NotRoot(f)) Son(gf, RightSon(gf, f)) = p;
	Connect(p, f, id ^ 1);
}
void PushAll(int p) { if (NotRoot(p)) PushAll(fa(p)); Spread(p); }
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

void Access(int p) { for (int x = 0; p; x = p, p = fa(p)) { Splay(p); rs(p) = x; } }
void MakeRoot(int p) { Access(p); Splay(p); tag(p) ^= 1; std::swap(ls(p), rs(p)); }
int FindRoot(int p)
{
	Access(p); Splay(p);
	while (ls(p)) { Spread(p); p = ls(p); }
	Splay(p); return p;
}
void Cut(int x, int y)
{
	MakeRoot(x);
	if (FindRoot(y) != x || fa(y) != x || ls(y)) return ;
	fa(y) = rs(x) = 0;
}
bool Link(int x, int y)
{
	MakeRoot(x);
	if (FindRoot(y) == x) return 0;
	fa(x) = y; return 1;
}

int main()
{
	m = Read();
	for (int i = 1; i <= m; ++i) { Edge[i].x = Read(), Edge[i].y = Read(); }
	int l = 1;
	for (int r = 1; r <= m; ++r)
	{
		while (!Link(Edge[r].x, Edge[r].y))
		{
			++sum1[m]; --sum1[r];
			sum2[l] += m - r + 1; sum2[r + 1] -= m - r + 1;
			Cut(Edge[l].x, Edge[l].y); ++l;
		}
	}
	for (int i = m - 1; i >= 1; --i) sum1[i] += sum1[i + 1];
	for (int i = 1; i <= m; ++i) sum2[i] += sum2[i - 1];
	for (int i = 1; i <= m; ++i) printf("%lld%c", sum2[i] + sum1[i] * (m - i + 1), " \n"[i == m]);
	return 0;
}