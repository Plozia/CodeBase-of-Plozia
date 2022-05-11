#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 10;
char s[MAXN];
int n, rk[MAXN << 1], sa[MAXN << 1];
struct node
{
	int a, b, id;
	bool operator <(const node &t)const
	{
		return (a ^ t.a) ? (a < t.a) : (b < t.b);
	}
}q[MAXN];

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

int main()
{
	scanf("%s", s + 1); n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) s[i + n] = s[i];
	n <<= 1; getsa();
	for (int i = 1; i <= n; ++i) if (sa[i] <= (n >> 1)) printf("%c", s[sa[i] + (n >> 1) - 1]);
	return 0;
}
