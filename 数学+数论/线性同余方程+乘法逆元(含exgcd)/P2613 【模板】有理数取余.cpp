/*
========= Plozia =========
	Author:Plozia
	Problem:P2613 【模板】有理数取余
	Date:2021/6/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
// const int MAXN = ;
const LL P = 19260817;
LL a, b;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) { sum = (sum << 3) + (sum << 1) + (ch ^ 48); sum %= P; }
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
LL ksm(LL fir, LL sec, LL p)
{
	LL ans = 1 % p;
	for (; sec; sec >>= 1, fir = fir * fir % p)
		if (sec & 1) ans = ans * fir % p;
	return ans;
}

int main()
{
	a = Read(); b = Read();
	if (b == 0) printf("Angry!\n");
	else printf("%lld\n", a * ksm(b, P - 2, P) % P);
	return 0;
}