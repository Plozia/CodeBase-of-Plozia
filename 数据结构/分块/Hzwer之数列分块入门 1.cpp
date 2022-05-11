#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
int n,b,op,l,r,c;
typedef long long LL;
LL a[MAXN],sum[MAXN],tag[MAXN];

void add(int l,int r,int k)
{
	int idl=l/b,idr=r/b;
	if(idl==idr)
	{
		for(int i=l;i<=r;i++)
		{
			a[i]+=k;sum[idl]+=k;
		}
	}
	else
	{
		for(int i=l;i<(idl+1)*b;i++)
		{
			a[i]+=k;sum[idl]+=k;
		}
		for(int i=idl+1;i<=idr-1;i++)
		{
			tag[i]+=k;sum[i]+=k*b;
		}
		for(int i=idr*b;i<=r;i++)
		{
			a[i]+=k;sum[idr]+=k;
		}
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
	n=read();b=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		a[i]=read();sum[i/b]+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		op=read();l=read();r=read();c=read();
		if(op==0) add(l,r,c);
		else cout<<a[r]+tag[r/b]<<"\n";
	}
	return 0;
}
