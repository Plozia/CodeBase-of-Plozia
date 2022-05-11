#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e6 + 10;
int n, sa[MAXN << 1], rk[MAXN << 1];
char s[MAXN];
struct node
{
	int a, b, id;
	bool operator <(const node &t)const {return (a ^ t.a) ? (a < t.a) : (b < t.b);}
}q[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	scanf("%s", s + 1); n = strlen(s + 1);
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
	for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
	printf("\n");
	return 0;
}
