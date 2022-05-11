/*
========= Plozia =========
	Author:Plozia
	Problem:CF1516D Cut
	Date:2021/9/8
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q, a[MAXN], f[MAXN][21], book[MAXN];
vector <int> v[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	int l = 0, r = 0, sum = 0;
	while (l <= n)
	{
		++l; ++r;
		for (int i = 0; i < v[l - 1].size(); ++i)
		{
			--book[v[l - 1][i]];
			if (book[v[l - 1][i]] == 1) --sum;
		}
		while (r <= n)
		{
			for (int i = 0; i < v[r].size(); ++i)
			{
				++book[v[r][i]];
				if (book[v[r][i]] > 1) ++sum;
			}
			if (sum != 0)
			{
				for (int i = 0; i < v[r].size(); ++i)
				{
					--book[v[r][i]];
					if (book[v[r][i]] == 1) --sum;
				}
				--r; break ;
			}
			++r;
		}
		if (r > n) f[l][0] = n;
		else f[l][0] = r;
	}
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			f[i][j] = f[Min(f[i][j - 1] + 1, n)][j - 1];
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i <= n; ++i)
	{
		int tmp = a[i];
		for (int j = 2; j * j <= tmp; ++j)
		{
			if (tmp % j == 0)
			{
				v[i].push_back(j);
				while (tmp % j == 0) tmp /= j;
			}
		}
		if (tmp != 1) v[i].push_back(tmp);
	}
	init();
	for (int i = 1; i <= q; ++i)
	{
		int l = Read(), r = Read(), sum = 0;
		for (int j = 20; j >= 0; --j)
			if (f[l][j] < r) l = f[l][j] + 1, sum += (1 << j);
		printf("%d\n", sum + 1);
	}
	return 0;
}