/*
 * 树dpHDU6201 每个点有收益，路上有消耗，
 * 问不定起点终点最大收益
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <set>
#include <cmath>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)
#define MP make_pair

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 100005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

inline void read(int &x) {
    x=0;
    char c;
    do {
        c= getchar();
    } while (c<'0'||c>'9');
    do {
        x = x*10+c-'0';
        c= getchar();
    } while (c>='0'&&c<='9');
}
struct Edge{
    int to, cost;
    Edge(){}
    Edge(int t, int c):to(t), cost(c){}
};
int price[maxn];
vector<Edge> g[maxn];
int dp[maxn][3];
void dfs1(int u,int f) {
    for(int i=(int)g[u].size()-1;i>=0;i--) {
        Edge &edge = g[u][i];
        if(edge.to==f) continue;
        dfs1(edge.to, u);
        int tmp = max(dp[edge.to][0],price[edge.to])-edge.cost;
        if (tmp>=dp[u][0]) {
            dp[u][1]=dp[u][0];
            dp[u][0]=tmp;
        } else if(tmp>dp[u][1]) {
            dp[u][1]=tmp;
        }
    }
}
void dfs2(int u,int f) {
    for(int i=(int)g[u].size()-1;i>=0;i--) {
        Edge &edge = g[u][i];
        if(edge.to==f) continue;
        if(dp[u][0] == dp[edge.to][0] - edge.cost || dp[u][0]==price[edge.to]-edge.cost) {
            dp[edge.to][2] = max(dp[edge.to][2],max(price[u],max(dp[u][2],dp[u][1])) - edge.cost);
        }
        else {
            dp[edge.to][2] = max(dp[edge.to][2],max(price[u], max(dp[u][2],dp[u][0])) - edge.cost);
        }
        dfs2(edge.to,u);
    }
}
int main() {
    int T,n,s,t,cost;
    read(T);
    while(T--) {
        read(n);
        for(int i=1;i<=n;i++) {
            g[i].clear();
            read(price[i]);
        }
        for(int i=1;i<n;i++) {
            read(s);
            read(t);
            read(cost);
            g[s].push_back(Edge(t,cost));
            g[t].push_back(Edge(s,cost));
        }
        memset(dp,0, sizeof(dp));
        dfs1(1,-1);
        dfs2(1,-1);
        int ans = 0;
        for(int i=1;i<=n;i++) {
            ans = max(ans,max(dp[i][0]-price[i],dp[i][2]-price[i]));
        }
        printf("%d\n",ans);
    }
    return 0;
}
