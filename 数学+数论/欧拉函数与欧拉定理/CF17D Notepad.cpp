/*
========= Plozia =========
	Author:Plozia
	Problem:CF17D Notepad
	Date:2021/5/20
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::string;

typedef long long LL;
// const int MAXN = ;
// int ;
LL phi = 1, c;
string str1, str2;
LL b, n;
bool flag;

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

LL ksm(LL fir, LL sec, LL p)
{
	LL ans = 1 % p;
	for (; sec; sec >>= 1, fir = fir * fir % p)
		if (sec & 1) ans = ans * fir % p;
	return ans;
}

void Get_phi()
{
	LL p = c;
	for (LL i = 2; i * i <= p; ++i)
	{
		LL sum = 0;
		while (p % i == 0) { p /= i; ++sum; }
		if (sum != 0) phi = phi * (i - 1) * ksm(i, sum - 1, c);
	}
	if (p != 1) phi = phi * (p - 1);
}

int main()
{
	std::cin >> str1 >> str2 >> c; Get_phi();
	for (int i = 0; i < str1.size(); ++i) b = (b * 10 + str1[i] - '0') % c;
	str2[str2.size() - 1]--;
	for (int i = 0; i < str2.size(); ++i)
	{
		n = n * 10 + str2[i] - '0';
		if (n >= phi) { n %= phi; flag = 1; }
	}
	if (flag) n += phi;
	LL t = b - 1;
	if (t < 0) t += c;
	printf("%lld\n", (t * ksm(b, n, c) % c == 0ll) ? c : (t * ksm(b, n, c) % c)); return 0;
}