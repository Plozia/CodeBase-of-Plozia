#include <bits/stdc++.h>
using namespace std;

typedef double db;
typedef long long LL;
const int MAXN = 2000 + 10;
int n, t;
double p, f[MAXN][MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == -1) ? -sum : sum;
}

int main()
{
	n = read(); scanf("%lf", &p); t = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= t; ++j)
			f[i][j] = f[i][j - 1] * (1 - p) + (f[i - 1][j - 1] + 1) * p;
	printf("%.10lf\n", f[n][t]);
	return 0;
}
