/*
========= Plozia =========
	Author:Plozia
	Problem:P6279 [USACO20OPEN]Favorite Colors G
	Date:2021/11/16
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;
using std::queue;

typedef long long LL;
const int MAXN = 2e5 + 5;
int n, fa[MAXN], Color[MAXN], col, m;
vector <int> v[MAXN], Son[MAXN];
queue <int> NeedMerge;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Merge(int x, int y)
{
	x = fa[x], y = fa[y]; if (x == y) return ;
	if (v[x].size() > v[y].size()) std::swap(x, y);
	for (int i = 0; i < v[x].size(); ++i) v[y].push_back(v[x][i]);
	for (int i = 0; i < Son[x].size(); ++i) fa[Son[x][i]] = y, Son[y].push_back(Son[x][i]);
	fa[x] = y; if (v[y].size() > 1) NeedMerge.push(y); return ;
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(); v[x].push_back(y);
	}
	for (int i = 1; i <= n; ++i)
	{
		fa[i] = i; if (v[i].size() > 1) NeedMerge.push(i);
		Son[i].push_back(i);
	}
	while (!NeedMerge.empty())
	{
		int x = NeedMerge.front(); NeedMerge.pop();
		while (v[x].size() > 1)
		{
			int fir = v[x].back(); v[x].pop_back(); int sec = v[x].back();
			if (fa[fir] != fa[sec]) Merge(fir, sec);
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!Color[fa[i]]) Color[fa[i]] = ++col;
		printf("%d\n", Color[fa[i]]);
	}
	return 0;
}