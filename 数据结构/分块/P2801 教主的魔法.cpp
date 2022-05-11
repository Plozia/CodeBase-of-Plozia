#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+5;
int n,q,ys[MAXN],block;
typedef long long LL;
LL a[MAXN],tag[MAXN];
vector<LL>v[MAXN];

int read()
{
	int sum=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum;
}

void add(int l,int r,LL k)
{
	if(ys[l]==ys[r])
	{
		int ll=(ys[l]-1)*block+1,lr=ys[l]*block;
		for(int i=l;i<=r;++i) a[i]+=k;
		v[ys[l]].clear();
		for(int i=ll;i<=lr;++i) v[ys[l]].push_back(a[i]);
		sort(v[ys[l]].begin(),v[ys[l]].end());
	}
	else
	{
		int ll=(ys[l]-1)*block+1,lr=ys[l]*block,rl=(ys[r]-1)*block+1,rr=ys[r]*block;
		for(int i=l;i<=lr;++i) a[i]+=k;
		v[ys[l]].clear();
		for(int i=ll;i<=lr;++i) v[ys[l]].push_back(a[i]);
		sort(v[ys[l]].begin(),v[ys[l]].end());
		for(int i=rl;i<=r;++i) a[i]+=k;
		v[ys[r]].clear();
		for(int i=rl;i<=rr;++i) v[ys[r]].push_back(a[i]);
		sort(v[ys[r]].begin(),v[ys[r]].end());
		for(int i=ys[l]+1;i<=ys[r]-1;++i) tag[i]+=k;
	}
}

int ask(int l,int r,LL k)
{
	int ll=(ys[l]-1)*block+1,lr=ys[l]*block,rl=(ys[r]-1)*block+1,rr=ys[r]*block,sum=0;
	if(ys[l]==ys[r])
	{
		for(int i=l;i<=r;++i)
			if(a[i]+tag[ys[l]]>=k) ++sum;
	}
	else
	{
		for(int i=l;i<=lr;++i)
			if(a[i]+tag[ys[l]]>=k) ++sum;
		for(int i=rl;i<=r;++i)
			if(a[i]+tag[ys[r]]>=k) ++sum;
		for(int i=ys[l]+1;i<=ys[r]-1;++i)
		{
			int p=lower_bound(v[i].begin(),v[i].end(),k-tag[i])-v[i].begin();
			sum+=v[i].size()-p;
		}
	}
	return sum;
}

void print(int x,char tail=0)
{
	if(x>9) print(x/10);
	putchar(x%10+48);
	if(tail) putchar(tail);
}

int main()
{
	n=read();q=read();block=900;
	for(int i=1;i<=n;++i) ys[i]=(i-1)/block+1;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) v[ys[i]].push_back(a[i]);
	for(int i=1;i<=ys[n];++i) sort(v[i].begin(),v[i].end());
	for(int i=1;i<=q;++i)
	{
		char ch;int l,r,k;
		ch=getchar();
		while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
		l=read();r=read();k=read();
		if(ch=='M') add(l,r,k);
		else print(ask(l,r,k),'\n');
	}
	return 0;
}
