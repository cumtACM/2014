/*
Given a string s, we define a substring that happens 
exactly kk times as an important string, and you need 
to find out how many substrings which are important strings. 
多次出现的子字符串在后缀数组中一定是连续的
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
#include <iomanip>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 100010;
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
int len;
char s[maxn];
int Log2[maxn];
void init() {
    for(int i=2;i<maxn;i++) Log2[i]=Log2[i>>1]+1;
}
struct SuffixArray {
    int s[maxn];      // 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
    int sa[maxn];     // 后缀数组
    int Rank[maxn];   // 名次数组. rank[0]一定是n-1，即最后一个字符
    int height[maxn]; // height数组
    int h[maxn][20];
    int t[maxn], t2[maxn], c[maxn]; // 辅助数组
    int n; // 字符个数

    void clear() { n = 0; memset(t, 0, sizeof(t)); memset(t2, 0, sizeof(t2));}
    void init(char *str,int len) {
        for (int i = 0; i < len; ++i) {
            s[n++]=str[i]-'a'+1;
        }
        s[n++]=0;
    }

    // m为最大字符值加1。调用之前需设置好s和nt
    void build_sa(int m) {
        int i, *x = t, *y = t2;
        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[i] = s[i]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for(i = n-k; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
            for(i = 0; i < m; i++) c[i] = 0;
            for(i = 0; i < n; i++) c[x[y[i]]]++;
            for(i = 0; i < m; i++) c[i] += c[i-1];
            for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for(i = 1; i < n; i++)
                x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
            if(p >= n) break;
            m = p;
        }
    }

    void build_height() {
        int i, j, k = 0;
        for(i = 0; i < n; i++) Rank[sa[i]] = i;
        for(i = 0; i < n; i++) {
            if(k) k--;
            j = sa[Rank[i]-1];
            while(s[i+k] == s[j+k]) k++;
            height[Rank[i]] = h[Rank[i]][0] = k;
        }
    }

    void RMQ_init(int nn) {
        for(int i=1;i<=nn;i++) h[i][0]=height[i];
        for(int j=1;(1<<j)<=nn;j++)
            for(int i=1;i+(1<<j)-1<=nn;i++)
                h[i][j]=min(h[i][j-1],h[i+(1<<(j-1))][j-1]);
    }
    int RMQ(int L,int R) {
        int k=Log2[R-L+1];
        return min(h[L][k], h[R-(1<<k)+1][k]);
    }
    lolo solve(int k) {
        lolo ans=0;
        int x,y;
        for (int i = 1; i+k <= n; ++i) {              // 这段区间内出现了k次的最长字符串长度x，
            x = k == 1 ? n-1 - sa[i] : RMQ(i + 1, i + k - 1);         // 那么s[1-z],z<=x都出现了k次，是x个
            y = max((i == 1 ? 0 : height[i]), (i + k < n ? height[i + k] : 0));             // 但要求是准确k次，所以要去掉多于k次的。
            if (x > y) ans += x - y;
        }
        return ans;
    }
}sa;

int main() {
    int T,k;
    init();
    read(T);
    while (T--) {
        read(k);
        scanf("%s",s);
        sa.clear();
        len= (int)strlen(s);
        sa.init(s, len);
        sa.build_sa(27);
        sa.build_height();
        sa.RMQ_init(len);
        out(sa.solve(k));
        putchar('\n');
    }
    return 0;
}
