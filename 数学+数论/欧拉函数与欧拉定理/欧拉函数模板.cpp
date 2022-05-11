/*
========= Plozia =========
	Author:Plozia
	Problem:无 /doge
	Date:2021/4/1
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e7 + 10;
int n, phi[MAXN];
bool book[MAXN];
vector <int> v;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

int ksm(int a, int b)
{
	int ans = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) ans = ans * a;
	return ans;
}

int Get(int n)//求单个数欧拉函数
{
	int ans = 1;
	for (int i = 2; i * i <= n; ++i)
	{
		int cnt = 0;
		while (n % i == 0) {n /= i; ++cnt;}
		if (cnt != 0) ans = ans * ksm(i, cnt - 1) * (i - 1);//基本性质 4
	}
	if (n != 1) ans = ans * (n - 1);//n^0=1
	return ans;
}

int main()
{
	/*
	式子：
	phi[n * p] = phi[n] * p, 如果 p | n;
	phi[n * p] = phi[n] * phi[p], 如果 p 不整除 n;
				 特别的，当 p 为 Prime 时，有 phi[n * p] = phi[n] * (p - 1);
	*/
	n = read();
	book[1] = 1; phi[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (!book[i]) {v.push_back(i); phi[i] = i - 1;}
		for (int j = 0; j < v.size(); ++j)
		{
			if (i * v[j] > n) break;
			book[i * v[j]] = 1;
			if (i % v[j] == 0) {phi[i * v[j]] = v[j] * phi[i]; break;}
			phi[i * v[j]] = phi[i] * (v[j] - 1); //phi[j] = v[j] - 1;
		}
	}
	for (int i = 1; i <= n; ++i) printf("%d ", phi[i]);
	printf("\n"); return 0;
}