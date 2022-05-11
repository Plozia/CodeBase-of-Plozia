#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e4+10;
int n,m,fa[MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y) {if(gf(x)!=gf(y)) fa[fa[x]]=fa[y];}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(fh=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		z=read();x=read();y=read();
		if(z==1) hb(x,y);
		else cout<<((gf(x)==gf(y))?'Y':'N')<<"\n";
	}
	return 0;
}
