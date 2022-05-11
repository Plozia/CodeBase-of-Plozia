/*
========= Plozia =========
	Author:Plozia
	Problem:
	Date:2021/3/16
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 100 + 10;
int n, m, Match[MAXN << 1], ans;
bool book[MAXN << 1];
vector <int> Next[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

bool dfs(int k)
{
	for (int i = 0; i < Next[k].size(); ++i)
	{
		int u = Next[k][i];
		if (book[u]) continue;
		book[u] = 1;
		if (!Match[u] || dfs(Match[u])) {Match[u] = k; return 1;}
	}
	return 0;
}

void Hungary()
{
	memset(Match, 0, sizeof(Match));
	for (int i = 1; i <= m; ++i)
	{
		memset(book, 0, sizeof(book));
		if (dfs(i)) ++ans;
	}
}

int main()
{
	m = read(), n = read();
	for (; ; )
	{
		int x = read(), y = read();
		if (x == y && x == -1) break;
		Next[x].push_back(y);
	}
	Hungary(); printf("%d\n", ans);
	for (int i = m + 1; i <= n; ++i)
		if (Match[i]) printf("%d %d\n", Match[i], i);
	return 0;
}
