#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 4e5 + 10;
int n, sa[MAXN << 1], rk[MAXN << 1], height[MAXN], len1, len2;
char s[MAXN];
struct node
{
	int a, b, id;
	bool operator < (const node &fir) {return (a ^ fir.a) ? (a < fir.a) : (b < fir.b);}
}q[MAXN];
LL ans;

void getsa()
{
	for (int i = 1; i <= n; ++i) rk[i] = s[i];
	for (int l = 1; l < n; l <<= 1)
	{
		for (int i = 1; i <= n; ++i) {q[i].a = rk[i]; q[i].b = rk[i + l]; q[i].id = i;}
		sort(q + 1, q + n + 1);
		int m = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (q[i].a != q[i - 1].a || q[i].b != q[i - 1].b) ++m;
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
		while (s[j + k] == s[i + k]) ++k;
		height[i] = k;
	}
}

bool pd(int k)
{
	int flag1 = 0, flag2 = 0;
	if (sa[k] < len1) flag1 = 1;
	if (sa[k + 1] < len1) flag2 = 1;
	if (flag1 ^ flag2) return 0;
	return 1;
}

LL Get(int k)
{
	return (LL)height[k] * (height[k] + 1) / 2;
}

int main()
{
	scanf("%s", s + 1); len1 = strlen(s + 1);
	scanf("%s", s + len1 + 2); len2 = strlen(s + 1) - len1;
	n = strlen(s + 1);
	getsa(); gethe();
	for (int i = 1; i < n; ++i)
	{
		if (pd(i)) continue;
		ans += Get(i + 1);
	}
	printf("%lld\n", ans);
	return 0;
}
