#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 6e3 + 10;
int n, r[MAXN], f[MAXN][2], root;
vector <int> Next[MAXN];
bool book[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

void dfs(int now, int fa)
{
	f[now][0] = 0, f[now][1] = r[now];
	for (int i = 0; i < Next[now].size(); ++i)
	{
		int u = Next[now][i];
		if (u == fa) continue;
		dfs(u, now);
		f[now][0] = Max(f[now][0], Max(f[now][0] + f[u][0], f[now][0] + f[u][1]));
		f[now][1] = Max(f[now][1], f[now][1] + f[u][0]);
	}
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) r[i] = read();
	for (int i = 1; i < n; ++i)
	{
		int x = read(), y = read(); book[x] = 1;
		Next[y].push_back(x); Next[x].push_back(y);
	}
	for (int i = 1; i <= n; ++i)
		if (!book[i]) {root = i; break;}
	dfs(root, root);
	printf("%d\n", Max(f[root][0], f[root][1]));
	return 0;
}
