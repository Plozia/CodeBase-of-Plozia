#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1000 + 10;
char s[MAXN];
int t, n, sa[MAXN << 1], rk[MAXN << 1], height[MAXN];
struct node
{
	int a, b, id;
	bool operator <(const node &t)const
	{
		return (a ^ t.a) ? (a < t.a) : (b < t.b);
	}
}q[MAXN];
LL ans;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void getsa()
{
	for (int i = 1; i <= n; ++i) rk[i] = s[i];
	for (int l = 1; l < n; l <<= 1)
	{
		for (int i = 1; i <= n; ++i) {q[i].a = rk[i]; q[i].b = rk[i + l]; q[i].id = i;}
		sort(q + 1, q + n + 1); int m = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (q[i - 1].a != q[i].a || q[i - 1].b != q[i].b) ++m;
			rk[q[i].id] = m;
		}
	}
	for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
}

void gethe()
{
	int k = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (k) --k;
		if (rk[i] == 1) continue;
		int j = sa[rk[i] - 1];
		while (s[j + k] == s[i + k]) k++;
		height[rk[i]] = k;
	}
}

int main()
{
	t = read();
	while (t--)
	{
		scanf("%s", s + 1); n = strlen(s + 1); ans = 0;
		memset(rk, 0, sizeof(rk)); memset(sa, 0, sizeof(sa)); memset(height, 0, sizeof(height));
		getsa(); gethe();
		for (int i = 1; i <= n; ++i) ans += (LL)(n - sa[i] + 1 - height[i]); 
		printf("%lld\n", ans);
	}
	return 0;
}
