/*
========= Plozia =========
	Author:Plozia
	Problem:P6196 [EER1]代价
	Date:2022/5/29
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e6 + 5;
int n, a[MAXN];
LL ans;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read(); for (int i = 1; i <= n; ++i) a[i] = Read();
	int Last = 1, Minn = 0x7f7f7f7f; a[n + 1] = 1;
	for (int i = 1; i <= n + 1; ++i)
	{
		if (a[i] != 1) continue ;
		ans += 1; Minn = 0x7f7f7f7f;
		for (int j = Last; j < i - 1; ++j) ans += 1ll * a[j] * a[j + 1], Minn = Min(Minn, a[j]);
		if (i > Last) ans += Min(Minn, a[i - 1]);
		Last = i + 1;
	}
	printf("%lld\n", ans - 1); return 0;
}