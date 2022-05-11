/*
========= Plozia =========
	Author:Plozia
	Problem:CF246E Blood Cousins Return
	Date:2022/5/8
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::set;
using std::string;
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, Head[MAXN], cntEdge, fa[MAXN], Root[MAXN], q, dep[MAXN], cntSgT, ans[MAXN];
string Name[MAXN];
vector <int> Query[MAXN], id[MAXN];
bool vis[MAXN];
struct node { int To, Next; } Edge[MAXN << 1];
struct SgT
{
	set <string> s;
	int ls, rs;
	#define ls(p) tree[p].ls
	#define rs(p) tree[p].rs
}tree[MAXN * 20];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void addEdge(int x, int y) { ++cntEdge; Edge[cntEdge] = (node){y, Head[x]}; Head[x] = cntEdge; }

void Insert(int &p, int x, string v, int lp, int rp)
{
	if (!p) p = ++cntSgT;
	if (lp == rp) { tree[p].s.insert(v); return ; }
	int mid = (lp + rp) >> 1;
	if (x <= mid) Insert(ls(p), x, v, lp, mid);
	else Insert(rs(p), x, v, mid + 1, rp);
}

void Merge(int &p1, int p2, int lp, int rp)
{
	if (!p1 || !p2) { p1 = p1 + p2; return ; }
	if (lp == rp)
	{
		if (tree[p1].s.size() < tree[p2].s.size()) std::swap(p1, p2);
		for (auto it = tree[p2].s.begin(); it != tree[p2].s.end(); ++it) tree[p1].s.insert(*it);
		return ;
	}
	int mid = (lp + rp) >> 1;
	Merge(ls(p1), ls(p2), lp, mid);
	Merge(rs(p1), rs(p2), mid + 1, rp);
}

int Ask(int p, int x, int lp, int rp)
{
	if (x < lp || x > rp || p == 0) return 0;
	if (lp == rp) return tree[p].s.size();
	int mid = (lp + rp) >> 1;
	if (x <= mid) return Ask(ls(p), x, lp, mid);
	else return Ask(rs(p), x, mid + 1, rp);
}

void dfs(int now, int father)
{
	dep[now] = dep[father] + 1;
	Insert(Root[now], dep[now], Name[now], 1, n);
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs(u, now); Merge(Root[now], Root[u], 1, n);
	}
	for (int i = 0; i < Query[now].size(); ++i) ans[id[now][i]] = Ask(Root[now], dep[now] + Query[now][i], 1, n);
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i)
	{
		std::cin >> Name[i]; fa[i] = Read();
		if (fa[i]) addEdge(i, fa[i]), addEdge(fa[i], i);
	}
	q = Read();
	for (int i = 1; i <= q; ++i) { int v = Read(), k = Read(); Query[v].push_back(k); id[v].push_back(i); }
	for (int i = 1; i <= n; ++i)
		if (fa[i] == 0) dfs(i, i);
	for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	return 0;
}