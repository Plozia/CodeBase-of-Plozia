/*
========= Plozia =========
	Author:Plozia
	Problem:P2398 GCD SUM
	Date:2021/4/6
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, phi[MAXN];
bool book[MAXN];
LL ans = 0, sum[MAXN];
vector <int> v;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	n = read(); book[1] = 1; phi[1] = 1; sum[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (!book[i]) {phi[i] = i - 1; v.push_back(i);}
		sum[i] = sum[i - 1] + (LL)phi[i];
		for (int j = 0; j < v.size(); ++j)
		{
			if (i * v[j] > n) break;
			book[i * v[j]] = 1;
			if (i % v[j] == 0) {phi[i * v[j]] = phi[i] * v[j]; break;}
			phi[i * v[j]] = phi[i] * (v[j] - 1); 
		}
	}
	//做法 1
	// for (int i = 1; i <= n; ++i)
	//     ans += (LL)phi[i] * (LL)(n / i) * (LL)(n / i);
	// printf("%lld\n", ans);
	//做法 2
	for (int i = 1; i <= n; ++i)
		ans += i * (2ll * sum[n / i] - 1);
	printf("%lld\n", ans);
	return 0;
}