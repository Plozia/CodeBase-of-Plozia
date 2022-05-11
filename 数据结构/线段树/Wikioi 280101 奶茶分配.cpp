#include <bits/stdc++.h>

using std::queue;

typedef long long LL;
const int MAXM = 1e5 + 10, P = 993244853;
int n, m, cnt, inv[10];
queue<int>q[10];
struct node
{
	int d[10][10];
	int x, y;
	node()
	{
		memset(d, 0, sizeof(d));
		x = y = 0;
	}
	void init(int xx, int yy)
	{
		memset(d, 0, sizeof(d));
		x = xx, y = yy;
		for (int i = 1; i <= x; ++i) d[i][i] = 1;
		return ;
	}
	node operator*(const node &b)
	{
		node c;
		c.x = x; c.y = b.y;
		for (int i = 1; i <= x; ++i)
			for (int k = 1; k <= y; ++k)
				for (int j = 1; j <= b.y; ++j)
					c.d[i][j] = (1ll * c.d[i][j] + 1ll * d[i][k] * b.d[k][j] % P) % P;
		return c;
	}
	void output()
	{
		for (int i = 1; i <= x; ++i)
		{
			for (int j = 1; j <= y; ++j) printf("%d ", d[i][j]);
			printf("\n");
		}
		return ;
	}
}tree[MAXM << 2], a;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void getinv(int x)
{
	inv[1] = 1;
	for(int i = 2; i <= x; ++i) inv[i] = ((LL)P - (LL)P / i) * inv[P % i] % P;
}

void build(int p, int l, int r)
{
	if (l == r) {tree[p].init(n, n); return ;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	tree[p].init(n, n);
}

void change(int p, int l, int r, int zzh, const node &s)
{
	if (l == r) {tree[p] = s; return ;}
	int mid = (l + r) >> 1;
	if (zzh <= mid) change(p << 1, l, mid, zzh, s);
	else change(p << 1 | 1, mid + 1, r, zzh, s);
	tree[p] = tree[p << 1] * tree[p << 1 | 1];
}

int main()
{
	//���֮Դ
//	freopen("tea.in", "r", stdin);
//	freopen("tea.out", "w", stdout);
	n = read(); m = read(); a.x = 1; a.y = n;
	for (int i = 1; i <= n; ++i)  a.d[1][i]= read();
	build(1, 1, m); getinv(n);
	for (int i = 1; i <= m; ++i)
	{
		int opt = read();node t;
		if (opt == 1)
		{
			++cnt;
			int p = read(), k = read();
			t.init(n,n);
			t.d[p][p] = 0;
			for (int j = 1; j <= k; ++j)
			{
				int tmp = read(); t.d[p][tmp] = inv[k];
			}
			change(1, 1, m, cnt, t);
			q[p].push(cnt);
		}
		else
		{
			int p = read();
			if (!q[p].empty())
			{
				t.init(n, n);
				change(1, 1, m, q[p].front(), t);
				q[p].pop();
			}
		}
		node ans = a * tree[1];
		ans.output();
	}
	return 0;
}
