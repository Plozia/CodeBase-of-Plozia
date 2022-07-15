/*
========= Plozia =========
	Author:Plozia
	Problem:CF932F Escape Through Leaf
	Date:2022/7/15
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 2e5 + 5, LEFT = -1e5, RIGHT = 1e5;
int n, Head[MAXN], cntEdge, cntsgt, Root[MAXN], Size[MAXN], cntline;
LL a[MAXN], b[MAXN], f[MAXN];
struct LINE { LL k, b; } Line[MAXN];
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT { int tag, ls, rs; } tree[MAXN * 40];
#define tag(p) tree[p].tag
#define ls(p) tree[p].ls
#define rs(p) tree[p].rs

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
void addEdge(int x, int y) { ++cntEdge; Edge[cntEdge] = (node){y, Head[x]}; Head[x] = cntEdge; }
LL Calc(int l, LL x) { return (l == 0) ? 0x3f3f3f3f3f3f3f3fll : (Line[l].k * x + Line[l].b); }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

void Insert(int &p, int k, int lp, int rp)
{
	if (!p) p = ++cntsgt;
	if (tag(p) == 0) { tag(p) = k; return ; }
	if (lp == rp)
	{
		if (Calc(tag(p), lp) > Calc(k, lp)) tag(p) = k;
		return ;
	}
	int mid = (lp + rp) >> 1;
	if (Line[tag(p)].k > Line[k].k)
	{
		if (Calc(tag(p), mid) > Calc(k, mid)) { Insert(ls(p), tag(p), lp, mid); tag(p) = k; }
		else Insert(rs(p), k, mid + 1, rp);
	}
	else if (Line[tag(p)].k < Line[k].k)
	{
		if (Calc(tag(p), mid) > Calc(k, mid)) { Insert(rs(p), tag(p), mid + 1, rp); tag(p) = k; }
		else Insert(ls(p), k, lp, mid);
	}
	else if (Calc(tag(p), mid) > Calc(k, mid)) tag(p) = k;
}

void Merge(int &p1, int p2, int lp, int rp)
{
	if (!p1 || !p2) { p1 = p1 + p2; return ; }
	if (lp == rp) { if (Calc(tag(p2), lp) < Calc(tag(p1), lp)) tag(p1) = tag(p2); return ; }
	int mid = (lp + rp) >> 1; Merge(ls(p1), ls(p2), lp, mid); Merge(rs(p1), rs(p2), mid + 1, rp);
	Insert(p1, tag(p2), lp, rp);
}

LL Ask(int &p, LL x, LL lp, LL rp)
{
	if (!p) p = ++cntsgt; if (lp == rp) return Calc(tag(p), x);
	int mid = (lp + rp) >> 1; LL val = 0x7f7f7f7f7f7f7f7f;
	if (x <= mid) val = Ask(ls(p), x, lp, mid); else val = Ask(rs(p), x, mid + 1, rp);
	return Min(val, Calc(tag(p), x));
}

void dfs(int now, int father)
{
	Size[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs(u, now); Size[now] += Size[u];
		Merge(Root[now], Root[u], LEFT, RIGHT);
	}
	if (Size[now] == 1)
	{
		Line[++cntline] = (LINE){b[now], 0}; f[now] = 0;
		Insert(Root[now], cntline, LEFT, RIGHT);
	}
	else
	{
		f[now] = Ask(Root[now], a[now], LEFT, RIGHT);
		Line[++cntline] = (LINE){b[now], f[now]};
		Insert(Root[now], cntline, LEFT, RIGHT);
	}
}

int main()
{
	freopen("test.in", "r", stdin); freopen("test.out", "w", stdout);
	n = Read(); for (int i = 1; i <= n; ++i) a[i] = Read(); for (int i = 1; i <= n; ++i) b[i] = Read();
	for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); addEdge(x, y); addEdge(y, x); }
	dfs(1, 1); for (int i = 1; i <= n; ++i) printf("%lld%c", f[i], " \n"[i == n]); return 0;
}