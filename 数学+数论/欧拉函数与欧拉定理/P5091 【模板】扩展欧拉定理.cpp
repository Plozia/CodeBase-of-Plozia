/*
========= Plozia =========
	Author:Plozia
	Problem:P5091 【模板】扩展欧拉定理
	Date:2021/5/19
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
// const int MAXN = ;
LL a, b, m, phi = 1;
bool flag = 0;

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

LL Specail_read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar())
	{
		sum = sum * 10ll + ch - '0';
		if (sum > phi) { sum %= phi; flag = 1; }
	}
	return sum * fh;
}

LL ksm(LL fir, LL sec, LL p)
{
	LL ans = 1 % p;
	for (; sec; sec >>= 1, fir = fir * fir % p)
		if (sec & 1) ans = ans * fir % p;
	return ans;
}

void Get_phi()
{
	int i, c = m;
	for (i = 2; i * i <= c; ++i)
	{
		int sum = 0;
		while (c % i == 0) { ++sum; c /= i; }
		if (sum != 0) phi *= (LL)(i - 1) * ksm(i, sum - 1, m);
	}
	if (c != 1) phi *= (c - 1);
}

int main()
{
	a = read(), m = read(); Get_phi();
	b = Specail_read();
	if (flag) b += phi;
	printf("%lld\n", ksm(a, b, m));
	return 0;
}