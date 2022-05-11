/*
========= Plozia =========
	Author:Plozia
	Problem:P5960 【模板】差分约束算法
	Date:2021/4/29
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 5e3 + 10;
int n, m, Head[MAXN], cnt_Edge = 1, dis[MAXN], cnt[MAXN];
struct node { int to, val, Next; } Edge[MAXN << 1];
bool book[MAXN];

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
	memset(dis, -0x3f, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	memset(book, 0, sizeof(book));
	queue <int> q; q.push(0); dis[0] = 0; book[0] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (dis[x] + Edge[i].val > dis[u])
			{
				dis[u] = dis[x] + Edge[i].val;
				if (!book[u])
				{
					book[u] = 1; q.push(u); ++cnt[u];
					if (cnt[u] > n) { printf("NO\n"); exit(0); }
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
		int x = read(), y = read(), z = read();//注意这里 x 和 y 的顺序
		add_Edge(x, y, -z);
	}
	for (int i = 1; i <= n; ++i) add_Edge(0, i, 0);
	SPFA();
	for (int i = 1; i <= n; ++i) printf("%d ", dis[i]);
	printf ("\n"); return 0;
}