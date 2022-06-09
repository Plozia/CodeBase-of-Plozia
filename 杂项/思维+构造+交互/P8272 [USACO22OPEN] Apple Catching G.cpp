/*
========= Plozia =========
	Author:Plozia
	Problem:P8272 [USACO22OPEN] Apple Catching G
	Date:2022/6/7
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::multiset;
using std::set;
typedef long long LL;

const int MAXN = 2e5 + 5;
int n;
struct node
{
	int opt, x, y, cnt;
	bool operator <(const node &fir)const { return (y ^ fir.y) ? (y > fir.y) : (x > fir.x); }
}a[MAXN];
struct Set
{
	int Num, cnt;
	bool operator <(const Set &fir)const { return Num < fir.Num; }
};
multiset <Set> s;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	n = Read(); int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		int q = Read(), t = Read(), x = Read(), c = Read();
		a[i] = (node){q, t + x, t - x, c};
	}
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
	{
		if (a[i].opt == 2) s.insert((Set){a[i].x, a[i].cnt});
		else
		{
			while (a[i].cnt > 0)
			{
				auto it = s.lower_bound((Set){a[i].x, 0});
				if (it == s.end()) break ;
				if ((*it).cnt > a[i].cnt)
				{
					ans += a[i].cnt; Set tmp = (*it); s.erase(it);
					s.insert((Set){tmp.Num, tmp.cnt - a[i].cnt}); break;
				}
				else
				{
					ans += (*it).cnt; a[i].cnt -= (*it).cnt; s.erase(it);
				}
			}
		}
	}
	printf("%d\n", ans); return 0;
}