/*
========= Plozia =========
	Author:Plozia
	Problem:
	Date:2021/3/23
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 5e3 + 10, MAXM = 5e4 + 10, INF = 0x7f7f7f7f;
int n, m, s, t, dis[MAXN], Flow[MAXN], Head[MAXN], cnt_Edge = 1, pre[MAXN], ans_flow, ans_spend;
struct EDGE {int to, w, c, Next;} Edge[MAXM << 1];
bool book[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh = (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}
void add_Edge(int u, int v, int w, int c) {Edge[++cnt_Edge] = (EDGE){v, w, c, Head[u]}; Head[u] = cnt_Edge;}
int Min(int fir, int sec) {return (fir < sec) ? fir : sec;}

bool SPFA()//��ע����û��
{
	queue <int> q; q.push(s);
	memset(dis, 0x7f, sizeof(dis));
	memset(Flow, 0x7f, sizeof(Flow));
	memset(pre, 0, sizeof(pre));
	memset(book, 0, sizeof(book));
	dis[s] = 0; book[s] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (Edge[i].w > 0 && dis[u] > dis[x] + Edge[i].c)
			{
				dis[u] = dis[x] + Edge[i].c;
				Flow[u] = Min(Edge[i].w, Flow[x]);
				pre[u] = i;
				if (!book[u]) {book[u] = 1; q.push(u);}
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
		for (; x != s; )
		{
			int k = pre[x];
			Edge[k].w -= Flow[t];
			Edge[k ^ 1].w += Flow[t];
			x = Edge[k ^ 1].to;
		}
		ans_flow += Flow[t];
		ans_spend += Flow[t] * dis[t];
	}
}

int main()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i)
	{
		int u = read(), v = read(), w = read(), c = read();
		add_Edge(u, v, w, c); add_Edge(v, u, 0, -c);
	}
	EK(); printf("%d %d\n", ans_flow, ans_spend);
	return 0;
}
