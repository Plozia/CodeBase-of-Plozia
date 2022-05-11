#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
int n,a[MAXN],ans[MAXN],m,cnt[MAXN],sum,block;
struct node
{
	int l,r,id,b;
}q[MAXN];

bool cmp(const node &fir,const node &sec)
{
	if(fir.b!=sec.b) return fir.b<sec.b;
	if(fir.b&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'&&ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}
void print(int x,char tail=0)
{
	if(x<0) {putchar('-');x=-x;}
	if(x>9) {print(x/10);x%=10;}
	putchar(x|48);
	if(tail) putchar(tail);
}

void Delete(int x)
{
	sum-=cnt[a[x]]*cnt[a[x]];
	cnt[a[x]]--;
	sum+=cnt[a[x]]*cnt[a[x]];
}
void Add(int x)
{
	sum-=cnt[a[x]]*cnt[a[x]];
	cnt[a[x]]++;
	sum+=cnt[a[x]]*cnt[a[x]];
}

int main()
{
	n=read();m=read();block=read();block=1000;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) {q[i].l=read();q[i].r=read();q[i].id=i;q[i].b=(q[i].l-1)/block+1;}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l) Delete(l++);
		while(l>q[i].l) Add(--l);
		while(r>q[i].r) Delete(r--);
		while(r<q[i].r) Add(++r);
		ans[q[i].id]=sum;
	}
	for(int i=1;i<=m;i++) print(ans[i],'\n');
	return 0;
}
