#include<bits/stdc++.h>
using namespace std;

const int MAXN=30000+10;
int t,fa[MAXN],front[MAXN],num[MAXN];

int gf(int x)
{
	if(fa[x]==x) return x;
	int f=gf(fa[x]);
	front[x]+=front[fa[x]];
	return fa[x]=f;
}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	t=read();
	for(int i=1;i<=30000;i++) fa[i]=i,front[i]=0,num[i]=1;
	for(int i=1;i<=t;i++)
	{
		char ch;int x,y;
		cin>>ch;x=read();y=read();
		if(ch=='M')
		{
			int fx=gf(x);
			int fy=gf(y);
			if(fx!=fy)
			{
				front[fx]=num[fy];
				num[fy]+=num[fx];
				num[fx]=0;
				fa[fx]=fy;
			}
		}
		else
		{
			if(gf(x)!=gf(y)) cout<<"-1\n";
			else cout<<abs(front[x]-front[y])-1<<"\n";
		}
	}
	return 0;
}
