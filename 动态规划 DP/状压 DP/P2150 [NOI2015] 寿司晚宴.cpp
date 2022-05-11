/*
========= Plozia =========
	Author:Plozia
	Problem:P2150 [NOI2015] 寿司晚宴
	Date:2021/6/4
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 500 + 10;
int n, P, f[MAXN][MAXN], f1[MAXN][MAXN], f2[MAXN][MAXN], ans;
int Prime_Num[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19};
struct node { int val, Prime, State; } a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp(const node &fir, const node &sec) { return fir.Prime > sec.Prime; }

int main()
{
	n = Read(), P = Read();
	for (int i = 2; i <= n; ++i)
	{
		a[i].val = i;
		for (int j = 1; j <= 8; ++j)
		{
			if (a[i].val % Prime_Num[j] == 0)
			{
				while (a[i].val % Prime_Num[j] == 0) a[i].val /= Prime_Num[j];
				a[i].State |= 1 << (j - 1);
			}
		}
		if (a[i].val != 1) a[i].Prime = a[i].val;
		else a[i].Prime = -1;
		a[i].val = i;
	}
	std::sort(a + 2, a + n + 1, cmp);
	f[0][0] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (i == 1 || a[i].Prime != a[i - 1].Prime || a[i].Prime == -1)
		{
			memcpy(f1, f, sizeof(f1)); memcpy(f2, f, sizeof(f2));
		}
		for (int j = 255; j >= 0; --j)
			for (int k = 255; k >= 0; --k)
			{
				if ((j & k) != 0) continue ;
				if ((a[i].State & j) == 0)
				{
					f1[j][a[i].State | k] += f1[j][k];
					if (f1[j][a[i].State | k] > P) f1[j][a[i].State | k] -= P;
				}
				if ((a[i].State & k) == 0)
				{
					f2[j | a[i].State][k] += f2[j][k];
					if (f2[j | a[i].State][k] > P) f2[j | a[i].State][k] -= P;
				}
			}
		if (i == n || a[i].Prime != a[i + 1].Prime || a[i].Prime == -1)
		{
			for (int j = 255; j >= 0; --j)
				for (int k = 255; k >= 0; --k)
				{
					if ((j & k) != 0) continue ;
					f[j][k] = ((f1[j][k] + f2[j][k]) % P + P - f[j][k]) % P;
				}
		}
	}
	for (int j = 255; j >= 0; --j)
		for (int k = 255; k >= 0; --k)
		{
			if ((j & k) != 0) continue ;
			ans += f[j][k]; if (ans > P) ans -= P;
		}
	printf("%d\n", ans); return 0;
}