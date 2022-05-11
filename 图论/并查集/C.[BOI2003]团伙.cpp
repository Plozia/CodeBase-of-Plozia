#include<bits/stdc++.h>
using namespace std;

const int MAXN=1000+10;
int n,m,ans,fa[MAXN];
vector<int>v[MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y) {if(gf(x)!=gf(y)) fa[fa[x]]=fa[y];}

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
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		char op;int p,q;
		cin>>op;p=read();q=read();
		if(op=='F') hb(p,q);
		else
		{
			v[p].push_back(q);
			v[q].push_back(p);
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<v[i].size();j++)
			for(int k=0;k<v[v[i][j]].size();k++) hb(i,v[v[i][j]][k]);
	for(int i=1;i<=n;i++) if(gf(i)==i) ans++;
	cout<<ans<<"\n";
	return 0;
}
