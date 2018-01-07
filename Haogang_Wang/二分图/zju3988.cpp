/*
 选择不多于k对数{i,j|a[i]+a[j]是素数}，使被选的数最多。
 暴力所有二元组{i, j}
如果{i, j}是个Pset，并且a[i]!=1 || a[j]!=1，那么i到j连一条无向边
这个时候得出的图很显然是二分图
为什么呢？因为质数一定是个奇数（除了2，不过a[i]!=1 || a[j]!=1所以不会出现2这种情况），而奇数=奇数+偶数
这样的话每条边的两端一定是个奇数和一个偶数，把所有奇数的点放在左边，偶数放在右边，得证
到这里问题就好办了，贪心就好了
求出二分图的最大匹配，最大匹配中的每个Pset都会对答案贡献2，除此之外剩下所有没有用的1，
两两配对对答案贡献也是2（不过注意一个细节：例如样例1 1 4 13，如果1和4匹配上了就错了！所以二分匹配时一定要让1最后匹配），
贡献为2的Pset处理完了，剩下的贡献一定只能为1了，加上就是答案
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

bool vis[maxn],val[maxn];
int n;
int a[maxn],flag[maxn];
vector<int> G[maxn];
bool isprime[maxp];
bool dfs(int u) {
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
//    freopen("../in.txt","r",stdin);
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
        int cnt0=0;
        for(int i=1;i<=n;i++) {
            scanf("%d",a+i);
            G[i].clear();
            flag[i]=0;
            val[i]=false;
            if(a[i]==1) {
                cnt0++;
            }
            for(int j=1;j<i;j++) {
                if(isprime[a[j]+a[i]]) {
                    val[i]=true;
                    val[j]=true;
                    if((a[i]&1)&&a[j]!=1)
                        G[i].push_back(j);
                    else if (a[i]!=1)
                        G[j].push_back(i);
                }
            }
        }
        int ret=0,ans=0;
        for(int i=1;i<=n;i++) {
            if(a[i]!=1) {
                memset(vis+1,false, sizeof(bool)*n);     // 先让非1的匹配
                if(dfs(i)) ret++;
            }
        }
        for(int i=1;i<=n;i++) {
            if(a[i]==1) {
                memset(vis+1,false, sizeof(bool)*n);     // 用1来匹配
                if(dfs(i)) ret++;
            }
        }
        for(int i=1;i<=n;i++) {
            if(a[flag[i]]==1) {
                cnt0--;
            }
        }
        if(k<=ret) {
            ans=k<<1;
        }
        else {
            ans = ret << 1;
            k -= ret;
            if ((k << 1) <= cnt0) ans += (k << 1);
            else {
                ans += (cnt0 >> 1) << 1;          // 1和1匹配
                k -= cnt0 >> 1;
                cnt0&=1;
                for (int i = 1; i <= n && k > 0; i++) {
                    if (a[i] == 1) {
                        if (flag[i] == 0 && val[i] && cnt0) {    // 选择没有匹配但是可以和已选的匹配的数
                            cnt0 = 0;
                            ans++, k--;
                        }
                    } else if (flag[i] == 0 && val[i]) {
                        ans++;
                        k--;
                    }
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}