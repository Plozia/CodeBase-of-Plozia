/*
========= Plozia =========
	Author:Plozia
	Problem:P3640 [APIO2013]出题人
	Date:2021/5/18
	Remark:由于本题为提交答案题，因此本题的代码将会分成 8 个 Subtask，分别输出数据。
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
// const int MAXN = ;
// int ;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Subtask1()
{
	//dij-Floyd-107
	freopen("1.txt", "w", stdout);
	printf("101\n");
	for (int i = 1; i <= 101; ++i) printf("0\n");
	printf("1\n1 100\n");
	fclose(stdout);
}

void Subtask2()
{
	//Floyd-BF-2222
	freopen("2.txt", "w", stdout);
	printf("100\n");
	printf("1 1 1\n");
	printf("0\n");
	printf("1 3 -1\n");
	printf("1 4 -1\n");
	printf("1 2 -1\n");
	int cnt = 1040;
	for (int i = 5; i < 100; ++i)
	{
		if (cnt >= 94)
		{
			cnt -= 94;
			printf("94 ");
			for (int j = 5; j < 100; ++j)
			{
				if (i != j) printf("%d %d ", j, 1);
			}
			printf("\n");
		}
		else
		{
			printf("%d ", cnt);
			for (int j = 5; j < 100; ++j)
			{
				if (cnt == 0) break ;
				if (i != j) { --cnt; printf("%d %d ", j, 1); }
			}
			printf("\n");
		}
	}
	printf("10\n");
	for (int i = 1; i <= 10; ++i) printf("0 1\n");
	fclose(stdout);
}

void Subtask3()
{
	//BF-Floyd-105
	freopen("3.txt", "w", stdout);
	printf("101\n");
	for (int i = 1; i <= 101; ++i) printf("0\n");
	printf("1\n1 100\n");
	fclose(stdout);
}

void Subtask4()
{
	//Floyd-dij-157
	freopen("4.txt", "w", stdout);
	printf("33\n");
	int dis = (1 << 20);
	for (int i = 0; i < 33; ++i)
	{
		if (i == 32) { printf("0\n"); continue ; }
		if (i & 1)
		{
		   dis >>= 1; printf("1 %d %d\n", i + 1, -dis);
		}
		else
		{
			printf("2 %d %d %d %d\n", i + 2, -2, i + 1, -1);
		}
	}
	printf("8\n");
	for (int i = 1; i <= 8; ++i) printf("%d %d\n", 0, 28);
	fclose(stdout);
}

void Subtask5()
{
	//dij-BF-1016
	freopen("5.txt", "w", stdout);
	printf("300\n");
	printf("1 1 1\n");
	printf("0\n");
	printf("1 3 -1\n");
	printf("1 4 -1\n");
	printf("1 2 -1\n");
	int cnt = 343;
	for (int i = 5; i < 300; ++i)
	{
		if (cnt > 294)
		{
			cnt -= 294; printf("294 ");
			for (int j = 5; j < 300; ++j)
				if (i != j) printf("%d %d ", j, 1);
			printf("\n");
		}
		else
		{
			printf("%d ", cnt);
			for (int j = 5; j < 300; ++j)
			{
				if (cnt == 0) break ;
				if (i != j) { --cnt; printf("%d %d ", j, 1); }
			}
			printf("\n");
		}
	}
	printf("10\n");
	for (int i = 1; i <= 10; ++i) printf("0 1\n");
	fclose(stdout);
}

void Subtask6()
{
	//BF-dij-143
	freopen("6.txt", "w", stdout);
	printf("33\n");
	int dis = (1 << 20);
	for (int i = 0; i < 33; ++i)
	{
		if (i == 32) { printf("0\n"); continue ; }
		if (i & 1)
		{
		   dis >>= 1; printf("1 %d %d\n", i + 1, -dis);
		}
		else
		{
			printf("2 %d %d %d %d\n", i + 2, -2, i + 1, -1);
		}
	}
	printf("6\n");
	for (int i = 1; i <= 6; ++i) printf("%d %d\n", 0, 32);
	fclose(stdout);
}

void Subtask7()
{
	srand(time(0));
	freopen("7.txt", "w", stdout);
	printf("100 ");
	bool book[100 + 10][100 + 10] = {0};
	int e = 0;
	for (; e <= 1500; )
	{
		int u = rand() % 100, v = rand() % 100;
		if (!book[u][v] && u != v)
		{
			book[u][v] = book[v][u] = 1; ++e;
		}
	}
	printf("%d\n", e);
	for (int i = 0; i < 100; ++i)
		for (int j = i + 1; j < 100; ++j)
			if (book[i][j]) printf("%d %d\n", i, j);
	fclose(stdout);
}

void Subtask8()
{
	freopen("8.txt", "w", stdout);
	printf("100 1501\n");
	int e = 1501; bool book[101][101] = {0};
	int col[101] = {0};
	for (int i = 0; i < 100; ++i) col[i] = rand() % 2;
	for (int i = 0; i < 100 && e; ++i)
	{
		for (int j = 0; j < 100 && e; ++j)
		{
			if (col[i] == col[j] || book[i][j]) continue ;
			printf("%d %d\n", i, j); --e; book[i][j] = book[j][i] = 1;
		}
	}
	if (e) printf("Error!\n");
	fclose(stdout);
}

int main()
{
	Subtask1();
	Subtask2();
	Subtask3();
	Subtask4();
	Subtask5();
	Subtask6();
	Subtask7();
	Subtask8();
	return 0;
}