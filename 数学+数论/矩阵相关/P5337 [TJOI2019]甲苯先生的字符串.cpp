/*
========= Plozia =========
	Author:Plozia
	Problem:P5337 [TJOI2019]甲苯先生的字符串
	Date:2021/6/11
	Remarks:字符串长度为 n 意思是走 n - 1 步而不是 n 步
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::string;

typedef long long LL;
const int MAXN = 26 + 5, P = 1e9 + 7;
LL n;
string str;
struct Matrix
{
	LL a[MAXN][MAXN];
	int r, c;
	void init()
	{
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= r; ++i) a[i][i] = 1;
	}
	Matrix operator *(const Matrix &fir)
	{
		Matrix ans; ans.r = r; ans.c = fir.c; memset(ans.a, 0, sizeof(ans.a));
		for (int i = 1; i <= r; ++i)
			for (int k = 1; k <= c; ++k)
			{
				LL t = a[i][k];
				for (int j = 1; j <= fir.c; ++j)
				{ ((ans.a[i][j] += t * fir.a[k][j]) >= P) ? (ans.a[i][j] %= P) : 0; }
			}
		return ans;
	}
}Base;

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

Matrix ksm(Matrix a, LL b)
{
	Matrix ans; ans.r = ans.c = a.r; ans.init();
	for (; b; b >>= 1, a = a * a)
		if (b & 1) ans = ans * a;
	return ans;
}

int main()
{
	n = Read(); std::cin >> str;
	Base.r = Base.c = 26;
	for (int i = 1; i <= 26; ++i)
		for (int j = 1; j <= 26; ++j)
			Base.a[i][j] = 1;
	for (int i = 0; i + 1 < str.size(); ++i)
	{
		if (str[i] == '\r' || str[i] == '\n') continue ;
		Base.a[str[i] - 'a' + 1][str[i + 1] - 'a' + 1] = 0;
	}
	Base = ksm(Base, n - 1);
	LL ans = 0;
	for (int i = 1; i <= 26; ++i)
		for (int j = 1; j <= 26; ++j)
			((ans += Base.a[i][j]) >= P) ? (ans -= P) : 0;
	printf("%lld\n", ans); return 0;
}