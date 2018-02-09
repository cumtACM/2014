#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 200010;
const int maxm = 100005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int MOD = 1000000007;

int n,m;
long double p[8][200],ans;
long double dp[70][200];      // 使用状态压缩，dp[i][j]表示使用j分钟达到状态i数学期望
int main() {
    ios::sync_with_stdio(false);
    cin>>n>>m;
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            cin>>p[i][j];
        }
    }
    ans=0;
    for (int i = 1; i < (1<<n); ++i) {
        for (int j = 0; j < n; ++j) {
            if(i&(1<<j)) {
                for (int k = 1; k <=m ; ++k) {
                    long double tmp=0;
                    for (int l = 1; l <= k; ++l) {
                        tmp+=(1+dp[i^(1<<j)][k-l])*p[j+1][l];   // 考虑所有使用l分钟完成j的情况
                    }
                    dp[i][k] = max(dp[i][k],tmp);
                    ans = max(dp[i][k],ans);
                }
            }
        }
    }
    cout<<fixed<< setprecision(5)<<ans<<endl;
    return 0;
}
