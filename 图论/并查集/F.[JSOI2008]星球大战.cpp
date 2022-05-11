#include<bits/stdc++.h>
using namespace std;

const int MAXN=4e5+10;
int n,fa[MAXN],m,k,des[MAXN],ans[MAXN],sum;
bool book[MAXN];
vector<int>v[MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y)
{
	if(gf(x)!=gf(y))
	{
		sum--;
		fa[fa[x]]=fa[y];
	}
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
	n=read();m=read();
	for(int i=0;i<n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x=read();int y=read();
		v[x].push_back(y);v[y].push_back(x);
	}
	k=read();sum=n;
	for(int i=1;i<=k;i++) book[des[i]=read()]=1;
	for(int i=0;i<n;i++)
		if(!book[i])
		{
			for(int j=0;j<v[i].size();j++)
			{
				if(!book[v[i][j]]) hb(i,v[i][j]);
			}
		}
	for(int zzh=k;zzh>=1;zzh--)
	{
		ans[zzh]=sum-zzh;
		book[des[zzh]]=0;
		for(int i=0;i<v[des[zzh]].size();i++)
			if(!book[v[des[zzh]][i]]) hb(v[des[zzh]][i],des[zzh]);
	}
	ans[0]=sum;
	for(int i=0;i<=k;i++) cout<<ans[i]<<"\n";
	return 0;
}
