#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m, cnt[MAXN], out[MAXN];
vector <int> Next[MAXN], Num[MAXN];
LL gcd(LL, LL);
LL lcm(LL, LL);
struct node
{
	LL fz, fm;
	void init()
	{
		fz = 0, fm = 1;
	}
	node operator + (const node &fir)
	{
		LL tfm = lcm(fm, fir.fm);
		LL tfz = tfm / fm * fz + tfm / fir.fm * fir.fz;
		LL gct = gcd(tfm, tfz);
		return (node){tfz / gct, tfm / gct};
	}
}ans[MAXN];

LL gcd(LL fir, LL sec) {return (sec == 0) ? fir : gcd(sec, fir % sec);}
LL lcm(LL fir, LL sec) {return fir / gcd(fir, sec) * sec;}

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void topsort()
{
	queue <int> q;
	for (int i = 1; i <= n; ++i)
		if (!cnt[i]) q.push(i);
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (int i = 0; i < Next[x].size(); ++i)
		{
			int u = Next[x][i], w = Num[x][i];
			node tx = (node){(ans[x].fz == 0) ? w : (ans[x].fz * (LL)w * ans[x].fm), ans[x].fm * (LL)out[x]};
			cnt[u]--; ans[u] = tx + ans[u];
			if (cnt[u] == 0) q.push(u);
		}
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i)
	{
		int x = read(), y = read(), z = read();
		Next[x].push_back(y), Num[x].push_back(z);
		cnt[y]++; out[x]++;
	}
	for (int i = 1; i <= n; ++i) ans[i].init();
	topsort();
	printf("%.2lf\n", (double)ans[n].fz / ans[n].fm);
	return 0;
}
