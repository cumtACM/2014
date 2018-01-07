/* UVALive7263
题意：一串数字变成另一串数字，可以单个数字转变，或者一类数字转变，问最少操作次数
分析：首先一类转换比单个转换优，先枚举找出最优的映射方案，然后将零碎的操作加上。
6位6进制表示map映射，比如123456->654321，表示map[1] = 6, map[2] = 5, map[3] = 4...
先预处理出每种方案的的操作数，用BFS+dp写，然后暴力枚举取最小值。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int,int> pii;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,b,a) for(int i=(b);i>=(a);i--)

const int maxn=1000005;
const int INF=0x3f3f3f3f;
const lolo inf=0x3f3f3f3f3f3f3f3f;
template <class T>
void read(T& x) {
    x=(T)0;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    do {
        x=(T)(x*10+c-'0');
        c=getchar();
    }while(c>='0'&&c<='9');
}
int st[666680];
int cnt;
char s2[120],s1[120];
int dist[1<<18];
int getNum(const int& x,const int& i) {
    return (x>>3*(6-i))&7;
}
void init() {
    queue<int> Q;
    int x=0;
    memset(dist,0x3f, sizeof(dist));
    for(int i=1;i<=6;i++) x=(x<<3)|i;
    Q.push(x);
    cnt=0;
    dist[x]=0;
    st[cnt++]=x;
    while(!Q.empty()) {
        int now=Q.front();Q.pop();
        for(int i=1;i<=6;i++) {  // 将当前出现的所有i变为j
            for(int j=1;j<=6;j++) {
                if(i==j) continue;
                int tmp=now;
                for(int k=0;k<6;k++) {
                    int z=(now>>(3*k))&7;
                    if(z==i)
                        tmp=tmp^(z<<(3*k))^(j<<(3*k));
                }
                if(dist[tmp]>dist[now]+1) {
                    Q.push(tmp);
                    dist[tmp]=dist[now]+1;
                    st[cnt++]=tmp;
                }
            }
        }
    }
}
int c[7];
int main() {
//    freopen("../out.txt","w",stdout);
    init();
    while(scanf("%s%s",s2,s1)!=EOF) {
        int ans=INF;
        if(strcmp(s2,s1)==0) {
            puts("0");
            continue;
        }
        for(int i=0;i<cnt;i++) {
            int now=st[i];
            for(int i=1;i<=6;i++) c[i]=getNum(now,i);
            int step=dist[now];
            if(step>=ans) break;
            for(int j=0;s1[j];j++) {
                int ord=s1[j]-'0';
                if(s2[j]!='0'+c[ord]) step++;   // 还没有变换成功的使用第一种操作。
            }
            if(step<ans) ans=step;
        }
        printf("%d\n",ans);
    }
    return 0;
}
