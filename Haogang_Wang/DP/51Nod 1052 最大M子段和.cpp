/*
 * 51Nod 1052 最大M子段和
 * 动态规划：
dp[i][j] ： 将序列a[1], a[2], ..., a[i] 划分为不超过j个子段的最大和。
对于状态dp[i][j], 考虑a[i]为结尾向前连续取多长。
dp[i][j] = dp[i-1][j]; 不取a[i]
dp[i][j] = max(sum[i] - sum[k] + dp[k][j-1] | 0 <= k < i); 取a[k+1], a[k+2], ..., a[i]
    = max(dp[k+1][j-1] - sum[k] | 0 <= k < i) + sum[i];

令f[i][j] = max(dp[k+1][j-1] - sum[k] | 0 <= k < i)
则 f[i][j] = max(dp[i-1][j-1] - sum[i-1, f[i-1][j])

所以dp[i][j] = max(dp[i-1][j], f[i][j] + sum[i])

ps:需要滚动数组优化空间，否则会超内存。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
const int MAXN = 5005;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const double eps = 1e-6;

lolo dp[MAXN],sum[MAXN],f[MAXN];
int a[MAXN];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int cnt=0;
    lolo ans=0;
    for(int i=1;i<=n;i++) {
        scanf("%d",a+i);
        if(a[i]>0) cnt++,ans+=a[i];
        sum[i]=sum[i-1]+a[i];
        for(int j=min(i,m);j>=1;j--) {
            f[j]=max(f[j],dp[j-1]-sum[i-1]);
            dp[j]=max(dp[j],f[j]+sum[i]);
        }
    }
    if(cnt<=m) {
        printf("%lld\n",ans);
    } else {
        printf("%lld\n",dp[m]);
    }
    return 0;
}