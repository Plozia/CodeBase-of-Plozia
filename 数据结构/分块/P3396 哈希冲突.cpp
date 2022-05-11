/*
========= Plozia =========
	Author:Plozia
	Problem:P3396 哈希冲突
	Date:2021/4/12
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 150000 + 10, MAXBlock = 400 + 10;
int n, m, a[MAXN], Size;
LL ans[MAXBlock][MAXBlock];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	n = read(), m = read(); Size = sqrt(n);
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= Size; ++i)
		for (int j = 1; j <= n; ++j)
			ans[i][j % i] += (LL)a[j];
	for (int i = 1; i <= m; ++i)
	{
		char ch; std::cin >> ch;
		if (ch == 'A')
		{
			int x = read(), y = read();
			if (x <= Size) printf("%lld\n", ans[x][y]);
			else
			{
				LL sum = 0;
				for (int i = y; i <= n; i += x) sum += a[i];
				printf("%lld\n", sum);
			}
		}
		else
		{
			int x = read(), y = read();
			for (int i = 1; i <= Size; ++i)
				ans[i][x % i] = ans[i][x % i] - (LL)a[x] + y;
			a[x] = y;
		}
	}
	return 0;
}