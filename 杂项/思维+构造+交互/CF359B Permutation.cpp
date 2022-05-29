/*
========= Plozia =========
	Author:Plozia
	Problem:CF359B Permutation
	Date:2022/5/16
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
// const int MAXN = ;
int n, k;

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
	n = Read(), k = Read(); printf("%d ", k + 1);
	for (int i = 1; i <= n * 2; ++i)
		if (i != k + 1) printf("%d ", i);
	printf("\n"); return 0;
}