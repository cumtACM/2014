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
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}
#define lowbit(x) ((x)&(-(x)))
struct Node {
    int x,y,t;
};
bool cmp1(const Node& a,const Node& b) {
    return a.x>b.x;
}
bool cmp2(const Node& a,const Node& b) {
    return a.y>b.y;
}
int a[maxn],n,m,b[maxn],pos[maxn],ca[maxm],dd[maxm];
Node tmp[maxm];
lolo ans;
int C[maxn];
int sum(int x) {
    int ret=0;
    while (x) {
        ret+=C[x];
        x-= lowbit(x);
    }
    return ret;
}
void add(int x,int d) {
    while (x<=n) {
        C[x]+=d;
        x+= lowbit(x);
    }
}
void process(int L,int R);
void solve(int L,int R) {
    if(L==R) return;
    int M=L+R>>1;
    solve(L, M);
    FOR(i, L, R) {
        tmp[i]=(Node){ca[i],pos[ca[i]],i};
    }
    process(L, R);  // 计算之前的操作的影响
    solve(M+1, R);
}
void process(int L,int R) {
    int M=L+R>>1;
    sort(tmp+L, tmp+R+1, cmp1);   // 按照被删除的数的大小降序排序
    FOR(i,L,R) {
        if(tmp[i].t<=M) {
            add(tmp[i].y, 1);     // 记录被删除的数的位置
        } else dd[tmp[i].t] += sum(tmp[i].y-1);  //  在它被删除之前被删除的在它前方的比它大的数
    }
    FOR(i, L, R) {
        if(tmp[i].t<=M) add(tmp[i].y, -1);
    }
    sort(tmp+L, tmp+R+1, cmp2);  // 按照被删除的数的位置降序排序
    FOR(i, L, R) {
        if(tmp[i].t<=M) {
            add(tmp[i].x, 1);    // 记录被删除的数
        } else dd[tmp[i].t] += sum(tmp[i].x-1);  // 在它被删除之前被删除的在它后方的比它小的数
    }
    FOR(i, L, R) {
        if(tmp[i].t<=M) add(tmp[i].x, -1);
    }
}
int main() {
    while (scanf("%d",&n)!=EOF) {
        read(m);
        ans=0;
        memset(C+1, 0, sizeof(int)*n);
        FOR(i, 1, n) {
            read(a[i]);
            pos[a[i]]=i;
            ans += (b[i] = i-1-sum(a[i]-1));// b[i]是左边的比a[i]大的数(i-1-sum(a[i]-1)
            b[i]+=a[i]-i+b[i];              //和右边的比a[i]小的数(a[i]-1-sum(a[i]-1))的数量
            add(a[i], 1);
        }
        memset(C+1, 0, sizeof(int)*n);
        memset(dd+1, 0, sizeof(int)*m);
        FOR(i, 1, m) {
            read(ca[i]);
        }
        solve(1, m);
        FOR(i, 1, m) {
            out(ans);
            putchar('\n');
            ans-=b[pos[ca[i]]]-dd[i];  // dd[i]是在i之前被删除的数造成的前方较大数减小和后方较小数减小量
        }
    }
    return 0;
}
