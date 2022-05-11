/*
========= Plozia =========
	Author:Plozia
	Problem:P4887 【模板】莫队二次离线（第十四分块(前体)）
	Date:本代码书写于 2020/12/16
========= Plozia =========
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m, k, a[MAXN], t[MAXN], p[MAXN], block, ys[MAXN];
LL ans[MAXN];
struct node
{
	int l, r, id;
	LL ans;
}q[MAXN];
vector <int> b;
vector < tuple <int, int, int, int> > v[MAXN];

int read()
{
	int sum = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum;
}

bool cmp(const node &fir, const node &sec)
{
	if (ys[fir.l] ^ ys[sec.l]) return ys[fir.l] < ys[sec.l];
	return fir.r < sec.r;
}

int Count(int x)
{
	int sum = 0;
	for (; x; x >>= 1)
		if (x & 1) sum++;
	return sum;
}

int main()
{
	n = read(); m = read(); k = read(); block = ceil(n / sqrt(m));
	if (k > 14)
	{
		for (int i = 1; i <= m; ++i) printf("0\n");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {a[i] = read(); ys[i] = (i - 1) / block + 1;}
	for (int i = 1; i <= m; ++i) {q[i].l = read(); q[i].r = read(); q[i].id = i;}
	sort(q + 1, q + m + 1, cmp);
	for (int i = 0; i < 16384; ++i)
		if (Count(i) == k) b.push_back(i);
	for (int i = 1; i <= n; ++i)
	{
		p[i] = t[a[i]];
		for (int j = 0; j < b.size(); ++j) t[a[i] ^ b[j]]++;
	}
	memset(t, 0, sizeof(t));
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i)
	{
		if (l > q[i].l) v[r].emplace_back(q[i].l, l - 1, i, 1);
		while (l > q[i].l) q[i].ans -= p[--l];
		if (r < q[i].r) v[l - 1].emplace_back(r + 1, q[i].r, i, -1);
		while (r < q[i].r) q[i].ans += p[++r];
		if (l < q[i].l) v[r].emplace_back(l, q[i].l - 1, i, -1);
		while (l < q[i].l) q[i].ans += p[l++];
		if (r > q[i].r) v[l - 1].emplace_back(q[i].r + 1, r, i, 1);
		while (r > q[i].r) q[i].ans -= p[r--];
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < b.size(); ++j) ++t[a[i] ^ b[j]];
		for (int j = 0; j < v[i].size(); ++j)
		{
            tuple x = v[i][j];
			for (int zzh = get<0>(x); zzh <= get<1>(x); ++zzh)
			{
				if (zzh <= i && k == 0) q[get<2>(x)].ans += get<3>(x) * (t[a[zzh]] - 1);
				else q[get<2>(x)].ans += get<3>(x) * t[a[zzh]];
			}
		}
	}
	for (int i = 1; i <= m; ++i) q[i].ans += q[i-1].ans;
	for (int i = 1; i <= m; ++i) ans[q[i].id] = q[i].ans;
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}
