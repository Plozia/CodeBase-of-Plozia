/*
========= Plozia =========
	Author:Plozia
	Problem:P2473 [SCOI2008] ������
	Date:2021/11/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
typedef double db;
const int MAXK = 100 + 5, MAXN = 15 + 5, MAXState = (1 << 15) + 1;
int k, n, p[MAXN], Pre[MAXN];
db f[MAXK][MAXState];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
db Min(db fir, db sec) { return (fir < sec) ? fir : sec; }
db Max(db fir, db sec) { return (fir > sec) ? fir : sec; }

int main()
{
	k = Read(), n = Read();
	for (int i = 1; i <= n; ++i)
	{
		p[i] = Read(); int tmp;
		while (tmp = Read()) Pre[i] |= (1 << (tmp - 1));
	}
	for (int i = k; i >= 1; --i)
	{
		for (int State = 0; State < (1 << n); ++State)
		{
			for (int j = 1; j <= n; ++j)
			{
				if ((State & Pre[j]) == Pre[j]) f[i][State] += Max(f[i + 1][State], f[i + 1][State | (1 << (j - 1))] + p[j]);
				else f[i][State] += f[i + 1][State];
			}
			f[i][State] /= n;
		}
	}
	printf("%.6lf\n", f[1][0]); return 0;
}
