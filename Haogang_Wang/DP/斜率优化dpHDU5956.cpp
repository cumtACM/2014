// 斜率优化dp HDU5956 从根出发到达一个点后选择中转消耗P，
// 不中转连续的路径消耗是总长度的平方
#include <bits/stdc++.h>
typedef long long lolo;

using namespace std;
const int maxn=100005;

template <class T>
void read(T& x) {
    x=0;
    char c;
    do {
        c=getchar();
    } while (c<'0'||c>'9');
    do {
        x=x*10+c-'0';
        c=getchar();
    } while (c>='0'&&c<='9');
}
int n;
int path[maxn];
lolo P,ans,dp[maxn],d[maxn];
struct Edge {
    int to,cost,nxt;
}edge[maxn<<1];
int head[maxn],tot;
void dfs(int u,int fa) {
    for(int i=head[u];i!=-1;i=edge[i].nxt) {
        if(edge[i].to==fa) continue;
        d[edge[i].to]=d[u]+edge[i].cost;
        dfs(edge[i].to,u);
    }
}
lolo dy(int i,int j) {
    return dp[i]-dp[j]+d[i]*d[i]-d[j]*d[j];
}
lolo dx(int i,int j) {
    return (d[i]-d[j])<<1;
}
lolo DP(int i,int j) {
    return dp[j]+(d[i]-d[j])*(d[i]-d[j])+P;
}
void DFS(int u,int fa,int s,int t) {
    while(s<t&&dy(path[s+1],path[s])<=d[u]*dx(path[s+1],path[s])) s++;
    dp[u]=min(dp[u],DP(u,path[s]));
    while(s<t&&dy(path[t],path[t-1])*dx(u,path[t])>=dy(u,path[t])*dx(path[t],path[t-1])) t--;
    int pre=path[++t];
    path[t]=u;
    ans = max(ans,dp[u]);
    for(int i=head[u];i!=-1;i=edge[i].nxt) {
        if (edge[i].to==fa) continue;
        DFS(edge[i].to,u,s,t);
    }
    if(pre!=-1) path[t]=pre;
}
void addEdge(int u,int v,int w) {
    edge[tot].to=v;
    edge[tot].cost=w;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}
int main() {
    int T,x,y,w;
    read(T);
    while(T--) {
        read(n);read(P);
        memset(head,-1, sizeof(head));
        tot=0;
        for(int i=1;i<n;i++) d[i]=path[i]=0;
        for(int i=1;i<n;i++) {
            read(x);read(y);read(w);
            addEdge(x,y,w);
            addEdge(y,x,w);
        }
        dfs(1,-1);
        for(int i=2;i<=n;i++) dp[i]=d[i]*d[i];
        path[0]=0;ans=0;
        DFS(1,0,1,0);
        printf("%lld\n",ans);
    }
    return 0;
}
