/*
========= Plozia =========
	Author:Plozia
	Problem:网络流 24 题#4——P2761 软件补丁问题
	Date:2021/3/29
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 21, MAXM = 100 + 10;
int n, m, t[MAXM], b1[MAXM], b2[MAXM], f1[MAXM], f2[MAXM], ans = 0x7f7f7f7f, dis[1 << MAXN];
bool book[1 << MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

void SPFA()
{
	queue <int> q; q.push((1 << n) - 1);
	memset(dis, 0x3f, sizeof(dis));
	dis[(1 << n) - 1] = 0; book[(1 << n) - 1] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		if (x == 0) ans = std::min(ans, dis[x]);
		for (int i = 1; i <= m; ++i)
		{
			if (((x & b1[i]) == b1[i]) && ((x & b2[i]) == 0))
			{
				int tState = (x | f2[i] | f1[i]) ^ f1[i];
				if (dis[tState] > dis[x] + t[i])
				{
					dis[tState] = dis[x] + t[i];
					if (!book[tState]) {book[tState] = 1; q.push(tState);}
				}
			}
		}
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i)
	{
		t[i] = read();
		char ch;
		for (int j = 1; j <= n; ++j)
		{
			std::cin >> ch;
			if (ch == '+') b1[i] = b1[i] | (1 << (j - 1));
			if (ch == '-') b2[i] = b2[i] | (1 << (j - 1));
		}
		for (int j = 1; j <= n; ++j)
		{
			std::cin >> ch;
			if (ch == '+') f2[i] = f2[i] | (1 << (j - 1));
			if (ch == '-') f1[i] = f1[i] | (1 << (j - 1));
		}
	}
	SPFA();
	if (ans != 0x7f7f7f7f) printf("%d\n", ans);
	else printf("0\n");
	return 0;
}