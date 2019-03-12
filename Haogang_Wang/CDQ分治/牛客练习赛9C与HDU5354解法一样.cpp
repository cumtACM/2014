/*
求删除哪些边以后图是二分图
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

const int maxn = 1001010;
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
pii edge[maxn];
int acnt;
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
void process(int o,int L,int R,int OL,int OR);
void solve(int o,int L,int R) {
    if(L==R) {
        ans[L]=true;
        acnt++;
        return;
    }
    int M=L+R>>1,lson=o<<1,rson=o<<1|1;
    process(lson, L, M, M+1,R);
    process(rson, M+1, R, L, M);
}
void process(int o,int L,int R,int OL,int OR) {
    vector<pair<int*,int> > sta;
    bool flag=true;
    for (int i = OL; i <=OR; ++i) {
        int &x=edge[i].first,&y=edge[i].second;
        pii fx = findset(x),fy = findset(y);
        if(fx.first==fy.first) {
            if(!(fx.second^fy.second)) {
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
    int n, m, T, a, b;
    read(n);
    FOR(j, 1, n) {
        pa[j] = j;
        rk[j] = 1;
        dpt[j] = 1;
    }
    read(m);
    FOR(j, 1, m) {
        read(edge[j].first);
        read(edge[j].second);
    }
    solve(1, 1, m);
    out(acnt);
    if(acnt) {
        putchar('\n');
        bool sp = false;
        FOR(j, 1, m) {
            if (ans[j]) {
                if (sp) putchar(' ');
                else sp = true;
                out(j);
                if (--acnt == 0) break;
            }
        }
        putchar('\n');
    }
    return 0;
}