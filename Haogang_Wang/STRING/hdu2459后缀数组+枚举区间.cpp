/*http://blog.csdn.net/wdcjdtc/article/details/38961275
The repetition number of a string is defined as the maximum 
number R such that the string can be partitioned into R same 
consecutive substrings. For example, the repetition number 
of "ababab" is 3 and "ababa" is 1.
Given a string containing lowercase letters, you are to find 
a substring of it with maximum repetition number.
LCP(i,i+L)/L+1就是子串s[i~i+L-1]的连续重复次数，画图演算可知。
*/
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <unordered_map>
#include <set>
#include <ctime>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 100005;
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
    int LCP(int x, int y){
        if(y>=n-1||x>=n-1) return 0;
        x = Rank[x]; y = Rank[y];
        if(x > y) swap(x, y);
        return RMQ(x+1,y);
    }
    void solve() {
        int ans=1;
        vector<int> ansv;
        for (int L=1;L<=len;L++) {
            for (int i=0;i+L<len;i+=L) {   // 枚举区间开始处
                if(s[i]!=s[i+L]) continue;
                int k= LCP(i, i+L);
                int tmp = i-(L-k%L);    // 往左偏移  
                int num=k/L+1;
                if(tmp>=0&&k%i&& LCP(tmp, tmp+L)>=k) num++;    // 还要加上左边的一个
                if(num > ans) {
                    ans=num;
                    ansv.clear();
                    ansv.push_back(L);
                } else if(num==ans) ansv.push_back(L);
            }
        }
        int sz = (int)ansv.size();
        int a,b;
        for (a = 0; a < len; ++a) {     // 后缀数组天然字典序
            for (b = 0; b < sz; ++b) {
                if(LCP(sa[a], sa[a]+ansv[b])>=ansv[b]*(ans-1)) break;
            }
            if(b<sz) break;
        }
        for (int j = 0; j < ans*ansv[b]; ++j) {
            putchar(s[sa[a]+j]+'a'-1);
        }
        putchar('\n');
    }
}sa;
int main() {
    int cas=0;
    init();
    while(scanf("%s",s)!=EOF&&s[0]!='#') {
        sa.clear();
        len= (int)strlen(s);
        sa.init(s, len);
        sa.build_sa(27);
        sa.build_height();
        sa.RMQ_init(sa.n-1);
        printf("Case %d: ",++cas);
        sa.solve();
    }
    return 0;
}
