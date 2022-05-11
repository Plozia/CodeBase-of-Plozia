#include<bits/stdc++.h>
using namespace std;

const int MAXN=4e5+10;
int n,m,cnt[MAXN],eular[MAXN<<1],cnte,ans[MAXN],total,ys[MAXN<<1],block,fa[MAXN][21],dep[MAXN],a[MAXN],fir[MAXN],las[MAXN],vis[MAXN],b[MAXN],lastn;
struct node
{
	int l,r,id,lca;
}q[MAXN];
vector<int>Next[MAXN];

int read()
{
	int sum=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum;
}

void dfs(int x)
{
	eular[++cnte]=x;
	fir[x]=cnte;
	for(int i=0;i<Next[x].size();i++)
	{
		int u=Next[x][i];
		if(dep[u]) continue;
		dep[u]=dep[x]+1;
		fa[u][0]=x;
		dfs(u);
	}
	eular[++cnte]=x;
	las[x]=cnte;
}

void st()
{
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1];
}


int getlca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=20;j>=0;j--) if(dep[x]>=dep[y]) x=fa[x][j];
	if(x==y) return x;
	for(int j=20;j>=0;j--) if(fa[x][j]!=fa[y][j]) x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}

bool cmp(const node &fir,const node &sec)
{
	if(ys[fir.l]^ys[sec.l]) return ys[fir.l]<ys[sec.l];
	if(ys[fir.l]&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

void del(int x)
{
	int t=lower_bound(b+1,b+lastn+1,a[x])-b-1;
	total-=!--cnt[t];
}
void add(int x)
{
	int t=lower_bound(b+1,b+lastn+1,a[x])-b-1;
	total+=!cnt[t]++;
}
void work(int pos)
{
	vis[pos]?del(pos):add(pos);vis[pos]^=1;
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) b[i]=a[i]=read();
	sort(b+1,b+n+1);
	lastn=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		Next[x].push_back(y);
		Next[y].push_back(x);
	}
	fa[1][0]=1;dep[1]=1;dfs(1);st();
	block=ceil(sqrt(cnte));
	for(int i=1;i<=(n<<1);i++) ys[i]=(i-1)/block+1;
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),lca=getlca(x,y);q[i].id=i;
		if(fir[x]>fir[y]) swap(x,y);
		if(fir[x]==lca) q[i].l=fir[x],q[i].r=fir[y];
		else q[i].l=las[x],q[i].r=fir[y],q[i].lca=lca;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l) work(eular[l++]);
		while(l>q[i].l) work(eular[--l]);
		while(r<q[i].r) work(eular[++r]);
		while(r>q[i].r) work(eular[r--]);
		if(q[i].lca) work(q[i].lca);
		ans[q[i].id]=total;
		if(q[i].lca) work(q[i].lca);
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
