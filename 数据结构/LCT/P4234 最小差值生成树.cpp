/*
========= Plozia =========
	Author:Plozia
	Problem:P4234 最小差值生成树
	Date:2022/4/24
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::multiset;

typedef long long LL;
const int MAXN = 5e4 + 5, MAXM = 2e5 + 5;
int n, m, cntn, ans = 0x7f7f7f7f, ys[MAXN + MAXM];
struct EDGE
{
	int x, y, z;
	bool operator <(const EDGE &fir)const { return z < fir.z; }
}Edge[MAXM];
struct LCT
{
	int fa, Son[2], val, id;
	bool tag;
}tree[MAXN + MAXM];
multiset <int> s;
#define fa(p) tree[p].fa
#define ls(p) tree[p].Son[0]
#define rs(p) tree[p].Son[1]
#define Son(p, x) tree[p].Son[x]
#define val(p) tree[p].val
#define id(p) tree[p].id
#define tag(p) tree[p].tag

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Connect(int f, int x, int p) { fa(x) = f; Son(f, p) = x; }
bool NotRoot(int p) { return ls(fa(p)) == p || rs(fa(p)) == p; }
bool RightSon(int f, int p) { return rs(f) == p; }
void Update(int p)
{
	id(p) = p;
	if (val(id(ls(p))) > val(id(p))) id(p) = id(ls(p));
	if (val(id(rs(p))) > val(id(p))) id(p) = id(rs(p));
}
void Spread(int p)
{
	if (!tag(p)) return ;
	if (ls(p)) { tag(ls(p)) ^= 1; std::swap(ls(ls(p)), rs(ls(p))); }
	if (rs(p)) { tag(rs(p)) ^= 1; std::swap(ls(rs(p)), rs(rs(p))); }
}
void PushAll(int p)
{
	if (NotRoot(p)) PushAll(fa(p));
	Spread(p);
}
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
	for (int x = 0; p; x = p, p = fa(p)) { Splay(p); Son(p, 1) = x; Update(p); }
}
void MakeRoot(int p) { Access(p); Splay(p); tag(p) ^= 1; std::swap(ls(p), rs(p)); }
int FindRoot(int p)
{
	Access(p); Splay(p);
	while (ls(p)) { Spread(p); p = ls(p); }
	Splay(p); return p;
}

void Link(int x, int y) { MakeRoot(x); fa(x) = y; }
void Split(int x, int y) { MakeRoot(x); Access(y); Splay(y); }
void Cut(int x, int y) { MakeRoot(x); rs(x) = fa(y) = 0; Update(x); }

int main()
{
	n = Read(), m = Read(); cntn = n;
	for (int i = 1; i <= m; ++i) Edge[i].x = Read(), Edge[i].y = Read(), Edge[i].z = Read();
	for (int i = 1; i <= n; ++i) val(i) = 0x7f7f7f7f;
	std::sort(Edge + 1, Edge + m + 1);
	for (int i = 1; i <= m; ++i)
	{
		if (Edge[i].x == Edge[i].y) continue ;
		MakeRoot(Edge[i].x);
		if (FindRoot(Edge[i].y) == Edge[i].x)
		{
			Split(Edge[i].x, Edge[i].y);
			Cut(id(Edge[i].y), Edge[ys[id(Edge[i].y)]].x); Cut(id(Edge[i].y), Edge[ys[id(Edge[i].y)]].y);
		}
		++cntn; ys[cntn] = i; val(cntn) = Edge[i].z, id(cntn) = cntn;
		Link(cntn, Edge[i].x); Link(Edge[i].y, cntn); s.insert(Edge[i].z);
	}
	return 0;
}