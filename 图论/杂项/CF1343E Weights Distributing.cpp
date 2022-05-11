/*
========= Plozia =========
	Author:Plozia
	Problem:CF1343E Weights Distributing
	Date:2021/8/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 2e5 + 5;
int t, n, m, Head[MAXN], cnt_Edge = 1, dis[4][MAXN], Start, Middle, End, p[MAXN];
LL ans = 0, sum[MAXN];
bool book[4][MAXN];
struct node { int to, val, Next; } Edge[MAXN << 1];
struct pri
{
	int u, Num;
	bool operator <(const pri &fir)const
	{
		return Num > fir.Num;
	}
};

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void Dijkstra()
{
	priority_queue <pri> q1, q2, q3;
	q1.push((pri){Start, 0}), q2.push((pri){Middle, 0}), q3.push((pri){End, 0});
	while (!q1.empty())
	{
		pri x = q1.top(); q1.pop();
		if (book[1][x.u]) continue ; book[1][x.u] = 1;
		for (int i = Head[x.u]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (book[1][u]) continue ;
			if (dis[1][u] > dis[1][x.u] + Edge[i].val)
			{
				dis[1][u] = dis[1][x.u] + Edge[i].val;
				q1.push((pri){u, dis[1][u]});
			}
		}
	}
	while (!q2.empty())
	{
		pri x = q2.top(); q2.pop();
		if (book[2][x.u]) continue ; book[2][x.u] = 1;
		for (int i = Head[x.u]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (book[2][u]) continue ;
			if (dis[2][u] > dis[2][x.u] + Edge[i].val)
			{
				dis[2][u] = dis[2][x.u] + Edge[i].val;
				q2.push((pri){u, dis[2][u]});
			}
		}
	}
	while (!q3.empty())
	{
		pri x = q3.top(); q3.pop();
		if (book[3][x.u]) continue ; book[3][x.u] = 1;
		for (int i = Head[x.u]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (book[3][u]) continue ;
			if (dis[3][u] > dis[3][x.u] + Edge[i].val)
			{
				dis[3][u] = dis[3][x.u] + Edge[i].val;
				q3.push((pri){u, dis[3][u]});
			}
		}
	}
}

int main()
{
	t = Read(); memset(dis, 0x7f, sizeof(dis));
	while (t--)
	{
		n = Read(), m = Read(), Start = Read(), Middle = Read(), End = Read();
		for (int i = 1; i <= n; ++i) Head[i] = book[1][i] = book[2][i] = book[3][i] = 0; cnt_Edge = 1;
		for (int i = 1; i <= n; ++i) dis[1][i] = dis[2][i] = dis[3][i] = 0x7f7f7f7f; ans = 0x7f7f7f7f7f7f7f7f;
		dis[1][Start] = dis[2][Middle] = dis[3][End] = 0;
		for (int i = 1; i <= m; ++i) p[i] = Read(); sum[0] = 0;
		std::sort(p + 1, p + m + 1);
		for (int i = 1; i <= m; ++i) sum[i] = (LL)p[i] + sum[i - 1];
		for (int i = 1; i <= m; ++i)
		{
			int x = Read(), y = Read();
			add_Edge(x, y, 1); add_Edge(y, x, 1);
		}
		Dijkstra();
		for (int i = 1; i <= n; ++i)
			if (dis[1][i] + dis[3][i] + dis[2][i] <= m) ans = Min(ans, sum[dis[1][i] + dis[3][i] + dis[2][i]] + sum[dis[2][i]]);
		printf("%lld\n", ans);
	}
	return 0;
}