/*
========= Plozia =========
	Author:Plozia
	Problem:CF1406E Deleting Numbers
	Date:2022/5/8
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, Prime[MAXN], cntPrime, p, ans = 1;
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	for (int i = 2; i <= n; ++i)
	{
		if (!book[i]) Prime[++cntPrime] = i;
		for (int j = 1; j <= cntPrime; ++j)
		{
			if (i * Prime[j] > n) break ;
			book[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break ;
		}
	}
}

int optA(int x) { printf("A %d\n", x); fflush(stdout); return Read(); }
int optB(int x) { printf("B %d\n", x); fflush(stdout); return Read(); }

int main()
{
	n = Read(); init(); for (p = 1; p * p <= n; ++p) ; --p; int i = 1;
	for (i = 1; Prime[i] <= p && i <= cntPrime; ++i)
	{
		optB(Prime[i]);
		int tmp = Prime[i];
		if (optA(Prime[i]) == 0) continue ;
		while (tmp * Prime[i] <= n) { if (optA(tmp * Prime[i]) == 0) break ; tmp *= Prime[i]; }
		ans = ans * tmp;
	}
	if (ans != 1)
	{
		for (; i <= cntPrime; ++i) 
			if (optA(Prime[i]) == 2) { ans *= Prime[i]; break ; }
	}
	else
	{
		int Last = i, Remain = optA(1);
		for(; i <= cntPrime; ++i)
		{
			optB(Prime[i]);
			if (i - Last + 1 == 100 || i == cntPrime)
			{
				int tmp = optA(1);
				if (Remain - tmp == i - Last + 1) { Last = i + 1; Remain = tmp; continue ; }
				for (int j = Last; j <= i; ++j)
				{
					if (optA(Prime[j]) == 1) { ans = Prime[j]; break ; }
				}
				break ;
			}
		}
	}
	printf("C %d\n", ans); fflush(stdout); return 0;
}