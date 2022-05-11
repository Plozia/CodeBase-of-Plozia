/*
========= Plozia =========
	Author:Plozia
	Problem:P3522 [POI2011]TEM-Temperature
	Date:2021/6/17
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::deque;

typedef long long LL;
const int MAXN = 1e6 + 5;
int n, l[MAXN], r[MAXN], ans = 1;
struct node { int l, r, Day; } ;
deque <node> q;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) l[i] = Read(), r[i] = Read();
	for (int i = 1; i <= n; ++i)
	{
		while (!q.empty() && q.front().l > r[i]) q.pop_front();
		if (!q.empty()) ans = Max(ans, i - q.front().Day + 1);
		int sum = i;
		while (!q.empty() && q.back().l < l[i]) { sum = q.back().Day; q.pop_back(); }
		q.push_back((node){l[i], r[i], sum});
	}
	printf("%d\n", ans); return 0;
}