/*
========= Plozia =========
	Author:Plozia
	Problem:P5005 �й����� - ������
	Date:2021/3/5
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int P = 1e9 + 7;
int n, m;
LL f[3][64][64], ans;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

int Getbit(int x, int a)
{
	if (a < 1) return 0;
	return x & (1 << (a - 1));
}

int check(int x, int a)
{
	if (a < 1) return 0;
	if (x & (1 << (a - 1))) return 1;
	return 0;
}

int Two_attack(int k)
{
	int State = 0;
	for (int i = 1; Getbit(-1, i) <= k; ++i)
	{
		if (!check(k, i)) continue;
		if (!check(k, i - 1)) State |= Getbit(-1, i - 2);
		if (!check(k, i + 1)) State |= Getbit(-1, i + 2);
	}
	return State;
}

int Three_attack(int k, int l)
{
	int State = 0;
	for (int i = 1; Getbit(-1, i) <= k; ++i)
	{
		if (!check(k, i)) continue;
		if (!check(l, i)) State |= Getbit(-1, i - 1), State |= Getbit(-1, i + 1);
	}
	return State;
}

int main()
{
	n = read(), m = read();
	for (int i = 0; i < (1 << m); ++i) f[1][i][0] = 1;
	for (int i = 0; i < (1 << m); ++i)
		for (int j = 0; j < (1 << m); ++j)
			if ((!(Two_attack(i) & j)) & (!(Two_attack(j) & i))) f[2][j][i] = (f[2][j][i] + f[1][i][0]) % P;
	for (int i = 3; i <= n; ++i)
		for (int j = 0; j < (1 << m); ++j)
			for (int k = 0; k < (1 << m); ++k)
			{
				f[i % 3][j][k] = 0;
				if (Two_attack(j) & k) continue;
				if (Two_attack(k) & j) continue;
				for (int l = 0; l < (1 << m); ++l)
				{
					if (Two_attack(l) & k) continue;
					if (Two_attack(k) & l) continue;
					if (Three_attack(l, k) & j) continue;
					if (Three_attack(j, k) & l) continue;
					f[i % 3][j][k] = (f[i % 3][j][k] + f[(i - 1) % 3][k][l]) % P;
				}
			}
	ans = 0;
	for (int i = 0; i < (1 << m); ++i)
		for (int j = 0; j < (1 << m); ++j)
			if ((!(Two_attack(i) & j)) & (!(Two_attack(j) & i))) ans = (ans + f[n % 3][i][j]) % P;
	printf("%lld\n", ans);
	return 0;
}
