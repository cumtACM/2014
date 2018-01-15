#include <iostream>
#include <cstdio>
#include <cstring>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 400010;
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
char s[maxn];
int n;
int lsth(char *s){
    int ans=1;
    for(int i=0;i<n;i++){
        int h=i,t=i;
        while(s[t+1]==s[h]) t++;
        i=t;
        while(h>0&&s[h-1]==s[t+1]){
            h--;
            t++;
        }
        ans=max(ans,t-h+1);
    }
    return ans;
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

    void clear() {
        n = 0;
        memset(t, 0, sizeof(t));
        memset(t2, 0, sizeof(t2));
    }

    // m为最大字符值加1。调用之前需设置好s和nt
    void build_sa(int m) {
        int i, *x = t, *y = t2;
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[x[i] = s[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (i = n - k; i < n; i++) y[p++] = i;
            for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
            for (i = 0; i < m; i++) c[i] = 0;
            for (i = 0; i < n; i++) c[x[y[i]]]++;
            for (i = 0; i < m; i++) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++)
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            if (p >= n) break;
            m = p;
        }
    }

    void build_height() {
        int i, j, k = 0;
        for (i = 0; i < n; i++) Rank[sa[i]] = i;
        for (i = 0; i < n; i++) {
            if (k) k--;
            j = sa[Rank[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            height[Rank[i]] = h[Rank[i]][0] = k;
        }
    }

    void RMQ_init(int nn) {
        for (int i = 1; i <= nn; i++) h[i][0] = height[i];
        for (int j = 1; (1 << j) <= nn; j++)
            for (int i = 1; i + (1 << j) - 1 <= nn; i++)
                h[i][j] = min(h[i][j - 1], h[i + (1 << (j - 1))][j - 1]);
    }

    int RMQ(int L, int R) {
        int k = Log2[R - L + 1];
        return min(h[L][k], h[R - (1 << k) + 1][k]);
    }

    int LCP(int x, int y) {
        if (y >= n - 1 || x >= n - 1) return 0;
        x = Rank[x];
        y = Rank[y];
        if (x > y) swap(x, y);
        return RMQ(x + 1, y);
    }

    void Add(int x) {
        s[n++] = x;
    }
}sa;

int main() {
    init();
    sa.clear();
    read(n);
    int n2 = n << 1, n3 = n * 3, n4 = n << 2;
    scanf("%s", s);
    int ans = lsth(s);
    FOR(j, 0, n - 1) {
        sa.Add(s[j] - 'A' + 1);
    }
    sa.Add(27);
    IFOR(i, n - 1, 0) {
        sa.Add(s[i] - 'A' + 1);   // 倒过来放，用后缀数组求回文串
    }
    sa.Add(28);
    scanf("%s", s);
    ans = max(ans, lsth(s));
    FOR(i, 0, n - 1) {
        sa.Add(s[i] - 'A' + 1);
    }
    sa.Add(29);
    IFOR(i, n - 1, 0) {
        sa.Add(s[i] - 'A' + 1);
    }
    sa.Add(0);
    sa.build_sa(30);
    sa.build_height();
    sa.RMQ_init(4 * n + 3);
    for (int i = 0; i < n; ++i) {                       // 以A中字符为中心
        int ji = sa.LCP(i + 1, n2 - i + 1) << 1 | 1;     // UvU形式
        int L = i - ji / 2 - 1, R = i + ji / 2;
        if (L >= 0 && R < n) ans = max(ans, ji + 2 * sa.LCP(n2 - L, n2 + 2 + R));
        int ou = sa.LCP(i, n2 - i + 1) << 1;             // UU形式
        L = i - ou / 2 - 1, R = i + ou / 2 - 1;
        if (L >= 0 && R < n) ans = max(ans, ou + 2 * sa.LCP(n2 - L, n2 + 2 + R));
    }
    for (int i = 0; i < n; ++i) {                      // 以B中字符为中心
        int ji = sa.LCP(n2 + 2 + i + 1, n4 + 2 - i + 1) << 1 | 1;
        int L = i - ji / 2, R = i + ji / 2 + 1;
        if (L >= 0 && R < n) ans = max(ans, ji + 2 * sa.LCP(n2 - L, n2 + 2 + R));
        int ou = sa.LCP(n2 + 2 + i, n4 + 2 - i + 1) << 1;
        L = i - ou / 2, R = i + ou / 2;
        if (L >= 0 && R < n) ans = max(ans, ou + 2 * sa.LCP(n2 - L, n2 + 2 + R));
    }
    out(ans);
    return 0;
}

// 别人的马拉车代码
// #include <bits/stdc++.h>
// using namespace std;
// #ifdef osayes
// #include "header.cpp"
// #endif
// char s1[212345], s2[212345];
// int len1[212345], len2[212345];
// void manacher(char s[], int n, int len[]) {
//     len[0] = 1;
//     int right_side = 0, center = 0;
//     for (int i = 1; i < n; i++) {
//         if (right_side <= i) {
//             len[i] = 1;
//             for (int j = i + 1; j < n && 2 * i - j >= 0 && s[2 * i - j] == s[j]; j++) {
//                 len[i] += 2;
//             }
//             right_side = i + len[i] / 2;
//             center = i;
//         } else {
//             len[i] = min(len[2 * center - i], 2 * (right_side - i) + 1);
//             if (len[2 * center - i] >= 2 * (right_side - i) + 1) {
//                 for (int j = right_side + 1; j < n && 2 * i - j >= 0 && s[2 * i - j] == s[j]; j++) {
//                     len[i] += 2;
//                 }
//                 right_side = i + len[i] / 2;
//                 center = i;
//             }
//         }
//     }
// }
// const unsigned int key = 19;
// struct string_hash {
//     unsigned long long h[212345], pow_key[212345];
//     void init(char s[], int n) {
//         h[0] = s[0];
//         pow_key[0] = 1;
//         for (int i = 1; i < n; i++) {
//             h[i] = h[i - 1] * key + s[i];
//             pow_key[i] = pow_key[i - 1] * key;
//         }
//     }
//     unsigned long long get(int l, int r) {
//         if (l == 0) {
//             return h[r];
//         }
//         return h[r] - h[l - 1] * pow_key[r - l + 1];
//     }
// } h1, h2;
// int solve(string A, string B, int n) {
//     for (int i = 0; i < n; i++) {
//         s1[i * 2] = A[i];
//         s2[n * 2 - i * 2 - 2] = B[i];
//     }
//     n = n * 2 - 1;
//     manacher(s1, n, len1);
//     manacher(s2, n, len2);
//     h1.init(s1, n);
//     h2.init(s2, n);
//     int ans = 0;
//     for (int i = 0; i < n; i++) {
//         int left_side1 = i - len1[i] / 2;
//         int right_side1 = i + len1[i] / 2;
//         int left_side2 = n + 1 - right_side1;
//         int lower = 0, upper = min(left_side1, left_side2);
//         while (lower < upper) {
//             int mid = (lower + upper + 1) / 2;
//             if (h1.get(left_side1 - mid, left_side1 - 1) == h2.get(left_side2 - mid, left_side2 - 1)) {
//                 lower = mid;
//             } else {
//                 upper = mid - 1;
//             }
//         }
//         int total = lower * 2 + len1[i];
//         if (i % 2 == 1) {
//             ans = max(ans, (total + 1) / 4 * 2);
//         } else {
//             ans = max(ans, total / 4 * 2 + 1);
//         }
//     }
//     return ans;
// }
// int main() {
//     int n;
//     string A, B;
//     cin >> n >> A >> B;
//     string C = B, D = A;
//     reverse(C.begin(), C.end());
//     reverse(D.begin(), D.end());
//     cout << max(solve(A, B, n), solve(C, D, n)) << endl;
//     return 0;
// }