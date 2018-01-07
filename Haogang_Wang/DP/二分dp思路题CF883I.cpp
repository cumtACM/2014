/*
 * 将一个序列分成任意个部分，使所有部分的最大最小值差中的最大值最小。
 */
#include <bits/stdc++.h>
typedef long long lolo;

using namespace std;

const int INF=0x3f3f3f3f;
template <class T>
void read(T& x) {
    x=0;
    char c;
    do {
        c=getchar();
    } while (c<'0'||c>'9');
    do {
        x=x*10+c-'0';
        c=getchar();
    } while (c>='0'&&c<='9');
}
const int maxn=300005;

int a[maxn],n,k;
int dp[maxn];
void read(int& x) {
    x=0;
    char c;
    do {
        c=getchar();
    } while (c<'0'||c>'9');
    do {
        x=x*10+c-'0';
        c=getchar();
    } while(c>='0'&&c<='9');
}
int b[maxn];   // b[i]中记录到i为止，能够满足情况的最长前缀的长度
bool check(int x) {
    int t=0;
    for(int i=k;i<=n;i++) {
        if(a[i]-a[b[i-k]+1]<=x)
            t=i;
        b[i]=t;
    }
    return b[n]==n;
}
int main() {
    read(n);read(k);
    for(int i=1;i<=n;i++) read(a[i]);
    a[n+1]=a[n+2]=INF;
    sort(a+1,a+n+1);
    int k2=min(n,(k<<1)-1);
    for(int i=k;i<=k2;i++)
        dp[i]=a[i]-a[1];
    dp[k2+1]=min(max(dp[k],a[k2]-a[k+1]),a[k2]-a[1]);
    if(k==1) {
        puts("0");
        return 0;
    }
    if(n<=(k<<1)) {
        printf("%d\n",dp[n]);
        return 0;
    }
    int L=0,R=a[n]-a[1],M;
    while(L<R) {
        M=L+((R-L)>>1);
        if(check(M)) R=M;else L=M+1;
    }
    printf("%d\n",R);
    return 0;
}
