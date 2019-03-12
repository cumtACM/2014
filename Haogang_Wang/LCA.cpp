// LCA
#include <bits/stdc++.h>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 100005;
const int inf = 0x3f3f3f3f;
const int mod = 1000000007;

int n,qa,qb,a[maxn],b[maxn],cnt=0;
int dfn[maxn<<1],d[maxn<<1],dp[maxn<<1][20];
int id[maxn];
vector<int> tr[maxn];
void dfs(int x ,int dep) {
    id[x]=cnt;
    dfn[cnt]=x;
    d[cnt++]=dep;
    int si = tr[x].size();
    for(int i=0;i<si;i++) {
        int y = tr[x][i];
        if(id[y]>0) continue;
        dfs(y,dep+1);
        dfn[cnt]=x;
        d[cnt++]=dep;
    }
}
void RMQ_Init() {
    for(int i=1;i<cnt;i++)
        dp[i][0]=i;
    for(int i=1;(1<<i)<cnt;i++) {
        for(int j=1;j+(1<<i)<=cnt;j++) {
            int x = dp[j][i-1],y=dp[j+(1<<(i-1))][i-1];
            dp[j][i]=d[x]<d[y]?x:y;
        }
    }
}
int RMQ(int L,int R) {
    int k=0;
    for(;(1<<(k+1))<R-L+1;k++);
    int x = dp[L][k],y=dp[R-(1<<k)+1][k];
    return d[x]<d[y]?x:y;
}
int LCA(int x,int y) {
    int ix=id[x],iy=id[y];
    return ix<iy?RMQ(ix, iy):RMQ(iy, ix);
}
bool cmp(int x,int y) {
    return id[x]<id[y];
}
int main() {
    int u,v,m;
    while (scanf("%d %d",&n,&m)!=EOF) {
        for(int i=1;i<n;i++) {
            scanf("%d %d",&u,&v);
            tr[u].push_back(v);
            tr[v].push_back(u);
        }
        memset(id, 0, sizeof(int)*(n+1));
        cnt = 1;
        dfs(1,1);
        RMQ_Init();
        while(m--) {
            scanf("%d",&qa);
            for(int i=0;i<qa;i++)
                scanf("%d",a+i);
            scanf("%d",&qb);
            for(int i=0;i<qb;i++)
                scanf("%d",b+i);
            sort(a, a+qa, cmp);
            sort(b, b+qb, cmp);
            int ans=0;
            for(int i=0,j=0;i<qa;i++) {
                while (j+1 < qb && id[b[j]] < id[a[i]]) ++j;
                int na;
                if (j > 0)
                {
                    na = LCA(a[i], b[j-1]);
                    ans = ans<d[na]?d[na]:ans;
                }
                na = LCA(a[i], b[j]);
                ans = ans<d[na]?d[na]:ans;
            }
            printf("%d\n",ans);
        }
        for(int i=1;i<=n;i++) tr[i].clear();
    }
    return 0;
}
