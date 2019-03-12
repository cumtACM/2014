/*
 判断删除一个点后，图是不是二分图。
 并查集判断图是否存在奇环，核心在于每个节点要维护他到当前并查集根的距离的
 奇偶性，由于本题需要回溯（并查集需要复原），因此不使用路径压缩写起来会方
 便些。每次回溯的时候，只需要提前记录当前合并了哪些节点，把产生的影响倒着
 复原即可。 
 对于本题来说，由于要求删去每个点之后图是否存在奇环，其实删去a之后的图和
 删去b之后的图有很多条边都不受影响。这告诉我们可以分治。solve(l,r)代表
 算出l−r的答案,我们可以考虑当前的边集，对于那些两端都不在l−mid的边，那
 显然必然存在于mid+1−r的图中，因此可以把这些边直接作用在并查集上，对于剩下
 的边我们可以直接存在l−mid中.后半段也类似考虑。对于这种类型的分治，可以采
 用与线段树相似的模型去思考。
*/
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

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 501010;
const int maxm = 200005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
char str[1100];
string scf() {
    scanf("%s",str);
    return str;
}
template<class T>
inline void out(T x) {
    if(x>9) out(x/10);
    x=x%10;
    putchar('0'+x);
}
int pa[maxn],rk[maxn],dpt[maxn];
vector<pii> edge[maxn<<2];
bool ans[maxn];
pii findset(int x) {
    int d=0;
    while(pa[x]!=x) {
        d^=dpt[x];
        x=pa[x];
    }
    d^=dpt[x];
    return make_pair(x, d);
}
void process(int o,int L,int R,vector<pii>& vec);
void solve(int o,int L,int R) {
    if(L==R) {
        ans[L]=true;
        return;
    }
    int M=L+R>>1,lson=o<<1,rson=o<<1|1;
    edge[lson].clear();
    edge[rson].clear();
    vector<pii> tmp[2];
    for (int i = 0; i < edge[o].size(); ++i) {
        pii& p=edge[o][i];
        if(IN(p.first, L, M)|| IN(p.second, L, M)) edge[lson].push_back(p);    // 有关联的边直接放在这个区间上
        else tmp[0].push_back(p);                                 // 无关联的边之后先处理
        if(IN(p.first, M+1, R)|| IN(p.second, M+1, R)) edge[rson].push_back(p);
        else tmp[1].push_back(p);
    }
    process(lson, L, M, tmp[0]);
    process(rson, M+1, R, tmp[1]);
}
void process(int o,int L,int R,vector<pii>& vec) {
    vector<pair<int*,int> > sta;
    bool flag=true;
    for (int i = 0; i < vec.size(); ++i) {           // 判断是不是没有关联的边就会形成奇环
        int &x=vec[i].first,&y=vec[i].second;
        pii fx = findset(x),fy = findset(y);
        if(fx.first==fy.first) {
            if(!(fx.second^fy.second)) {             // 形成了奇环，这个区间内的点删了也不会影响到，所以无法形成二分图
                flag=false;
                break;
            }
        } else {
            if(rk[fx.first]<rk[fy.first]) swap(fx, fy);
            if(rk[fx.first]==rk[fy.first]) {
                sta.push_back(make_pair(rk+fx.first, rk[fx.first]));
                rk[fx.first]++;
            }
            sta.push_back(make_pair(pa+fy.first, pa[fy.first]));
            sta.push_back(make_pair(dpt+fy.first, dpt[fy.first]));
            pa[fy.first]=fx.first;
            dpt[fy.first]^=(fx.second^fy.second);
        }
    }
    if(!flag) {
        fill(ans+L, ans+R+1, false);
    } else solve(o, L, R);
    IFOR(i, sta.size()-1, 0) {
        pair<int*,int> pi=sta[i];
        *pi.first=pi.second;
    }
}
int main() {
    int n,m,T,a,b;
    read(T);
    while(T--) {
        read(n);
        FOR(j, 1, n) {
            pa[j]=j;
            rk[j]=1;
            dpt[j]=1;        // 表示距离根节点距离为偶数
        }
        read(m);
        edge[1].clear();
        while(m--) {
            read(a);
            read(b);
            edge[1].push_back(make_pair(a, b));
        }
        solve(1, 1, n);
        FOR(j, 1, n) putchar(ans[j]?'1':'0');
        putchar('\n');
    }
    return 0;
}