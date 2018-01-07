#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <set>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 100005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps=1e-8;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
int A[maxn],n,dp[maxn][2],ans;  // dp[u][0]、dp[u][1]分别表示以u为起点，差为0的等差数列长度-1的最大和次大值
vector<int> G[maxn]; 
map<int,int> ds[maxn];  // ds[u][d]表示以u为起点差为d的等差数列长度-1
void dfs(int u, int fa) {
    int sz=G[u].size();
    FOR(i, 0, sz-1) {
        int& v=G[u][i];
        if(v==fa) continue;
        dfs(v, u);
        int d=A[u]-A[v];
        if(d) {
            if(!ds[u].count(d)) {
                ds[u][d]=1;
            }
            if(ds[v].count(d)) {
                ds[u][d]=max(ds[u][d],ds[v][d]+1);
            }
        } else {
            if(dp[u][0]<dp[v][0]+1) {
                dp[u][1]=dp[u][0];
                dp[u][0]=dp[v][0]+1;
            } else if(dp[u][1]<dp[v][0]+1) {
                dp[u][1]=dp[v][0]+1;
            }
        }
    }
    for(map<int,int>::iterator it=ds[u].begin();it!=ds[u].end();it++) {
        if(ds[u].count(-it->first)) {
            ans=max(ans,it->second+ds[u][-it->first]);  // 跨过根u，差为it->first的等差数列
        }
        ans= max(ans, it->second);
    }
    ans=max(ans,dp[u][0]+dp[u][1]);   // 跨过根u，差为0的等差数列
}
int main() {
    read(n);
    int x,y;
    FOR(j, 1, n) read(A[j]);
    FOR(j, 2, n) {
        read(x);
        read(y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,-1);
    printf("%d\n",ans+1);
    return 0;
}