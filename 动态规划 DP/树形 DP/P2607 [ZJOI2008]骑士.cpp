#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 1e6 + 10;
int n, a[MAXN], fa[MAXN];
LL f[MAXN][2];
bool vis[MAXN];
vector <int> Next[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

void dfs(int now, int fa, int root)
{
	vis[now] = 1;
	f[now][0] = 0, f[now][1] = a[now];
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == fa) continue;
		if (u == root) {f[now][1] = -0x3f3f3f3f3f3f3f3f; continue;}
		dfs(u, now, root);
		f[now][0] += Max(f[u][0], f[u][1]);
		f[now][1] += f[u][0];
	}
}

LL DP(int k)
{
	vis[k] = 1;
	int root = k;
	while (!vis[fa[root]]) {root = fa[root]; vis[root] = 1;}
	dfs(root, root, root);
	LL ans = 0;
	ans = Max(ans, Max(f[root][0], f[root][1]));
	root = fa[root]; vis[root] = 1;
	dfs(root, root, root);
	ans = Max(ans, Max(f[root][0], f[root][1]));
	return ans;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		a[i] = read(); fa[i] = read();
		Next[fa[i]].push_back(i);
	}
	LL sum = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) sum += DP(i);
	printf("%lld\n", sum);
	return 0;
}
