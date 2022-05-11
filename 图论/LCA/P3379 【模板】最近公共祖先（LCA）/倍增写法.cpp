/*
========= Plozia =========
	Author:Plozia
	Problem:P3379 ��ģ�塿����������ȣ�LCA��
	Date:2021/3/8
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 5e5 + 10;
int n, m, f[MAXN][21], dep[MAXN], root;
vector <int> Next[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

void dfs(int now, int fa, int depth)
{
	dep[now] = depth;
	f[now][0] = fa;
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == fa) continue;
		dfs(u, now, depth + 1);
	}
}

int lca(int x, int y)
{
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; i >= 0; --i)
		if (dep[f[x][i]] >= dep[y]) x = f[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; --i)
		if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

int main()
{
	n = read(), m = read(), root = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		Next[x].push_back(y), Next[y].push_back(x);
	}
	dfs(root, root, 1);
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1];
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		printf("%d\n", lca(x, y));
	}
	return 0;
}
