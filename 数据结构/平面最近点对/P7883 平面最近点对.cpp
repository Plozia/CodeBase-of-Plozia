/*
========= Plozia =========
	Author:Plozia
	Problem:P1429 / P7883 平面最近点对
	Date:2022/3/25
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::multiset;

typedef long long LL;
const int MAXN = 4e5 + 5;
int n;
LL ans = 0;
struct node
{
	int x, y;
	bool operator <(const node &fir)const { return x < fir.x; }
}a[MAXN];
struct SET
{
	LL y, id;
	SET(LL y, LL id): y(y), id(id){}
	bool operator <(const SET &fir)const { return y < fir.y; }
};
multiset <SET> s;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
LL Abs(LL x) { return (x < 0) ? -x : x; }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) a[i].x = Read(), a[i].y = Read();
	std::sort(a + 1, a + n + 1);
	int l = 1; ans = 1ll * (a[1].x - a[2].x) * (a[1].x - a[2].x) + 1ll * (a[1].y - a[2].y) * (a[1].y - a[2].y);
	for (int i = 1; i <= n; ++i)
	{
		if (l < i && a[i].x - a[l].x > ans) s.erase((SET){a[l].y, l});
		auto it = s.lower_bound((SET){a[i].y - ans, i});
		for (; it != s.end() && Abs(a[i].y - a[(*it).id].y) <= ans; ++it)
			ans = Min(ans, 1ll * (a[i].x - a[(*it).id].x) * (a[i].x - a[(*it).id].x) + 1ll * (a[i].y - a[(*it).id].y) * (a[i].y - a[(*it).id].y));
		s.emplace(a[i].y, i);
	}
	printf("%lld\n", ans); return 0;
}