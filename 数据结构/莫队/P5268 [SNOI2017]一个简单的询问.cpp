#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 5e4 + 10;
int n, m, ys[MAXN], block, total, cnt[MAXN], a[MAXN];
LL ans[MAXN][2];
struct node
{
	int l, r, id1, id2;
}q[MAXN << 1];

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
	if (ys[fir.l] & 1) return fir.r < sec.r;
	return fir.r > sec.r;
}

int main()
{
	n = read(); block = ceil(sqrt(n));
	for (int i = 1; i <= n; ++i) {a[i] = read(); ys[i] = (i - 1) / block + 1;}
	m = read();
	for (int i = 1; i <= (m << 1); ++i)
	{
		q[i].l = read(); q[i].r = read();
		if (i & 1) q[i].id1 = (i + 1) >> 1, q[i].id2 = 0;
		else q[i].id1 = i >> 1, q[i].id2 = 1;
	}
	sort(q + 1, q + (m << 1) + 1, cmp);
	int l = 1, r = 0;
	for (int i = 1; i <= (m << 1); ++i)//l--,r++,r--,l++
	{
		while (l > q[i].l) total += !cnt[a[--l]]++;
		while (r < q[i].r) total += !cnt[a[++r]]++;
		while (r > q[i].r) total -= !--cnt[a[r--]];
		while (l < q[i].l) total -= !--cnt[a[l++]];
		ans[q[i].id1][q[i].id2] = (LL)total;
	}
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i][0] * ans[i][1]);
	return 0;
}
