/*
========= Plozia =========
	Author:Plozia
	Problem:整除分块板子 - ABC230E
	Date:2022/2/18
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e6 + 5;
LL n, Left[MAXN], Right[MAXN], cnt;

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
	std::cin >> n;
	LL ans = 0, k = n;
	for (LL l = 1, r = 0; l <= n; l = r + 1)
	{
		if (k / l == 0) r = n;
		else r = Min(k / (k / l), n);
		Left[++cnt] = l; Right[cnt] = r;
	}
	for (int i = 1; i <= cnt; ++i)
		ans += 1ll * (Right[i] - Left[i] + 1) * (n / Left[i]);
	printf("%lld\n", ans); return 0;
}