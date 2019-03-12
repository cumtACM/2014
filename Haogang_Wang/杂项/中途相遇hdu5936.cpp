/*
f(y,K)=(y每位上的数字的K次幂之和)
　X=f(y,K)-y。现在给定X和K，求有多少Y满足题意。

中途相遇法
　　数据范围x在[0,109],y的位数不会超过10位。
　　所以想直接对半分，先枚举前5位，记下相应的值，再枚举后5位，与前面的匹配看是否能够凑成x，最后统计答案即可。
　　将每个出现的值都记下来，排序，正反扫一遍。。过了。
　　可以预处理一些操作、运算。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
const int maxn=100005;
const int maxm=10;
lolo e[maxm];
lolo pre[maxm][maxn],suf[maxm][maxn],mis[maxm][maxm];
void init() {
    e[0]=1;
    for(int i=1;i<=9;i++) e[i]=e[i-1]*10;
    for(int i=0;i<10;i++) {
        mis[i][0]=1;
        for(int j=1;j<10;j++) mis[i][j]=mis[i][j-1]*i;
    }
    for(int i=1;i<10;i++) {
        for(int j=0;j<e[5];j++) {
            int x=j;
            pre[i][j]=suf[i][j]=0;
            while(x) {
                pre[i][j]+=mis[x%10][i];
                suf[i][j]+=mis[x%10][i];
                x/=10;
            }
            pre[i][j]-=j*e[5];
            suf[i][j]-=j;
        }
        sort(pre[i],pre[i]+e[5]);
        sort(suf[i],suf[i]+e[5]);
    }
}
int main() {
    int T;
    init();
    scanf("%d",&T);
    int cas=1;
    while(T--) {
        lolo x;
        int k;
        scanf("%lld%d",&x,&k);
        lolo ans=0;
        int i=0,j=e[5]-1;
        for(;i<e[5]&&j;) {
            if(pre[k][i]+suf[k][j]>x) j--;
            else if(pre[k][i]+suf[k][j]<x) i++;
            else {
                int px=1,py=1;
                while(pre[k][++i]==pre[k][i-1]&&i<e[5]) px++;
                while(suf[k][--j]==suf[k][j+1]&&j) py++;
                ans+=1LL*px*py;
            }
        }
        if(x==0) ans--;
        printf("Case #%d: %lld\n",cas++,ans);
    }
}
