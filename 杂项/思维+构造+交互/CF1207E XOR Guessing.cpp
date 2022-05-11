/*
========= Plozia =========
	Author:Plozia
	Problem:CF1207E XOR Guessing
	Date:2022/5/5
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5;
int a[MAXN], b[MAXN], ans1, ans2, ans;

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
	for (int i = 1; i <= 100; ++i) a[i] = i, b[i] = i * (1 << 7);
	printf("? "); for (int i = 1; i <= 100; ++i) printf("%d%c", a[i], " \n"[i == 100]);
	fflush(stdout); ans1 = Read();
	printf("? "); for (int i = 1; i <= 100; ++i) printf("%d%c", b[i], " \n"[i == 100]);
	fflush(stdout); ans2 = Read();
	printf("! %d\n", (ans1 >> 7 << 7) ^ (ans2 - (ans2 >> 7 << 7))); fflush(stdout); return 0;
}