#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=5e4+10;
int n,m,a[MAXN],block,ys[MAXN<<1],size;
LL cnt[MAXN],ans1[MAXN],ans2[MAXN],total;
struct node
{
	int l,r,b,id;
}q[MAXN];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}

bool cmp(const node &fir,const node &sec)
{
	if(fir.b!=sec.b) return fir.b<sec.b;
	if(fir.b&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

void del(int x)
{
	total-=cnt[a[x]]*cnt[a[x]];
	cnt[a[x]]--;
	total+=cnt[a[x]]*cnt[a[x]];
}
void add(int x)
{
	total-=cnt[a[x]]*cnt[a[x]];
	cnt[a[x]]++;
	total+=cnt[a[x]]*cnt[a[x]];
}

LL gcd(LL a,LL b) {return (b==0)?a:gcd(b,a%b);}

int main()
{
	n=read();m=read();size=sqrt(n);block=ceil((double)n/size);
	for(int i=1;i<=block;i++)
		for(int j=(i-1)*size+1;j<=i*size;j++)
			ys[j]=i;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) {q[i].l=read();q[i].r=read();q[i].id=i;q[i].b=ys[q[i].l];}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		if(q[i].l==q[i].r)
		{
			ans1[q[i].id]=0;ans2[q[i].id]=1;
			continue;
		}
		while(l<q[i].l) del(l++);
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		LL len=(LL)(q[i].r-q[i].l+1)*(q[i].r-q[i].l);
		ans1[q[i].id]=(total-(q[i].r-q[i].l+1))/gcd(total-(q[i].r-q[i].l+1),len);
		ans2[q[i].id]=len/gcd(total-(q[i].r-q[i].l+1),len);
	}
	for(int i=1;i<=m;i++) printf("%d/%d\n",ans1[i],ans2[i]);
	return 0;
}
