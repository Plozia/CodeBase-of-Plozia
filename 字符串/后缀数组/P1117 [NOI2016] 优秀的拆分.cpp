/*
========= Plozia =========
	Author:Plozia
	Problem:P1117 [NOI2016] 优秀的拆分
	Date:2022/2/10
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 6e4 + 5;
int t, sa[MAXN << 1], rk[MAXN << 1], height[MAXN], n, Before[MAXN], saBefore[MAXN << 1], rkBefore[MAXN << 1], fir[MAXN], sec[MAXN];
char str[MAXN << 1], str2[MAXN << 1];
struct node
{
	int a, b, id;
	bool operator <(const node &fir)const { return (a ^ fir.a) ? (a < fir.a) : (b < fir.b); }
}a[MAXN];
struct SgT
{
	int l, r, Minn;
	#define l(k, p) tree[k][p].l
	#define r(k, p) tree[k][p].r
	#define Minn(k, p) tree[k][p].Minn
}tree[2][MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void GetHeight()
{
	for (int i = 1; i <= n; ++i) rk[i] = str[i];
	for (int len = 1; len <= n; len *= 2)
	{
		for (int i = 1; i <= n; ++i) { a[i] = (node){rk[i], rk[i + len], i}; }
		std::sort(a + 1, a + n + 1); int m = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (a[i].a != a[i - 1].a || a[i].b != a[i - 1].b) ++m;
			rk[a[i].id] = m;
		}
	}
	for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
	int k = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (k) --k; if (rk[i] == 1) continue ;
		int j = sa[rk[i] - 1];
		while (str[j + k] == str[i + k]) ++k;
		height[rk[i]] = k;
	}
	// 求 Height，其中下面这段是从上面这段复制的，就改了改数组名
	for (int i = 1; i <= n; ++i) rkBefore[i] = str2[i];
	for (int len = 1; len <= n; len *= 2)
	{
		for (int i = 1; i <= n; ++i) { a[i] = (node){rkBefore[i], rkBefore[i + len], i}; }
		std::sort(a + 1, a + n + 1); int m = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (a[i].a != a[i - 1].a || a[i].b != a[i - 1].b) ++m;
			rkBefore[a[i].id] = m;
		}
	}
	for (int i = 1; i <= n; ++i) saBefore[rkBefore[i]] = i;
	k = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (k) --k; if (rkBefore[i] == 1) continue ;
		int j = saBefore[rkBefore[i] - 1];
		while (str2[j + k] == str2[i + k]) ++k;
		Before[rkBefore[i]] = k;
	}
}

void Build(int k, int p, int l, int r)
{
	l(k, p) = l, r(k, p) = r;
	if (l == r) { Minn(k, p) = (k == 0) ? height[l] : Before[l]; return ; }
	int mid = (l + r) >> 1;
	Build(k, p << 1, l, mid); Build(k, p << 1 | 1, mid + 1, r);
	Minn(k, p) = Min(Minn(k, p << 1), Minn(k, p << 1 | 1));
}

int AskMin(int k, int p, int l, int r)
{
	if (l(k, p) >= l && r(k, p) <= r) return Minn(k, p);
	int mid = (l(k, p) + r(k, p)) >> 1, val = 0x7f7f7f7f;
	if (l <= mid) val = Min(val, AskMin(k, p << 1, l, r));
	if (r > mid) val = Min(val, AskMin(k, p << 1 | 1, l, r));
	return val;
}

int main()
{
	t = Read();
	while (t--)
	{
		memset(sa, 0, sizeof(sa)); memset(rk, 0, sizeof(rk));
		memset(height, 0, sizeof(height)); memset(Before, 0, sizeof(Before));
		memset(saBefore, 0, sizeof(saBefore)); memset(rkBefore, 0, sizeof(rkBefore));
		memset(fir, 0, sizeof(fir)); memset(sec, 0, sizeof(sec));
		// 全是清零
		scanf("%s", str + 1); n = strlen(str + 1);
		for (int i = 1; i <= n; ++i) str2[i] = str[n - i + 1];
		GetHeight(); Build(0, 1, 1, n); Build(1, 1, 1, n); // 建树
		for (int len = 1; len <= n; ++len)
		{
			for (int i = len; i + len <= n; i += len)
			{
				int j = i + len;
				int x = AskMin(0, 1, i, j), y = AskMin(1, 1, n - j + 2, n - i + 2); // x -> LCP, y -> LCS
				x = Min(x, len); y = Min(y, len - 1);
				if (x + y >= len)
				{
					++sec[i - y]; --sec[i + x - len + 1];
					++fir[j - y + len - 1]; --fir[j + x];
				}
			}
		} // 主部分
		for (int i = 1; i <= n; ++i) fir[i] += fir[i - 1], sec[i] += sec[i - 1];
		LL ans = 0;
		for (int i = 1; i <= n; ++i) ans += 1ll * fir[i] * sec[i + 1];
		printf("%lld\n", ans); // printf("n:%d\n", n);
		// printf("rk:"); for (int i = 1; i <= n; ++i) printf("%d%c", rk[i], " \n"[i == n]);
		// printf("sa:"); for (int i = 1; i <= n; ++i) printf("%d%c", sa[i], " \n"[i == n]);
		// printf("fir:"); for (int i = 1; i <= n; ++i) printf("%d%c", fir[i], " \n"[i == n]);
		// printf("sec:"); for (int i = 1; i <= n; ++i) printf("%d%c", sec[i], " \n"[i == n]);
		// printf("Height:"); for (int i = 1; i <= n; ++i) printf("%d%c", height[i], " \n"[i == n]);
		// printf("BeforeHeight:"); for (int i = 1; i <= n; ++i) printf("%d%c", Before[i], " \n"[i == n]);
	}
	return 0;
}