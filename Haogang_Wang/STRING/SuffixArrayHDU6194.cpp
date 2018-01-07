// 后缀数组 HDU6194
// 题意：给出一个字符串，问其中出现k次的子串的个数有多少个*/
/*************************************************************************
    按序枚举每一个 sa[i] ，显然有效子串的下界为
    max(0,heighti,heighti+k) 。上界为 min(height[i+1,i+k−1])
     （当 k=1 时，上界为 sa[i] 的长度）。在串长在上下界之间的所有
     sa[i] 的前缀子串都对答案贡献为 1 。
 ************************************************************************/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 100005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9+7;

inline void read(int &x) {
    x=0;
    char c;
    do {
        c= getchar();
    } while (c<'0'||c>'9');
    do {
        x = x*10+c-'0';
        c= getchar();
    } while (c>='0'&&c<='9');
}

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

    void clear() { n = 0; memset(sa, 0, sizeof(sa)); memset(s, 0, sizeof(s));}

    // m为最大字符值加1。调用之前需设置好s和n
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
        if(x>=n-1||y>=n-1) return 0;
        x = Rank[x]; y = Rank[y];
        if(x > y) swap(x, y);
        return RMQ(x+1,y+1);
    }
    lolo solve(int k) {
        lolo ans=0;
        int len1,len2;
        for(int i=1;i<=n-k+1;i++) {
            len1=k==1?n-sa[i]:RMQ(i+1,i+k-1);
            len2=0;
            if(i!=1) len2=max(len2,height[i]);
            if(i!=n-k+1) len2=max(len2,height[i+k]);
            if(len1>len2) ans+=len1-len2;
        }
        return ans;
    }
}a;
char expr[maxn];
int k;
int main() {
    int T;
    init();
    read(T);
    while(T--) {
        a.clear();
        read(k);
        scanf("%s",expr);
        a.n=(int)strlen(expr);
        for(int i=0;i<=a.n;i++) a.s[i]=expr[i]-'a'+1; a.s[a.n++]=0;
        a.build_sa(27);
        a.build_height();
        a.n--;
        a.RMQ_init(a.n);
        a.height[a.n+1]=0;
        printf("%lld\n", a.solve(k));
    }
    return 0;
}
