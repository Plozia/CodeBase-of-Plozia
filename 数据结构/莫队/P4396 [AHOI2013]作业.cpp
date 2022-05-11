/*
========= Plozia =========
	Author:Plozia
	Problem:P4396 [AHOI2013]作业
	Date:2021/7/10
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 10;
int n, m, a[MAXN], Maxn, block, s[MAXN], ys[MAXN], block_s, ans[MAXN][2], sum[MAXN], sum2[MAXN];
struct node
{
	int l, r, a, b, id;
}q[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
bool cmp(const node &fir, const node &sec)
{
	return (ys[fir.l] ^ ys[sec.l]) ? (fir.l < sec.l) : ((ys[fir.l] & 1) ? (fir.r < sec.r) : (fir.r > sec.r));
}

void Change(int x, int opt)
{
	if (opt == 1) { ++s[x]; ++sum[(x - 1) / block_s + 1]; if (s[x] == 1) ++sum2[(x - 1) / block_s + 1]; }
	else { --s[x]; --sum[(x - 1) / block_s + 1]; if (s[x] == 0) --sum2[(x - 1) / block_s + 1]; }
}

int Ask(int l, int r)
{
	int ysl = (l - 1) / block_s + 1, ysr = (r - 1) / block_s + 1;
	int bl = (ysl - 1) * block_s + 1, el = Min(ysl * block_s, Maxn);
	int br = (ysr - 1) * block_s + 1, er = Min(ysr * block_s, Maxn);
	int val = 0;
	if (ysl == ysr) { for (int i = l; i <= r; ++i) val += s[i]; }
	else
	{
		for (int i = l; i <= el; ++i) val += s[i];
		for (int i = br; i <= r; ++i) val += s[i];
		for (int i = ysl + 1; i <= ysr - 1; ++i) val += sum[i];
	}
	return val;
}

int Ask2(int l, int r)
{
	int ysl = (l - 1) / block_s + 1, ysr = (r - 1) / block_s + 1;
	int bl = (ysl - 1) * block_s + 1, el = Min(ysl * block_s, Maxn);
	int br = (ysr - 1) * block_s + 1, er = Min(ysr * block_s, Maxn);
	int val = 0;
	if (ysl == ysr) { for (int i = l; i <= r; ++i) val += (s[i] > 0); }
	else
	{
		for (int i = l; i <= el; ++i) val += (s[i] > 0);
		for (int i = br; i <= r; ++i) val += (s[i] > 0);
		for (int i = ysl + 1; i <= ysr - 1; ++i) val += sum2[i];
	}
	return val;
}

int main()
{
	n = Read(), m = Read(); block = sqrt(n);
	for (int i = 1; i <= n; ++i) Maxn = Max(Maxn, a[i] = Read());
	block_s = sqrt(Maxn);
	for (int i = 1; i <= n; ++i) ys[i] = (i - 1) / block + 1;
	for (int i = 1; i <= m; ++i) q[i].l = Read(), q[i].r = Read(), q[i].a = Read(), q[i].b = Read(), q[i].id = i;
	std::sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i)
	{
		while (l > q[i].l) Change(a[--l], 1);
		while (r < q[i].r) Change(a[++r], 1);
		while (l < q[i].l) Change(a[l++], 0);
		while (r > q[i].r) Change(a[r--], 0);
		ans[q[i].id][0] = Ask(q[i].a, q[i].b);
		ans[q[i].id][1] = Ask2(q[i].a, q[i].b);
	}
	for (int i = 1; i <= m; ++i) printf("%d %d\n", ans[i][0], ans[i][1]); return 0;
}