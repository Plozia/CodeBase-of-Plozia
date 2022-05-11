/*
========= Plozia =========
	Author:Plozia
	Problem:P3275 [SCOI2011]糖果
	Date:2021/5/4
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, k, Head[MAXN], cnt_Edge = 1, cnt[MAXN];
LL dis[MAXN];
bool book[MAXN];
struct node { int to, val, Next; } Edge[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void SPFA()
{
	memset(dis, 0x3f, sizeof(dis));
	memset(book, 0, sizeof(book));
	memset(cnt, 0, sizeof(cnt));
	queue <int> q; q.push(0); book[0] = 1; dis[0] = 0;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (dis[u] > dis[x] + Edge[i].val)
			{
				dis[u] = dis[x] + Edge[i].val;
				if (!book[u])
				{
					book[u] = 1; ++cnt[u]; q.push(u);
					if (cnt[u] > n) { printf("-1\n"); exit(0); }
				}
			}
		}
	}
}

int main()
{
	n = read(), k = read();
	for (int i = 1; i <= k; ++i)
	{
		int z = read(), x = read(), y = read();
		if (z == 1) { add_Edge(y, x, 0); add_Edge(x, y, 0); }
		if (z == 2) { if (x == y) { printf("-1\n"); return 0; } add_Edge(x, y, -1); }
		if (z == 3) { add_Edge(y, x, 0); }
		if (z == 4) { if (x == y) { printf("-1\n"); return 0; } add_Edge(y, x, -1); }
		if (z == 5) { add_Edge(x, y, 0); }
	}
	for (int i = n; i >= 1; --i) add_Edge(0, i, -1);
	SPFA(); LL sum = 0;
	for (int i = 1; i <= n; ++i) sum += -dis[i];
	printf("%lld\n", sum); return 0;
}