#include <bits/stdc++.h>
using namespace std;

typedef double db;
typedef long long LL;
const int MAXN = 1e5 + 10;
int n;
db p[MAXN], x1[MAXN], x2[MAXN], ans[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == -1) ? -sum : sum;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) scanf("%lf", &p[i]);
	for (int i = 1; i <= n; ++i)
	{
		x1[i] = (x1[i - 1] + 1) * p[i];
		x2[i] = (x2[i - 1] + 2 * x1[i - 1] + 1) * p[i];
		ans[i] = ans[i - 1] + (3 * x2[i - 1] + 3 * x1[i - 1] + 1) * p[i];
	}
	printf("%.1lf", ans[n]);
	return 0;
}
