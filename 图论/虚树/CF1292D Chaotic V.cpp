/*
========= Plozia =========
	Author:Plozia
	Problem:CF1292D Chaotic V.
	Date:2021/12/23
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::map;

typedef long long LL;
const int MAXN = 20000 + 5;
int n, Head[MAXN], cnt_Edge, Prime[MAXN], cnt_Prime, Key[MAXN], cnt_Key, Size[MAXN], cnt_node;
LL f[MAXN], g[MAXN];
struct node { int To, val, Next; } Edge[MAXN << 2];
bool vis[MAXN];
struct Number
{
	int p[700];
	void init() { for (int i = 0; i <= 699; ++i) p[i] = 0; }
	bool operator <(const Number &fir)const
	{
		for (int i = 1; i <= cnt_Prime; ++i)
			if (p[i] < fir.p[i]) return 1;
			else if (p[i] > fir.p[i]) return 0;
		return 1;
	}
	bool operator ==(const Number &fir)const
	{
		for (int i = 1; i <= cnt_Prime; ++i)
			if (p[i] != fir.p[i]) return 0;
		return 1;
	}
}a[MAXN];
map <Number, int> ys;
map <int, Number> sy;
map <int, int> sum;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void init()
{
	for (int i = 2; i <= 5000; ++i)
	{
		if (!vis[i]) Prime[++cnt_Prime] = i;
		for (int j = 1; j <= cnt_Prime; ++j)
		{
			if (i * Prime[j] > 5000) break ;
			vis[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break ;
		}
	}
	for (int i = 1; i <= 5000; ++i)
	{
		int tmp = i;
		for (int j = 1; j <= cnt_Prime; ++j)
			while (tmp % Prime[j] == 0) { tmp /= Prime[j]; ++a[i].p[j]; }
	}
	for (int i = 1; i <= 5000; ++i)
		for (int j = 1; j <= cnt_Prime; ++j)
			a[i].p[j] += a[i - 1].p[j];
	for (int i = 1; i <= 5000; ++i) ys[a[i]] = i, sy[i] = a[i];
}

int lca(int x, int y)
{
	Number tmp; tmp.init(); int i = cnt_Prime;
	for (; i >= 1; --i)
		if (sy[x].p[i] == sy[y].p[i]) tmp.p[i] = sy[x].p[i];
		else break ;
	if (i != 0) tmp.p[i] = Min(sy[x].p[i], sy[y].p[i]);
	if (ys[tmp] == 0)
	{
		++cnt_node; ys[tmp] = cnt_node; // Wrong.
		sy[cnt_node] = tmp;
	}
	printf("Debug2:%d\n", ys[tmp]);
	return ys[tmp];
}

int dis(int x, int y)
{
	int s = 0;
	for (int i = 1; i <= cnt_Prime; ++i)
		s += abs(sy[x].p[i] - sy[y].p[i]);
	return s;
}

bool cmp(const int &fir, const int &sec) { return sy[fir] < sy[sec]; }

void DP1(int now, int father)
{
	Size[now] = sum[now];
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		DP1(u, now); Size[now] += Size[u];
		f[now] += 1ll * Edge[i].val * Size[u];
	}
}

void DP2(int now, int father)
{
	for (int i = Head[now]; i; i = Edge[i].Next)
	{
		int u = Edge[i].To;
		if (u == father) continue ;
		f[u] = f[now] - 1ll * Edge[i].val * Size[u] + 1ll * Edge[i].val * (Size[Key[1]] - Size[u]);
		DP2(u, now);
	}
}

void Build()
{
	for (int i = 1; i <= 5000; ++i)
	{
		if (sum[i]) Key[++cnt_Key] = i;
		sy[i] = a[i];
	}
	cnt_node = 5000;
	std::sort(Key + 1, Key + cnt_Key + 1, cmp);
	for (int i = 2, Plozia = cnt_Key; i <= Plozia; ++i) // Start.
	{
		int LCA = lca(Key[i - 1], Key[i]);
		if (LCA != Key[i - 1] && LCA != Key[i]) Key[++cnt_Key] = LCA;
		if (LCA == 0) puts("Plozia");
	}
	std::sort(Key + 1, Key + cnt_Key + 1);
	cnt_Key = std::unique(Key + 1, Key + cnt_Key + 1) - (Key + 1);
	std::sort(Key + 1, Key + cnt_Key + 1, cmp); // End.
	for (int i = 2; i <= cnt_Key; ++i)
	{
		int LCA = lca(Key[i - 1], Key[i]);
		add_Edge(LCA, Key[i], dis(LCA, Key[i]));
	}
	DP1(Key[1], Key[1]); DP2(Key[1], Key[1]);
	LL ans = 0x7f7f7f7f7f7f7f7f;
	for (int i = 1; i <= cnt_Key; ++i)
		ans = Min(ans, f[Key[i]]);
	printf("%lld\n", ans);
	for (int i = 1; i <= cnt_Key; ++i)
		printf("%lld%c", Key[i], " \n"[i == cnt_Key]);
}

int main()
{
	init(); n = Read();
	for (int i = 1; i <= n; ++i)
	{
		int tmp = Max(Read(), 1);
		++sum[tmp];
	}
	Build(); return 0;
}