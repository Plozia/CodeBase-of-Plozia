/*
========= Plozia =========
	Author:Plozia
	Problem:CF1416B Make Them Equal
	Date:2022/5/23
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::queue;

typedef long long LL;
const int MAXN = 1e4 + 5;
int t, n, a[MAXN], b[MAXN];
queue <int> q[3];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Solve()
{
	LL sum = 0;
	n = Read(); for (int i = 1; i <= n; ++i) sum += (b[i] = a[i] = Read());
	if (sum % n != 0) { puts("-1"); return ; } sum /= n;
	for (int i = 2; i <= n; ++i)
	{
		if (a[i] % i != 0)
		{
			q[0].push(1), q[1].push(i), q[2].push(i - a[i] % i);
			a[1] -= i - a[i] % i; a[i] += i - a[i] % i;
		}
		q[0].push(i), q[1].push(1), q[2].push(a[i] / i);
		a[1] += a[i]; a[i] = 0;
	}
	for (int i = 2; i <= n; ++i)
	{
		q[0].push(1), q[1].push(i), q[2].push(sum);
		a[1] -= sum; a[i] += sum;
	}
	printf("%d\n", q[0].size());
	while (!q[0].empty())
	{
		int tmp1 = b[q[0].front()], tmp2 = b[q[1].front()];
		tmp1 -= q[0].front() * q[2].front(), tmp2 += q[0].front() * q[2].front();
		if (tmp1 < 0) q[0].push(q[0].front()), q[1].push(q[1].front()), q[2].push(q[2].front());
		else { b[q[0].front()] = tmp1, b[q[1].front()] = tmp2; printf("%d %d %d\n", q[0].front(), q[1].front(), q[2].front()); }
		q[0].pop(), q[1].pop(), q[2].pop();
	}
}

int main()
{
	t = Read(); while (t--) Solve(); return 0;
}