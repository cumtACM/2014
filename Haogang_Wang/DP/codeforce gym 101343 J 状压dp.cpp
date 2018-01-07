// 状态压缩DP CF gym101343J
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 10005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

inline void read(int &x) {
    x = 0;
    int flag=1;
    char c;
    do {
        c = getchar();
        if(c=='-') break;
    } while (c < '0' || c > '9');
    if(c=='-')
        c='0',flag=-1;
    do {
        x = x * 10 + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    x*=flag;
}
int a[20][1005],vis[20],cnt,num[20][20],dp[(1<<16)][20];
int main(){
    int n,i,j,k,l;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i][0]);
        for(j=1;j<=a[i][0];j++)
            read(a[i][j]);
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j||vis[j]||vis[i]) continue;
            if(a[i][0]<a[j][0]) continue;
            for(k=1;k<=a[i][0];k++){
                if(a[i][0]-k+1<a[j][0]) continue;
                if(memcmp(a[i]+k,a[j]+1, sizeof(int)*a[j][0])==0) {
                    vis[j]=1;
                }
            }
        }
    }
    for(i=1;i<=n;i++){
        if(vis[i]) continue;
        cnt++;
        memcpy(a[cnt],a[i], sizeof(int)*(a[i][0]+1));
    }
    n=cnt;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j)continue;
            for(k=1;k<=a[i][0];k++){
                if(k>=a[j][0]) break;
                if(memcmp(a[i]+(a[i][0]-k+1),a[j]+1,k* sizeof(int))==0) {
                    num[i][j]=k;
                }
            }
        }
    }
    memset(dp,INF,sizeof(dp));
    for(i=1;i<=n;i++) dp[(1<<(i-1))][i]=a[i][0];
    int tot=(1<<n)-1;
    for(i=1;i<=tot;i++){
        for(j=1;j<=n;j++){
            if(!((1<<(j-1))&i)) continue;
            for(k=1;k<=n;k++){
                if((1<<(k-1))&i) continue;
                dp[i|(1<<(k-1))][k]=min(dp[i|(1<<(k-1))][k],dp[i][j]+a[k][0]-num[j][k]);
            }
        }
    }
    int ans=INF;
    for(i=1;i<=n;i++)
        ans=min(ans,dp[(1<<n)-1][i]);
    printf("%d\n",ans);
    return 0;
}
