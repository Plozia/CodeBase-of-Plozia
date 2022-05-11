/*
========= Plozia =========
	Author:Plozia
	Problem:P2157 [SDOI2009]ѧУʳ��
	Date:2021/3/2
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Min(a, b) ((a < b) ? a : b)

typedef long long LL;
const int MAXN = 1000 + 10, MAXP = (1 << 8) - 1;
int n, t[MAXN], b[MAXN], f[MAXN][MAXP][20];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

namespace Plozia
{
	void main()
	{
		n = read();
		memset(t, 0, sizeof(t)); memset(b, 0, sizeof(b));
		for (int i = 1; i <= n; ++i) t[i] = read(), b[i] = read();
		memset(f, 0x3f, sizeof(f));
		f[1][0][7] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j <= MAXP; ++j)
				for (int k = -8; k <= 7; ++k)
				{
					if (f[i][j][k + 8] != 0x3f3f3f3f)
					{
						if (j & 1) f[i + 1][j >> 1][k - 1 + 8] = Min(f[i + 1][j >> 1][k - 1 + 8], f[i][j][k + 8]);
						else
						{
							int r = 0x3f3f3f3f;
							for (int l = 0; l <= 7; ++l)
							{
								if ((j >> l) & 1) continue;
								if (i + l > r) break;
								r = Min(r, i + l + b[i + l]);
								f[i][j | (1 << l)][l + 8] = Min(f[i][j | (1 << l)][l + 8], f[i][j][k + 8] + ((i + k) ? (t[i + k] ^ t[i + l]) : 0));
							}
						}
					}
				}
		int ans = 0x3f3f3f3f;
		for (int i = 0; i <= 8; ++i)
			ans = Min(ans, f[n + 1][0][i]);
		printf("%d\n", ans);
		return ;
	}
}

int main()
{
	int t = read();
	while (t--) Plozia::main();
	return 0;
}
