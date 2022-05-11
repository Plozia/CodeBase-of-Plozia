/*
========= Plozia =========
	Author:Plozia
	Problem:P3386 ��ģ�塿����ͼ���ƥ��
	Date:2021/3/14
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 500 + 10;
int n, m, e, Match[MAXN], ans;
vector <int> Next[MAXN];
bool book[MAXN];

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
	for (int i = 1; i <= n; ++i)
	{
		memset(book, 0, sizeof(book));
		if (dfs(i)) ++ans;
	}
}

int main()
{
	n = read(), m = read(), e = read();
	for (int i = 1; i <= e; ++i)
	{
		int u = read(), v = read();
		Next[u].push_back(v);
	}
	Hungary();
	printf("%d\n", ans);
	return 0;
}
