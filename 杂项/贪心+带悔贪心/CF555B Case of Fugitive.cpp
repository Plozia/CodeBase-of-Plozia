/*
========= Plozia =========
	Author:Plozia
	Problem:CF555B Case of Fugitive
	Date:2021/8/14
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 2e5 + 5;
int n, m;
LL l[MAXN], r[MAXN], ans[MAXN];
struct node1
{
	LL l, r, id;
	bool operator <(const node1 &fir)const { return r > fir.r; }
} a[MAXN];
struct node2 { LL d, id; } q[MAXN];
priority_queue <node1> pq;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp1(const node1 &fir, const node1 &sec) { return (fir.l < sec.l); }
bool cmp2(const node2 &fir, const node2 &sec) { return fir.d < sec.d; }

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) l[i] = Read(), r[i] = Read();
	for (int i = 1; i <= m; ++i) q[i].d = Read(), q[i].id = i;
	for (int i = 1; i < n; ++i) a[i].l = l[i + 1] - r[i], a[i].r = r[i + 1] - l[i], a[i].id = i;
	std::sort(a + 1, a + n, cmp1); std::sort(q + 1, q + m + 1, cmp2);
	int j = 1;
	for (int i = 1; i <= m; ++i)
	{
		while (j < n && a[j].l <= q[i].d) pq.push(a[j++]);
		if (pq.empty()) continue ;
		if (pq.top().r < q[i].d) { printf("No\n"); return 0; }
		node1 x = pq.top(); pq.pop(); ans[x.id] = q[i].id;
	}
	if (!pq.empty() || j != n) { printf("No\n"); return 0; }
	printf("Yes\n");
	for (int i = 1; i < n; ++i) printf("%lld ", ans[i]); printf("\n"); return 0;
}