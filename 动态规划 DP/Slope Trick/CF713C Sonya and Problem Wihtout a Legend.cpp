/*
========= Plozia =========
	Author:Plozia
	Problem:CF713C Sonya and Problem Wihtout a Legend
	Date:2021/9/22
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 3000 + 5;
int n, a[MAXN];
LL ans = 0;
priority_queue <LL> q;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read() - i;
	for (int i = 1; i <= n; ++i)
	{
		q.push(a[i]);
		if (q.top() > a[i])
		{
			ans += q.top() - a[i];
			q.pop(); q.push(a[i]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}