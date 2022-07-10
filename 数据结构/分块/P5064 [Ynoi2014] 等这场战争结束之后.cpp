/*
========= Plozia =========
	Author:Plozia
	Problem:P5064 [Ynoi2014] 等这场战争结束之后
	Date:2022/7/9
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e5 + 1;
unsigned int n, m, Head[MAXN], cntEdge, Block = 4250;
int ans[MAXN];
unsigned int fa[MAXN], Size[MAXN];
unsigned short f[MAXN][25];
struct node { unsigned int opt, x, y; } q[MAXN];
struct EDGE { unsigned int To, Next; } Edge[MAXN];
struct NODE
{
	unsigned int a, id;
	bool operator <(const NODE &fir)const { return a < fir.a; }
}a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
void addEdge(int From, int To)
{
	++cntEdge; Edge[cntEdge] = (EDGE){To, Head[From]}; Head[From] = cntEdge;
}
int gf(int x)
{
	while (fa[x] != x) x = fa[x];
	return x;
}

void Merge(int &fx, int &fy)
{
	if (Size[fx] > Size[fy]) fx ^= fy ^= fx ^= fy;
	fa[fx] = fy; Size[fy] += Size[fx];
	for (int j = 1; j <= 24; ++j) f[fy][j] += f[fx][j];
}
void Split(int fx, int fy)
{
	fa[fx] = fx; Size[fy] -= Size[fx];
	for (int j = 1; j <= 24; ++j) f[fy][j] -= f[fx][j];
}

void Calc(int fx, int u)
{
	int sum = 0, flag = 0;
	for (int j = 1; j <= 24; ++j)
	{
		if (sum + f[fx][j] < q[u].y) sum += f[fx][j];
		else { flag = j; break ; }
	}
	for (int j = (flag - 1) * Block + 1, pz = std::min(flag * Block, n); j <= pz; ++j)
	{
		if (gf(a[j].id) == fx) ++sum;
		if (sum == q[u].y) { ans[u] = a[j].a; break ; }
	}
}

void dfs(int now)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (q[u].opt == 1)
		{
			int fx = gf(q[u].x), fy = gf(q[u].y);
			if (fx != fy) Merge(fx, fy);
			dfs(u);
			if (fx != fy) Split(fx, fy);
		}
		else if (q[u].opt == 3)
		{
			int fx = gf(q[u].x);
			if (q[u].y > Size[fx]) { ans[u] = -1; dfs(u); continue ; }
			Calc(fx, u); dfs(u);
		}
		else dfs(u);
	}
}

int main()
{
	n = Read(), m = Read(); for (int i = 1; i <= n; ++i) a[i].a = Read(), a[i].id = i;
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; ++i) { q[i].opt = Read(), q[i].x = Read(); if (q[i].opt != 2) q[i].y = Read(); }
	for (int i = 1; i <= m; ++i)
	{
		if (q[i].opt != 2) addEdge(i - 1, i);
		else addEdge(q[i].x, i);
	}
	for (int i = 1; i <= n; ++i) fa[i] = i, Size[i] = 1, ++f[a[i].id][(i - 1) / Block + 1];
	dfs(0);
	for (int i = 1; i <= m; ++i)
		if (q[i].opt == 3) printf("%d\n", ans[i]);
	return 0;
}