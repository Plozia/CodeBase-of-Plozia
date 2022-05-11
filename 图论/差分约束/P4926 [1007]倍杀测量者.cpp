/*
========= Plozia =========
	Author:Plozia
	Problem:P4926 [1007]倍杀测量者
	Date:2021/5/5
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
typedef double DB;
const int MAXN = 1000 + 10;
const DB eps = 1e-8;
int n, s, t, Head[MAXN], cnt_Edge = 1, cnt[MAXN];
struct node { int to, Next, Tag; DB val; } Edge[MAXN << 2];
struct node2 { int op, x, y, z; } a[MAXN << 2];
DB c[MAXN], dis[MAXN];
bool book[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
void add_Edge(int x, int y, int Tag, DB z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x], Tag, log2(z)}; Head[x] = cnt_Edge; }

bool check(DB mid)
{
	memset(Head, 0, sizeof(Head));
	memset(Edge, 0, sizeof(Edge));
	memset(cnt, 0, sizeof(cnt));
	memset(book, 0, sizeof(book));
	cnt_Edge = 1;
	for (int i = 1; i <= n; ++i)
		if (c[i] != 0) { add_Edge(i, 0, 1, (DB)c[i]); add_Edge(0, i, 0, (DB)c[i]); }
		else add_Edge(i, 0, 1, 0), add_Edge(0, i, 0, 0);
	for (int i = 1; i <= s; ++i)
	{
		if (c[a[i].x] != 0 && c[a[i].y] != 0)
		{
			if (a[i].op == 1 && (DB)c[a[i].x] > (DB)c[a[i].y] * (a[i].z - mid)) return 1;
			if (a[i].op == 2 && (DB)c[a[i].x] * (a[i].z + mid) < (DB)c[a[i].y]) return 1;
		}
		if (a[i].op == 1) add_Edge(a[i].x, a[i].y, 1, (DB)(a[i].z - mid));
		else add_Edge(a[i].x, a[i].y, 0, (DB)(a[i].z + mid));
	}
	queue <int> q;
	for (int i = 1; i <= n; ++i) dis[i] = 1e17;
	dis[0] = 0.0; q.push(0); book[0] = 1;
	while (!q.empty())
	{
		int x = q.front(); q.pop(); book[x] = 0;
		for (int i = Head[x]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			DB val = (Edge[i].Tag == 1) ? (dis[x] - Edge[i].val) : (dis[x] + Edge[i].val);
			if (dis[u] > val)
			{
				dis[u] = val;
				if (!book[u])
				{
					book[u] = 1; cnt[u]++; q.push(u);
					if (cnt[u] > n + 1) return 1;
				}
			}
		}
	}
	return 0;
}

int main()
{
	n = read(), s = read(), t = read();
	DB l = 0, r = 1e18, ans = -1.0;
	for (int i = 1; i <= s; ++i)
	{
		a[i].op = read(), a[i].x = read(), a[i].y = read(), a[i].z = read();
		if (a[i].op == 1) r = std::min(r, (DB)a[i].z);
	}
	for (int i = 1; i <= t; ++i)
	{
		int C = read(), x = read(); c[C] = 1.0 * x;
	}
	// /*Debug*/ printf("%d\n", (int)check((l + r) / 2.0));
	while (r - l > eps)
	{
		DB mid = (l + r) / 2.0;
		if (check(mid)) l = ans = mid;
		else r = mid;
	}
	if (std::fabs(ans + 1.0) <= eps) printf("-1\n");
	else printf("%.10lf\n", ans);
	return 0;
}