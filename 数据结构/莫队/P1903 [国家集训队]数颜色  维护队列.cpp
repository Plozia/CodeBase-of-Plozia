#include<bits/stdc++.h>
using namespace std;

const int MAXN=133333+10,MAXA=1e6+10;
int n,m,a[MAXN],cnt[MAXA],total,ans[MAXN],cntq,cntc,size,block,ys[MAXN<<1];
struct query
{
    int l,r,id,Time;
}q[MAXN];
struct change
{
    int pos,val;
}c[MAXN];

int read()
{
    int sum=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
    return sum;
}
void print(int x,char tail=0)
{
    if(x>9) print(x/10);
    putchar(x%10+48);
    if(tail) putchar(tail);
}

bool cmp(const query &fir,const query &sec)
{
    if(ys[fir.l]^ys[sec.l]) return ys[fir.l]<ys[sec.l];
    if(ys[fir.r]^ys[sec.r]) return ys[fir.r]<ys[sec.r];
    return fir.Time<sec.Time;
}

int main()
{
    n=read();m=read();size=2000;
    for(int i=1;i<=n;++i) ys[i]=(i-1)/size+1;
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=m;++i)
    {
        char ch=getchar();
        while(ch==' '||ch=='\n'||ch=='\r') ch=getchar();
        if(ch=='Q')
        {
            q[++cntq].l=read();
            q[cntq].r=read();
            q[cntq].id=cntq;
            q[cntq].Time=cntc;
        }
        else
        {
            c[++cntc].pos=read();
            c[cntc].val=read();
        }
    }
    sort(q+1,q+cntq+1,cmp);
    int l=1,r=0,t=0;
    for(int i=1;i<=cntq;++i)
    {
        while(l<q[i].l) total-=!--cnt[a[l++]];
        while(l>q[i].l) total+=!cnt[a[--l]]++;
        while(r<q[i].r) total+=!cnt[a[++r]]++;
        while(r>q[i].r) total-=!--cnt[a[r--]];
        while(t<q[i].Time)
        {
            ++t;
            if(q[i].l<=c[t].pos&&c[t].pos<=q[i].r) total-=!--cnt[a[c[t].pos]]-!cnt[c[t].val]++;
            swap(a[c[t].pos],c[t].val);
        }
        while(t>q[i].Time)
        {
            if(q[i].l<=c[t].pos&&c[t].pos<=q[i].r) total-=!--cnt[a[c[t].pos]]-!cnt[c[t].val]++;
            swap(a[c[t].pos],c[t].val);
            --t;
        }
        ans[q[i].id]=total;
    }
    for(int i=1;i<=cntq;++i) print(ans[i],'\n');
    return 0;
}
