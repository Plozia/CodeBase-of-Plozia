/*
========= Plozia =========
	Author:Plozia
	Problem:P3805 【模板】manacher算法
	Date:2021/5/12
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Max(a, b) (((a) > (b)) ? (a) : (b))

typedef long long LL;
const int MAXN = 2.3e7 + 10;
int len1, len2, f[MAXN];
char str1[MAXN], str2[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
// int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	len1 = strlen(str1);
	str2[0] = '^'; str2[1] = '$';
	for (int i = 0; i < len1; ++i)
	{
		str2[(i << 1) + 2] = str1[i];
		str2[(i << 1) + 3] = '$';
	}
	str2[(len1 << 1) + 2] = '@';
	len2 = (len1 << 1) + 2;
}

void Manacher()
{
	int id = 0, Maxn = 0;
	for (int i = 1; i < len2; ++i)
	{
		if (Maxn > i) f[i] = Min(f[(id << 1) - i], Maxn - i);
		else f[i] = 1;
		for (; str2[i + f[i]] == str2[i - f[i]]; ++f[i]) ;
		if (f[i] + i > Maxn) { Maxn = f[i] + i; id = i; }
	}
}

int main()
{
	scanf("%s", str1);
	init(); Manacher(); int ans = 0;
	for (int i = 0; i <= len2; ++i) ans = Max(ans, f[i]);
	printf("%d\n", ans - 1);
}