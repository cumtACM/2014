/*
 * 二分图匹配，预处理边集，匹配完之后分两种情况k>匹配数，那么可以直接输出匹配数*2，
 * 否则可以选取匹配数*2+min（k-匹配数，剩余没有匹配的而且有边的点），这里是因为没
 * 有匹配的点有边，连着之前匹配过的点，我们可以复用，只要保证不超过k个集合就可以了，
 */
#include <bits/stdc++.h>
#define MEM(a,b) memset((a),(b),sizeof(a))
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 3005;
const int maxp = 2000005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

bool vis[maxn];
int n;
int a[maxn],flag[maxn];
vector<int> G[maxn];
bool isprime[maxp];
bool dfs(int u) {
    vis[u]=true;
    for(int i=G[u].size()-1;i>=0;i--) {
        int &v=G[u][i];
        if(vis[v]) continue;
        vis[v]=true;
        if(!flag[v]||dfs(flag[v])) {
            flag[v]=u;
            flag[u]=v;
            return true;
        }
    }
    return false;
}
int main() {
    freopen("../in.txt","r",stdin);
    for (int i = 2; i < maxp; ++i) {
        isprime[i]=true;
    }
    for (int i = 2; i < maxp; ++i) {
        if(isprime[i]) {
            for(lolo j=1LL*i*i;j<maxp;j+=i) isprime[j]=false;
        }
    }
    int T,k;
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) {
            scanf("%d",a+i);
            G[i].clear();
            flag[i]=-1;
            for(int j=1;j<i;j++) {
                if(isprime[a[j]+a[i]]) {
                    G[i].push_back(j);
                    G[j].push_back(i);
                    flag[i]=flag[j]=0;
                }
            }
        }
        int ret=0,ans=0,cnt0=0;
        for(int i=1;i<=n;i++) {
            if(flag[i]==0) {
                memset(vis + 1, false, sizeof(bool) * n);
                if (dfs(i)) ret++;
            }
        }
        for(int i=1;i<=n;i++) {
            if(flag[i]==0) {
                cnt0++;
            }
        }
        if(k<=ret) {
            ans=k<<1;
        }
        else {
            ans = ret*2+min(k-ret,cnt0);
        }
        printf("%d\n",ans);
    }
    return 0;
}