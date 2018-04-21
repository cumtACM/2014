// 最小割最小边dinic版本 HDU6217
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 210
#define inf 1ll<<60
#define mod 100001
#define maxm 2100
int n,m;
int level[maxn],que[maxn];
int head[maxn],lon;
long long min(long long a,long long b) {
    if(a<b) return a;
    else return b;
}
struct EDGE {
    int next,to;
    long long c;
}e[maxm];
void edgeinit() {
    memset(head,-1,sizeof(head));
    lon=-1;
}
void edgemake(int from,int to,long long c) {
    e[++lon].c=c;
    e[lon].to=to;
    e[lon].next=head[from];
    head[from]=lon;
}
void make(int from,int to,long long c) {
    edgemake(from,to,c);
    edgemake(to,from,0);
}

bool makelevel(int s,int t) {
    memset(level,0,sizeof(level));
    int FRONT=1,End=0;
    que[++End]=s;
    level[s]=1;
    while(FRONT<=End) {
        int u=que[FRONT++];
        if(u==t) return true;
        for(int k=head[u];k!=-1;k=e[k].next) {
            int v=e[k].to;
            if(!level[v]&&e[k].c) {
                que[++End]=v;
                level[v]=level[u]+1;
            }
        }
    }
    return false;
}

long long dfs(int now,int t,long long maxf) {
    if(now==t||maxf==0) return maxf;
    long long ret=0;
    for(int k=head[now];k!=-1;k=e[k].next) {
        int u=e[k].to;
        if(level[u]==level[now]+1&&e[k].c) {
            long long f=dfs(u,t,min(e[k].c,maxf-ret));
            e[k].c-=f;
            e[k^1].c+=f;
            ret+=f;
            if(ret==maxf) return ret;
        }
    }
    if(ret==0) level[now]=0;
    return ret;
}

long long maxflow(int s,int t) {
    long long ret=0;
    while(makelevel(s,t)) {
        ret+=dfs(s,t,inf);
    }
    return ret;
}

int main() {
    int cas;
    int sum=0;
    scanf("%d",&cas);
    while(cas--) {
        sum++;
        int i,j;
        int u,v,flag;
        long long w;
        scanf("%d%d",&n,&m);
        int ss, tt;
        scanf("%d%d", &ss, &tt);
        edgeinit();
        for(i=1;i<=m;i++) {
            scanf("%d%d%lld",&u,&v,&w);
            make(u,v,w*mod+1);
        }
        printf("%lld\n",maxflow(ss,tt)%mod);
    }
}
