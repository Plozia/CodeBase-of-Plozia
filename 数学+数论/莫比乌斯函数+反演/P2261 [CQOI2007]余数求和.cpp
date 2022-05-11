/*
========= Plozia =========
	Author:Plozia
	Problem:P2261 [CQOI2007]余数求和
	Date:2022/2/18
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, k, Left[MAXN], Right[MAXN], cnt;
LL ans = 0;

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
	n = Read(), k = Read(); ans = 1ll * n  * k;
	for (int l = 1, r; l <= n; l = r + 1)
	{
		if (k / l == 0) r = n;
		else r = Min(k / (k / l), n);
		++cnt; Left[cnt] = l, Right[cnt] = r;
	}
	for (int i = 1; i <= cnt; ++i)
		ans = ans - 1ll * (k / Left[i]) * 1ll * (Left[i] + Right[i]) * (Right[i] - Left[i] + 1) / 2;
	printf("%lld\n", ans); return 0;
}