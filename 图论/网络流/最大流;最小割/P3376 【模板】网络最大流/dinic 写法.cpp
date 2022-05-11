/*
========= Plozia =========
	Author:Plozia
	Problem:P3376 ��ģ�塿�������������dinic ���
	Date:2021/3/18
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 200 + 10, MAXM = 5000 + 10;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, m, s, t, Head[MAXN], cnt_Edge = 1, dep[MAXN], cur[MAXN];
struct node {int to; LL val; int Next;} Edge[MAXM << 1];
bool vis[MAXN];
LL ans;
LL Min(LL fir, LL sec) {return (fir < sec) ? fir : sec;}
void add_Edge(int x, int y, int z) {Edge[++cnt_Edge] = (node){y, (LL)z, Head[x]}; Head[x] = cnt_Edge;}

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

bool bfs()
{
	queue <int> q; q.push(s);
	memset(vis, 0, sizeof(vis));
	memset(dep, 0, sizeof(dep));
	dep[s] = 1; vis[s] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (Edge[i].val == 0 || vis[u]) continue;//ֻ�����������ĵ�
			vis[u] = 1; dep[u] = dep[x] + 1;
			q.push(u);
		}
	}
	return dep[t];
}

LL dfs(int now, LL Flow)
{
	if (now == t) return Flow;
	LL used = 0;
	for (int i = cur[now]; i; i = Edge[i].Next)//������������
	{
		cur[now] = i;//��ǰ���Ż�
		int u = Edge[i].to;
		if (Edge[i].val && dep[u] == dep[now] + 1)
		{
			LL Minn = dfs(u, Min(Flow - used, Edge[i].val));
			Edge[i].val -= Minn; Edge[i ^ 1].val += Minn; used += Minn;
			if (used == Flow) return used;
		}
	}
	if (used == 0) dep[now] = 0;//�޸Ĳ���
	return used;
}

int main()
{
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read(), z = read();
		add_Edge(x, y, z); add_Edge(y, x, 0);
	}
	while (bfs()) {for (int i = 1; i <= n; ++i) cur[i] = Head[i]; ans += dfs(s, INF);}//����������·
	printf("%lld\n", ans);
	return 0;
}
