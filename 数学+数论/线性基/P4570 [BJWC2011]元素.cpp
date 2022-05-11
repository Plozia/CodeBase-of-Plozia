/*
========= Plozia =========
	Author:Plozia
	Problem:P4570 [BJWC2011]元素
	Date:2021/7/1
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1000 + 5;
int n;
struct node
{
	LL Number;
	int Magic;
}a[MAXN];
LL d[70], ans;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp(const node &fir, const node &sec) { return fir.Magic > sec.Magic; }

int Add(LL x)
{
	for (int i = 63; i >= 0; --i)
	{
		if (x & (1ll << i))
		{
			if (d[i] & x) x ^= d[i];
			else { d[i] = x; return 1; }
		}
	}
	return 0;
}

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) { a[i].Number = Read(); a[i].Magic = Read(); }
	std::sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; ++i)
		if (Add(a[i].Number)) ans += (LL)a[i].Magic;
	printf("%lld\n", ans); return 0;
}