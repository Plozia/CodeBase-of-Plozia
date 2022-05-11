#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
int n, m, a[MAXN], cnt[MAXN], block, ys[MAXN], total, ans[MAXN];
struct node
{
	int l, r, id;
}q[MAXN];

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
	n = read(); block = sqrt(n);
	for (int i = 1; i <= n; ++i) {a[i] = read(); ys[i] = (i - 1) / block + 1;}
	m = read();
	for (int i = 1; i <= m; ++i) {q[i].l = read(); q[i].r = read(); q[i].id = i;}
	sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i)
	{
		while (l > q[i].l) total += !cnt[a[--l]]++;
		while (r > q[i].r) total -= !--cnt[a[r--]];
		while (r < q[i].r) total += !cnt[a[++r]]++;
		while (l < q[i].l) total -= !--cnt[a[l++]];
		ans[q[i].id] = total;
	}
	for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
