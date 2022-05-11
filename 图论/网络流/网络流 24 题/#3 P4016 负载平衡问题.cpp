/*
========= Plozia =========
	Author:Plozia
	Problem:网络流 24 题#3——P4016 负载平衡问题
	Date:2021/3/26
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 100 + 10, INF = 0x3f3f3f3f;
int n, Ave, a[MAXN], dis[MAXN], Flow[MAXN], cnt_Edge = 1, Head[MAXN], las[MAXN], ans, s, t, pre[MAXN];
bool book[MAXN];
struct node{int to, Flow, val, Next;} Edge[MAXN * 6];
void add_Edge(int x, int y, int f, int v) {++cnt_Edge; Edge[cnt_Edge] = (node){y, f, v, Head[x]}; Head[x] = cnt_Edge;}

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

bool SPFA()
{
	queue <int> q;
	memset(book, 0, sizeof(book));
	memset(Flow, 0x3f, sizeof(Flow));
	memset(dis, 0x3f, sizeof(dis));
	memset(pre, 0, sizeof(pre));
	q.push(s); book[s] = 1; dis[s] = 0;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (Edge[i].Flow == 0) continue ;
			if (dis[u] > dis[x] + Edge[i].val)
			{
				dis[u] = dis[x] + Edge[i].val;
				Flow[u] = std::min(Flow[x], Edge[i].Flow);
				pre[u] = i;
				if (!book[u]) {q.push(u); book[u] = 1;}
			}
		}
	}
	return dis[t] != INF;
}

void EK()
{
	while (SPFA())
	{
		int x = t;
		ans += Flow[t] * dis[t];
		while (x != s)
		{
			int p = pre[x];
			Edge[p].Flow -= Flow[t];
			Edge[p ^ 1].Flow += Flow[t];
			x = Edge[p ^ 1].to;
		}
	}
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) Ave += a[i];
	Ave /= n; s = n + 1, t = n + 2;
	for (int i = 1; i <= n; ++i) a[i] -= Ave;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i] > 0) add_Edge(s, i, a[i], 0), add_Edge(i, s, -a[i], 0);
		if (a[i] < 0) add_Edge(i, t, -a[i], 0), add_Edge(t, i, a[i], 0);
	}
	for (int i = 1; i <= n; ++i)
	{
		if (i != 1) add_Edge(i, i - 1, INF, 1), add_Edge(i - 1, i, 0, -1);
		if (i != n) add_Edge(i, i + 1, INF, 1), add_Edge(i + 1, i, 0, -1);
	}
	add_Edge(1, n, INF, 1); add_Edge(n, 1, 0, -1);
	add_Edge(n, 1, INF, 1); add_Edge(1, n, 0, -1);
	EK();
	printf("%d\n", ans);
	return 0;
}