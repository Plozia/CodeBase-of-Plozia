/*
========= Plozia =========
	Author:Plozia
	Problem:CF1060E Sergey and Subway
	Date:2022/7/17
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 2e5 + 5;
int n, Head[MAXN], cntEdge = 1, dep[MAXN], Size[MAXN];
LL ans, cnt[2];
struct node { int To, Next; } Edge[MAXN << 1];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
void addEdge(int x, int y) { ++cntEdge; Edge[cntEdge] = (node){y, Head[x]}; Head[x] = cntEdge; }

void dfs(int now, int father)
{
	dep[now] = dep[father] + 1; ++cnt[dep[now] & 1]; Size[now] = 1;
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To; if (u == father) continue ;
		dfs(u, now); Size[now] += Size[u];
	}
}

int main()
{
	n = Read(); for (int i = 1; i < n; ++i) { int x = Read(), y = Read(); addEdge(x, y); addEdge(y, x); }
	dfs(1, 1);
	for (int i = 2; i <= cntEdge; i += 2)
	{
		int x = Edge[i].To, y = Edge[i ^ 1].To; if (dep[x] > dep[y]) std::swap(x, y);
		ans += 1ll * Size[y] * (n - Size[y]);
	}
	LL sum = cnt[0] * cnt[1]; ans = ((ans - sum) >> 1) + sum; printf("%lld\n", ans); return 0;
}