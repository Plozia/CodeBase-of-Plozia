/*
========= Plozia =========
	Author:Plozia
	Problem:P8273 [USACO22OPEN] Pair Programming G.cpp
	Date:2022/6/7
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 2e3 + 5;
const int P = 1e9 + 7;
int t, n, f[MAXN][MAXN][2], len1, len2;
char str1[MAXN], str2[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

void Solve()
{
	n = Read(); len1 = len2 = 0;
	char ch = getchar();
	while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
	while (ch != ' ' && ch != '\r' && ch != '\n')
	{
		if (ch == '0') len1 = 0;
		if (ch == '+') str1[++len1] = '+';
		else if (ch != '1') str1[++len1] = '*';
		ch = getchar();
	}
	while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
	while (ch != ' ' && ch != '\r' && ch != '\n')
	{
		if (ch == '0') len2 = 0;
		if (ch == '+') str2[++len2] = '+';
		else if (ch != '1') str2[++len2] = '*';
		ch = getchar();
	}
	memset(f, 0, sizeof(f)); f[0][0][1] = 1;
	for (int i = 0; i <= len1; ++i)
		for (int j = 0; j <= len2; ++j)
		{
			if (i > 0) f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % P;
			if (j > 0) f[i][j][1] = f[i][j - 1][1];
			if (i > 0 && j > 0 && str1[i] != str2[j]) f[i][j][1] = (f[i][j][1] + f[i][j - 1][0]) % P;
		}
	printf("%d\n", (f[len1][len2][0] + f[len1][len2][1]) % P);
}

int main()
{
	t = Read();
	while (t--) Solve();
	return 0;
}