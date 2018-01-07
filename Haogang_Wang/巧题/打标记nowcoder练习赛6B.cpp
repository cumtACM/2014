/*题目描述
给你一棵树，最开始点权为0，每次将与一个点x树上距离<=1的所有点点权+1，之后询问这些点修改后的点权和.

输入描述:
第一行两个数n和m
第二行n-1个数，第i个数fa[i + 1]表示i + 1点的父亲编号，保证fa[i + 1] < i + 1
第三行m个数，每个数x依次表示这次操作的点是x

输出描述:
输出一个数，即这m次操作的答案的hash值
如果是第i次操作，这次操作结果为ans,则这个hash值加上
i * ans
输出hash值对19260817取模的结果

mark[x]:x点被操作的次数
a[x]:x点被相邻的边影响的次数
b[x]:x点的孩子的孩子被操作的次数
sz[x]: x的孩子数+1

比如当前操作的点x，我们需要将点权和tmp算出来。首先考虑x的父亲fa[x],如果fa[x]之前被操作过mark[fa[x]]次，那么tmp += a[fa[x]]+mark[fa[x]]*2;
然后考虑x的孩子和自己，tmp += （vec[x].size()+1）*mark[x]+a[x]*2+b[x];
（（vec[x].size()+1）*mark[x]:表示x对自己和儿子的影响；a[x]*2：表示儿子对儿子和自己的影响；b[x]:表示孙子的影响）
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<long,int> pii;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,b,a) for(int i=(b);i>=(a);i--)

const int maxn=100005;
const int INF=0x3f3f3f3f;
const lolo inf=0x3f3f3f3f3f3f3f3f;
const int mod=19260817;
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

int fa[maxn];
lolo sz[maxn],tag[maxn],sontag[maxn],b[maxn];
int main() {
//    freopen("../in.txt","r",stdin);
    int n,m;
    read(n);read(m);
    sz[1]++;
    FOR(i,2,n) {
        read(fa[i]);
        sz[i]++;
        sz[fa[i]]+=sz[i];
    }
    int x;
    lolo ans=0;
    FOR(i,1,m){
        read(x);
        tag[x]++;
        lolo tmp=0;
        if(fa[x]) {    // 父亲节点会影响到自己和孩子（x）
            sontag[fa[x]]++;
            tmp=(tmp+tag[fa[x]]*2+sontag[fa[x]])%mod;
        }
        if(fa[fa[x]]) {       // x的父亲节点被其父亲节点影响，要考虑。
            int& t=fa[fa[x]];
            tmp=(tmp+tag[t])%mod;
            b[t]++;
        }
        tmp=(tmp+tag[x]*sz[x]+sontag[x]*2+b[x])%mod;   // 考虑x自己、x的孩子、x的孩子的孩子
        ans=(ans+i*tmp)%mod;
    }
    printf("%lld",ans);
    return 0;
}
