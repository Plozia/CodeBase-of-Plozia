/*
========= Plozia =========
	Author:Plozia
	Problem:CF134C Swaps
	Date:2021/8/15
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 2e5 + 5;
int n, s, a[MAXN], x[MAXN], y[MAXN], cnt, cntd;
struct node
{
	int Num, id;
	bool operator <(const node &fir)const
	{
		return Num < fir.Num;
	}
}d[MAXN];
priority_queue <node> q;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	n = Read(), s = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	if (s & 1) { printf("No\n"); return 0; }
	for (int i = 1; i <= n; ++i)
		if (a[i] >= n) { printf("No\n"); return 0; }
	for (int i = 1; i <= n; ++i) if (a[i]) q.push((node){a[i], i});
	while (!q.empty())
	{
		node p = q.top(); q.pop(); if (p.Num > q.size()) { printf("No\n"); return 0; }
		for (int i = 1; i <= p.Num; ++i)
		{
			node p2 = q.top(); q.pop();
			--p2.Num; x[++cnt] = p.id; y[cnt] = p2.id; d[++cntd] = p2;
		}
		for (int i = 1; i <= cntd; ++i)
			if (d[i].Num) q.push(d[i]);
		cntd = 0;
	}
	printf("Yes\n%d\n", cnt);
	for (int i = 1; i <= cnt; ++i) printf("%d %d\n", x[i], y[i]); return 0;
}