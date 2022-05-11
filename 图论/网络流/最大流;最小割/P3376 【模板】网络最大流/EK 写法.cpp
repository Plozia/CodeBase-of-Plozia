/*
========= Plozia =========
	Author:Plozia
	Problem:P3376 ��ģ�塿�������������EK д��
	Date:2021/3/18
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 200 + 10, MAXM = 5000 + 10;
LL INF = 0x7f7f7f7f7f7f7f7f;
int n, m, s, t, cnt_Edge = 1, Head[MAXN], pre[MAXN], vis[MAXN];
LL dis[MAXN], ans;
struct node
{
	int to; LL val; int Next;
}Edge[MAXM << 1];
int book[MAXN][MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
void add_Edge(int x, int y, int z) {Edge[++cnt_Edge] = (node){y, (LL)z, Head[x]}; Head[x] = cnt_Edge;}
LL Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}

bool bfs()
{
	queue <int> q; q.push(s);
	memset(vis, 0, sizeof(vis));
	vis[s] = 1; dis[s] = INF;
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (Edge[i].val <= 0) continue;
			if (vis[u] == 1) continue;
			pre[u] = i; vis[u] = 1;
			dis[u] = Min(dis[x], Edge[i].val);
			q.push(u);
			if (u == t) return 1;
		}
	}
	return 0;
}

void update()
{
	for (int i = t; i != s;)
	{
		int v = pre[i];
		Edge[v].val -= dis[t]; Edge[v ^ 1].val += dis[t];
		i = Edge[v ^ 1].to;
	}
	ans += dis[t];
}

int main()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read(), z = read();
		add_Edge(x, y, z); add_Edge(y, x, 0);
	}
	while (bfs()) {update();}
	printf("%lld\n", ans);
	return 0;
}
