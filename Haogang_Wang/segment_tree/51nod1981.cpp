/*
最重要的优化是省去pushdown,a中存放此区间包含的元素，lazy中存放此区间内每个集合包含的元素
*/
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 10005;
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
char str[110];
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

bitset<maxn> a[1<<17|16],lazy[1<<17|16],ret;   
bitset<maxn> f[maxn];
int n,q,op,l,r,c;

void update(int o,int L,int R) {
    a[o].set(c);         // 大区间包含小区间
    if(l<=L&&r>=R) {  
        lazy[o].set(c);   // 此区间内每个集合都有c
        return;
    }
    int mid=(L+R)>>1;
    if(l<=mid) update(o<<1,L,mid);
    if(r>mid) update(o<<1|1,mid+1,R);
}
void query(int o,int L,int R) {
    if(l<=L&&R<=r) {
        ret|=a[o];      
        return;
    }
    int mid=(L+R)>>1;
    if(l<=mid) query(o<<1,L,mid);
    if(r>mid) query(o<<1|1,mid+1,R);
    ret|=lazy[o];         // 肯定不会错，这是这个区间内每个集合都包含的
}

int main() {
    f[0].set(0);
    FOR(i, 1, 10000) {
        f[i]=f[i-1];
        f[i].set(i);
    }
    read(n);
    read(q);
    int maxc=0;
    while(q--) {
        read(op);read(l);read(r);read(c);
        if(op==1) {
            update(1, 1, n);
            maxc=max(c,maxc);
        } else {
            ret.reset();
            if(c==0) {
                puts("-1");
                continue;
            }
            query(1, 1, n);
            if(ret.count()<c) {
                puts("-1");
            } else if(c<100){
                int ans=ret._Find_first();
                for (int i = 1; i < c; ++i) {
                    ans=ret._Find_next(ans);
                }
                out(ans);
                putchar('\n');
            } else {
                int ans = -1, L = (int) ret._Find_first() + c - 1, R = maxc+2, m;
                while (R >= L) {
                    m = (L + R) >> 1;
                    if ((ret & f[m]).count() < c)
                        L = m + 1;
                    else R = m - 1, ans = m;

                }
                out(ans);
                putchar('\n');
            }
        }
    }
    return 0;
}