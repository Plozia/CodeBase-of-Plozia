#include <bits/stdc++.h>
#define Min(a, b) ((a < b) ? a : b)
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 5e5 + 10;
int f[MAXN][3][2], cnt;
//1 = red, 2 = green(goal), 3 = blue
//0 = min, 1 = max
struct node
{
	int l, r;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

int build()
{
	int now = ++cnt; int t;
	scanf("%1d", &t);
	if (t == 1) l(now) = build();
	if (t == 2) {l(now) = build(); r(now) = build();}
	return now;
}
//0 = min, 1 = max
void dfs(int now)
{
	f[now][2][0] = f[now][2][1] = 1;
	if (l(now)) dfs(l(now));
	if (r(now)) dfs(r(now));
	if (l(now) && !r(now))
	{
		f[now][1][0] += Min(f[l(now)][2][0], f[l(now)][3][0]);
		f[now][2][0] += Min(f[l(now)][1][0], f[l(now)][3][0]);
		f[now][3][0] += Min(f[l(now)][1][0], f[l(now)][2][0]);
		f[now][1][1] += Max(f[l(now)][2][1], f[l(now)][3][1]);
		f[now][2][1] += Max(f[l(now)][1][1], f[l(now)][3][1]);
		f[now][3][1] += Max(f[l(now)][1][1], f[l(now)][2][1]);
	}
	else if (r(now) && !l(now))
	{
		f[now][1][0] += Min(f[r(now)][2][0], f[r(now)][3][0]);
		f[now][2][0] += Min(f[r(now)][1][0], f[r(now)][3][0]);
		f[now][3][0] += Min(f[r(now)][1][0], f[r(now)][2][0]);
		f[now][1][1] += Max(f[r(now)][2][1], f[r(now)][3][1]);
		f[now][2][1] += Max(f[r(now)][1][1], f[r(now)][3][1]);
		f[now][3][1] += Max(f[r(now)][1][1], f[r(now)][2][1]);
	}
	else if (l(now) && r(now))
	{
		f[now][1][0] += Min(f[l(now)][2][0] + f[r(now)][3][0], f[l(now)][3][0] + f[r(now)][2][0]);
		f[now][2][0] += Min(f[l(now)][1][0] + f[r(now)][3][0], f[l(now)][3][0] + f[r(now)][1][0]);
		f[now][3][0] += Min(f[l(now)][1][0] + f[r(now)][2][0], f[l(now)][2][0] + f[r(now)][1][0]);
		f[now][1][1] += Max(f[l(now)][2][1] + f[r(now)][3][1], f[l(now)][3][1] + f[r(now)][2][1]);
		f[now][2][1] += Max(f[l(now)][1][1] + f[r(now)][3][1], f[l(now)][3][1] + f[r(now)][1][1]);
		f[now][3][1] += Max(f[l(now)][1][1] + f[r(now)][2][1], f[l(now)][2][1] + f[r(now)][1][1]);
	}
}

int main()
{
	build();
	dfs(1);
	printf("%d %d\n", Max(f[1][1][1], Max(f[1][2][1], f[1][3][1])), Min(f[1][1][0], Min(f[1][2][0], f[1][3][0])));
	return 0;
}
