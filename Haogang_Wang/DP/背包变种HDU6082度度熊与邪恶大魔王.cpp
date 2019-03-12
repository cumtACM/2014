/*
 * 背包变种hdu6082
*/
#include <bits/stdc++.h>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

using namespace std;


typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 100005;
const int inf = 0x3f3f3f3f;
const long long mod = 1e9 + 7;

struct Skill {
    int c,a;
    double pr;

}skills[1003],skill;

int hp[maxn],df[maxn];
lolo dp[1005][12];
int main() {
    int n,m;
    while(scanf("%d %d",&n,&m)==2) {
        memset(dp,inf,sizeof(dp));
        lolo ans=0LL;
        int maxdf=0,maxa=0,maxhp=0;
        for(int i=0;i<n;i++) {
            scanf("%d %d",hp+i,df+i);
            maxdf=MAX(maxdf,df[i]);
            maxhp=MAX(maxhp,hp[i]);
        }
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=0;i<m;i++) {
            scanf("%d %d",&skills[i].c,&skills[i].a);
            maxa=MAX(skills[i].a,maxa);
            for(int d=0;d<=maxdf;d++) {
                int tmp=skills[i].a-d;
                if(tmp<=0) break;
                for(int k=0;k<tmp;k++) {
                    dp[k][d]=min(dp[k][d],(lolo)skills[i].c);  // 残血也要攻击
                }
                for(int k=tmp;k<=maxhp;k++) {
                    dp[k][d]=min(dp[k][d],dp[k-tmp][d]+skills[i].c);   // 从前往后，每个技能可用多次
                }
            }
        }
        if(maxa<=maxdf) {
            printf("-1\n");
            continue;
        }
        for(int i=0;i<n;i++) {
            ans+=dp[hp[i]][df[i]];
        }
        cout<<ans<<endl;
    }
    return 0;
}

/*完全背包*/
