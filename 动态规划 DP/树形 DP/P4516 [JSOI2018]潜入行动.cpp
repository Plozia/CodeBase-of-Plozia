#include <bits/stdc++.h>
#define Min(a, b) ((a < b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10, P = 1e9 + 7, MAXK = 100 + 10;
int n, k, f[MAXN][MAXK][2][2], tmp[MAXK][2][2], size[MAXN];
vector <int> Next[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

void dfs(int now, int fa)
{
	size[now] = f[now][0][0][0] = f[now][1][1][0] = 1;
	for (int v = 0; v < Next[now].size(); ++v)
	{
		int u = Next[now][v];
		if (u == fa) continue;
		dfs(u, now);
		for (int i = 0; i <= k; ++i)
		{
			tmp[i][0][0] = f[now][i][0][0]; f[now][i][0][0] = 0;
			tmp[i][0][1] = f[now][i][0][1]; f[now][i][0][1] = 0;
			tmp[i][1][0] = f[now][i][1][0]; f[now][i][1][0] = 0;
			tmp[i][1][1] = f[now][i][1][1]; f[now][i][1][1] = 0;
		}
		for (int i = 0; i <= Min(size[now], k); ++i)
			for (int j = 0; j <= Min(size[u], k - i); ++j)
			{
				f[now][i + j][0][0] = ((LL)f[now][i + j][0][0] + (LL)tmp[i][0][0] * f[u][j][0][1]) % P;
				f[now][i + j][0][1] = ((LL)f[now][i + j][0][1] + (LL)tmp[i][0][0] * f[u][j][1][1] % P + (LL)tmp[i][0][1] * ((LL)f[u][j][0][1] + f[u][j][1][1]) % P) % P;
				f[now][i + j][1][0] = ((LL)f[now][i + j][1][0] + (LL)tmp[i][1][0] * ((LL)f[u][j][0][1] + f[u][j][0][0]) % P) % P;
				f[now][i + j][1][1] = ((LL)f[now][i + j][1][1] + (LL)tmp[i][1][0] * ((LL)f[u][j][1][0] + f[u][j][1][1]) % P + (LL)tmp[i][1][1] * ((LL)f[u][j][0][0] + f[u][j][0][1] + f[u][j][1][0] + f[u][j][1][1]) % P) % P;
			}
		size[now] += size[u];
	}
}

int main()
{
	n = read(), k = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		Next[x].push_back(y); Next[y].push_back(x);
	}
	dfs(1, 1);
	printf("%d\n", ((LL)f[1][k][0][1] + f[1][k][1][1]) % P);
	return 0;
}
