/*
========= Plozia =========
	Author:Plozia
	Problem:CF1483B Playlist
	Date:2022/5/18
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;
using std::pair;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, a[MAXN], ans[MAXN], cnt;
bool book[MAXN];
struct List { int Right; } l[MAXN];
queue < pair <int, int> > q;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }

void Solve()
{
	cnt = 0; n = Read(); for (int i = 1; i <= n; ++i) a[i] = Read(), book[i] = 0;
	while (!q.empty()) q.pop();
	for (int i = 1; i < n; ++i) q.push(std::make_pair(i, i + 1)), l[i].Right = i + 1;
	q.push(std::make_pair(n, 1)), l[n].Right = 1;
	while (!q.empty())
	{
		pair <int, int> tmp(q.front()); q.pop();
		if (book[tmp.first] || book[tmp.second]) continue ;
		if (gcd(a[tmp.first], a[tmp.second]) != 1) continue ;
		l[tmp.first].Right = l[l[tmp.first].Right].Right; book[tmp.second] = 1;
		++cnt; ans[cnt] = tmp.second; q.push(std::make_pair(tmp.first, l[tmp.first].Right));
	}
	printf("%d ", cnt);
	for (int i = 1; i <= cnt; ++i) printf("%d%c", ans[i], " \n"[i == cnt]);
}

int main()
{
	int t = Read();
	while (t--) Solve();
	return 0;
}