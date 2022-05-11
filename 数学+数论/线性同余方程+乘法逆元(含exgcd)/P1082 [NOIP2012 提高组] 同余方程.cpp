/*
========= Plozia =========
	Author:Plozia
	Problem:P1082 [NOIP2012 提高组] 同余方程
	Date:2021/4/7
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
// const int MAXN = ;
int a, b;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int gcd(int fir, int sec) {return (sec == 0) ? fir : gcd(sec, fir % sec);}

void exgcd(int a, int b, LL &x, LL &y)
{
	if (b == 0) {x = 1; y = 0; return ;}
	exgcd(b, a % b, x, y);
	LL p = x; x = y; y = p - ((LL)a / b) * y;
}

int main()
{
	a = read(), b = read();
	LL x, y;  exgcd(a, b, x, y); x = (x % b + b) % b;
	printf ("%lld\n", x); return 0;
}