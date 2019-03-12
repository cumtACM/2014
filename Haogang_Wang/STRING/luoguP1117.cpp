/*************************************************************************
    求字符串拆分成 AABB的方案数

    求两个数组：pre[i]与suf[i]，分别表示以i这个字符开头与以i这个字符结尾的‘AA’形式的串
    有多少个，那么答案就是∑n−1i=1pre[i+1]∗suf[i]，难点在于如何求出这两个数组：
    我们枚举一个长度L表示当前找的‘AA’型串的长度的一半，枚举i=k∗L,j=i+L,
    记x=lcp(suf(i),suf(j)), 记y=lcs(pre(i−1),pre(j−1))，
    如果x+y>=L，记t=x+y−L+1，表示我们找到了t个长度为2L的’AA‘串
    （自己可以举个例子看看，如’abcabcab‘）
    为了方便理解，假设x+y=L，那么我们恰好找到一个(i−y,j+x−1)的’AA‘串。
    但是每次有一个连续区间，我们不能一个一个加上，因为时效会出问题。所以用到差分的思想，
    在区间开始的地方加一，在区间结束的后一个位置减一，那么最后做一遍前缀和即可。
 ************************************************************************/
 #include <bits/stdc++.h>
 using namespace std;
 typedef long long lolo;

 const int maxn = 100005;

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
 }a,b;
 lolo pre[maxn],suf[maxn],ans;
 char s[maxn];
 int main() {
     init();
     int T,n;
     scanf("%d", &T);
     while(T--) {
         a.clear();b.clear();
         scanf("%s", s);
         n=(int)strlen(s);
         a.n=b.n=n+1;
         for(int i=0;i<n;i++) a.s[i]=s[i]-'a'+1, b.s[n-i-1]=a.s[i];
         a.s[n]=b.s[n]=0;
         a.build_sa(27);
         b.build_sa(27);
         a.build_height();
         b.build_height();
         a.RMQ_init(n);
         b.RMQ_init(n);
         ans=0;
         memset(pre,0,sizeof(pre));
         memset(suf,0,sizeof(suf));
         int lim=n>>1;
         for(int l=1;l<=lim;l++) {
             for(int i=l-1,j=(l<<1)-1;j<n;i+=l,j+=l) {
                 int x=min(a.LCP(i,j),l),y=min(b.LCP(n-i,n-j),l-1);
                 if(x+y<l) continue;
                 int t=x+y-l+1;
                 pre[i-y]++;pre[i-y+t]--;
                 suf[j+x-t]++;suf[j+x]--;
             }
         }
         for(int i=1;i<n;i++) {
             pre[i]+=pre[i-1];
             suf[i]+=suf[i-1];
         }
         for(int i=0;i<n;i++) ans+=pre[i+1]*suf[i];
         printf("%lld\n",ans);
     }
     return 0;
 }
