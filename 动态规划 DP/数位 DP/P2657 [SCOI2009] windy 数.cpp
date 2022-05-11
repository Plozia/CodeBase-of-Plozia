#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
//const int MAXN = ;
int l, r, f[20][10], a[20], cnt;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}
int Abs(int x) {return (x < 0) ? -x : x;}

int dfs(int pos, int las, int zero, int limit)
{
	if (pos == 0) return 1;
	if (!zero && !limit && f[pos][las] != -1) return f[pos][las];
	int t = limit ? a[pos] : 9, ans = 0;
	for (int i = 0; i <= t; ++i)
	{
		if (zero && i == 0) ans += dfs(pos - 1, -2, zero, i == a[pos] && limit);
		else if (Abs(i - las) >= 2) ans += dfs(pos - 1, i, 0, i == a[pos] && limit);
	}
	if (!zero && !limit) f[pos][las] = ans;
	return ans;
}

int Get(int k)
{
	cnt = 0; memset(a, 0, sizeof(a));
	while (k) {a[++cnt] = k % 10; k /= 10;}
	return dfs(cnt, -2, 1, 1);
}

int main()
{
	l = read(), r = read();
	memset(f, -1, sizeof(f));
	printf("%d\n", Get(r) - Get(l - 1));
	return 0;
}
/*
25 26 27 28 29
30 31 35 36 37
38 39 40 41 42
46 47 48 49 50
*/
