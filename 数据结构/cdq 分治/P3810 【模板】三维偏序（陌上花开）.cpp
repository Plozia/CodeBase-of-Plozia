/*
========= Plozia =========
	Author:Plozia
	Problem:P3810 【模板】三维偏序（陌上花开）
	Date:2022/4/5
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5, MAXK = 2e5 + 5;
int n, m, f[MAXN], s[MAXN], cntn, val[MAXN];
struct node { int a, b, c, id; } a[MAXN], b[MAXN], tmp[MAXN];
struct sgt { int sum; } tree[MAXK << 2];

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
	if (fir.a ^ sec.a) return fir.a < sec.a;
	if (fir.b ^ sec.b) return fir.b < sec.b;
	return fir.c < sec.c;
}

void Change(int p, int k, int s, int lp, int rp)
{
	if (lp == rp) { tree[p].sum += s; return ; }
	int mid = (lp + rp) >> 1;
	if (k <= mid) Change(p << 1, k, s, lp, mid);
	else Change(p << 1 | 1, k, s, mid + 1, rp);
	tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum;
}

int Ask(int p, int l, int r, int lp, int rp)
{
	if (lp >= l && rp <= r) return tree[p].sum;
	int mid = (lp + rp) >> 1, val = 0;
	if (l <= mid) val += Ask(p << 1, l, r, lp, mid);
	if (r > mid) val += Ask(p << 1 | 1, l, r, mid + 1, rp);
	return val;
}

void MergeSort(int l, int r)
{
	if (l == r) return ; int mid = (l + r) >> 1;
	MergeSort(l, mid); MergeSort(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r)
	{
		if (a[i].b <= a[j].b) { Change(1, a[i].c, val[a[i].id], 1, m); tmp[k++] = a[i++]; }
		else { f[a[j].id] += Ask(1, 1, a[j].c, 1, m); tmp[k++] = a[j++]; }
	}
	while (j <= r) { f[a[j].id] += Ask(1, 1, a[j].c, 1, m); tmp[k++] = a[j++]; }
	for (int p = l; p < i; ++p) Change(1, a[p].c, -val[a[p].id], 1, m);
	while (i <= mid) tmp[k++] = a[i++];
	for (int i = l; i <= r; ++i) a[i] = tmp[i];
}

int main()
{
	n = Read(), m = Read();
	for (int i = 1; i <= n; ++i) b[i].a = Read(), b[i].b = Read(), b[i].c = Read();
	std::sort(b + 1, b + n + 1, cmp);
	for (int i = 1; i <= n; ++i)
	{
		if (b[i].a != b[i - 1].a || b[i].b != b[i - 1].b || b[i].c != b[i - 1].c)
		{
			++cntn; a[cntn] = b[i]; val[cntn] = 1; a[cntn].id = cntn;
		}
		else ++val[cntn];
	}
	MergeSort(1, cntn);
	for (int i = 1; i <= cntn; ++i) s[f[i] + val[i] - 1] += val[i];
	for (int i = 0; i < n; ++i) printf("%d\n", s[i]);
	return 0;
}